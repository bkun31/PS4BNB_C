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
#include <time.h>    // time()
#include <string.h>
#include "../include/transaction.h"
#include "../include/user.h"
#include "../include/queue.h"
#include "../include/skiplist.h"
#include "../include/sha256.h"
#include "../include/sha256_utils.h"

/* ------------------------------------------------------- */
/* Opérateur */

Transaction generate_transaction(User user_source, User user_destination)
{
	/*on doit préparer le format de la transaction qui est : 
	 *"Source usern-Destination : userm montant_transaction"
	 *on doit générer un nombre aléatoire qui sera le montant (inférieur à MAX_VALUE et au user.wallet)
	 */
	long montantMaximal;
	if (MAX_VALUE < user_source->wallet) //pour choisir un nombre qui dépasse pas le wallet ni le max value 
	{
		montantMaximal = MAX_VALUE; 
	}
	else 
	{
		montantMaximal = user_source->wallet;
	}

	//fonction qui génère un nombre aléatoire 
	long montantAleatoire=rand()%montantMaximal+1; //génère un nombre entre 1 et MAX_VALUE ou user_source.wallet

	char buffer[1024];
	sprintf(buffer, "Source %s-Destination : %s %ld", user_source->name, user_destination->name, montantAleatoire);

	Transaction transaction = strAlloc(buffer, 100);
	return transaction;
}

SkipList construct_transaction_list(Queue * transactions_queue)
{
	/*On vérifie si MAX_TRANSACTIONS est inférieur au nombre d'éléments de la file (besoin de connaître la taille de la file)
	 * (besoin d'accéder à la file pour récupérer les transacitons, normalement avec pop)
	 * SI OUI : on pop un nombre aléatoire de transactions
	 * (besoin de générer un nombre aléatoire)
	 * SI NON : on prend toutes les transactions restantes
	 */
	 SkipList transactions_list = skiplist_create(4);

	 if (MAX_TRANSACTIONS < queueSize(transactions_queue))
	 {
		 int nbAleatoireTransactions=rand()%10+1; //génère un nombre aléatoire de transactions avec 10 la constante
		 for (int i=0; i<nbAleatoireTransactions; i++)
		 {
			 Transaction transaction=strAlloc(queuePop(transactions_queue), 100);
			 skiplist_insert(transactions_list, i, transaction);
		 }
     }
     else 
     {
		 while (queueSize(transactions_queue) > 0) 
		 {
			 Transaction transaction=strAlloc(queuePop(transactions_queue), 100);
			 skiplist_insert(transactions_list, queueSize(transactions_queue), transaction);
		 }
	 }	 
	 return transactions_list;
}

void skiplist_to_queue(void *transaction, void *queue)
{
	queuePush((Queue *)queue, (Transaction *)transaction);
}

char *calculate_merkleTree(SkipList transactions_list, char merkleRoot[SHA256_BLOCK_SIZE * 2 + 1])
{
	Queue * transactions_queue = createQueue();
	Queue * merkleTree = createQueue();
	Queue * merkleTreeTemp = createQueue();

	skiplist_map(transactions_list, skiplist_to_queue, transactions_queue);
	while (queueEmpty(transactions_queue) == false)
	{
		char hashNode[SHA256_BLOCK_SIZE * 2 + 1];
		sha256ofString((BYTE *)queuePop(transactions_queue), hashNode);
		
		queuePush(merkleTree, strAlloc(hashNode, SHA256_BLOCK_SIZE * 2 + 1));
	}

	//On dépile les éléments 2 à 2, on les concatène et on stock le résultat de leur hash dans une nouvelle pile.
	//On répète l'opération jusqu'à ce que la MerkleTree ne contienne plus qu'un seul élement (le MerkleRoot)
	while (queueSize(merkleTree) != 1)
	{
		char * hash1;
		char * hash2;
		char hash12[SHA256_BLOCK_SIZE * 2 + 1];
		char concatHash12[2* (SHA256_BLOCK_SIZE * 2 + 1)];

		//Si la MerkeTree contient un nombre impair de noeuds, on duplique le noeud en tête de file.
		if (queueSize(merkleTree) %2 != 0)
		{
			queuePush(merkleTree, strAlloc(queueTop(merkleTree), SHA256_BLOCK_SIZE * 2 + 1));
		}

		while (queueEmpty(merkleTree) == false)
		{	
			hash1 = (char *) queuePop(merkleTree);
			hash2 = (char *) queuePop(merkleTree);

			strcpy(concatHash12, hash1);
			strcat(concatHash12, hash2);

			sha256ofString((BYTE *)concatHash12, hash12);
			queuePush(merkleTreeTemp, strAlloc(hash12, SHA256_BLOCK_SIZE * 2 + 1));

			free(hash1);
			free(hash2);
		}

		deleteQueue(&merkleTree);
		merkleTree = merkleTreeTemp;
		merkleTreeTemp = createQueue();
	}

	strcpy (merkleRoot , queuePop(merkleTree));

	deleteQueue(&merkleTreeTemp);
	deleteQueue(&merkleTree);
	deleteQueue(&transactions_queue);

	return merkleRoot;
}

void print_transaction(FILE *f, Transaction tx)
{
    (void)f;
    (void)tx;
}

char * strAlloc(char * strToCopy, int stringLen)
{
	char * str = malloc(sizeof(char)*(stringLen));
	strcpy(str, strToCopy);
	return str;
}

/* ------------------------------------------------------- */
