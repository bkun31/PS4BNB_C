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
#include<time.h>
#include "../../include/transaction.h"
#include "../../include/user.h"
#include "../../include/queue.h"

int main()
{
    srand(time(NULL));

    User usr0 = user_create(0);
    User usr5 = user_create(5);

    usr0 = user_add_money(usr0, 50000);
    usr5 = user_add_money(usr5, 20000);

    /** generate_transaction **/

    Queue * transactions_queue = createQueue();

    char * transaction = generate_transaction(usr0, usr5);
    char * transaction2 = generate_transaction(usr0, usr5);
    char * transaction3 = generate_transaction(usr0, usr5);

    queuePush(transactions_queue, generate_transaction(usr0, usr5));
    queuePush(transactions_queue, generate_transaction(usr0, usr5));
    queuePush(transactions_queue, generate_transaction(usr0, usr5));
    queuePush(transactions_queue, generate_transaction(usr0, usr5));
    queuePush(transactions_queue, generate_transaction(usr0, usr5));

    Queue * transactions_list = construct_transaction_list(transactions_queue);

    char merkleRoot[SHA256_BLOCK_SIZE * 2 + 1];

    calculate_merkleTree(transactions_list, merkleRoot);

    printf(merkleRoot);

    //FILE *fp = fopen("transaction_queue_dump.txt","w");

    deleteQueue(&transactions_queue);
    deleteQueue(&transactions_list);
    user_delete(&usr0);
    user_delete(&usr5);

    return 0;
}
