#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include "R2.hpp"
#include "grille.hpp"
#include "adjacency.hpp"
#include "dijkstra.hpp"
#include "points_gnu.hpp"

// *** A LIRE *** \\
// Pour créer le maillage de points et le chemin, modifier les variables au début du fichier dijkstra.cpp
// et modifier dans points_gnu.cpp le return de la fonction f pour qu'il utilise la fonction à deux variables souhaitée.

using namespace std;

int main(){
	R2 ** G = grille(N_x,N_y); // On crée une grille de points de (0,0) à (1,1) divisée en N_x*N_y points.
	double** A = adjacency(G); // On crée la matrice d'adjacence de cette grille avec un coût défini par f dans points_gnu.cpp

	/*for(int i=0; i<I; i++) // Affiche la matrice d'adjacence
	{   // /!\ Matrice à I^2 éléments donc trop long à afficher avec de grandes valeurs !
        for(int j=0; j<I; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl; */

	int* Adj = dijkstra(A, n_depart); // On applique l'algorithme de Dijkstra au point de départ qui nous retourne les antécédents les plus proches
	// pour chaque point dans ce cas-ci.
	int n=n_arrivee;
	int t=1;
	while(n!=n_depart) // On veut ici connaitre le nombre d'antécédents requis pour passer du départ à l'arrivée.
	{
		n=Adj[n];
		t++;
	}

	int t_ant[t]; // On crée ensuite le tableau des antécédents par lesquels passer pour aller de notre point de départ au point d'arrivée.
    n=n_arrivee;
    t_ant[0]=n; // On met d'abord le point d'arrivée
	int j=1;
	while(n!=n_depart) // Puis on ajoute son antécédent, et l'antécédent de celui-ci etc. jusqu'à arriver au point de départ.
	{
        n=Adj[n];
		t_ant[j]=n;
		j++;
	} // On a alors un tableau avec les indices de tous les points du chemin le moins coûteux.

	ofstream fic1("Maillage.txt", ios::out | ios::trunc); // On ouvre deux fichiers en écriture
	ofstream fic2("Chemin.txt", ios::out | ios::trunc);
	ofstream fic3("trace.txt", ios::out | ios::trunc);
	if(fic1)
	{
        cout << "MAILLAGE OUVERT" << endl; // Dans le premier on y écrit les coordonnées des points de notre maillage
        double x, y;
		for(int i = 0; i<I; i++)
		{
                x = G[i/N_x][i%N_x][0]; // Avec notre numérotation on a N_x*N_y = I points. Les points 0 à I/N_x - 1 sont sur la première ligne
                y = G[i/N_x][i%N_x][1]; // Puis I/N_x à 2*I/N_x - 1 sur la deuxième etc. donc G[i/N_x][i%N_y] a pour coordonnées (x,y).
				fic1 << x << '\t' << y << '\t' << f(x,y) << endl; // Leur coordonnée z est définie par la fonction f (modifiable).
		}
	}
	else {cout << "PB MAILLAGE" << endl;}

	if(fic2)
	{
        cout << "CHEMIN OUVERT" << endl << "Les antécédents sont :" << endl;
        double x, y;
		for(int i=0; i<t; i++)
		{
		    cout << t_ant[i] << endl; // On écrit maintenant les coordonnées des points du chemin le moins coûteux.
		    x = G[t_ant[i]/N_x][t_ant[i]%N_x][0]; // Les indices de ces points sont rangés dans t_ant.
		    y = G[t_ant[i]/N_x][t_ant[i]%N_x][1];
			fic2 << x << '\t' << y << '\t' << f(x,y) << endl;
		}
	}
	else {cout << "PB CHEMIN" << endl;}

	if(fic3)
    {
               fic3 << "splot \"Maillage.txt\" with dots, \"Chemin.txt\" with lines pal" << endl;
        }
    fic3.close();

    // Mettre en commentaire le système d'exploitation non-utilisé en enlever les "//" devant la ligne de votre système d'exploitation

    system("gnuplot --persist trace.txt"); // COMMANDE LINUX
    //system("start \"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" gnuplot --persist trace.txt"); // COMMANDE WINDOWS


	for(int i = 0; i<I; i++) // On détruit désormais tous les tableaux alloués dynamiquement
	{
		delete [] A[i];
	}
	for(int i = 0; i<N_x; i++)
	{
		delete [] G[i];
	}
	delete [] A; delete [] G; delete [] Adj;
	return 0;
}
