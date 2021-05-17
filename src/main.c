/**
 * @file main.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 2021-04-23
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "../include/user.h"
#include "../include/block.h"
#include "../include/transaction.h"
#include "../include/blockchain.h"
#include "../include/queue.h"
#include "../include/bnb.h"
#include "../include/config.h"
#include "../include/cheaters.h"

#define MAX_LIST_USER_SIZE config.max_users
#define MAX_TX_AMOUNT config.max_tx_amount
#define MAX_TX_IN_BLOCK config.max_tx_block
#define CHEATER_BLOCK config.cheater_block
#define CHEATER_TRANSACTION config.cheater_transaction
#define CHEATER_FREQUENCY config.cheater_ferquency
#define DIFFICULTY config.difficulty
#define REWARD config.reward
#define BNB_HALVING config.bnb_halving
#define MAX_BLOCK config.max_block

static volatile bool stop_running = false;

void interrupt(int code)
{
  fprintf(stdout, "\n>>> SIGINT received [%d]\n", code);
  stop_running = true;
}

void exit_function()
{
  printf("\nExiting...\n");
}

int main()
{
  atexit(exit_function);      /* Lance la fonction exit_function quand le programme se termine normalement sans erreurs */
  signal(SIGINT, &interrupt); /* Permet de lancer la fonction interrupt si SIGINT est intercepté */
  conf config = conf_init();
  User users[config.max_users];
  Blockchain blockchain;
  Queue *queue_transaction = createQueue();
  satoBnb money_supply = 0;
  satoBnb reward = REWARD;

  srand(time(NULL));
  /* on initialise le tableau d´utilisateurs */
  for (int i = 0; i < MAX_LIST_USER_SIZE; i++)
  {
    users[i] = user_create(i);
  }

  fprintf(stdout, "CONFIGURATION :\n"
                  "Difficulty : %d\n"
                  "Max block : %d\n"
                  "Number of users : %d\n"
                  "Initial Reward : %ld (%f Bnb)\n"
                  "Bnb halving : %d\n"
                  "Max transaction in block : %d\n"
                  "Max transaction amount : %ld (%f Bnb)\n"
                  "Cheater block enabled : %d\n"
                  "Cheater transaction enabled : %d\n"
                  "Cheater frequency : %f\n",

          DIFFICULTY, MAX_BLOCK, MAX_LIST_USER_SIZE, REWARD, satobnb_to_bnb(REWARD), BNB_HALVING,
          MAX_TX_IN_BLOCK, MAX_TX_AMOUNT, satobnb_to_bnb(MAX_TX_AMOUNT), CHEATER_BLOCK,
          CHEATER_TRANSACTION, CHEATER_FREQUENCY);

  /* -------------------- GENESIS -------------------- */

  blockchain = blockchain_create(DIFFICULTY);
  fprintf(stdout, "\n-------------------- GENESIS --------------------\n"
                  "Block Create !!! : %s Block n° : %d Nonce = %d\n"
                  "Money supply = %ld\n",
          block_hash(get_latest_block(blockchain)),
          block_index(get_latest_block(blockchain)),
          block_nonce(get_latest_block(blockchain)),
          money_supply);
  fprintf(stdout, "\n-------------------- GENESIS-END --------------------\n");

  /* on termine le programme si on a atteint la limite de block pour la blockchain */
  if (blockchain_size(blockchain) == (unsigned int)MAX_BLOCK || stop_running)
  {
    goto end_execution;
  }

  /* -------------------- GENESIS-END -------------------- */

  /* -------------------- HELICOPTER MONEY -------------------- */

  fprintf(stdout, "\n-------------------- HELICOPTER MONEY --------------------\n");
  for (int i = 1; i < MAX_LIST_USER_SIZE; i++)
  {
    /* pour chaque utilisateur on crée une unique transaction coinbase dans un nouveau bloc a chaque fois */
    SkipList tx_list = skiplist_create(1);
    Transaction helicopter_tx = generate_helicopter_transaction(users[i], REWARD);
    skiplist_insert(tx_list, 0, helicopter_tx);
    next_block_create(blockchain, tx_list);
    money_supply += REWARD;
    fprintf(stdout, "Block Mined !!! : %s Block n° : %d Nonce = %d\n",
            block_hash(get_latest_block(blockchain)),
            block_index(get_latest_block(blockchain)),
            block_nonce(get_latest_block(blockchain)));

    /* On réduit de moitié la récompense si BNB_HALVING blocs ont été crée */
    if (blockchain_size(blockchain) % BNB_HALVING == 0)
    {
      reward /= 2;
      fprintf(stdout, "Reward = %ld Money supply = %ld (%f Bnb)\n", reward, money_supply, satobnb_to_bnb(money_supply));
    }

    /* on utilise les cheaters, s´il sont activé et selon leur fréquences d´activation */
    if (CHEATER_BLOCK && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block = !delete_index_block ? 1 : delete_index_block;
      printf("\nCheater Block for Block index : %d !\n", delete_index_block);
      cheater_deleteBlock(blockchain, delete_index_block);

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }
    else if (CHEATER_TRANSACTION && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block_tx = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block_tx = !delete_index_block_tx ? 1 : delete_index_block_tx;
      unsigned int delete_index_tx = (unsigned int)(rand() % block_tx_count(get_block(blockchain, delete_index_block_tx)));
      if (block_tx_count(get_block(blockchain, delete_index_block_tx)) > 1)
      {
        printf("\nCheater Transaction for Block index : %d, transaction %d !\n\n", delete_index_block_tx, delete_index_tx);
        cheater_deleteTransaction(blockchain, delete_index_block_tx, delete_index_tx);
      }
      else
      {
        printf("\nCheater Block : Block index : %d!\n", delete_index_block_tx);
        cheater_deleteBlock(blockchain, delete_index_block_tx);
      }

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }

    /* on termine le programme si on a atteint la limite de block pour la blockchain */
    if (blockchain_size(blockchain) == (unsigned int)MAX_BLOCK || stop_running)
    {
      goto end_execution;
    }
  }
  fprintf(stdout, "\n-------------------- HELICOPTER-MONEY-END --------------------\n");

  /* -------------------- HELICOPTER-MONEY-END -------------------- */

  /* -------------------- INFLATION -------------------- */
  fprintf(stdout, "\n-------------------- INFLATION --------------------\n");
  while (reward)
  {
    /* phase inflation, on génère des transactions aléatoires que l´on met dans une file queue_transaction
    puis on crée un nouveau bloc en piochant ces transactions dans la file et on les mettants dans une liste */
    SkipList tx_list = skiplist_create(1);
    int gen_tx_count = rand() % MAX_TX_IN_BLOCK + 1;
    int tx_position = 0;
    for (int i = 0; i < gen_tx_count; i++)
    {
      int user_source = rand() % MAX_LIST_USER_SIZE;
      int user_destination = rand() % MAX_LIST_USER_SIZE;
      queuePush(queue_transaction, generate_transaction(users[user_source], users[user_destination], MAX_TX_AMOUNT));
    }
    gen_tx_count = rand() % MAX_LIST_USER_SIZE + 1;
    while (gen_tx_count > 0 && !queueEmpty(queue_transaction))
    {
      Transaction tx = queuePop(queue_transaction);
      skiplist_insert(tx_list, tx_position++, tx);
    }
    next_block_create(blockchain, tx_list);
    money_supply += REWARD;
    fprintf(stdout, "Block Mined !!! : %s Block n° : %d Nonce = %d\n",
            block_hash(get_latest_block(blockchain)),
            block_index(get_latest_block(blockchain)),
            block_nonce(get_latest_block(blockchain)));

    /* On réduit de moitié la récompense si BNB_HALVING blocs ont été crée */
    if (blockchain_size(blockchain) % BNB_HALVING == 0)
    {
      reward /= 2;
      fprintf(stdout, "Reward = %ld Money supply = %ld (%f Bnb)\n", reward, money_supply, satobnb_to_bnb(money_supply));
    }

    /* on utilise les cheaters, s´il sont activé et selon leur fréquences d´activation */
    if (CHEATER_BLOCK && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block = !delete_index_block ? 1 : delete_index_block;
      printf("\nCheater Block for Block index : %d !\n", delete_index_block);
      cheater_deleteBlock(blockchain, delete_index_block);

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }
    else if (CHEATER_TRANSACTION && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block_tx = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block_tx = !delete_index_block_tx ? 1 : delete_index_block_tx;
      unsigned int delete_index_tx = (unsigned int)(rand() % block_tx_count(get_block(blockchain, delete_index_block_tx)));
      if (block_tx_count(get_block(blockchain, delete_index_block_tx)) > 1)
      {
        printf("\nCheater Transaction for Block index : %d, transaction %d !\n\n", delete_index_block_tx, delete_index_tx);
        cheater_deleteTransaction(blockchain, delete_index_block_tx, delete_index_tx);
      }
      else
      {
        printf("\nCheater Block : Block index : %d!\n", delete_index_block_tx);
        cheater_deleteBlock(blockchain, delete_index_block_tx);
      }

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }

    /* on termine le programme si on a atteint la limite de block pour la blockchain */
    if (blockchain_size(blockchain) == (unsigned int)MAX_BLOCK || stop_running)
    {
      goto end_execution;
    }
  }
  fprintf(stdout, "Reward = %ld Final money supply = %ld (%f Bnb)\n"
                  "\n-------------------- INFLATION-END --------------------\n",
          reward, money_supply, satobnb_to_bnb(money_supply));

  /* -------------------- INFLATION-END -------------------- */

  /* -------------------- MARKET -------------------- */

  fprintf(stdout, "\n-------------------- MARKET --------------------\n");
  while (1)
  {
    /* même chose que l´inflation sauf qu´il n´y a plus de récompenses pour les mineurs */
    SkipList tx_list = skiplist_create(1);
    int gen_tx_count = rand() % MAX_TX_IN_BLOCK + 1;
    int tx_position = 0;
    for (int i = 0; i < gen_tx_count; i++)
    {
      int user_source = rand() % MAX_LIST_USER_SIZE;
      int user_destination = rand() % MAX_LIST_USER_SIZE;
      queuePush(queue_transaction, generate_transaction(users[user_source], users[user_destination], MAX_TX_AMOUNT));
    }
    gen_tx_count = rand() % MAX_LIST_USER_SIZE + 1;
    while (gen_tx_count > 0 && !queueEmpty(queue_transaction))
    {
      Transaction tx = queuePop(queue_transaction);
      skiplist_insert(tx_list, tx_position++, tx);
    }
    next_block_create(blockchain, tx_list);
    money_supply += REWARD;
    fprintf(stdout, "Block Mined !!! : %s Block n° : %d Nonce = %d\n",
            block_hash(get_latest_block(blockchain)),
            block_index(get_latest_block(blockchain)),
            block_nonce(get_latest_block(blockchain)));

    /* on utilise les cheaters, s´il sont activé et selon leur fréquences d´activation */
    if (CHEATER_BLOCK && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block = !delete_index_block ? 1 : delete_index_block;
      printf("\nCheater Block for Block index : %d !\n", delete_index_block);
      cheater_deleteBlock(blockchain, delete_index_block);

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }
    else if (CHEATER_TRANSACTION && !(rand() % (int)(1 / CHEATER_FREQUENCY)))
    {
      clock_t t;
      t = clock();
      //printf("Compteur demarre\n");

      unsigned int delete_index_block_tx = (unsigned int)(rand() % blockchain_size(blockchain));
      delete_index_block_tx = !delete_index_block_tx ? 1 : delete_index_block_tx;
      unsigned int delete_index_tx = (unsigned int)(rand() % block_tx_count(get_block(blockchain, delete_index_block_tx)));
      if (block_tx_count(get_block(blockchain, delete_index_block_tx)) > 1)
      {
        printf("\nCheater Transaction for Block index : %d, transaction %d !\n\n", delete_index_block_tx, delete_index_tx);
        cheater_deleteTransaction(blockchain, delete_index_block_tx, delete_index_tx);
      }
      else
      {
        printf("\nCheater Block : Block index : %d!\n", delete_index_block_tx);
        cheater_deleteBlock(blockchain, delete_index_block_tx);
      }

      //printf("Compteur fini \n");
      t = clock() - t;
      double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
      printf("The cheater took %f seconds to execute\n\n", time_taken);
    }
    /* on termine le programme si on a atteint la limite de block pour la blockchain */
    if (blockchain_size(blockchain) == (unsigned int)MAX_BLOCK || stop_running)
    {
      goto end_execution;
    }
  }
  fprintf(stdout, "\n-------------------- MARKET-END --------------------\n");

  /* -------------------- MARKET-END -------------------- */

end_execution:
  if (is_valid_chain(blockchain) && is_valid_chain_merkleTree(blockchain))
  {
    blockchain_dump(stdout, blockchain);
    puts("\n\n BLOCKCHAIN VERIFIÉE \n\n");
  }
  // blockchain_dump(stdout, blockchain);

  return 0;
}
