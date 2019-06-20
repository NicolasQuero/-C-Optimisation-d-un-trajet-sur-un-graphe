#include <iostream>
#include <math.h>
#include "R2.hpp"
using namespace std;

R2::R2()
{
	m_x = 1;
	m_y = 1;
}

R2::R2(double x,double y)
{
	m_x = x;
	m_y = y;
}

R2::R2(R2 const& vect)
{
	m_x = vect.m_x;
	m_y = vect.m_y;
}


double	dist(R2 const& vect1, R2 const& vect2)
{
	return(sqrt(pow((vect1.m_x-vect2.m_x),2)+pow((vect1.m_y-vect2.m_y),2)));
}


void	R2::operator=(R2 const& vect)
{
	m_x = vect.m_x;
	m_y = vect.m_y;
}

R2	R2::operator+(R2 const& vect1)
{
	R2 result;
	result.m_x = vect1.m_x + m_x;
	result.m_y = vect1.m_y + m_y;
	return(result);
}

ostream& operator<<(ostream &flux, R2 const& vect)
{
	flux << "x=" << vect.m_x << endl << "y=" << vect.m_y << endl;
    return flux;
}

R2	operator*(double x, R2 const& vect)
{
	R2 result;
	result.m_x = x*vect.m_x;
	result.m_y = x*vect.m_y;
	return(result);
}


double	R2::operator[](int i)
{
	if(i==0)
		return(m_x);
	if(i==1)
		return(m_y);
	return(0);
}

