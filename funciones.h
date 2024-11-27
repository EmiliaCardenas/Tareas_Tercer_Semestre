/*
 *
 * Emilia Cárdenas Lobatón
 * A01706807
 * 1_Funciones_Iterativas_Recursivas
 * 
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

class Funciones{
  public:
  int sumaIterativa(int num);
  int sumaRecursiva(int num);
  int sumaDirecta(int num);
};

int Funciones :: sumaIterativa(int num){
  int acum  = 0;
  for(int i = 0; i <= num; i++){
    acum = acum + i;
  }
 return acum;
}

int Funciones :: sumaRecursiva(int num){
  if (num < 1){
    return 0;
  }
  else{
    int acum = num + sumaRecursiva(num - 1);
    return acum;
  }
}

int Funciones :: sumaDirecta(int num){
  int sum = 0;
  while(num > 0){
    sum = sum + num;
    num = num - 1;
  }
  return sum;
}

#endif
