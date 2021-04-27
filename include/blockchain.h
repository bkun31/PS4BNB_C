/**
 * @file blockchain.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @defgroup Blockchain Type abstrait Blockchain
 * @brief Définition du type Blockchain et ses opérateurs
 * @version 0.2
 * @date 2021-02-25
 *
 * @copyright Domaine public 2021
 * @{
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#define ERREUR_ALLOCATION_BLOCKCHAIN 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/block.h"
#include "../include/skiplist.h"

/* ------------ Déclaration Type : ------------ */

/**
 * @brief Définition du type abstrait de donnée Blockchain
 *
 */
typedef struct s_Blockchain *Blockchain;

/* ------------ Déclaration Constructeur : ------------ */

/**
 * @brief Crée la blockchain bc et son premier bloc gńeésis. \n
 * Le bloc génésis contient une unique donnée qui se restreint à la chaîne "Génésis",
 * le hash de son prédécésseur est 0 et sa nonce reste à 0.
 * @param difficulté pour le minage des blocs.
 * @return La blockchain correctement crée.
 */
Blockchain blockchain_create(int difficulty);

/**
 * @brief Crée le prochain bloc de la blockchain bc.
 *
 * @param bc Blockchain dont on veut créer le prochain bloc.
 * @param list_transaction Liste de transactions qui sera contenue dans le nouveau bloc.
 * @return La blockchain modifié avec un nouveau bloc.
 */
Blockchain next_block_create(Blockchain bc, SkipList list_transaction);

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Renvoie la taille de la blockchain bc.
 *
 * @param bc Blockchain dont on veut connaitre la taille.
 * @return le nombre de blocs dans la blockchain bc.
 */
unsigned int blockchain_size(const Blockchain bc);

/**
 * @brief Vérifie si le premier bloc est bien le bloc génésis. \n
 * L’index du bloc doit être égale à l’index + 1 de son pŕédécesseur. \n
 * le Hash précédent du bloc génésis, doit être 0 dans sa représentation ascii hexadécimal. \n
 * le hash du bloc est valide.
 *
 * @param bc Blockchain.
 * @return true Si le premier bloc est bien le bloc génésis.
 * @return false Si le premier bloc n´est pas le bloc génésis.
 */
bool is_valid_genesis(const Blockchain bc);

/**
 * @brief Vérifie que le bloc indexé par index est bien valide. \n
 * L’index du bloc doit être égale à l’index + 1 de son prédécesseur. \n
 * le Hash prédécesseur du bloc doit correspondre au hash de son prédécesseur. \n
 * le hash du bloc est valide.
 *
 * @param bc Blockchain.
 * @param index Indice du bloc à vérifier.
 * @return true Si le bloc est valide.
 * @return false Si le bloc n´est pas valide
 */
bool is_valid_block(const Blockchain bc, unsigned int index);

/**
 * @brief Vérifie que le chaînage des hashs est valide. \n
 * L’index de chaque bloc (sauf le bloc génésis) doit être égale à l’index + 1 de son prédécesseur. \n
 * le Hash précédent de chaque bloc doit correspondre au hash de leur prédécesseurs. \n
 * le hash de chaque bloc est valide.
 *
 * @param bc Blockchain.
 * @param index Indice du bloc à vérifier.
 * @return true Si le bloc est valide.
 * @return false Si le bloc n´est pas valide
 */
bool is_valid_chain(const Blockchain bc);

/**
 * @brief Vérifie que le Merkle Tree du bloc indexé dans la blockchain par index est valide et donc que les transactions n´ont pas étaient altéré.
 *
 * @param bc Blockhain
 * @param index indice du Bloc dont il faut vérifier le Merkle Tree.
 * @return true Si le hash Merkle Tree est correct (les transactions n´ont pas étaient altéré).
 * @return false Si le hash Merkle Tree est faux (les transactions ont étaient altéré).
 */
bool is_valid_block_merkleTree(const Blockchain bc, unsigned int index);

/**
 * @brief Vérifie que le Merkle Tree de chaque bloc contenu dans la blockchain est valide et donc que les transactions n´ont pas étaient altéré.
 *
 * @param bc Blockhain
 * @return true Si le hash Merkle Tree de tous les blocs sont correct (les transactions n´ont pas étaient altéré).
 * @return false Si le hash Merkle Tree d´au moins un bloc est faux (les transactions ont étaient altéré).
 */
bool is_valid_chain_merkleTree(const Blockchain bc);

/**
 * @brief Imprime dans le fichier f, le contenu du bloc indexé par index dans la blockchain bc. \n
 * Les informations retrouvé sont : \n
 * - l´index du bloc dans la blockchain \n
 * - le date de création du bloc au format type suivant Fri Jan 19 13 :40 :09 2018" \n
 * - le Hash du bloc \n
 * - le Hash de son bloc prédécesseur \n
 * - la nonce du bloc \n
 * - le hash de la liste des transactions (Merkle Tree Hash Root) \n
 * - la nombre de transactions contenue dans le bloc \n
 * - les transactions contenue dans le bloc \n
 *
 * @param f Fichier de sortie.
 * @param bc Blockchain.
 * @param index index du bloc à imprimer.
 */
void block_contents(FILE *f, Blockchain bc, unsigned int index);

/**
 * @brief Imprime en brut dans le fichier f, l´intégralité du contenu de la blockchain. \n
 * Imprime les informations de la blockchain (sa longueur, et sa difficulté),
 * ainsi que celle de tous les blocs qu´elle contient et leur données.
 *
 * @param f Fichier de sortie.
 * @param bc Blockchain à imprimer.
 */
void blockchain_dump(FILE *f, Blockchain bc);

/**
 * @brief Renvoie le dernier bloc crée de la blockchain.
 *
 * @param bc Blockchain.
 * @return Block Dernier bloc crée dans la blockchain bc.
 */
Block get_latest_block(Blockchain bc);

/**
 * @brief Renvoie le bloc d´indice index s´il est contenue dans la blockchain.
 *
 * @param bc Blockchain.
 * @param index Index du bloc à récupérer
 * @return Le Block d´indice index ou NULL si non présent.
 */
Block get_block(Blockchain bc, unsigned int index);

/**
 * @brief Renvoie la chaîne de blocs de la blockchain bc.
 *
 * @param bc Blockchain.
 * @return Liste doublement chaînée de bloc.
 */
SkipList get_chain(Blockchain bc);

/** @} */

/** @} */
#endif
