/**
 * @file blockchain.h
 * @author Bilel, Cedric
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * 
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../include/block.h"

/* ------------ Déclaration Type : ------------ */

typedef struct blockchain blockchain;


/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Initialise la blockchain bc.
 * 
 * @param bc Adresse de la blockchain à initialiser
 */
void initBlockchain(blockchain *bc);


/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Renvoie la taille de la blockchain bc.
 * 
 * @param bc Blockchain dont on veut connaitre la taille
 * @return le nombre de blocs dans la blockchain bc
 */
int sizeBlockchain(const blockchain bc);

/**
 * @brief Ajoute un bloc blk à la blockchain bc
 * 
 * @param bc Adresse de la blockchain dont on veut ajouter un bloc
 * @param blk Bloc à ajouter
 */
void pushBack(blockchain *bc, const block blk);

#endif