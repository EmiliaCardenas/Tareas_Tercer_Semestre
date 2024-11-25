/*
 *
 * Emilia Cárdenas Lobatón
 * A01706807
 * 2_Algoritmos_Busqueda_Ordenamiento
 * 
 */

#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <list>
#include <iostream>
using namespace std;

template <class T>
class Sorts{
  public:
    vector<T> ordenaSeleccion(vector<T>&);
    vector<T> ordenaBurbuja(vector<T>&);
    vector<T>  ordenaMerge(vector<T>&);
    int busqSecuencial(vector<T>&, int val);
    int busqBinaria(vector<T>&, int val);
};

template <class T>
void swap(std::vector<T> &v, int i, int j) {
  T aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &v){
  int max;
  for (int i = v.size() - 1; i > 0;i--){
    max = i;
    for (int j = 0; j < i; j++){
      if (v[j] > v[max]){
        max = j;
      }
    }
    swap(v, i, max);
  }
  return v;
};

template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T> &v){
  for (int i = v.size() - 1; i > 0; i--){
    for (int j = 0; j < i; j++){
      if (v[j] > v[j+1]){
        swap(v, j, j + 1);
      }
    }
  }
  return v;
};


template <class T>
void merge(vector<T> &v, int left, int right) {
    int mid = (left + right) / 2;
    int n1 = mid - left + 1; 
    int n2 = right - mid;   
    int i = 0, j = 0, k = left;

    vector<int> leftv(n1);
    vector<int> rightv(n2);

    for (int i = 0; i < n1; ++i)
        leftv[i] = v[left + i];
    for (int j = 0; j < n2; ++j)
        rightv[j] = v[mid + 1 + j];

    while (i < n1 && j < n2) {
        if (leftv[i] <= rightv[j]) {
            v[k] = leftv[i];
            i++;
        } else {
            v[k] = rightv[j];
            j++;
        }
        k++;
    }
  
    while (i < n1) {
        v[k] = leftv[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = rightv[j];
        j++;
        k++;
    }
}

template <class T>
void mergeSort(vector<T>& v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(v, left, mid);
        mergeSort(v, mid + 1, right);

        merge(v, left, right);
    }
}

template <class T>
vector<T> Sorts<T>::ordenaMerge(vector<T> &v){
  mergeSort(v, 0, v.size() - 1);
  return v;
};

template <class T>
int buscar_numero(vector<T> &v, int n){
  for(int i=0; i<v.size();i++){
    if (v[i] == n){
      return i;
    }
  }
  return -1;
}

template <class T>
int Sorts<T>::busqSecuencial(vector<T>& v, int val){
  int mid;
  int low = 0;
  int high = v.size() - 1;

  int index = buscar_numero(v, val);
  if (index == -1) {
      return index;
  }

  while(low < high){
    mid = (high + low) / 2;
    if (val == v[mid]){
      return mid;
    } else if (val < v[mid]){
      high = mid - 1;
    } else if (val > v[mid]){
      low = mid + 1;
    } 
  }
  return low;
};

template <class T>
int busqueda_aux(vector<T>& v, int low, int high, int val) {
  int mid;

  int index = buscar_numero(v, val);
  if (index == -1) {
      return index;
  }

  if (low<high){
    mid = (high + low) / 2;
    if (val == v[mid]){
      return mid;
    } else if (val < v[mid]){
      return busqueda_aux(v,low,mid-1,val);
    } else if (val > v[mid]){
      return busqueda_aux(v,mid+1,high,val);
    }
  }
  return low;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T>& v, int val){
  return busqueda_aux(v,0,v.size()-1,val);
};

#endif