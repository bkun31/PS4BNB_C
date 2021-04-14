/**
 * @file bnb.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 2021-04-05
 * 
 * @copyright Domaine public 2021
 * 
 */

#include "../include/bnb.h"

/* ------------------------------------------------------- */
/* Opérateur */

satoBnb bnb_to_satobnb(Bnb amount)
{
    return CONVERT_BNB_TO_SATOBNB(amount);
}

Bnb satobnb_to_bnb(satoBnb amount)
{
    return CONVERT_SATOBNB_TO_BNB(amount);
}


/* ------------------------------------------------------- */