/**
 * @file transaction.c
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
#include "../include/transaction.h"

/* ------------------------------------------------------- */
/* Opérateur */

Transaction generate_transaction(User user_source, User user_destination)
{
	/*on doit préparer le format de la transaction qui est : 
	 *"Source usern-Destination : userm montant_transaction"
	 *on doit générer un nombre aléatoire qui sera le montant (inférieur à MAX_VALUE et au user.wallet)
	 */
	int MAX_VALUE=50;
	int montantMaximal;
	if MAX_VALUE < user_source.wallet //pour choisir un nombre qui dépasse pas le wallet ni le max value 
	{
		montantMaximal = MAX_VALUE; 
	}
	else 
	{
		montantMaximal = user_source.wallet; 
	}
	//fonction qui génère un nombre aléatoire 
	srand(time(NULL)); 
	int montantAleatoire=rand()%montantMaximal+1; //génère un nombre entre 1 et MAX_VALUE ou user_source.wallet
	return("Source user %i -Destination : user %i %i", user_source, user_destination, montantAleatoire); 
}

SkipList construct_transaction_list(Queue *transactions_queue)
{
	/*On vérifie si MAX_TRANSACTIONS est inférieur au nombre d'éléments de la file (besoin de connaître la taille de la file)
	 * (besoin d'accéder à la file pour récupérer les transacitons, normalement avec pop)
	 * SI OUI : on pop un nombre aléatoire de transactions
	 * (besoin de générer un nombre aléatoire)
	 * SI NON : on prend toutes les transactions restantes
	 */
	 srand(time(NULL));
	 if MAX_TRANSACTIONS < queueSize(transactions_queue)
	 {
		 int nbAleatoireTransactions=rand()%10+1; //génère un nombre aléatoire de transactions avec 10 la constante
		 for (i=0; i<nbAleatoireTransactions; i++)
		 {
			 Transaction transaction=queuePop(q);
			 insererDansFile(transaction); //fonction qui prend l'element reçu en parametre et l'insere dans la file (renvoie une file)TP2
		 }
     }
     else 
     {
		 while (queueSize(transactions_queue) != 0) 
		 {
			 Transaction transaction=queuePop(q);
			 insererDansListe(transaction);
		 }
	 }	 
	 return transactions_list;
}

//fonction insererDansListe qui retourne transactions_list 
Queue insererDansFile (Transaction transaction) 
{
	
//fonction selectionElement

char *calculate_merkleTree(Queue transactions_queue, char hash[SHA256_BLOCK_SIZE * 2 + 1])
{
	for (i=0, i<nbTransactions, i++)// ? ? ? ? 
	{
		 char hashRes[SHA256_BLOCK_SIZE*2 + 1];
		 char * var = selectionElement(transactions_queue); //on sélectionne la transaction que l'on insére dans la variable
		 sha256ofString(var ,hashRes); //on obtient le hash 
		 char tab[nbTransactions]; //on cree un tableau pour le hash des transactions
		 tab[i]=hashRes; //on ajoute le hash de la transaciton au tableau
		 i++; //on passe à l'index suivant 
	}
	int j=0;//index du tableau où on insère les elements
	int i=0;//index du tableau duquel on prend les éléments 
	if (nbTransactions%2!=0) //si le nombre de transactions est impair 
	{
		tab[nbTransactions]=tab[nbTransactions-1] //on dédouble la case pour pouvoir calculer le hash 
	}
	while (i <nbTransactions)
	{
		char * concatenation //on crée une variable concatenation qui contient la concatenation
		concatenation = strcat(tab[i], tab[i+1]); //on concatene 2 à 2 les elements du tableau 
		char tableau[nbTransactions] 
		tableau[j]=sha256ofString(concatenation); //on insere le hash de la concatenation dans notre nouveau tableau  
		i+=2;
		j+=1;

	} 
	while (tab[1]!=NULL) //maintenant on fait la boucle jusqu'à ce qu'on atteint le merkle root 
	{
		char * concatenation; //on crée une variable concatenation qui contient la concatenation
		concatenation = strcat(tableau[i], tableau[i+1]); //on concatene 2 à 2 les elements du tableau 
		tableau[j]=sha256ofString(concatenation); //on insere le hash de la concatenation dans notre nouveau tableau 
		int tailleTableau = sizeof(tableau)/sizeof(tableau[0]);   //on diminue la taille du tableau 
		tailleTableau--;
		i+=2;
		j+=1;
		return tableau[0];
	}
}

void print_transaction(FILE *f, Transaction tx)
{
    (void)f;
    (void)tx;
}

/* ------------------------------------------------------- */
