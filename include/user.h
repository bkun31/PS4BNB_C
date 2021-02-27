/**
 * @file user.h
 * @author Bilel, Cedric
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * 
 */

#ifndef USER_H
#define USER_H

/* ------------ Déclaration Type : ------------ */

typedef struct user user;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Initialise l'utilisateur pointé par usr.
 * 
 * @param usr Adresse de l'utilisateur à initialiser
 * @param nm Nom de l'utilisateur
 */
void initUser(user *usr, char * nm);


/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Renvoie le nom de l'utilisateur.
 * 
 * @param usr Utilisateur dont on veut récupérer le nom
 * @param str Chaîne de caractère qui va contenir le nom de l'utilisateur
 */
void getName(const user usr, char *str);

/**
 * @brief Renvoie la somme de bnb que possède l'utilisateur ur
 * 
 * @param usr Utilisateur dont on veut récupérer la somme d'argent qu'il possède.
 */
void getWallet(const user usr);

/**
 * @brief ajoute l'argent de l'utilisateur
 * 
 * @param usr utilisateur
 * @param amt montant à ajouter
 */
void add(user usr, int amt);

/**
 * @brief soustrait l'argent de l'utilisateur
 * 
 * @param usr utilisateur
 * @param nb montant à enlever
 */
void sub(user usr, int amt);

#endif