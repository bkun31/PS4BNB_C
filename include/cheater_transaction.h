#ifndef CHEATER_TRANSACTION_H #define CHEATER_TRANSACTION_H /* ------------ Déclaration Type : ------------ /

typedef struct cheater;

/ ------------ Déclaration Constructeur : ------------ /


/ ------------ Déclaration Opérateur : ------------ */ 
/*
 * @brief parcourt la liste doublement chainée jusqu'à trouver la transaction et le bloc saisis 
 * @param numTx numéro de la transaction à supprimer 
 * @param *bc adresse de la blockchain où on va supprimer le bloc 
 * @param index Numéro du bloc
 * @return suppression du bloc 
*/

void cheaterSuppressionTx(int numTx, int index, blockchain *bc);

 
/* @brief modifie le numero des transactions afin de ne laisser aucune trace *
 
 * @param int index l'index qu'on va incrémenter de 1 à chaque fois à partir du dernier bloc 
 * @return 
 */ 
int transactionIndex(int index);

/*
 * @brief recalcule les merkle root 
 * 
 * @param hash Hash du merkle root à partir de laquelle on modifiera les hashs suivants 
 * @return 
*/

char cheaterMerkleRootTx(char hash[SHA256_BLOCK_SIZE2+1]); 

/* @brief recalcule les hash suivants
  *
  * @param hash Hash de la transaction à partir de laquelle on modifiera les hashs suivants
  * @return
*/

char cheaterRecalculTx(char hash[SHA256_BLOCK_SIZE2+1]); #endif
