#include <iostream>
#include <fstream>
#include "dijkstra.hpp"
#include "R2.hpp"
#include "grille.hpp"
#include "points_gnu.hpp"
#include "adjacency.hpp"
#include <cmath>
#include <float.h>

// ************* Valeurs à modifier en fonction du résultat souhaité ************* \\

int N_x = 100; // Notre graphe est de taille N_x*N_y, modifier N_x quand le code est lancé !

int n_depart = 2040; // Point de départ pour calculer le plus court chemin partant de ce point, minimum 0.
int n_arrivee = 7754; // Point d'arrivée pour afficher le chemin le plus court jusqu'à ce point, maximum I-1.


double a = 0.6; // a est le coefficient du coût, il indique le rapport entre mettre la priorité sur la distance entre deux points
               // ou entre le cout associé à ce déplacement. a est compris entre 0 et 1, où a = 1 ne prend pas en compte que la distance et inversement.

// ******************************************************************************* \\

int N_y = N_x; // On laissera N_y = N_x
int I = N_x*N_y;// I est le nombre de points, ne pas modifier I.

using namespace std;

int* dijkstra(double** const &Mat_a, int begin_i){ // On prend en argument la Matrice d'adjacence (qui, si l'arête existe, vaut le poids de l'arète en question et 0 si elle n'existe pas) et l'indice du point de départ.

	double Poids[I]; // Tableau du Poids requis pour aller du point de départ à celui de coordonnée i

	bool Parcourus[I]; // Tableau de booléens qui prend true si on est passé par le point i

	int* Adj = new int[I]; // Tableau des antécédents de chaque point

	for(int i=0; i<I; i++) // On initialise les distances à l'infini, Parcourus à false car aucun point n'a été parcouru et les adjacents à -1 pour commencer
	{
		Poids[i]=DBL_MAX; Parcourus[i]=false; Adj[i]=-1;
	}
	Poids[begin_i]=0.; // Le poids du point de départ vaut 0

    int min_d;

	for(int i=0; min_d!=n_arrivee; i++) // On doit maintenant trouver le chemin le plus court pour chaque point
	{
		min_d = Trouve_min(Poids, Parcourus);  // On cherche le point non parcouru de distance minimale
		Parcourus[min_d]=true; // On le note comme parcouru

		for(int k=0; k<I; k++) // On parcourt la matrice d'ajacence à la ligne du point minimal ci-dessus
		{
			if(!Parcourus[k] && Mat_a[min_d][k]!=0 && Poids[min_d]!=DBL_MAX && Poids[min_d]+Mat_a[min_d][k] < Poids[k])
	// Si le point k n'a pas été parcouru, et qu'il y a une arète allant du point min_d à k (valeur non nulle dans la matrice d'adjacence, ici représenté par <0.01), et que le poids du point min_d n'est pas infini (sinon la distance est trop grande), et que le poids du point min_d + le poids de l'arète min_d,k est plus petit que le poids du point k
			{
			    //cout << min_d << " " << k << " " << Poids[k] << " " << Poids[min_d]+Mat_a[min_d][k] << endl;
				Poids[k]=Poids[min_d]+Mat_a[min_d][k]; // Alors il est plus rapide de passer par le point min_d pour accéder à k donc k prend ce nouveau poids
				Adj[k]=min_d; // On met à jour l'antécédent
			}

			if(min_d-N_y-1>0 && k < min_d - N_y - 1) // On optimise les comparaisons de la même manière que dans adjacency.cpp
                k = min_d - N_y - 2;
            else if(k > min_d + N_y + 1) // On saute les comparaisons inutiles car un point ne peut être connecté qu'à des points proches de lui
                k = I;
            else if(k%N_y == min_d%N_y + 1)
                k = k + N_y - 3;
		}
	}
	// On affiche le poids de chaque sommet et son antécédent
	/*
	cout << "En partant de " << begin_i << " on obtient :" << endl;
	for(int i = 0; i<I; i++)
	{ // On numerote les sommets de 0 à I-1
		cout << "Poids de " << i << " : " << Poids[i] << " | Adj de " << i << " : " << Adj[i] << endl;
	} */
	return Adj;

}

int Trouve_min(double* Poids, bool* Parcourus) // On cherche le point non-parcouru avec un poids minimal
{
	double min = DBL_MAX; // On initialise un minimum à l'infini
	int sommet_i; // On initialise l'indice du sommet minimal
	for(int i=0; i<I; i++)
	{
		if(Parcourus[i]==false && Poids[i]<=min) // Si le sommet n'a pas été parcouru et que son poids est inférieur au minimum alors c'est notre nouveau minimum
		{
			sommet_i=i; min=Poids[i];
			//cout  << " S_I " << sommet_i << " min " << min << " " << Poids[i] << endl;
		}
	}
	return sommet_i; // On renvoie l'indice du sommet dont le poids est minimal
}





