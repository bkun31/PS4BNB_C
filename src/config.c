/**
 * @file config.c
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/config.h"

#define MAX_LENGHT_LINE 80

#define FILE_CONF "config.cfg"

#define MAX_USER "MAX_USER"
#define MAX_TX_AMOUNT "MAX_TX_AMOUNT"
#define MAX_TX_IN_BLOCK "MAX_TX_IN_BLOCK"
#define CHEATER_BLOCK "CHEATER_BLOCK"
#define CHEATER_TRANSACTION "CHEATER_TRANSACTION"
#define CHEATER_FREQUENCY "CHEATER_FREQUENCY"
#define DIFFICULTY "DIFFICULTY"
#define REWARD "REWARD"
#define BNB_HALVING "BNB_HALVING"
#define MAX_BLOCK "MAX_BLOCK"

bool read_conf_file(char *setting, char *setting_value)
{
    FILE *file = NULL;
    char line[MAX_LENGHT_LINE];
    bool find = false;
    size_t setting_len = strlen(setting);

    file = fopen(FILE_CONF, "r");
    if (!file)
    {
        perror("\nUNABLE TO OPEN CONFIG FILE\n");
        exit(1);
    }
    /* tant qu'on a pas trouvé la ligne recherché et tant qu´on est pas atteint la fin du fichier
    on va rechercher la ligne de la configuration désiré en paramatre "setting" */
    while (!find && fgets(line, sizeof(line), file))
    {
        if (line[0] != '#')
        {
            /* si la ligne n´est pas un commentaire, on la compare avec la ligne recherché "setting" */
            if (!strncmp(line, setting, setting_len))
            {
                /* si on a trouvé la ligne on récupère la valeur du paramètre */
                strcpy(setting_value, &line[setting_len + 1]);
                /* on supprime le caractère de retour à la ligne si il est présent */
                if (setting_value[strlen(setting_value) - 1] == '\n')
                {
                    setting_value[strlen(setting_value) - 1] = '\0';
                }
                find = true;
            }
        }
    }
    fclose(file);

    return find;
}

int conf_max_users(char *setting_value)
{
    int max_users = 10; /* valeur par défaut */
    if (read_conf_file(MAX_USER, setting_value))
    {
        max_users = atoi(setting_value) > 0 ? atoi(setting_value) : 10;
    }

    return max_users;
}

long conf_max_tx_amount(char *setting_value)
{
    long max_tx_amount = 2000000000; /* valeur par défaut */
    if (read_conf_file(MAX_TX_AMOUNT, setting_value))
    {
        max_tx_amount = atol(setting_value) >= 100000 ? atol(setting_value) : 2000000000;
    }

    return max_tx_amount;
}

int conf_max_tx_block(char *setting_value)
{
    int max_tx_block = 10; /* valeur par défaut */
    if (read_conf_file(MAX_TX_IN_BLOCK, setting_value))
    {
        max_tx_block = atoi(setting_value) >= 0 ? atoi(setting_value) : 10;
    }

    return max_tx_block;
}

int conf_enable_cheater_block(char *setting_value)
{
    int cheater_block = 0; /* valeur par défaut */
    if (read_conf_file(CHEATER_BLOCK, setting_value))
    {
        cheater_block = atoi(setting_value) > 0 ? 1 : 0;
    }

    return cheater_block;
}

int conf_enable_cheater_transaction(char *setting_value)
{
    int cheater_transaction = 0; /* valeur par défaut */
    if (read_conf_file(CHEATER_TRANSACTION, setting_value))
    {
        cheater_transaction = atoi(setting_value) > 0 ? 1 : 0;
    }

    return cheater_transaction;
}

float conf_cheater_frequency(char *setting_value)
{
    float cheater_frequency = 0.05; /* valeur par défaut */
    if (read_conf_file(CHEATER_FREQUENCY, setting_value))
    {
        cheater_frequency = atof(setting_value) >= 0 ? (float)atof(setting_value) : 0.05;
    }

    return cheater_frequency;
}

int conf_difficulty(char *setting_value)
{
    int difficulty = 3; /* valeur par défaut */
    if (read_conf_file(DIFFICULTY, setting_value))
    {
        difficulty = atoi(setting_value) >= 0 ? atoi(setting_value) : 3;
    }

    return difficulty;
}

long conf_reward(char *setting_value)
{
    long reward = 5000000000; /* valeur par défaut */
    if (read_conf_file(REWARD, setting_value))
    {
        reward = atol(setting_value) >= 100000 ? atol(setting_value) : 5000000000;
    }

    return reward;
}

int conf_bnb_halving(char *setting_value)
{
    int bnb_halving = 50; /* valeur par défaut */
    if (read_conf_file(BNB_HALVING, setting_value))
    {
        bnb_halving = atoi(setting_value) >= 1 ? atoi(setting_value) : 50;
    }

    return bnb_halving;
}

int conf_max_block(char *setting_value)
{
    int max_block = 100; /* valeur par défaut */
    if (read_conf_file(MAX_BLOCK, setting_value))
    {
        max_block = atoi(setting_value) >= 1 ? atoi(setting_value) : 100;
    }

    return max_block;
}

conf conf_init()
{
    char setting_value[MAX_LENGHT_LINE];
    conf config;

    config.bnb_halving = conf_bnb_halving(setting_value);
    config.difficulty = conf_difficulty(setting_value);
    config.reward = conf_reward(setting_value);
    config.max_block = conf_max_block(setting_value);
    config.max_tx_amount = conf_max_tx_amount(setting_value);
    config.max_tx_block = conf_max_tx_block(setting_value);
    config.max_users = conf_max_users(setting_value);
    config.cheater_ferquency = conf_cheater_frequency(setting_value);

    if (config.cheater_ferquency)
    {
        config.cheater_block = conf_enable_cheater_block(setting_value);
        config.cheater_transaction = conf_enable_cheater_transaction(setting_value);
    }
    else
    {
        config.cheater_block = 0;
        config.cheater_transaction = 0;
    }

    return config;
}