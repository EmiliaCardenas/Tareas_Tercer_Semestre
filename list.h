/*
Emilia Cárdenas Lobatón
A01706807

Lista Ligada
*/

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

template <class T> class List;

template <class T>
class Link {
private:
  Link(T);
  Link(T, Link<T>*);
  Link(const Link<T>&);

  T	    value;
  Link<T> *next;

  friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T> 
class List{
  public:
  List();
  List(const List<T>&);

  std::string toString() const;
  T insertion(T val); 
  T search(T val);
  T update(int val,T val2);
  T deleteAt(T val);

  private:
  Link<T> *head;
  int 	size;

  friend class ListIterator<T>;
};

template <class T>
List<T>::List() : head(0), size(0) {}


template <class T>
std::string List<T>::toString() const {
  std::stringstream aux;
  Link<T> *p;

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
T List<T>::insertion(T val){
  Link<T> *nuevo = new Link<T>(val);

  if(head==NULL){
    head = nuevo;
  } else{
    Link<T> *temp = head;
    while(temp->next!=0){
      temp=temp->next;
    }
    temp->next=nuevo;
    size++;
  }
  return (val);
}

template <class T>
T List<T>::search(T val){
  Link<T> *nuevo;
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
T List<T>::update(int val, T val2){
  Link<T> *nuevo = head;
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
T List<T>::deleteAt(T val){
  Link<T> *nuevo, *prev;
  if(head==NULL){
    head = nuevo;
  }

  if (val == 0) {
    nuevo = head;
    head = head->next;        
    T eliminado = nuevo->value; 
    delete nuevo;            
    size--;            
    return eliminado; 
  }

  nuevo = head;
  prev = NULL;
  int i = 0;

  while (nuevo != NULL && i < val) {
    prev = nuevo;             
    nuevo = nuevo->next;    
    i++;
  }

  prev->next = nuevo->next; 
  T eliminado = nuevo->value;  
  delete nuevo;              
  size--;               
  return eliminado;  
}

#endif