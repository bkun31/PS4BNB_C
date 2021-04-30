#ifndef CHEATER_H
#define CHEATER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../include/skiplist.h"
#include "../include/blockchain.h"

/// Iterator from the begining to the end
#define CHEATER_BLOCK 0
/// Iterator from the end to the beginning
#define CHEATER_TRANSACTION 1

/**
 * @brief Supprime un bloc. \n
 * 
 * @param blockchain 
 * @param indexBloc index du bloc à supprimer 
 * @return un booléen qui indique si le bloc a été supprimé.
 */
bool cheater_deleteBlock(SkipList blockchain, unsigned int indexBloc);


/**
 * @brief Recalcule le hash et l'index des blocs suivants celui qui a été supprimé. \n
 * 
 * @param blockchain 
 * @param indexBloc index du bloc où a eu lieu l'opération de suppression
 * @param cheaterType type de cheater : CHEATER_BLOCK ou CHEATER_TRANSACTION
 * @return temps d'execution du programme en millisecondes
 */
int cheater_recalcul(SkipList blockchain, unsigned int indexBloc, unsigned int cheaterType); 


/**
 * @brief Supprime une transaction + recalcul merkle tree. \n
 * 
 * @param blockchain 
 * @param indexBloc index du bloc où se situe la transaction
 * @param indexTransaction l'index de la transaction à supprimer au sein de la liste de transactions
 * @return un booléen qui indique si la transaction a été supprimée.
 */
bool cheater_deleteTransaction(SkipList blockchain, unsigned int indexBloc, int indexTransaction);




#endif 
