/**
 * @file user.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.2
 * @date 2021-02-25
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/queue.h"

/* ------------------------------------------------------- */
/* Implémentation structure blockchain*/

struct s_User
{
};

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

User user_create(unsigned int user_num)
{
    User user;
    (void)user_num;
    return user;
}

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

char *user_name(const User user)
{
    char *name;
    (void)user;
    return name;
}

satoBnb user_wallet(const User user)
{
    satoBnb money;
    (void)user;
    return money;
}


User user_add_money(User user, satoBnb amount)
{
    (void)amount;
    return user;
}


User user_sub_money(User user, satoBnb amount)
{
    (void)amount;
    return user;
}

User mine(User user, Queue *transactions_queue, satoBnb reward)
{
    (void)transactions_queue;
    (void)reward;
    return user;
}

/* ------------------------------------------------------- */