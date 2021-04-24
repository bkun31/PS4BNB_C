/**
 * @file test_config.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 2021-04-24
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include "../../include/config.h"
#include "../../include/bnb.h"

#define MAX_LIST_USER_SIZE config.max_users
#define MAX_TX_AMOUNT config.max_tx_amount
#define MAX_TX_IN_BLOCK config.max_tx_block
#define CHEATER_BLOCK config.cheater_block
#define CHEATER_TRANSACTION config.cheater_transaction
#define CHEATER_FREQUENCY config.cheater_ferquency
#define DIFFICULTY config.difficulty
#define REWARD config.reward
#define BNB_HALVING config.bnb_halving
#define MAX_BLOCK config.max_block

int main()
{
    conf config = conf_init();

    fprintf(stdout, "CONFIGURATION :\n"
                    "Difficulty : %d\n"
                    "Max block : %d\n"
                    "Number of users : %d\n"
                    "Initial Reward : %ld (%f Bnb)\n"
                    "Bnb halving : %d\n"
                    "Max transaction in block : %d\n"
                    "Max transaction amount : %ld (%f Bnb)\n"
                    "Cheater block enabled : %d\n"
                    "Cheater transaction enabled : %d\n"
                    "Cheater frequency : %f\n",
                    

            DIFFICULTY, MAX_BLOCK, MAX_LIST_USER_SIZE, REWARD, satobnb_to_bnb(REWARD), BNB_HALVING,
            MAX_TX_IN_BLOCK, MAX_TX_AMOUNT, satobnb_to_bnb(MAX_TX_AMOUNT), CHEATER_BLOCK,
            CHEATER_TRANSACTION, CHEATER_FREQUENCY);

    return 0;
}