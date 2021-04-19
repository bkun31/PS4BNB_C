/**
 * @file test_block.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Tests implémentation TAD Block
 * @version 0.1
 * @date 2021-04-12
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/block.h"

#define OK 0
#define UNABLE_OPEN_FILE 1

#define TRANSACTION_PATH "transaction.txt"
#define HASH_PATH "hash.txt"

#define HASH_SIZE SHA256_BLOCK_SIZE * 2 + 1
#define TRANSACTION_SIZE 140

#define DIFFICULTY 4

/* returne une transaction depuis un fichier f */
char *transaction(FILE *f)
{
    char tx_char[140];
    char *tx_dynamic;
    fgets(tx_char, TRANSACTION_SIZE, f);
    tx_dynamic = malloc(sizeof(char) * (strlen(tx_char) + 1));
    strcpy(tx_dynamic, tx_char);

    return tx_dynamic;
}

/* libère la transaction crée plus haut */
void free_tx(void *tx)
{
    free((char *)tx);
}

int main()
{
    FILE *f_tx;   /* on va piocher dans un fichier des transactions */
    FILE *f_hash; /* idem on va piocher des hash pour construire le bloc */

    f_tx = fopen(TRANSACTION_PATH, "r");

    if (f_tx == NULL)
    {
        perror(TRANSACTION_PATH);
        exit(UNABLE_OPEN_FILE);
    }

    f_hash = fopen("hash.txt", "r");

    if (f_hash == NULL)
    {
        perror(HASH_PATH);
        fclose(f_tx);
        exit(UNABLE_OPEN_FILE);
    }

    else
    {
        SkipList sl_tx = skiplist_create(4);
        Block blk;
        char prevhash[SHA256_BLOCK_SIZE * 2 + 1];
        int tx_count;

        /* récupère le nombre de transactions qui doit être pioché, le fichier doit donc commencer par un entier indiquant ce nombre */
        fscanf(f_tx, "%d", &tx_count);
        getc(f_tx); /* pour récupérer le retour à la ligne qui n´a pas été récupéré avec fscanf sinon il y a un bug */

        /* on construit la liste des transactions pour le bloc */
        while (tx_count)
        {
            skiplist_insert(sl_tx, tx_count--, transaction(f_tx));
        }

        /* on va créer le bloc on récupère deux hash pour simuler le merkle tree et le hash du bloc précédent */
        fscanf(f_hash, "%s", prevhash);

        printf("Creation bloc et affichage des informations du bloc  avant minage, avec les getters.\n\n");
        blk = block_create(2, sl_tx, prevhash);
        printf("index : %d\n" /* on regarde que chaque getters fonctionne et que les informations sont cohérentes (bloc bien construit) */
               "nonce : %d\n"
               "hash : %s\n"
               "hashprev : %s\n"
               "merkleTree :%s\n"
               "timestamp : %ld\n"
               "tx_count : %d\n",
               block_index(blk),
               block_nonce(blk),
               block_hash(blk),
               block_prevhash(blk),
               block_merkle_tree(blk),
               block_timestamp(blk),
               block_tx_count(blk));

        printf("\nMinage du bloc !\n");
        proof_of_work(blk, DIFFICULTY); /* on mine le bloc */

        /* j´ajoute les hash dans les fichiers textes pour pouvoir les réutiliser si jamais,
        à décommenter si besoin d´ajouter des hash au fichier test */
        // fseek(f_hash, 0, SEEK_END);
        // fprintf(f_hash, "\n%s", block_hash(blk));

        printf("\nAffichage informations du bloc après minage, avec block_dump.\n");
        block_dump(stdout, blk); /* on vérifie que la fonction dump fonctionne */

        /* on vérifie la longueur du hash du bloc miné et qu´il commence bien par le nombre de 0 voulu */
        int long_hash = strlen(block_hash(blk)); // sa longueur en caractères hexadécimaux
        printf("Le sha : %s avec %d caractères hexadécimaux, soit %d octets comme prévu\n", block_hash(blk), long_hash, long_hash / 2);

        /* on n´oublie pas de tout libérer ! */
        fclose(f_tx);
        fclose(f_hash);
        skiplist_delete(sl_tx, free_tx);
        free(blk);
    }

    return OK;
}