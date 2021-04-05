/**
 * @file transaction.c
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

#include <stdio.h>
#include <stdlib.h>
#include "../include/transaction.h"

/* ------------------------------------------------------- */
/* Opérateur */

Transaction generate_transaction(User user_source, User user_destination)
{
    Transaction tx;
    (void)user_source;
    (void)user_destination;
    return tx;
}

SkipList construct_transaction_list(Queue *transactions_queue)
{
    SkipList d;
    (void)transactions_queue;
    return d;
}


void calculate_merkleTree(SkipList transactions_list, char hash[SHA256_BLOCK_SIZE * 2 + 1])
{
    (void)transactions_list;
    (void)hash;
}


void print_transaction(FILE *f, Transaction tx)
{
    (void)f;
    (void)tx;
}

/* ------------------------------------------------------- */