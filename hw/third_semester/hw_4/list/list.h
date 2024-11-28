#pragma once

#include <iostream>

#include <vector>

class listException {
    private:
        const char* reason; // причина исключения
    public:
        listException(const char *txt = "list error") : reason(txt) {}
        const char* what() const {return reason;}
};

template <class T>
class List{
private:
    class ListHead { //он не интересует внешнено прользователя, поэтому внутри определен
    public:
        ListHead* next;
        ListHead* prev;
    public:
        ListHead( 
            ListHead* n = nullptr,
            ListHead* p = nullptr
        ) : next(n), prev(p) {}

        void link(ListHead* n) {
            next = n;
            n ->prev = this;
        }
    };

    class ListElem : public ListHead { //наследуем методы бати класса, но добавим свое
    private:
        T elem;
    public:
        ListElem(const T& e= T()) : ListHead(), elem(e) {}
    };

private:
    ListHead head;
    int numelems; //col-vo elementov
public:
    List() : head(&head, &head), numelems(0) {}
    List(const List& ) = delete; //запретили copy-constructor для компилятора
    List& operator = (const List&)  = delete;
    bool empty() const {return(numelems ==0);}
    int size() const {return numelems;}

    class iterator {
    private: 
        List* lst;
        ListHead* pos;
    public:
        iterator(List* l = nullptr, ListHead* h= nullptr) :lst(l), pos(h) {}
        bool operator== (const iterator& i ) const {
            return(lst == i.lst && pos == i.pos);
        }
        bool operator!= (const iterator& i) const {
            return (!(*this == i));
        }
        iterator& operator++ (){ //++i лучше пользоваться им, а не i++

            pos = pos -> next; // pos = (*pos).next;
            return *this;
        }
        ireator& operator --() {
            pos = post-> prev;
            return *this;
        }
        iterator operator++(int) { //i++
            itearor old = *this;
            ++(*this);
            return old;
        }
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
        const T& operator* () const { // сам объект возвращает
            if(pos == &(lst->head)) //если итератор указывает на header, который пустой
                throw StackException ("list iterator out of range");
            return ((const ListElem*)pos) -> elem; //преобразование указателя от ListHead к ListElem
            // static_cast <const ListElem*>(pos); -- это аналог строчки выше
        }
        T& operator*() {
            if(pos == &(lst->head)) 
                throw StackException ("list iterator out of range");
            return ((ListElem*)pos) -> elem;
        }
        const T* operator->() const { // возврат адреса объекта 
            return &(*this);
        }
    }; // конец итератора

    iterator begin() { // по хорощему писать const iterator.... но это стандарт c++11
        return iterator(this,head.next);
    }
    
    iterator end() {
        return iterator(this, &head);
    }

    iterator insert(iterator i, const T& e) {
        ListElem* block = new ListElem(e);
        i.pos -> prev->link(block);
        block -> link(i.pos);
        return block;
    }

    iterator erase(const iterator& pos) {
        ListHead* prevBlock = pos->prev;
        prevBlock->link(pos->next);
        delete &(*pos);
        return iterator(this, prevBlock);
    }
};