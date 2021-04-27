typedef int make_iso_compilers_happy;
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
#include <string.h>
#include "../include/blockchain.h"
#include "../include/block.h"
#include "../include/skiplist.h"
#include "../include/transaction.h"

#define MAX_LEVELS_SKIPLIST 5 /* on va prendre 5 pour commencer */

/* ------------------------------------------------------- */
/* Implémentation structure blockchain*/

struct s_Blockchain
{
    int dificulty;          //difficulte
    int b_nb;        //nombre de block de la chaine
    SkipList b_list; //liste de blocks
};

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

Blockchain blockchain_create(int dificulty)
{
    Blockchain blockchain = malloc(sizeof(struct s_Blockchain));

    /* on crée une liste de transaction avec une unique transaction à l´interieur
    se réduisant à la chaîne de caractère Génésis */
    SkipList genesis_tx = skiplist_create(1);
    skiplist_insert(genesis_tx, 0, "Génésis");

    Block genesis = block_create(0, genesis_tx, "\0");

    blockchain->b_list = skiplist_create(MAX_LEVELS_SKIPLIST);
    skiplist_insert(blockchain->b_list, 0, genesis);

    blockchain->b_nb = 1;
    blockchain->dificulty = dificulty;
    return blockchain;
}

Blockchain next_block_create(Blockchain bc, SkipList list_transaction)
{
    /* Création du hash du Merkle Tree de la liste des transactions */
    //char merkleTreeHash[SHA256_BLOCK_SIZE * 2 + 1];
    //printf("aa\n");
    //calculate_merkleTree(list_transaction, merkleTreeHash);

    /* Insertion du nouveau bloc dans la blockchain */
    Block blk = block_create(bc->b_nb, list_transaction, (char *) block_hash(skiplist_ith(bc->b_list, bc->b_nb - 1)));
    skiplist_insert(bc->b_list, bc->b_nb, blk);

    proof_of_work(blk, bc->dificulty);
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

    //hash_c hash du genesis recalculé
    char hash_c[SHA256_BLOCK_SIZE * 2 + 1];
    calculate_hash_block(genesis, hash_c);
    return block_index(genesis) == 0 && !strcmp(block_prevhash(genesis), "") && !strcmp(hash_c, block_hash(genesis));
}

bool is_valid_block(const Blockchain bc, unsigned int index)
{
    if (index==0) {
        return is_valid_genesis(bc);
    }
    else {
        Block blk = skiplist_ith(bc->b_list, index);
        Block blk_prev = skiplist_ith(bc->b_list, index - 1);

        char hash_recalculated[SHA256_BLOCK_SIZE * 2 + 1];
        calculate_hash_block(blk, hash_recalculated);

        return block_index(blk)-1 == block_index(blk_prev) && !strcmp(block_prevhash(blk), block_hash(blk_prev)) && !strcmp(block_hash(blk), hash_recalculated);
    }
}

bool is_valid_chain(const Blockchain bc)
{
    int index = bc->b_nb;
    while (index--)
    {
        if (!is_valid_block(bc, index))
        {
            return false;
        }
    }
    return true;
}

bool is_valid_block_merkleTree(const Blockchain bc, unsigned int index)
{
    Block block = skiplist_ith(bc->b_list, index);
    char hash_recalculated[SHA256_BLOCK_SIZE * 2 + 1];
    calculate_merkleTree(block_transactions(block), hash_recalculated);
    return !strcmp(block_merkle_tree(block), hash_recalculated);
}

bool is_valid_chain_merkleTree(const Blockchain bc)
{
    int index = bc->b_nb;
    while (index--)
    {
        if (!is_valid_block_merkleTree(bc, index))
        {
            return false;
        }
    }
    return true;
}

void block_contents(FILE *f, Blockchain bc, unsigned int index)
{

    Block blk = skiplist_ith(bc->b_list, index);
    block_dump(f, blk);
}

void blockchain_dump(FILE *f, Blockchain bc)
{
    printf("*******************************************************************************************\n");
	  printf("				***************\n");
		printf("				* DUMP BLOCk  *\n");
		printf("				***************\n");
    printf("*******************************************************************************************\n");

    fprintf(f, "\nDifficulté = %d\n", bc->dificulty);
    fprintf(f, "Longueur = %d\n", bc->b_nb);
    int index = 0;
    while (index < bc->b_nb)
    {
        block_contents(f, bc, index);
        index++;
    }
    printf("*******************************************************************************************\n");
}

Block get_latest_block(Blockchain bc)
{
    return skiplist_ith(bc->b_list, bc->b_nb - 1);
}

Block get_block(Blockchain bc, unsigned int index)
{
    return skiplist_ith(bc->b_list, index);
}

SkipList get_chain(Blockchain bc)
{
  return bc->b_list;
}






// /* ------------------------------------------------------- */
