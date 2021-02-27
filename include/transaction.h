/**
 * @file transaction.h
 * @author Bilel, Cedric
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * 
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../include/user.h"
#include "sha256.h"

/* ------------ Déclaration Type : ------------ */

//typedef struct transaction transaction;

/* ------------ Déclaration Constructeur : ------------ */

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Génère une transaction sous forme de chaine de caractère.
 * 
 * @param usern Utilisateur source
 * @param userm Utilisatuer destiniation
 * @param amt Montant de la transaction 
 * @param str Adresse qui va recevoir la chaine de caractère de la transaction
 */
void genTx(user *usern, user *userm, int amt, char *str);

/**
 * @brief Calcul l'arbre de merkel d'une liste de transaction.
 * 
 * @param pTx Tableau de pointeur de transaction
 * @param nb Nombre de transactions dans le tableau pTx.
 * @param hash Chaîne de caractère qui va contenir la racine de l'arbre (Merkle tree root)
 */
void genMth(void **pTx, int nb, char hash[SHA256_BLOCK_SIZE * 2 + 1]);

/**
 * @brief Fait la conversion BNB en satoBnb ou inversement (1 Bnb = 10^8 satoBnb).
 * 
 * @param amt Montant à convertir
 * @param mode mode == 0 --> Conversion Bnb en satoBnb \n mode == 1 --> Conversion satoBnb en Bnb
 * @return Retourne l'entier convertit selon le mode choisi.
 */
long int cvrtBnb(int amt, int mode);

#endif