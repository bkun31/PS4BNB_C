/**
 * @file test_cheaters.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Tests cheaters
 * @version 0.1
 * @date 2021-05-17
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include <string.h>
#include "../../include/cheaters.h"
#include "../../include/block.h"
#include "../../include/transaction.h"
#include "../../include/blockchain.h"

/* permet de libérer une transaction */
void free_transactions(void *transaction)
{
    free((Transaction)transaction);
}

int main()
{
    Blockchain bchain = blockchain_create(4); /* on crée la blockchain et le bloc génésis */
    SkipList tx_list_index1 = skiplist_create(1);
    SkipList tx_list_index2 = skiplist_create(1);
    User user1 = user_create(1), user2 = user_create(2);

    /* on ajoute un bloc dans la blockchain */
    tx_list_index1 = skiplist_insert(tx_list_index1, 0, generate_transaction(user1, user2, 534759375248));
    tx_list_index1 = skiplist_insert(tx_list_index1, 1, generate_transaction(user2, user1, 208572985408));
    next_block_create(bchain, tx_list_index1);

    /* on ajoute un second bloc dans la blockchain */
    tx_list_index2 = skiplist_insert(tx_list_index2, 0, generate_transaction(user2, user2, 10000000000));
    tx_list_index2 = skiplist_insert(tx_list_index2, 1, generate_transaction(user1, user1, 40000000000));
    tx_list_index2 = skiplist_insert(tx_list_index2, 2, generate_transaction(user1, user2, 98220000000));
    tx_list_index2 = skiplist_insert(tx_list_index2, 3, generate_transaction(user2, user1, 34758390000));
    next_block_create(bchain, tx_list_index2);

    /* on affiche la blockchain sur la sortie standard avant d'activer les cheaters */
    puts("\n---------- Blockchain before enabled of the cheater ----------\n");
    blockchain_dump(stdout, bchain);

    /* on active le cheater de transactions sur le deuxième bloc pour la premiere transaction */
    cheater_deleteTransaction(bchain, 1, 0);
    if (is_valid_chain_merkleTree(bchain) && is_valid_chain(bchain))
        puts("\nUnaltered blockchain ! successful transaction deletion  !\n");
    else
        puts("\nAltered blockchain ! failure to delete transaction without alteration !\n");
    puts("\n---------- Blockchain after enabled of the transaction cheater (Block index 1, first transaction) ----------\n");
    blockchain_dump(stdout, bchain);

    /* on active le cheater de bloc sur le deuxième bloc */
    cheater_deleteBlock(bchain, 1);
    if (is_valid_chain_merkleTree(bchain) && is_valid_chain(bchain))
        puts("\nUnaltered blockchain ! successful block deletion  !\n");
    else
        puts("\nAltered blockchain ! failure to delete block without alteration !\n");
    puts("\n---------- Blockchain after enabled of the block cheater (Block index 1) ----------\n");
    blockchain_dump(stdout, bchain);

    /* on active le cheater de transactions sur le troisième bloc (qui est devenue le deuxième si tout c'est bien passé) pour la troisième transaction */
    cheater_deleteTransaction(bchain, 1, 2);
    if (is_valid_chain_merkleTree(bchain) && is_valid_chain(bchain))
        puts("\nUnaltered blockchain ! successful transaction deletion  !\n");
    else
        puts("\nAltered blockchain ! failure to delete transaction without alteration !\n");
    puts("\n---------- Blockchain after enabled of the transaction cheater (Block index 1, third transaction) ----------\n");
    blockchain_dump(stdout, bchain);

    /* on active le cheater de bloc sur le troisième bloc */
    cheater_deleteBlock(bchain, 1);
    if (is_valid_chain_merkleTree(bchain) && is_valid_chain(bchain))
        puts("\nUnaltered blockchain ! successful block deletion  !\n");
    else
        puts("\nAltered blockchain ! failure to delete block without alteration !\n");
    puts("\n---------- Blockchain after enabled of the block cheater (Block index 1) ----------\n");

    /* la blockchain ne devrait à present ne contenir que le block genésis */
    blockchain_dump(stdout, bchain);

    /* on libère le tout */
    skiplist_delete(tx_list_index1, free_transactions);
    skiplist_delete(tx_list_index2, free_transactions);
    skiplist_delete(bchain->b_list, NULL);
    user_delete(&user1);
    user_delete(&user2);
    
    free(bchain);

    return 0;
}