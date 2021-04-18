//typedef int make_iso_compilers_happy;
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

#define USER_NAME_SIZE 8

char *name_create(char *user_name, unsigned int user_num);

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

User user_create(unsigned int user_num)
{
    User user = malloc(sizeof(struct s_User));
    if (user == NULL)
    {
        perror("\nALLOCATION USER ERROR\n");
        exit(ERREUR_ALLOCATION_USER);
    }
    name_create(user->name, user_num);
    user->wallet = 0;

    return user;
}
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

/* Crée le nom de l´utilisateur en fonction de son numéro */
char *name_create(char *user_name, unsigned int user_num)
{
    if (user_num)
    {
        sprintf(user_name, "user%d", user_num);
    }
    else
    {
        sprintf(user_name, "Creator");
    }

    return user_name;
}

const char *user_name(const User user)
{
    return user->name;
}

satoBnb user_wallet(const User user)
{
    return user->wallet;
}

User user_add_money(User user, satoBnb amount)
{
    user->wallet += amount;
    return user;
}

User user_sub_money(User user, satoBnb amount)
{
    user->wallet -= amount;
    return user;
}

void user_delete(User *user)
{
    free(*user);
    *user = NULL;
}

/* ------------------------------------------------------- */
