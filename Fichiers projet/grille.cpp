#include "grille.hpp"
#include "R2.hpp"
#include<math.h>


//N_x et N_y definissent le nombre de points pour la discrétisation 

R2**	grille(int const N_x,int const N_y) //la routourne retourne un pointeur
{
	int n;//compteur
	int m;
	double dx;
	double dy;
	R2 **tab(0);//Tableau des sommets

	n = 0;
	tab = new R2 *[N_x];//Alloue N_x lignes
	while(n < N_x)
	{
		tab[n] = new R2[N_y];//Alloue N_y colonne à chaque ligne
		n++;
	}

	n = 0;
	dx = 1.0/(N_x - 1.0);// 1.0 obligatoire
	dy = 1.0/(N_y - 1.0);//On définit le pas.
	while(n < N_x)
	{
		m = 0;
		while(m < N_y)
		{
				tab[n][m] = R2(n*dx,m*dy);
			m++;
		}
		n++;
	}
	//Le tableau de points est construit, on construit maintenant les aretes
	return(tab);
}
