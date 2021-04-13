/**
 * @file skiplist.c
 * @author Mathias Paulin (Mathias.Paulin@irit.fr)
 * @author Cédric Carro (cedric.carro@univ-tlse3.fr)
 * @author Asma Hamza (asma.hamza@univ-tlse3.fr)
 * @author Bilel Besseghieur (bilel.besseghieur@univ-tlse3.fr)
 * @brief Implantation du TAD SkipList vu en tp de Structure de données, modifié pour les besoins du projet.
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Domaine public 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../include/skiplist.h"
#include "../include/rng.h"

/* définition structure noeud de la liste raccourcie */
typedef struct s_Node
{
	int key;
	void *elem;
	unsigned int level;
	struct s_Node **previous;
	struct s_Node **next;

} Node;

/* définition structure liste raccourcie avec utilisation de la sentinelle */

struct s_SkipList
{
	Node *sentinel;
	unsigned int nblevels;
	unsigned int size;
	RNG rng;
};

/**
 * @brief fonction de création d'un noeud, retourne l'adresse du noeud crée
 * 
 * @param key facultatif, pointeur vers un entier désignant la clé du noeud, le pointeur peut être NULL si value l'est aussi
 * @param elem facultatif, pointeur vers un objet désignant l´élément du noeud, le pointeur peut être NULL si key l'est aussi
 * @param level niveau du noeud
 * @return Node* le pointeur vers le noeud correctement crée
 */
