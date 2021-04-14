/**
 * @file test_bnb.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Jeu de tests module Bnb.
 * @version 0.1
 * @date 2021-04-13
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include "../../include/bnb.h"

#define EPSILON 0.00000001
#define AMOUNT_BNB 4.64538490
#define AMOUNT_SATO_BNB 139003910

double abs_value(double value)
{
    value = value >= 0 ? value : -value;
    return value;
}

int main()
{
    printf("Conversion de 4.64538490 Bnb en satoBnb\n");
    if (bnb_to_satobnb(AMOUNT_BNB) != 464538490)
    {
        printf("Erreur conversion Bnb vers satoBnb\n %ld != 464500000\n", bnb_to_satobnb(AMOUNT_BNB));
    }
    else
    {
        printf("%lf Bnb = %ld satoBnb \n", AMOUNT_BNB, bnb_to_satobnb(AMOUNT_BNB));
    }
    printf("\nConversion de %d satoBnb en Bnb\n", AMOUNT_SATO_BNB);
    if (abs_value(satobnb_to_bnb(AMOUNT_SATO_BNB) - 1.39003910) >= EPSILON)
    {
        printf("Erreur conversion satoBnb vers Bnb\n %lf != 1.39003910\n", satobnb_to_bnb(AMOUNT_SATO_BNB));
    }
    else
    {
        printf("%d satoBnb = %lf Bnb \n", AMOUNT_SATO_BNB, satobnb_to_bnb(AMOUNT_SATO_BNB));
    }

    return 0;
}