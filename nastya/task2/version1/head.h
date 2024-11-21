#ifndef PROGRAM
#define PROGRAM

#include <iostream>
#include <cmath>

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

	double getX() const;
	double getY() const;
	
};

class CVect{
private:
    size_t lenght;
	CVectElem* arr;
public:
	CVect();
	CVect(const CVectElem* other, size_t lenght);
    CVect(const CVect& other);
	CVect(CVect&& other);
    ~CVect();

    CVect operator=(const CVect& other);
    CVect& operator=(CVect&& other);
    CVect& operator++();
    CVect operator++(int);
    CVect& operator--();
    CVect operator--(int);
	// CVect operator+(const CVect&& other) const;
	CVect operator+(const CAngl& other);
	CAngl operator-(const CVect& other) const;

    size_t getLenght() const;
	CVectElem getVect(int k) const;

	friend std::ostream& operator<<(std::ostream& os, const CVect& v);
};

class CAngl{
private:
    size_t lenght;
	double* angle;
public:
	CAngl();
	CAngl(double* _angle, size_t lenght);
	CAngl(const CAngl& other);
    CAngl(CAngl&& other);
    ~CAngl();

	CAngl operator=(const CAngl& other);
    CAngl& operator=(CAngl&& other);
    CAngl& operator++();
    CAngl operator++(int);
    CAngl& operator--();
    CAngl operator--(int);
    CVect operator+(CVect& other);
	
    size_t getLenght() const;
	double getAngle(int k) const;

	friend std::ostream& operator<<(std::ostream& os, const CAngl& a);
	
};

#endif