Node *node_create(int *key, void *elem, int level)
{
	/* key et elem sont liées, une des deux ne peux pas être NULL si l'autre ne l'est pas */
	assert((key == NULL && elem == NULL) || (key != NULL && elem != NULL));
	Node *n = malloc(sizeof(Node));
	if (n == NULL)
	{
		perror("\nNode Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	if (key && elem)
	{
		n->key = *key; /* le noeud contient une clé */
		n->elem = elem; /* le noeud contient un élément */
	}
	n->level = level;
	n->next = malloc(level * sizeof(Node *));
	if (n->next == NULL)
	{
		perror("\nNode Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	n->previous = malloc(level * sizeof(Node *));
	if (n->previous == NULL)
	{
		perror("\nNode Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	while (level--)
	{
		n->next[level] = NULL;
		n->previous[level] = NULL;
	}
	return n;
}

/**
 * @brief libère en mémoire le noeud n, éventuellement aussi la valeur du noeud si une fonction f de libération est fournie
 * 
 * @param n noeud à libérer
 * @param f facultatif, fonction qui va libèrer l'objet élément de la structure Node, doit être évaluer à NULL si pas de fonction
 */
void node_delete(Node *n, FreeOperator f)
{
	if (f != NULL)
		f(n->elem);
	free(n->next);
	free(n->previous);
	free(n);
}

SkipList skiplist_create(int nblevels)
{
	SkipList d = malloc(sizeof(struct s_SkipList));
	if (d == NULL)
	{
		perror("\nSkiplist Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	d->rng = rng_initialize(time(NULL));
	d->nblevels = nblevels;
	d->size = 0;
	d->sentinel = node_create(NULL, NULL, nblevels);
	while (nblevels--)
	{
		d->sentinel->next[nblevels] = d->sentinel;
		d->sentinel->previous[nblevels] = d->sentinel;
	}

	return d;
}

void skiplist_delete(SkipList d, FreeOperator f)
{
	while (d->sentinel->next[0] != d->sentinel)
	{
		d->sentinel->next[0] = d->sentinel->next[0]->next[0];
		node_delete(d->sentinel->next[0]->previous[0], f);
	}
	node_delete(d->sentinel, NULL);
	free(d);
}


SkipList skiplist_insert(SkipList d, int key, void *elem)
{
	unsigned int level;
	Node *n;
	Node *to_insert[d->nblevels];
	Node *insert = d->sentinel;
	unsigned int l = d->nblevels;

	/* on va lister tous les pointeurs next qui peuvent être mis à jour */
	while (l--)
	{
		while (insert->next[l] != d->sentinel && insert->next[l]->key < key)
			insert = insert->next[l];
		to_insert[l] = insert;
	}
	/* si la clé est existante on ne fait rien */
	if (insert->next[0] != d->sentinel && insert->next[0]->key == key)
		return d;

	/* sinon on crée le noeud et on met à jour tous les pointeurs en fonction du niveau du noeud crée */
	level = rng_get_value(&d->rng, d->nblevels - 1) + 1;
	n = node_create(&key, elem, level);
	for (l = 0; l < level; l++)
	{
		n->next[l] = to_insert[l]->next[l];
		n->previous[l] = to_insert[l];
		n->next[l]->previous[l] = n;
		n->previous[l]->next[l] = n;
	}
	d->size++;
	return d;
}

unsigned int skiplist_size(SkipList d)
{
	return d->size;
}

void *skiplist_ith(SkipList d, unsigned int key)
{
	assert(d->size);
	Node *at = d->sentinel;
	unsigned int level = d->nblevels;
	while (level--)
	{

		while (at->next[level] != d->sentinel && at->next[level]->key < (int)key)
		{
			at = at->next[level];
		}

		if (at->next[level] != d->sentinel && at->next[level]->key == (int)key)
		{
			return at->next[level]->elem;
		}
	}

	return NULL;
}

void skiplist_map(SkipList d, ScanOperator f, void *user_data)
{
	for (Node *e = d->sentinel->next[0];
		 e != d->sentinel;
		 e = e->next[0])
	{
		f(e->elem, user_data);
	}
}

bool skiplist_search(SkipList d, int key)
{
	Node *e = d->sentinel;
	unsigned int level = d->nblevels;
	bool found = false;
	while (level--)
	{

		while (e->next[level] != d->sentinel && e->next[level]->key < key)
		{
			e = e->next[level];
		}

		if (e->next[level] != d->sentinel && e->next[level]->key == key)
		{
			found = true;
			break;
		}
	}

	return found;
}

SkipList skiplist_remove(SkipList d, int key, FreeOperator f)
{
	Node *remove = d->sentinel;
	unsigned int level = d->nblevels;
	while (level--)
	{
		while (remove->next[level] != d->sentinel && remove->next[level]->key < key)
			remove = remove->next[level];

		if (remove->next[level] != d->sentinel && remove->next[level]->key == key)
		{
			remove = remove->next[level];
			for (level = 0; level < remove->level; level++)
			{
				remove->previous[level]->next[level] = remove->next[level];
				remove->next[level]->previous[level] = remove->previous[level];
			}

			node_delete(remove, f);
			d->size--;
			break;
		}
	}

	return d;
}

/* --------- ITERATOR ------------ */

/* définition structure iterateur */

struct s_SkipListIterator
{
	struct s_SkipList *list;
	struct s_Node *current;
	struct s_Node *begin;
	struct s_Node *(*next)(struct s_Node *);
};

/**
 * @brief fonction allant au noeud droit suivant
 * 
 * @param e noeud
 * @return Node* noeud droit suivant
 */
Node *goto_next(Node *e)
{
	return e->next[0];
}

/**
 * @brief fonction allant au noeud gauche suivant
 * 
 * @param e 
 * @return Node* noeud gauche suivant
 */
Node *goto_previous(Node *e)
{
	return e->previous[0];
}

SkipListIterator skiplist_iterator_create(SkipList d, unsigned char w)
{
	SkipListIterator it = malloc(sizeof(struct s_SkipListIterator));
	if (it == NULL)
	{
		perror("\nIterator Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	it->list = d;

	if (w == FORWARD_ITERATOR)
	{
		it->begin = d->sentinel->next[0];
		it->next = goto_next;
	}
	else
	{
		it->begin = d->sentinel->previous[0];
		it->next = goto_previous;
	}
	it->current = it->begin;

	return it;
}

void skiplist_iterator_delete(SkipListIterator it)
{
	free(it);
}

SkipListIterator skiplist_iterator_begin(SkipListIterator it)
{
	it->current = it->begin;
	return it;
}

bool skiplist_iterator_end(SkipListIterator it)
{
	return it->current == it->list->sentinel;
}

SkipListIterator skiplist_iterator_next(SkipListIterator it)
{
	it->current = it->next(it->current);
	return it;
}

void *skiplist_iterator_value(SkipListIterator it)

{
	return it->current->elem;
}