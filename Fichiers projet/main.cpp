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
// Pour cr�er le maillage de points et le chemin, modifier les variables au d�but du fichier dijkstra.cpp
// et modifier dans points_gnu.cpp le return de la fonction f pour qu'il utilise la fonction � deux variables souhait�e.

using namespace std;

int main(){
	R2 ** G = grille(N_x,N_y); // On cr�e une grille de points de (0,0) � (1,1) divis�e en N_x*N_y points.
	double** A = adjacency(G); // On cr�e la matrice d'adjacence de cette grille avec un co�t d�fini par f dans points_gnu.cpp

	/*for(int i=0; i<I; i++) // Affiche la matrice d'adjacence
	{   // /!\ Matrice � I^2 �l�ments donc trop long � afficher avec de grandes valeurs !
        for(int j=0; j<I; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl; */

	int* Adj = dijkstra(A, n_depart); // On applique l'algorithme de Dijkstra au point de d�part qui nous retourne les ant�c�dents les plus proches
	// pour chaque point dans ce cas-ci.
	int n=n_arrivee;
	int t=1;
	while(n!=n_depart) // On veut ici connaitre le nombre d'ant�c�dents requis pour passer du d�part � l'arriv�e.
	{
		n=Adj[n];
		t++;
	}

	int t_ant[t]; // On cr�e ensuite le tableau des ant�c�dents par lesquels passer pour aller de notre point de d�part au point d'arriv�e.
    n=n_arrivee;
    t_ant[0]=n; // On met d'abord le point d'arriv�e
	int j=1;
	while(n!=n_depart) // Puis on ajoute son ant�c�dent, et l'ant�c�dent de celui-ci etc. jusqu'� arriver au point de d�part.
	{
        n=Adj[n];
		t_ant[j]=n;
		j++;
	} // On a alors un tableau avec les indices de tous les points du chemin le moins co�teux.

	ofstream fic1("Maillage.txt", ios::out | ios::trunc); // On ouvre deux fichiers en �criture
	ofstream fic2("Chemin.txt", ios::out | ios::trunc);
	ofstream fic3("trace.txt", ios::out | ios::trunc);
	if(fic1)
	{
        cout << "MAILLAGE OUVERT" << endl; // Dans le premier on y �crit les coordonn�es des points de notre maillage
        double x, y;
		for(int i = 0; i<I; i++)
		{
                x = G[i/N_x][i%N_x][0]; // Avec notre num�rotation on a N_x*N_y = I points. Les points 0 � I/N_x - 1 sont sur la premi�re ligne
                y = G[i/N_x][i%N_x][1]; // Puis I/N_x � 2*I/N_x - 1 sur la deuxi�me etc. donc G[i/N_x][i%N_y] a pour coordonn�es (x,y).
				fic1 << x << '\t' << y << '\t' << f(x,y) << endl; // Leur coordonn�e z est d�finie par la fonction f (modifiable).
		}
	}
	else {cout << "PB MAILLAGE" << endl;}

	if(fic2)
	{
        cout << "CHEMIN OUVERT" << endl << "Les ant�c�dents sont :" << endl;
        double x, y;
		for(int i=0; i<t; i++)
		{
		    cout << t_ant[i] << endl; // On �crit maintenant les coordonn�es des points du chemin le moins co�teux.
		    x = G[t_ant[i]/N_x][t_ant[i]%N_x][0]; // Les indices de ces points sont rang�s dans t_ant.
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

    // Mettre en commentaire le syst�me d'exploitation non-utilis� en enlever les "//" devant la ligne de votre syst�me d'exploitation

    system("gnuplot --persist trace.txt"); // COMMANDE LINUX
    //system("start \"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" gnuplot --persist trace.txt"); // COMMANDE WINDOWS


	for(int i = 0; i<I; i++) // On d�truit d�sormais tous les tableaux allou�s dynamiquement
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
