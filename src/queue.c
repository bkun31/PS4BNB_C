/**
 * @file queue.c
 * @author Mathias Paulin (Mathias.Paulin@irit.fr)
 * @brief Implémentation du TAD QUEUE
 * @version 0.1
 * @date 2021-04-05
 * 
 * @copyright Tous les droits réservés à son auteur 2021
 * 
 */

/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD Queue étudié en cours.
 
 */
/*-----------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/queue.h"

/* ------------------------------------------------------- */
/* Implémentation structure File*/

/* Full definition of the queue structure */
typedef struct s_internalQueue
{
    void *value;
    struct s_internalQueue *next;
} InternalQueue;

struct s_queue
{
    InternalQueue *head;
    InternalQueue *tail;
    unsigned int size;
};

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

Queue *createQueue()
{
    Queue *q = malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    q->size = 0;
    return (q);
}

Queue *queuePush(Queue *q, void *v)
{
    InternalQueue **insert_at = (q->size ? &(q->tail->next) : &(q->head));
    InternalQueue *new = malloc(sizeof(InternalQueue));
    new->value = v;
    new->next = NULL;
    *insert_at = new;
    q->tail = new;
    ++(q->size);
    return (q);
}

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

void deleteQueue(ptrQueue *q)
{
    InternalQueue *toDelete = (*q)->head;
    while (toDelete)
    {
        InternalQueue *f = toDelete;
        toDelete = toDelete->next;
        free(f);
    }
    free(*q);
    *q = NULL;
}

Queue *queuePop(Queue *q)
{
    assert(!queueEmpty(q));
    InternalQueue *old = q->head;
    q->head = q->head->next;
    q->size--;
    free(old);
    return (q);
}

void *queueTop(Queue *q)
{
    assert(!queueEmpty(q));
    return (q->head->value);
}

bool queueEmpty(Queue *q)
{
    return (q->size == 0);
}

unsigned int queueSize(Queue *q)
{
    return q->size;
}

void queueDump(FILE *f, Queue *q, void (*dumpfunction)(FILE *f, void *e))
{
    fprintf(f, "(%d) --  ", q->size);
    for (InternalQueue *c = q->head; c != NULL; c = c->next)
        dumpfunction(f, c->value);
}

/* ------------------------------------------------------- */