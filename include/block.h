/**
 * @file block.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @defgroup Block Type abstrait Bloc
 * @brief Définition du type Block et de ses opérateurs
 * @version 0.2
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * @{
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "sha256.h"
#include "../include/skiplist.h"

#define AUCUNE_ERREUR 0
#define ERREUR_ALLOCATION_BLOCk 1

/* ------------ Déclaration Type : ------------ */

/**
 * @brief Définition du type abstrait de donnée Block.
 * 
 */
typedef struct s_Block *Block;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Construit un bloc.
 * 
 * @param index Numéro du bloc.
 * @param transactions Liste de transactions à mettre dans le bloc.
 * @param merkle_tree Arbre de merkle de la liste des transactions.
 * @param previous_hash Hash du bloc précédent (bloc d'indice index - 1).
 * @return Un bloc correctement crée sans minage.
 */
Block block_create(unsigned int index, SkipList transactions, char merkle_tree[SHA256_BLOCK_SIZE * 2 + 1], char previous_hash[SHA256_BLOCK_SIZE * 2 + 1]);

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Récupère l´indice du bloc blk.
 * 
 * @param blk Bloc.
 * @return unsigned int L´indice du bloc.
 */
unsigned int block_index(const Block blk);

/**
 * @brief Récupère la nonce du bloc blk.
 * 
 * @param blk Bloc.
 * @return unsigned int La nonce du bloc.
 */
unsigned int block_nonce(const Block blk);

/**
 * @brief Recupère le hash du bloc blk.
 * 
 * @param blk Bloc dont il faut récupérer le hash.
 * @return char* Le hash du bloc blk d´une taille de 65 octets (caractère de fin de chaîne inclus).
 */
const char *block_hash(const Block blk);

/**
 * @brief Recupère le hash du bloc précédent de blk.
 * 
 * @param blk Bloc dont il faut récupérer le hash de son précédent.
 * @return char* Le hash du bloc précédent blk d´une taille de 65 octets (caractère de fin de chaîne inclus).
 */
const char *block_prevhash(const Block blk);

/**
 * @brief Récupère l'arbre de merkle de la liste de transactions contenue dans le bloc blk.
 * 
 * @param blk Bloc de transactions dont il faut récupérer l'arbre de merkle.
 * @return char* L'arbre de merkle de la liste des transaction du bloc blk d´une taille de 65 octets (caractère de fin de chaîne inclus).
 */
const char *block_merkle_tree(const Block blk);

/**
 * @brief Récupère la liste des transactions contenue dans le bloc blk.
 * 
 * @param blk Bloc de transactions.
 * @return SkipList* La liste des transactions contenue dans le bloc blk.
 */
SkipList block_transactions(const Block blk);

/**
 * @brief Récupère la date de création du bloc en nombre de secondes écoulées depuis le 01/01/1970 à 00:00:00 UTC jusqu´à la création du bloc.
 * 
 * @param blk Bloc dont il faut récupérer la date de création du bloc.
 * @return time_t Nombre de secondes écoulées depuis le 01/01/1970 à 00:00:00 UTC jusqu´à la création du bloc .
 */
time_t block_timestamp(const Block blk);

/**
 * @brief Renvoie le nombre de transactions du bloc blk.
 * 
 * @param blk Bloc de transactions.
 * @return unsigned int Nombre de transactions contenue dans le bloc blk.
 */
unsigned int block_tx_count(const Block blk);

/**
 * @brief Calcule le hash du bloc blk.
 * 
 * @param blk Bloc à calculer.
 * @param hash Chaîne de caractères d´une taille de 65 octets (caractère de fin de chaîne inclus) qui va contenir le hash.
 * @return char* Le pointeur vers la chaîne de caractères hash du bloc correspondant à son contenu.
 */
char *calculate_hash_block(Block blk, char hash[SHA256_BLOCK_SIZE*2+1]);

/**
 * @brief Algorithme de consensus. \n
 * Calcul le hash du bloc pour qu´elle commence par un nombre de difficulty zéros,
 * en incrémentant la nonce jusqu´à satisfaire la condition.
 * 
 * @param blk Bloc.
 * @param difficulty Difficulté de minage.
 * @return true Si le block a correctement était miné.
 */
bool proof_of_work(Block blk, unsigned int difficulty);

/**
 * @brief Imprime dans le fichier f, le contenu du bloc blk. \n
 * Les informations imprimé sont dans l´ordre suivant : \n
 * - l´index du bloc \n
 * - le timestamp du bloc en seconde écoulée depuis le 01-01-1970 à 00:00:00 \n
 * - le Hash du bloc \n
 * - le Hash de son bloc prédécesseur \n
 * - la nonce du bloc \n
 * - le hash de la donnée (Merkle Tree Hash Root) \n
 * - la taille de la donnée contenue dans le bloc \n
 * - la donnée contenue dans le bloc \n
 * À besoin pour fonctionner d´une fonction d qui va imprimer les données du bloc dans le fichier f.
 * 
 * @param f Fichier de sortie.
 * @param blk Bloc à imprimer.
 */
void block_dump(FILE *f, const Block blk);

/** @} */

/** @} */

#endif