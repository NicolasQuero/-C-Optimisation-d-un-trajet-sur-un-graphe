#ifndef DEF_R2
#define DEF_R2
#include <iostream>
using namespace std;

class R2
{
	public:
	R2();
	R2(R2 const& vect);
	R2(double x,double y);

	friend double dist(R2 const& vect1, R2 const& vect2);
	void operator=(R2 const& vect);
	friend ostream& operator<<(ostream &flux, R2 const& vect);
	R2 operator+(R2 const& vect1);
	friend R2 operator*(double x, R2 const& vect);
	double operator[](int i);


	private:
	double m_x;
	double m_y;

};
#endif
