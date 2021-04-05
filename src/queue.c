/**
 * @file queue.c
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 2021-04-05
 * 
 * @copyright Domaine public 2021
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include "../include/queue.h"

/* ------------------------------------------------------- */
/* Implémentation structure File*/

typedef struct s_queue Queue;

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Constructeur */

Queue *createQueue()
{
    Queue *q;
    return q;
}

Queue *queuePush(Queue *q, void *v)
{
    (void)v;
    return q;
}

/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* Opérateur */

void deleteQueue(ptrQueue *q)
{
    (void)q;
}

Queue *queuePop(Queue *q)
{
    return q;
}


void *queueTop(Queue *q)
{
    return (void*)q;
}


bool queueEmpty(Queue *q)
{
    (void) q;
    return true;
}

unsigned int queueSize(Queue *q)
{
    (void)q;
    return 0;
}

void queueDump(FILE *f, Queue *s, void(*dumpfunction)(FILE *f, void *e))
{
    (void)f;
    (void)s;
    (void)dumpfunction;
}

/* ------------------------------------------------------- */