/**
 * @file block.c
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
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/block.h"
#include "../include/sha256.h"
#include "../include/sha256_utils.h"
#include "../include/transaction.h"

/* Taille buffer pour la concaténation des éléments du bloc en chaîne de caractères */
#define BUFFER_SIZE (sizeof(time_t) +                              \
                     3 * sizeof(unsigned int) +                    \
                     3 * sizeof(char[SHA256_BLOCK_SIZE * 2 + 1]) + \
                     140 * 10)

/* Structure Bloc */

struct s_Block
{
    time_t timestamp;                              /* timestamp */
    unsigned int index;                            /* indice du bloc */
    unsigned int nonce;                            /* nonce du bloc */
    unsigned int tx_count;                         /* nombre de transactions que contient le bloc */
    SkipList transactions;                         /* liste de transactions contenue dans le bloc */
    char merkle_tree[SHA256_BLOCK_SIZE * 2 + 1];   /* Arbre de merkle de la liste des transactions */
    char hash[SHA256_BLOCK_SIZE * 2 + 1];          /* hash du bloc courant*/
    char previous_hash[SHA256_BLOCK_SIZE * 2 + 1]; /* hash du bloc précédent */
};

/***************
* Constructeur *
****************/

Block block_create(unsigned int index, SkipList transactions, char previous_hash[SHA256_BLOCK_SIZE * 2 + 1])
{
    Block blk = malloc(sizeof(struct s_Block));
    if (blk == NULL)
    {
        perror("\nBlock Allocation Error\n");
        exit(ERREUR_ALLOCATION_BLOCk);
    }
    blk->timestamp = time(NULL);
    blk->index = index;
    blk->nonce = 0;
    blk->transactions = transactions;
    blk->tx_count = skiplist_size(transactions);
    strcpy(blk->previous_hash, previous_hash);
    calculate_merkleTree(transactions, blk->merkle_tree);
    calculate_hash_block(blk, blk->hash);

    return blk;
}

/************
* Opérateur *
*************/

/*------------------------  Getter  -----------------------------*/

unsigned int block_index(const Block blk)
{
    return blk->index;
}

unsigned int block_nonce(const Block blk)
{
    return blk->nonce;
}

const char *block_hash(const Block blk)
{
    return blk->hash;
}

const char *block_prevhash(const Block blk)
{
    return blk->previous_hash;
}

const char *block_merkle_tree(const Block blk)
{
    return blk->merkle_tree;
}

SkipList block_transactions(const Block blk)
{
    return blk->transactions;
}

time_t block_timestamp(const Block blk)
{
    return blk->timestamp;
}

unsigned int block_tx_count(const Block blk)
{
    return blk->tx_count;
}

/*------------------------  hash calculation  -----------------------------*/

/**
 * @brief Concatène dans la chaîne de caractères string, la représentation binaire de la donnée pointé par ptr sous forme de caratères d´un octet.
 * 
 * @param ptr Pointeur vers la donnée à convertir.
 * @param size Taille en octets du type de la donnée qui est pointé par ptr.
 * @param string Chaînes de caractères qui va être concaténé avec la représentations binaire de la données. \n
 * Doit être assez grand pour être concaténer avec le résultat de la fonction, sinon le comportement est indéfini.
 * @return char* Le pointeur vers le résultat de la chaîne de caractères string.
 */
char *to_string(const void *ptr, size_t size, char *string)
{
    char buffer[size + 1];
    /* on utilise un pointeur vers un char pour se déplacer octet par octet */
    const unsigned char *p = (const unsigned char *)ptr;

    /* on va ajouter au buffer octet par octet la donnée pointé par ptr */
    for (int i = 0; i < (int)size; i++)
    {
        buffer[i] = *(p + i);
    }
    buffer[size] = '\0';

    return strcat(string, buffer);
}

/**
 * @brief Concatène dans la chaîne de caractère string la chaîne pointé par transactions.
 * 
 * @param transactions Chaînes de caractères d´une transaction.
 * @param string Chaînes de caractères quelconque qui contenir la concaténation de transaction avec elle. \n
 * string doit être assez grand, sinon le comportement est indéfini.
 */
void concatenate_transactions(void *transactions, void *string)
{
    strcat(string, transactions);
}

char *calculate_hash_block(Block blk, char hash[SHA256_BLOCK_SIZE * 2 + 1])
{
    char string[BUFFER_SIZE] = "";

    /* on convertit en chaînes de caratères les types qui ne sont pas des chaînes
    de caractères et on concatène le tout */
    to_string(&(blk->timestamp), sizeof(time_t), string);
    to_string(&(blk->index), sizeof(unsigned int), string);
    to_string(&(blk->nonce), sizeof(unsigned int), string);
    to_string(&(blk->tx_count), sizeof(unsigned int), string);
    skiplist_map(blk->transactions, concatenate_transactions, string);
    strcat(string, blk->merkle_tree);
    strcat(string, blk->previous_hash);

    /* on calcule le hash */
    sha256ofString((BYTE *)string, hash);

    return hash;
}

/*------------------------  block mining   -----------------------------*/

/**
 * @brief Vérifie que le hash commence par difficulty zéros.
 * 
 * @param hash Hash de 64 caractères hexadécimaux.
 * @param difficulty Nombre de zéros que doit commencer le hash.
 * @return true Si difficulty est égale à 0 (on à trouvé diffulty 0).
 * @return false Si difficulty n´est pas égale à 0 (on a trouvé autre chose que 0).
 */
bool start_difficulty_zeros(char hash[SHA256_BLOCK_SIZE * 2 + 1], unsigned int difficulty)
{
    while (difficulty && hash[difficulty - 1] == '0')
        difficulty--; /* on décrémente difficulty à chaque 0 trouvé */

    return !difficulty;
}

bool proof_of_work(Block blk, unsigned int difficulty)
{
    while (!start_difficulty_zeros(blk->hash, difficulty))
    {
        blk->nonce++;
        calculate_hash_block(blk, blk->hash);
    }
    return true;
}

/*------------------------  print block to file    -----------------------------*/

/**
 * @brief Foncteur d' affichage de transactions pour l' opérateur skiplist_map.
 * 
 * @param tx Pointeur vers une transaction.
 * @param file Pointeur vers un fichier.
 */
void tx_Dump(void *tx, void *file)
{
    //print_transaction((FILE *)file, (Transaction)tx);
    fprintf((FILE *)file, "%s\n", (char *)tx);
}

void tx_DumpList(FILE *f, const void *skiplist)
{
    skiplist_map((void *)skiplist, tx_Dump, f);
}

void block_dump(FILE *f, const Block blk)
{
    fprintf(f,
            "\n*******************************************************************************************\n"
            "\t\t\t\t***************\n"
            "\t\t\t\t* DUMP BLOCk  *\n"
            "\t\t\t\t***************\n"
            "********************************************************************************************\n\n"
            "DUMP: INDEX BLOCK : %d\n"
            "DUMP: TIMESTAMP BLOCK : %ld\n"
            "DUMP: HASH BLOCK : %s\n"
            "DUMP: HASH PREVIOUS BLOCK : %s\n"
            "DUMP: NONCE BLOCK : %d\n"
            "DUMP: MERKLE ROOT : %s\n"
            "DUMP: TRANSACTIONS COUNT : %d\n"
            "\n\t*** DUMP DATA ***\n\n",
            blk->index, blk->timestamp, blk->hash, blk->previous_hash, blk->nonce, blk->merkle_tree, blk->tx_count);
    tx_DumpList(f, blk->transactions);
    fprintf(f, "\n****************************************************************************************\n");
}