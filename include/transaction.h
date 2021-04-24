/**
 * @file transaction.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @defgroup Transaction Type abstrait Transaction
 * @brief Définition du type Trransaction et de ses opérateurs
 * @version 0.2
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * @{
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdio.h>
#include "user.h"
#include "skiplist.h"
#include "sha256.h"
#include "queue.h"

#define MAX_VALUE 1000000000 /* Montant max en satoBnb des transactions (10 Bnb) */
#define MAX_TRANSACTIONS 10  /* Nombre de transactions maximum dans une liste */

#define ERREUR_GENERATION_TRANSACTION 1
#define ERREUR_CALCUL_MERKLEROOT 2

/* ------------ Déclaration Type : ------------ */

/**
 * @brief Définition type Transaction.
 * 
 */
typedef char *Transaction;

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Génère une transaction sous forme de chaine de caractère. \n
 * Le format type de la transaction est le suivant : \n
 * "Source usern-Destination : userm montant_transaction Bnb" \n
 * où montant_transaction est un nombre aléatoire compris entre 1 et MAX_VALUE.
 * 
 * @param user_source Utilisateur source.
 * @param user_destination Utilisatuer destiniation.
 * @return char* Chaine de caractère de la transaction crée.
 */
Transaction generate_transaction(User user_source, User user_destination);

/**
 * @brief Génère une transaction de la phase helicopter money sous forme de chaine de caractère. \n
 * Le format type de la transaction est le suivant : \n
 * Coinbase envoie amount Bnb à user" \n
 * 
 * @param user Utilisateur.
 * @param amount Montant.
 * @return char* Chaine de caractère de la transaction crée.
 */
Transaction generate_helicopter_transaction(User user, satoBnb amount);


/**
 * @brief Construit une file  de transactions depuis la file globale transactions_queue,
 * en prenant aléatoirement un nombre de transactions entre 1 et MAX_TRANSACTIONS 10,
 * si MAX_TRANSACTIONS est inferieur au nombres de transactions dans la file,
 * sinon tous les l´éléments restants dans la file.
 * 
 * @param transactions_queue File de transactions en attente.
 * @return Queue 
 */
SkipList construct_transaction_list(Queue *transactions_queue);

/**
 * @brief Calcul l'arbre de merkel d'une liste de transaction.
 * 
 * @param transactions_list Liste des transactions.
 * @param hash Chaîne de caractères d´une taille de 65 octets, qui va contenir le hash code de list_transaction (Merkle Tree Root).
 */
char *calculate_merkleTree(SkipList transactions_list, char merkleRoot[SHA256_BLOCK_SIZE * 2 + 1]);

/**
 * @brief imprime sur le fichier f la transaction tx.
 * 
 * @param tx Transaction à afficher.
 */
void print_transaction(FILE *f, Transaction tx);

/** @} */

/** @} */

char * strAlloc(char * strToCopy, int stringLen);

#endif
