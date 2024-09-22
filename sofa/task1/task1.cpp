#include "task1.h"

using namespace std;
CIntN::CIntN() {
    n = 1;
    arr = new char[3];
    arr[0] = '+';
    arr[1] = '0';
    arr[2] = '\0';
}

CIntN::CIntN(const int N, const char* s){
    if(s == nullptr) exit(-1);
    bool sign = false;
    int len_s = strlen(s);
    arr = new char[N + 2];
    if (s[0] != '+' || s[0] != '-') {
        if (!isdigit(s[0])) {
            delete[] arr;
            exit(-1);
        }
        if(N != len_s) {
            delete [] arr;
            exit (-1);
        }
        arr[0] = '+';
    } 
    else {
        if(len_s == 1 || N != len_s - 1) {
            delete[] arr;
            exit(-1);
        }
        sign  = true;
        arr[0] = s[0];   
    }
    for(int i = 1, k = ((sign) ? 1 : 0); i < N; i++, k++){
        if(isdigit(s[k])) { 
			arr[i] = s[k];
		}
        else {
            cout << "Incorrect data\n" << endl;
            delete[] arr;
            exit(-1);
        }
	}

}
CIntN::CIntN(const CIntN &a){
    int N = a.getN();
    n = N;
    arr = new char[n+2];
    for(int i = 0; i < n+2; i++){
        arr[i] = a.arr[i];
    }
}
CIntN::CIntN(const int N, int num){
    arr = new char[N+2];
    if (num < 0) {
        arr[0] =  '-';
    } else if ( num > 0) {
        arr[0] = '+';
    } else {
        if (N != 1) {
            cout << "\nIncorrect data" << endl;
            exit(-1);
        }

        arr[0] = '+';
        arr[1] = '0';
        arr[2] = '\0';
    }
    num = abs(num);

    int index = N;
    while (index >= 0){
        arr[index] = num % 10;
        num = num/10;
        index--;
        if (num == 0 && index >= 0) {
            cout << "\nIncorrect data" << endl;
            exit(-1);
        }
    }
    if (num != 0) {
         cout << "\nIncorrect data" << endl;
        exit(-1);
    }
    arr[N+1] = '\0';
}

CIntN::~CIntN() {
    delete[] arr;
}

char CIntN::operator[] (int k) const {
    if (k < 0 || k > n) {
        cout << "\nIncorrect index" << endl;
        exit(-1);
    }
    return arr[k];
}

CIntN CIntN::operator=(const CIntN &a) {
	delete[] arr;
    n = a.getN();
    arr = new char[n+2];
    for (int i = 0; i < n+2; i++) {
		arr[i] = a.arr[i];
	}

	return *this;
}

CIntN CIntN::operator+(const CIntN &a) const{
    int s1 = this->getSign(), s2 = a.getSign(); 
    if (s1 == -1 || s1 == -1) {
        if (s1 == s2) {
            return (this->neg()+a.neg()).neg();
        } else {
            if (s1 == -1) {
                return (*this - a.neg()).neg();
            } else {
                return (*this - a.neg());
            }
        }
    }

    int elem = 0, perenos = 0;
    int max = (n > a.getN()) ? n : a.getN();
	char* array;
	array = new char[max+3];
	array[max+2] = 0;
    array[1] = 0;
    array[0] = '+';
    for(int i = n, k = a.getN(); i>= 0 && k>= 0; i--, k--){
        elem = arr[i] - 48 + a[k] - 48  + perenos;
        perenos = elem / 10;
        elem = elem % 10;
        array[i] = elem+48;
    }

    if (array[1] == 0) {
        char* tmp = array;
        delete[] array;
        array = new char[max+2];
        array[0] = tmp[0];
        for (int i = 1; i < max+2; i++) {
            array[i] = tmp[i+1];
        }

        delete[] tmp;
    } else {
        max++;
    }

    CIntN p(max, array);
    delete[] array;
    
	return p;
}

CIntN CIntN::operator-(const CIntN &a) const{
    int s1 = this->getSign(), s2 = a.getSign(); 
    if (s1 == -1 || s1 == -1) {
        if (s1 == s2) {
            return (this->neg()-a.neg()).neg();
        } else {
            if (s1 == -1) {
                return (this->neg() + a).neg();
            } else {
                return (*this + a.neg());
            }
        }
    }

    if (this->getN() <= a.getN()) {
        if (this->getN() < a.getN()) {
            return (a-(*this)).neg();
        } else {
            for ( int i = 1; i < this->getN(); i++) {
                if((*this)[i] - a[i] < 0) {
                    return (a-(*this)).neg();
                }
            }
        }
    }
    
    
    int elem, perenos = 0;
    char* array;
    int N = this->getN();
    array = new char [N+2];
    array[0] = '+';
    for (int i = 1; i < N+1; i++) {
        array[i] = 0;
    }
    array[N+1] = 0;
    for(int i = N, k = a.getN(); i >= 0 && k >= 0; i --, k--){
        elem = arr[i] - a[k] - perenos;
        perenos = 0;
        if (elem < 0){ 
            elem += 10; 
            perenos = 1;
        }
        array[i] = elem + 48;
    }
    int counter = 0;
    for (int i = 1; i < N+1; i++) {
        if (array[i] == '0') {
            counter++;
        } else { 
            break;
        }
    }

    if (counter == N) {
        delete[] array;
        return CIntN();
    }
    N -= counter;
    char* tmp = array;
    delete[] array;
    array = new char [N+2];
    array[0] = '+';
    array[N+1] = '\0';
    for (int i = 1; i < N+1; i++) {
        array[i] = tmp[i+counter];
    }
    delete[] tmp;
    CIntN b(N, array);
    delete[] array;
    return b;

}
CIntN CIntN::neg(void) const{
    char *array = new char[n+2];
    for (int i = 1; i < n+2; i++) {
        array[i] = arr[i];
    }
    array[0] = (arr[0] == '+') ? '-' : '+';
    CIntN tmp(n, array);
    delete[] array;
    return tmp;
}
char* CIntN::print() const{
    char *res;

    res = new char[n+2];
    for (int i = 0; i < n+2; i++) {
        res[i] = arr[i];
    }

    return res;
}

CIntN CIntN::get(bool sgn, int N) {
    if (N <= 0) {
        cout << "\nIncorrect data" << endl;
        exit(-1);
    }
    delete[] arr;
    n = N;
    arr = new char [n+2];
    arr[0] = (sgn) ? '-' : '+';
    arr[n+1] = '\0';    
	for (int i = 1; i < n+1; i++) {
		if (i == 1) {
			arr[i] = rand()%9 +1;
		} else {
			arr[i] = rand()%10;
		}
	}

	return *this;
}

int CIntN::getN(void) const {
    return n;
}

int CIntN::getSign(void) const {
    return (arr[0] == '+') ? 1 : -1;
}