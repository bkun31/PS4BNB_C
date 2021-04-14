/**
 * @file test_user.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Jeu de tests module User.
 * @version 0.1
 * @date 2021-04-13
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include "../../include/user.h"

int main()
{
    User usr0 = user_create(0);
    User usr5 = user_create(5);

    printf("Name usr0 : %s\n"
           "Wallet usr0 : %ld\n"
           "Name usr5 : %s\n"
           "Wallet usr5 : %ld\n\n\n",
           user_name(usr0),
           user_wallet(usr0),
           user_name(usr5),
           user_wallet(usr5));

    usr0 = user_add_money(usr0, 50000);
    usr0 = user_sub_money(usr0, 20000);
    usr5 = user_add_money(usr5, 20000);

    printf("Name usr0 : %s\n"
           "Wallet usr0 : %ld\n"
           "Name usr5 : %s\n"
           "Wallet usr5 : %ld\n",
           user_name(usr0),
           user_wallet(usr0),
           user_name(usr5),
           user_wallet(usr5));

    user_delete(&usr0);
    user_delete(&usr5);

    return 0;
}