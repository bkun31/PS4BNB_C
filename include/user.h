/**
 * @file user.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @defgroup User Type abstrait Utilisateur
 * @brief Définition du type User et de ses opérateurs
 * @version 0.2
 * @date 2021-02-25
 *
 * @copyright Domaine public 2021
 * @{
 */

#ifndef USER_H
#define USER_H

#include "bnb.h"

#define ERREUR_ALLOCATION_USER 1

#define USER_NAME_SIZE 8

/* ------------------------------------------------------- */
/* Implémentation structure user */

struct s_User
{
    char name[USER_NAME_SIZE];
    satoBnb wallet;
};

/* ------------ Déclaration Type : ------------ */

typedef struct s_User *User;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Crée l'utilisateur numéro user_num.
 *
 * @param user_num Numéro de l´utilisateur, si user_num = 0, l´utilisateur crée est "Créator", sinon l´utilisateur crée est "usern__user_num__".
 */
User user_create(unsigned int user_num);

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Renvoie le nom de l'utilisateur.
 *
 * @param user Utilisateur dont on veut récupérer le nom.
 */
const char *user_name(const User user);

/**
 * @brief Renvoie la somme de bnb que possède l'utilisateur user.
 *
 * @param user Utilisateur dont on veut récupérer la somme d'argent qu'il possède.
 */
satoBnb user_wallet(const User user);

/**
 * @brief Ajoute amount satoBnb au portefeuille de l´utilisateur.
 *
 * @param user Utilisateur.
 * @param amount Montant à ajouter.
 * @return L´utilisateur avec son portefeuille actualisé.
 */
User user_add_money(User user, satoBnb amount);

/**
 * @brief Soustrait amount satoBnb au portefeuille de l´utilisateur.
 * @pre Le montant du portefeuille de l´utilisateur doit être superieur au montant qu´on lui soustrait
 * @param user Utilisateur.
 * @param amount Montant à enlever.
 * @return L´utilisateur avec son portefeuille actualisé.
 */
User user_sub_money(User user, satoBnb amount);

/**
 * @brief Libère en mémoire et supprime l´utilisateur user.
 * 
 * @param user Utilisateur à supprimer.
 */
void user_delete(User *user);

/** @} */

/** @} */

#endif
