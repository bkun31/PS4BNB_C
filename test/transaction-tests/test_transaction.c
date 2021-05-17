/**
 * @file test_transaction.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Jeu de tests module Transaction.
 * @version 0.1
 * @date 2021-04-18
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/transaction.h"
#include "../../include/user.h"
#include "../../include/queue.h"

/* permet de libérer une transaction */
void free_transaction(void *transaction)
{
    free((Transaction)transaction);
}

int main()
{
    srand(time(NULL));

    User usr0 = user_create(0);
    User usr5 = user_create(5);

    usr0 = user_add_money(usr0, 50000);
    usr5 = user_add_money(usr5, 20000);

    /** generate_transaction **/

    Queue *transactions_queue = createQueue();

    // char * transaction = generate_transaction(usr0, usr5);
    // char * transaction2 = generate_transaction(usr0, usr5);
    // char * transaction3 = generate_transaction(usr0, usr5);

    queuePush(transactions_queue, generate_transaction(usr0, usr5, 657927520042));
    queuePush(transactions_queue, generate_transaction(usr0, usr5, 42761054842));
    queuePush(transactions_queue, generate_transaction(usr0, usr5, 1438479734682));
    queuePush(transactions_queue, generate_transaction(usr0, usr5, 378263188364));
    queuePush(transactions_queue, generate_transaction(usr0, usr5, 3729192734743));

    SkipList transactions_list = construct_transaction_list(transactions_queue);

    char merkleRoot[SHA256_BLOCK_SIZE * 2 + 1];

    calculate_merkleTree(transactions_list, merkleRoot);

    int long_hash = strlen(merkleRoot); // sa longueur en caractères hexadécimaux
    printf("Le sha : %s avec %d caractères hexadécimaux, soit %d octets comme prévu\n", merkleRoot, long_hash, long_hash / 2);

    //FILE *fp = fopen("transaction_queue_dump.txt","w");

    deleteQueue(&transactions_queue);
    skiplist_delete(transactions_list, free_transaction); /* on libère la liste et les transactions */
    user_delete(&usr0);
    user_delete(&usr5);

    return 0;
}
