#ifndef CHEATER_BLOCK_H 
#define CHEATER_BLOCK_H 
/* ------------ Déclaration Type : ------------ /

/ ------------ Déclaration Constructeur : ------------ /


/ ------------ Déclaration Opérateur : ------------ */ 
/*
 * @brief parcourt la liste doublement chainée jusqu'à trouver le bloc ayant l'index correspondant puis le supprime 
 * puisque c'est une liste doublement chainee chaque bloc contient l'adnt etresse du bloc suivant et celle du bloc precedent
 * @param *bc adresse de la blockchain où on va supprimer le bloc 
 * @param index Numéro du bloc
 * @return 
*/

void cheaterSuppressionBloc(int index, blockchain *bc);

 
/* @brief modifie l'index et l'adresse des blocs suivants une fois le bloc saisi supprimé afin de ne laisser aucune trace 
  *
  * @param block *pblk adresse du bloc suivant contenue dans le bloc n+1 que l'on va ajouter au nouveau bloc n 
  * @param int index l'index qu'on va incrémenter de 1 à chaque fois à partir du dernier bloc 
  * @return */
  
int cheaterAdresseIndex(block *pblk, int index);
/*
  * 
  * @brief recalcule les hash des blocs suivants * 
  * @param hash Hash du bloc courant de n-1 (hash du bloc precedent) à partir duquel on modifiera les hashs suivants 
  * @return */

char[] cheaterRecalcul(char hash[SHA256_BLOCK_SIZE2+1]);

#endif
