/**
 * @file block.h
 * @author Bilel, Cedric
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * 
 */

#ifndef BLOCK_H
#define BLOCK_H

#include "sha256.h"

/* ------------ Déclaration Type : ------------ */

typedef struct block block;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Initialise le bloc pointé par pblk.
 * 
 * @param pblk Adresse du bloc à initialiser
 * @param hash Hash du bloc précédent
 * @param index Numéro du bloc
 * @param ppTx Adresse de la liste de transactions
 */
void initBlock(block *pblk, char hash[SHA256_BLOCK_SIZE*2+1], int index, char **ppTx);


/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Recupère le hash du bloc blk.
 * 
 * @param blk Bloc dont il faut récupérer le hash
 * @param hash Chaîne de 32 caractères qui va contenir le hash
 * @return Le hash du bloc blk
 */
void getHash(const block blk, char hash[SHA256_BLOCK_SIZE*2+1]);

/**
 * @brief Récupère le hash code du merkle tree root contenu dans le bloc blk.
 * 
 * @param blk Bloc dont il faut récupérer le hash code merkle tree root
 * @param hash Chaîne de 32 caractères qui va contenir le hash
 */
void getMth(const block blk, char hash[SHA256_BLOCK_SIZE*2+1]);

/**
 * @brief Mine le bloc pointé par pblk en lui générant son hash conforme à la difficulté dp.
 * 
 * @param pblk adresse du bloc
 * @param dp diffculté du programme
 */
void mineblk(block *pblk, int dp);




#endif