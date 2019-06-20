#include "R2.hpp"
#include"adjacency.hpp"
#include<cmath>

double sqcos(double x, double y)
{
    x = (x-0.5)*20;
    y = (y-0.5)*20;
    return(pow(x,2)*abs(cos(y))); // x^2*cos(y)
}

double frac(double x, double y)
{
    x = (x-0.5)*20;
    y = (y-0.5)*20;
    return((pow(x,3)-3*(x))/(1+pow(9*y,2))); // (x^3-3x)/(1+y^2)
}

double constant(double x, double y)
{
    return(1.);
}

double crat(double x, double y)
{
    x = (x-0.5)*6; // On ajuste l'échelle pour afficher les résultats de la fonction pour x et y compris entre -3 et 3
    y = (y-0.5)*6;
    return(2*(pow(x,2)+pow(x,2))*exp(-pow(x,2)-pow(y,2))); // 2(x^2+y^2)e^(-x^2-y^2)
}

double gauss(double x, double y)
{
    return(exp(-10*(pow(x-0.5,2.0)+pow(y-0.5,2.0)))); // Gaussienne centrée en (0.5,0.5)
}

double f(double x, double y)
{
    return(crat(x,y)); // Fonction du coût à modifier pour modifier le coût considéré par la Matrice d'adjacence !
}
