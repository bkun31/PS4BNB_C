#include <stdio.h>
#include <string.h>
#include "../include/cheaters.h"

#include "../include/block.h" //inclu en .c pour permettre de modifier les attributs du bloc directement

#include "../include/transaction.h"

#include "../include/blockchain.h"

void free_transaction(void *tx)
{
    free(tx);
}

bool cheater_deleteBlock(Blockchain blockchain, unsigned int indexBloc)
{
    if (skiplist_search(blockchain->b_list, indexBloc))
    {
        skiplist_remove(blockchain->b_list, indexBloc, free);
        --blockchain->b_nb;
        cheater_recalcul(blockchain, indexBloc, CHEATER_BLOCK_);
        return true;
    }
    else
    {
        printf("Ce bloc n'existe pas.");
        return false;
    }
}

int cheater_recalcul(Blockchain blockchain, unsigned int indexBloc, unsigned int cheaterType)
{
    SkipListIterator it = skiplist_iterator_create(blockchain->b_list, FORWARD_ITERATOR);
    Block previous_blk = NULL;
    unsigned int indexCourant = indexBloc;

    while (indexCourant--) //tant q'on atteint pas le bloc cible
    {
        previous_blk = (Block)skiplist_iterator_value(it); //bloc precedent toujours derriere l'iterateur
        skiplist_iterator_next(it);                        //l'iterateur avance
    }

    // if (!previous_blk)
    // {
    //     Block blk = (Block)skiplist_ith(blockchain->b_list, 0);
    //     strcpy(blk->previous_hash, "0");
    //     blk->index--;
    //     calculate_hash_block(blk, blk->hash);
    //     proof_of_work(blk, blockchain->difficulty);
    //     previous_blk = blk;
    //     skiplist_iterator_next(it);
    // }
    // if (!skiplist_iterator_end(it))
    //     printf("Block Index 2nd while : %d\n", block_index(skiplist_iterator_value(it)));
    
    while (skiplist_iterator_end(it) == false) //Tant qu'on n'a pas atteint la sentinel
    {
        Block blk = (Block)skiplist_iterator_value(it);
        if (cheaterType == CHEATER_BLOCK_)
        {
            blk->index--; //Dans le cas où on est dans un cheater de bloc, il faut décrémenter les indexes des blocs suivants celui qui a été supprimé.
        }
        strcpy(blk->previous_hash, previous_blk->hash);
        // printf("Block index : %d Hash : %s\n", blk->index, blk->hash);
        calculate_hash_block(blk, blk->hash);
        proof_of_work(blk, blockchain->difficulty);
        // printf("Block index : %d Hash : %s\n", blk->index, blk->hash);
        skiplist_iterator_next(it);
        previous_blk = blk;
    }

    return 0;
}

bool cheater_deleteTransaction(Blockchain blockchain, unsigned int indexBloc, int indexTransaction)
{

    bool transactionDeleted = false;

    if (skiplist_search(blockchain->b_list, indexBloc))
    {
        Block blk = (Block)skiplist_ith(blockchain->b_list, indexBloc);

        if (skiplist_search(blk->transactions, indexTransaction))
        {
            skiplist_remove(blk->transactions, indexTransaction, free_transaction);
            calculate_merkleTree(blk->transactions, blk->merkle_tree); //Le merkleRoot doit être recalculé suite à la suppression de la transaction
            transactionDeleted = true;
            blk->tx_count--;
            cheater_recalcul(blockchain, indexBloc, CHEATER_TRANSACTION_);
        }
        else
        {
            printf("Cette transaction n'existe pas.");
        }
    }
    else
    {
        printf("Ce bloc n'existe pas.");
    }

    return transactionDeleted;
}
