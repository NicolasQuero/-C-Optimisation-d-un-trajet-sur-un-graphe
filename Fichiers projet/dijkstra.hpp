#ifndef DIJKSTRA_H
#define DIJKSTRA_H

extern int N_x, N_y, I, n_depart, n_arrivee; // Variables partagées par tous les fichiers qui importent dijkstra.hpp

extern double a;

int* dijkstra(double** const &Mat_a, int begin_i);

int Trouve_min(double* Poids, bool* Parcourus);

#endif
