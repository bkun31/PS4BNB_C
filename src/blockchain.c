/**
 * @file blockchain.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief
 * @version 0.2
 * @date 2021-02-25
 *
 * @copyright Domaine public 2021
 *
 */

#include "../include/blockchain.h"
#include "../include/block.h"
#include "../include/skiplist.h"
#include "../include/transaction.h"

/* ------------------------------------------------------- */
/* Implémentation structure blockchain*/

struct s_Blockchain
{
  int dp; //difficulte
  int b_nb; //nombre de block de la chaine
  SkipList b_list; //liste de blocks
};

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

Blockchain blockchain_create(int dp)
{
    Blockchain blockchain;
    Block genesis = block_create(0, 0, "Génésis", NULL);//SizeOperator f ?

    blockchain->b_list = skiplist_create(4);//??
    skiplist_insert(blockchain->b_list, 0, &genesis);

    blockchain->b_nb = 1;
    blockchain->dp = dp;
    return blockchain;
}

Blockchain next_block_create(Blockchain bc, SkipList list_transaction)
{
    char hash_prev[SHA256_BLOCK_SIZE*2+1];
    block_hash(skiplist_ith(bc->b_list, bc->b_nb-1), hash_prev);

    skiplist_insert(bc->b_list, bc->b_nb, block_create(hash_prev, bc->b_nb, list_transaction, NULL));//SizeOperator f ?

    (bc->b_nb)++;
    return bc;
}

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

unsigned int blockchain_size(const Blockchain bc)
{
    return bc->b_nb;
}

bool is_valid_genesis(const Blockchain bc)
{
    Block genesis = skiplist_ith(bc->b_list, 0);

    char hash_prev[SHA256_BLOCK_SIZE*2+1];
    block_prevhash(genesis, hash_prev);

    //hash_c hash du genesis recalculé, hash_b hash du genesis enregistré
    char hash_c[SHA256_BLOCK_SIZE*2+1];
    calculate_hash_block(genesis, hash_c);
    char hash_b[SHA256_BLOCK_SIZE*2+1];
    block_hash(genesis, hash_b);

    return block_index(genesis) == 0 && hash_prev == 0 && hash_c == hash_b;
}


bool is_valid_block(const Blockchain bc, unsigned int index)
{
    Block blk = skiplist_ith(bc->b_list, index);
    Block blk_prev = skiplist_ith(bc->b_list, index-1);

    //prev block
    char hash_prev_saved[SHA256_BLOCK_SIZE*2+1];
    block_prevhash(blk, hash_prev_saved);
    char hash_prev_recalculated[SHA256_BLOCK_SIZE*2+1];
    calculate_hash_block(blk_prev, hash_prev_recalculated);

    //block
    char hash_saved[SHA256_BLOCK_SIZE*2+1];
    block_hash(blk, hash_saved);
    char hash_recalculated[SHA256_BLOCK_SIZE*2+1];
    calculate_hash_block(blk, hash_recalculated);

    return block_index(blk) == block_index(blk_prev) && hash_prev_saved == hash_prev_recalculated && hash_saved == hash_recalculated;
}


bool is_valid_chain(const Blockchain bc)
{
    int index = bc->b_nb;
    while (index > 0) {
        if (!is_valid_block(bc, index)) {
            return false;
        }
        index--;
    }
    return true;
}

bool is_valid_block_merkleTree(const Blockchain bc, unsigned int index)
{
    char hash_saved[SHA256_BLOCK_SIZE*2+1];
    block_merkleTree(skiplist_ith(bc->b_list, index), hash_saved);

    char hash_recalculated[SHA256_BLOCK_SIZE * 2 + 1];
    calculate_merkleTree(block_data(skiplist_ith(bc->b_list, index)), hash_recalculated);

    return hash_saved == hash_recalculated;
}

bool is_valid_chain_merkleTree(const Blockchain bc)
{
    int index = bc->b_nb;
    while (index > 0) {
        if (!is_valid_block_merkleTree(bc, index)) {
            return false;
        }
        index--;
    }
    return true;
}

void block_contents(FILE *f, Blockchain bc, unsigned int index)
{

    Block blk = skiplist_ith(bc->b_list, index);
    block_dump(f, blk, NULL); //DataDumpOperator d ?
}

void blockchain_dump(FILE *f, Blockchain bc)
{

    fprintf(f, "Difficulté = %d\n", bc->dp);
    fprintf(f, "Longueur = %d\n", bc->b_nb);
    int index = 0;
    while (index < bc->b_nb) {
        block_contents(f, bc, index);
        index++;
    }
}

/* Ces fonctions peuvent être utiles à voir,
   cependant, on ne peut pas les déclarer dans l´en tête,
   car ça compromettrai l´intégrité de la blockchain,
   si quelqu´un utilise les blocs retourné pour autre choses que prévu */

// /**
//  * @brief Renvoie le dernier bloc crée de la blockchain.
//  *
//  * @param bc Blockchain.
//  * @return Block Dernier bloc crée dans la blockchain bc.
//  */
// Block get_latest_block(Blockchain bc)
// {
//     Block blk;
//     (void)bc;
//     return blk;
// }

// /**
//  * @brief Renvoie le bloc d´indice index s´il est contenue dans la blockchain.
//  *
//  * @param bc Blockchain.
//  * @param index Index du bloc à récupérer
//  * @return Le Block d´indice index ou NULL si non présent.
//  */
// Block get_block(Blockchain bc, unsigned int index)
// {
//     Block blk;
//     (void)bc;
//     (void)index;
//     return blk;
// }

/* ------------------------------------------------------- */
