#include "R2.hpp"
#include<cmath>
#include "points_gnu.hpp"
#include "dijkstra.hpp"

double**	adjacency(R2** const &tab)
{
	int N;
	int b;//Permet de gagner des opérations par tour
	int c;//Permet de gagner des opérations par tour
	int d;//Permet de gagner des opérations par tour
	int e;//Permet de gagner des opérations par tour
	double dx;
	double dy;
	double delta;//Limite au-delà de laquelle on ne trace par l'arete
	double **matrix(0);//Matrice d'adjacence
	int n;
	int m;


//Chaque sommet porte un numéro qui est donné dans l'ordre croissant
//en partant d'en haut à gauche de la grille
//Ainsi, le sommet tab[i][j] porte le numéro i*N_y +j
	N = N_x * N_y;
	dx = 1.0/(N_x - 1.0);
	dy = 1.0/(N_y - 1.0);
	delta = 2*fmin(dx,dy);
        matrix = new double *[N];
	n = -1;

	while(++n < N)
		matrix[n] = new double[N];

	n = -1;
	m = -1;
    while(++n < N)
    {
        while(++m < N){
            matrix[n][m] = 0;
        }
        m = -1;
    }

	n = 0;
	while(n < N)
	{
		m = fmax(0,n-N_y-1);//On ne revient pas au début, c'est inutile
		while(m < n + 1)//On ne fait que la moitié car la matrice est symétrique
		{
/*n et m correspondent à des clefs de notre tableau de sommets
 * donc il existe (b,c),(d,e) tels que n = b*N_y+c et m = d*N_y+e
 * donc c = n%N_y et b = (n - c)/N_y, on fait de même pour m
 * si dist(tab[b][c],tab[d][e]) < delta
 * et tab[b][c] != tab[d][e] on trace l'arete*/
			c = n%N_y;
			b = (n-c)/N_y;
			e = m%N_y;
			d = (m-e)/N_y;
			if(dist(tab[b][c],tab[d][e]) < delta && n!= m)
			{
			//arete entre le nieme sommet et le mieme sommet de valeur son cout
				matrix[n][m] = a*dist(tab[b][c],tab[d][e])/fmax(dx,dy)
				+(1-a)*abs(f(tab[b][c][0], tab[b][c][1]) -
				f(tab[d][e][0], tab[d][e][1]))/
				dist(tab[b][c],tab[d][e]);

				/*matrix[n][m] = a*dist(tab[b][c],tab[d][e])/fmax(dx,dy)
				+ (1-a)*(f(tab[b][c][0],tab[b][c][1])-f(tab[d][e][0],tab[d][e][1]))/dist(tab[b][c],tab[d][e]);*/
			}

            matrix[m][n] = matrix[n][m];
			if(m == n - N_y + 1 && N_y != 2)//On saute les comparaisons inutiles
				m = m + N_y - 3;//Si N_y == 2 on a une boucle infinie
			m++;
		}
		n++;
	}
	return(matrix);
}
