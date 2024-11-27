/*
Emilia Cárdenas Lobatón
A01706807

Arbol heap
*/

#ifndef HEAP_H_
#define HEAP_H_
#include <iostream>
#include <string>
#include <sstream>

template <class T>
class Heap {
private:
	T *data;
	unsigned int sizes;
	unsigned int count;

	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	bool empty() const;
	void add(T) ;
    T push(T val);
    T pop();
	T size();
	T top();
	void clear();
	std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
	sizes = sze;
	data = new T[sizes];
	count = 0;
}

template <class T>
Heap<T>::~Heap() {
	delete [] data;
	data = 0;
	sizes = 0;
	count = 0;
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2*pos)+1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2*pos)+2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int izq = left(pos);
	unsigned int der = right(pos);
	unsigned int min = pos;

	if (izq <= count && data[izq] < data[min]) {
		min = izq;
	}
	if (der <= count && data[der] < data[min]) {
		min = der;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
T Heap<T>::push(T val){
	unsigned int pos;

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]){
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
	return val;
}

template <class T>
T Heap<T>::pop(){
	T aux = data[0];
	
	data[0] = data[--count];
	heapify(0);

	return aux;
}

template <class T>
T Heap<T>::size(){
	return count;
}

template <class T>
T Heap<T>::top(){
	return data[0];
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}


#endif