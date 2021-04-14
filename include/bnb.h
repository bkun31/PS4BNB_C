/**
 * @file bnb.h
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @defgroup Bnb Type abstrait Bonobo
 * @brief Définition du type "Bonobo" (Bnb) et de ses opérateurs 
 * @version 0.1
 * @date 2021-04-05
 * 
 * @copyright Domaine public 2021
 * @{
 */

#ifndef BNB_H
#define BNB_H

/* Macro de conversion de la crypto-devise Bnb */
#define CONVERT_BNB_TO_SATOBNB(amount) (amount * 100000000)
#define CONVERT_SATOBNB_TO_BNB(amount) (amount * 0.00000001)

/* ------------ Déclaration Type : ------------ */

/**
 * @brief Définition type Bnb.
 * 
 */
typedef double Bnb;

/**
 * @brief Définition type satoBnb. \n
 * 1 Bnb =  100,000,000 satoBnb.
 * 
 */
typedef unsigned long int satoBnb;

/* ------------ Déclaration Opérateur : ------------ */

/**
 * @brief Fait la conversion Bnb en satoBnb (1 Bnb = 10^8 satoBnb).
 * 
 * @param amount Montant à convertir.
 * @return Retourne la conversion en satoBnb.
 */
satoBnb bnb_to_satobnb(Bnb amount);

/**
 * @brief Fait la conversion satoBnb en Bnb (1 Bnb = 10^8 satoBnb).
 * 
 * @param amount Montant à convertir.
 * @return Retourne la conversion en Bnb.
 */
Bnb satobnb_to_bnb(satoBnb amount);

/** @} */

/** @} */

#endif