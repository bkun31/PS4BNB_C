/**
 * @file test_block.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Tests implémentation TAD Blockchain
 * @version 0.1
 * @date 2021-04-24
 *
 * @copyright Domaine public 2021
 *
 */

#include <stdlib.h>
#include <string.h>
//#include "../../include/block.h"
#include "../../include/blockchain.h"
#include "../../include/user.h"
#include "../../include/transaction.h"

#include "../../src/block.c"

void verif(bool mod, bool v_is_valid_genesis, bool v_is_valid_block, bool v_is_valid_chain, bool v_is_valid_block_merkleTree, bool v_is_valid_chain_merkleTree) {
  if (mod) {
    printf("***** Tests de blockchain valide *****\n");
  }
  else {
    printf("***** Tests de blockchain invalide *****\n");
  }

  if (!(v_is_valid_genesis ^ mod)) {
    printf("| is_valid_genesis OK\n");
  }
  else {
    printf("| !is_valid_genesis paOK\n");
  }
  if (!(v_is_valid_block ^ mod)) {
    printf("| is_valid_block OK\n");
  }
  else {
    printf("| !is_valid_block paOK\n");
  }
  if (!(v_is_valid_chain ^ mod)) {
    printf("| is_valid_chain OK\n");
  }
  else {
    printf("| !is_valid_chain paOK\n");
  }
  if (!(v_is_valid_block_merkleTree ^ mod)) {
    printf("| is_valid_block_merkleTree OK\n");
  }
  else {
    printf("| !is_valid_block_merkleTree paOK\n");
  }
  if (!(v_is_valid_chain_merkleTree ^ mod)) {
    printf("| is_valid_chain_merkleTree OK\n");
  }
  else {
    printf("| !is_valid_chain_merkleTree paOK\n");
  }
}

bool tests_genesis(Blockchain bc) {//renvoit faux si le block genesis est invalide
  bool test = true;
  Block block = skiplist_ith(get_chain(bc), 0);
  block->index = 10;
  test = test && !is_valid_genesis(bc);
  sprintf(block->previous_hash, "aaeqgfqeg");
  test = test && !is_valid_genesis(bc);
  sprintf(block->hash, "aaeqgfqeg");
  test = test && !is_valid_genesis(bc);
  return !test;
}

bool tests_block(Blockchain bc, unsigned int index) {//renvoit faux si le block est invalide
  bool test = true;
  Block block = skiplist_ith(get_chain(bc), index);
  block->index = 0;
  test = test && !is_valid_genesis(bc);
  sprintf(block->previous_hash, "aaeqgfqeg");
  test = test && !is_valid_genesis(bc);
  sprintf(block->hash, "aaeqgfqeg");
  test = test && !is_valid_genesis(bc);
  return !test;
}



int main() {
  /****************************************************************************/
  /**********************Creation et tests de la blockchain********************/
  /****************************************************************************/
  Blockchain bc = blockchain_create(0);
  Block block;
  SkipList list_transaction = skiplist_create(3);

  User users[2];
  for (int i = 0; i < 2; i++)
  {
    users[i] = user_create(i);
    user_add_money(users[i], 50);
  }
  //test blockchain_create, is_valid_genesis
  bool v_is_valid_genesis = is_valid_genesis(bc) && blockchain_size(bc) == 1;

  Transaction tx = generate_transaction(users[0], users[1]);
  skiplist_insert(list_transaction, 0, tx);
  bc = next_block_create(bc, list_transaction);
  //test next_block_create, is_valid_block
  bool v_is_valid_block = is_valid_block(bc, blockchain_size(bc)-1);

  bc = next_block_create(bc, list_transaction);
  tx = generate_transaction(users[1], users[0]);
  skiplist_insert(list_transaction, 0, tx);
  bc = next_block_create(bc, list_transaction);
  //test is_valid_chain
  bool v_is_valid_chain = is_valid_chain(bc);
  //test is_valid_block_merkleTreetests_block(Blockchain bc, unsigned int index)
  bool v_is_valid_block_merkleTree = is_valid_block_merkleTree(bc, blockchain_size(bc)-1);
  //test is_valid_chain_merkleTree
  bool v_is_valid_chain_merkleTree = is_valid_chain_merkleTree(bc);

  //checking for a valid blockchain
  verif(true, v_is_valid_genesis, v_is_valid_block, v_is_valid_chain, v_is_valid_block_merkleTree, v_is_valid_chain_merkleTree);
  /****************************************************************************/



  /****************************************************************************/
  /**********************Tests de la blockchain invalide***********************/
  /****************************************************************************/


  //test blockchain_create, is_valid_genesis
  v_is_valid_genesis = tests_genesis(bc);
  //test next_block_create, is_valid_block
  v_is_valid_block = tests_block(bc, blockchain_size(bc)-1);
  //test is_valid_chain
  v_is_valid_chain = is_valid_chain(bc);

  block = skiplist_ith(get_chain(bc), 2);
  block->merkle_tree[0] = 'a';
  //test is_valid_block_merkleTree
  v_is_valid_block_merkleTree = is_valid_block_merkleTree(bc, 2);
  //test is_valid_chain_merkleTree
  v_is_valid_chain_merkleTree = is_valid_chain_merkleTree(bc);


  //checking for an invalid blockchain
  verif(false, v_is_valid_genesis, v_is_valid_block, v_is_valid_chain, v_is_valid_block_merkleTree, v_is_valid_chain_merkleTree);
  /****************************************************************************/
  //blockchain_dump(stdout, bc);

  skiplist_delete(list_transaction, NULL);

  return 0;
}
