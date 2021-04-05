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
char *user_name(const User user);

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
 * @brief Fait miner un bloc à un utilisateur et lui donne une récompense si elle est non nul. \n
 * La fonction choisit aléatoirement un nombre de transactions dans la file transactions_queue dans l´intervalle [1, MAX_TRANSACTIONS],
 * si MAX_TRANSACTIONS est inferieur aux nombres de transaction contenue dans la file, sinon [1, queueSize(transactions_queue)]. \n
 * Les transactions sont ensuite mis dans une liste pour enfin créer et miner un nouveau bloc. \n
 * Recalcule la nouvelle récompense quand un certains de nombres de blocs ont étaient miné.
 * 
 * @param user Utilisateur qui va créer et miner le nouveau bloc.
 * @param transactions_queue File de transactions en attentes.
 * @param reward Récompense pour les mineurs en phase d´inflations
 * @return User Utilisateur ayant miné le bloc correctement.
 */
User mine(User user, Queue *transactions_queue, satoBnb reward);

/** @} */

/** @} */

#endif