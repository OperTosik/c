#ifndef STACK_H
#define STACK_H

class StackExeption {
private:
    const char* reason;

public:
    StackExeption(const char* txt = ""):
        reason(txt)
    {}

    const char* what() const {
        return reason;
    }
};

template <class T> class Stack {
private:
    T* elems;
    int capacity;
    int numElems;

public:
    Stack(int maxSize = 256):
        elems(new T[maxSize]),
        capacity(maxSize),
        numElems(0)
    {}

    Stack (const Stack<T>& s):
        elems(new T[s.capacity]),
        capacity(s.capacity),
        numElems(s.size())
    {
        for (int i = 0; i < numElems; ++i) {
            elems[i] = s.elems[i];
        }
    }

    Stack (Stack<T>&& s):
        elems(s.elems),
        capacity(s.capacity),
        numElems(s.size()) 
    {
        s.elems = nullptr;
        capacity = 0;
        numElems = 0;
    }

    ~Stack() {
        delete[] elems;
    }

    Stack& operator=(const Stack& s) {
        if (s.size() > capacity) {
            delete[] elems;
            elems = new T[s.capacity];
            capacity = s.capacity;
        }
        for (int i = 0; i < numElems; ++i) {
            elems[i] = s.elems[i];
        }
        numElems = s.numElems;
        return *this;
    }

    const T& top() const {
        if (numElems == 0) {
            throw StackExeption("Trying to take element from empty stack");
        }
        return elems[numElems - 1];
    }

    T& top() {
        if (numElems == 0) {
            throw StackExeption("Trying to take element from empty stack");
        }
        return elems[numElems - 1];
    }

    void pop() {
        if (numElems == 0) {
            throw StackExeption("Trying to pop element from empty stack");
        }
        if (numElems == 0) {
            cout << 
        }
    }

    void push(const T& x) {
        if (numElems == capacity) {
            int extend = capacity /4;
            if (extend < 64) {
                extend = 64;
            }
            T* newElems = new T[capacity + extend];
        }
    }
    
};

#endif