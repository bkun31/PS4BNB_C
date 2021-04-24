/**
 * @file config.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 2021-04-23
 * 
 * @copyright Domaine public 2021
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

/* ------------ Déclaration Type : ------------ */

typedef struct s_conf
{
    long reward;
    long max_tx_amount;
    float cheater_ferquency;
    int cheater_block;
    int cheater_transaction;
    int difficulty;
    int bnb_halving;
    int max_users;
    int max_block;
    int max_tx_block;
} conf;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Initialise les paramètres de configurations du programme.
 * 
 * @return Une structure contenant tous les paramètres du programme. 
 */
conf conf_init();

#endif