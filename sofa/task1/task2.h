#ifndef TASK2
#define TASK2

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cstring>
#include <string>



class CIntN
{
    private:
        int n;
        char *arr;
    public:
        CIntN();
        CIntN(const int N, const char*);
        CIntN(const CIntN &);
        CIntN(const int N, int);
	    ~CIntN();
        char operator[] (int k) const;
	    CIntN operator=(const CIntN &);
        CIntN operator+(const CIntN &) const;
        CIntN operator-(const CIntN &) const;
        CIntN neg(void) const;
        char* print () const;
        // void CIntN::print() const;

        CIntN get(bool, int);
        int getN(void) const;
        int getSign(void) const;
};

#endif
