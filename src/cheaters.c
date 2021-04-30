#include <stdio.h>
#include "../include/cheaters.h"

#include "../src/block.c" //inclu en .c pour permettre de modifier les attributs du bloc directement

bool cheater_deleteBlock(SkipList blockchain, unsigned int indexBloc)
{
    if (skiplist_search(blockchain, indexBloc))
    {
        skiplist_remove(blockchain,  indexBloc, free);
        return true;
    }
    else 
    {
        printf("Ce bloc n'existe pas."); 
        return false;	
    }
}

int cheater_recalcul(SkipList blockchain, unsigned int indexBloc, unsigned int cheaterType)
{
    SkipListIterator it = skiplist_iterator_create(blockchain, FORWARD_ITERATOR);
    Block previous_blk;
    unsigned int indexCourant = cheaterType == CHEATER_BLOCK ? indexBloc+1 : indexBloc;
    

    while(((Block) skiplist_iterator_value(it))->index != indexCourant) //tant q'on atteint pas le bloc cible
    {
        previous_blk = (Block) skiplist_iterator_value(it); //bloc precedent toujours derriere l'iterateur 
        skiplist_iterator_next(it); //l'iterateur avance 
    }

    while (skiplist_iterator_end(it) == false) //Tant qu'on n'a pas atteint la sentinel
    {
        Block blk = (Block) skiplist_iterator_value(it);
        if(cheaterType == CHEATER_BLOCK) { 
            blk->index--; //Dans le cas où on est dans un cheater de bloc, il faut décrémenter les indexes des blocs suivants celui qui a été supprimé.
        }
        strcpy(blk->previous_hash, previous_blk->hash);
        calculate_hash_block(blk, blk->hash); 
        skiplist_iterator_next(it);
        previous_blk = blk;
    }

    return 0;
}


bool cheater_deleteTransaction(SkipList blockchain, unsigned int indexBloc, int indexTransaction)
{

    bool transactionDeleted = false;

    if (skiplist_search(blockchain, indexBloc))
    {
        Block blk = (Block) skiplist_ith(blockchain, indexBloc);
        
        if (skiplist_search(blk->transactions, indexTransaction))
        {
            skiplist_remove(blk->transactions,  indexTransaction, free);
            calculate_merkleTree(blk->transactions, blk->merkle_tree); //Le merkleRoot doit être recalculé suite à la suppression de la transaction
            transactionDeleted = true;
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

