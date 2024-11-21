#ifndef PROGRAM
#define PROGRAM

#include <iostream>
#include <cmath>

#define N 10

class CVect;
class CVectElem;
class CAngl;

std::ostream& operator<<(std::ostream& out, const CVect& n);
std::ostream& operator<<(std::ostream& out, const CAngl& n);

class CVectElem{
private:
	double x;
    double y;
public:
	CVectElem();
	CVectElem(double _x, double _y);

	CVectElem operator+(const CVectElem& other) const;
	// CVectElem operator=(const CVectElem& other) const;

	double getX() const;
	double getY() const;
	
};

class CVect{
private:
	CVectElem arr[N];
public:
	CVect();
	CVect(const CVectElem other[N]);
	CVect(const CVect& other);

	CVect operator+(const CVect& other) const;
	CVect operator+(const CAngl& other) const;
	CAngl operator-(const CVect& other) const;
	// CVect operator=(const CVect& other) const;
	CVectElem operator[](int k) const;

	friend std::ostream& operator<<(std::ostream& out, const CVect& n);
	friend std::ostream& operator<<(std::ostream& out, const CAngl& n);
};

class CAngl{
private:
	double angle[N];
public:
	CAngl();
	CAngl(double _angle[N]);

	CVect operator+(const CVect& other) const;
	
	double operator[](int k) const;
	
};

#endif