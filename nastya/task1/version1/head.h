#ifndef PROGRAM
#define PROGRAM

#include <iostream>
#include <cmath>

#define N 10


using namespace std;

class CAngl;

class CVect{
public:
	double x[N];
    double y[N];
	CVect();
	CVect(double* _x, double* _y);
	CVect operator+(const CVect& other);
	CVect operator+(const CAngl& other);
	CAngl operator-(const CVect& other);
};

class CAngl{
public:
	double angle[N];
	CAngl();
	CAngl(double* _angle);
	CVect operator+(const CVect& other);
};

#endif