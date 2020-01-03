#include <stdio.h>
#include <string.h>
#include "mergesort.h"

void merge(void** vector,int inicio1, int fin1, int fin2, int (*comparador)(void*, void*)){
  int inicio2=fin1+1;  
  while(inicio1<=fin1 && inicio2 <= fin2){
    if(comparador(vector[inicio1], vector[inicio2]))
      inicio1++;
    else{
      void* aux = vector[inicio2];
      for(int i=inicio2;i > inicio1;i--)
      vector[i]=vector[i-1];
      vector[inicio1] = aux;
      inicio1++;
      inicio2++;
      fin1++;
    }
  }
}

void mergesort_interno(void** vector,int inicio, int fin, int (*comparador)(void*, void*)){
  if(inicio==fin){
    return;
  } 
  int medio = (fin+inicio)/2;
  mergesort_interno(vector, inicio, medio, comparador);
  mergesort_interno(vector, medio+1, fin, comparador);
  merge(vector, inicio, medio, fin, comparador);
  
}

void mergesort(void** vector,int cantidad, int (*comparador)(void*, void*)){
  mergesort_interno(vector, 0, cantidad-1,comparador);
}




