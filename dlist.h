/*
Emilia Cárdenas Lobatón
A01706807

Lista Doblemente Ligada
*/

#ifndef DLIST_H_
#define DLIST_H_
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
  DLink(T);
  DLink(T, DLink<T>*, DLink<T>*);
  DLink(const DLink<T>&);

  T	    value;
  DLink<T> *next;
  DLink<T> *prev;

  friend class DList<T>;
  friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), next(0), prev(0) {}

template <class T>
DLink<T>::DLink(T val, DLink* nxt, DLink* prv) : value(val), next(nxt), prev(prv) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), next(source.next), prev(source.previous) {}

template <class T> 
class DList{
  private:
  DLink<T> *head;
  DLink<T> *tail;
  int 	size;

  friend class DListIterator<T>;

  public:
  DList();
  ~DList();
  DList(const DList<T>&);

  std::string toStringForward() const;
  std::string toStringBackward() const;
  T insertion(T val); 
  T search(T val);
  T update(T val,T val2);
  T deleteAt(T val);
};


template <class T>
DList<T>::DList() : head(NULL), tail(NULL), size(0) {}

template <class T>
DList<T>::~DList() {
  DLink<T> *current = head;
  DLink<T> *nextNode;
  
  while (current != nullptr) {
    nextNode = current->next;
    delete current;
    current = nextNode;
  }
}

template <class T>
T DList<T>::insertion(T val){
  
  DLink<T> *nuevo = new DLink<T>(val);

  if (tail == NULL) {
    head = nuevo;
    tail = nuevo; 
  } else {
    tail->next = nuevo; 
    nuevo -> prev = tail;
    tail = nuevo;
  }
  size++;
  
  return val;
}

template <class T>
T DList<T>::search(T val){
  DLink<T> *nuevo;
  nuevo = head;
  int pos = 0;
  while (nuevo != 0){
    if (nuevo -> value == val){
      return pos;
    }
    pos++;
    nuevo = nuevo -> next;
  }
  return -1;
}

template <class T>
T DList<T>::update(T val, T val2){
  DLink<T> *nuevo = head;
  int i = 0;

  while (nuevo != NULL){
    if (i == val){
      T aux = nuevo -> value;
      nuevo -> value = val2;
      return aux;
    }
    i++;
    nuevo = nuevo -> next;
  }
  return T();
}

template <class T>
T DList<T>::deleteAt(T val){
  DLink<T> *nuevo = head;
  DLink<T> *prev = NULL;
  T eliminado;
  int i = 0;

  if (val == 0) {
    eliminado = head->value;
    nuevo = head;
    head = head->next;
    if (head != NULL) {
      head->prev = NULL;
    } else {
      tail = NULL;
    }
    delete nuevo;
    size--;
    return eliminado;
  }

  while (nuevo != NULL && i < val) {
    prev = nuevo;
    nuevo = nuevo->next;
    i++;
  }

  eliminado = nuevo->value;
  prev->next = nuevo->next; 

  if (nuevo->next != NULL) {
    nuevo->next->prev = prev;
  } else {
    tail = prev;
  }

  delete nuevo; 
  size--;
  return eliminado;
}

template <class T>
std::string DList<T>::toStringForward() const {
  std::stringstream aux;
  DLink<T> *p;

  p = head;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}


template <class T>
std::string DList<T>::toStringBackward() const {
  std::stringstream aux;
  DLink<T> *p = tail;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->prev!= 0) {
      aux << ", ";
    }
    p = p->prev;
  }
  aux << "]";
  return aux.str();
}
#endif