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
};

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

Blockchain blockchain_create(int dp)
{
    Blockchain bc;
    (void)dp;
    return bc;
}

Blockchain next_block_create(Blockchain bc, SkipList list_transaction)
{
    (void)list_transaction;
    return bc;
}

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

unsigned int blockchain_size(const Blockchain bc)
{
    (void)bc;
    return 0;
}

bool is_valid_genesis(const Blockchain bc)
{
    (void)bc;
    return true;
}


bool is_valid_block(const Blockchain bc, unsigned int index)
{
    (void)bc;
    (void)index;
    return true;
}


bool is_valid_chain(const Blockchain bc)
{
    (void)bc;
    return true;
}

bool is_valid_block_merkleTree(const Blockchain bc, unsigned int index)
{
    (void)bc;
    (void)index;
    return true;
}

bool is_valid_chain_merkleTree(const Blockchain bc)
{
    (void)bc;
    return true;
}

void block_contents(FILE *f, Blockchain bc, unsigned int index)
{
    (void)f;
    (void)bc;
    (void)index;
}

void blockchain_dump(FILE *f, Blockchain bc)
{
    (void)f;
    (void)bc;
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