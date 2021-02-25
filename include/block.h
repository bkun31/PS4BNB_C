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

typedef struct bloc bloc;

/**
 * @brief creer un bloc
 * 
 * @param hash hash du bloc précédent
 * @param pbloc pointeur qui va recevoir l'adresse du bloc creer
 * @param index numéro du bloc
 */
void creerBloc(char hash[SHA256_BLOCK_SIZE*2+1], void *pbloc, int index);

/**
 * @brief recupère le hash du bloc b
 * 
 * @param b bloc
 * @return le hash du bloc
 */
char hashBloc(bloc b);

#endif