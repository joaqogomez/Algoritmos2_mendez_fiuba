#include "pila.h"
#include <stdio.h>
#define FALLO 0
#define FUNCIONO 1


int DadaUnaPilaVacia_CuandoSeApilanElementosYLuegoSeDesapilanTodosImprimiendoCadaElemento_EntoncesLaPilaQuedaVacia(pila_t* pila){
  char elemento1 = '!';
  char elemento2 = '2';
  char elemento3 = 'o';
  char elemento4 = 'g';
  char elemento5 = 'l';
  char elemento6 = 'A';

  pila=pila_crear();
  pila_apilar(pila, &elemento1);
  pila_apilar(pila, &elemento2);
  pila_apilar(pila, &elemento3);
  pila_apilar(pila, &elemento4);
  pila_apilar(pila, &elemento5);
  pila_apilar(pila, &elemento6);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  

  if(pila_vacia(pila)){
    printf("Prueba pasada :)\n");
    pila_destruir(pila);
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    pila_destruir(pila);
    return FALLO;
  }
}
int DadaUnaPilaVacia_CuandoSeIntentaDesapilar_EntoncesNoPuedoDesapilar(pila_t* pila){
  bool no_desapilo=false;
  pila = pila_crear();
  if(pila_desapilar(pila)){
    no_desapilo=true;
    printf("No se puede desapilar.\n");
  }
  pila_destruir(pila);

  if(no_desapilo){
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadaUnaPilaVacia_CuandoSeApilanLosPrimerosCienNumeros_EntoncesElTopeEsElNumero100(pila_t* pila){
  int numero=1;

  pila = pila_crear();
  for (int i = 0; i < 99; ++i){
    pila_apilar(pila, &numero);
    numero++;
  }
  printf("El elemento tope es %i. \n",*(int*)(pila_tope(pila)) );
  if((*(int*)(pila_tope(pila)))==100){
    printf("Prueba pasada :)\n");
    pila_destruir(pila);
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    pila_destruir(pila);
    return FALLO;
  }
}
int DadoUnPunteroAUnaPilaSinCrear_CuandoSeApilaSinCrearLaPila_EntoncesNoPuedoAPilar(pila_t* pila){
    pila=NULL;
    int numero=1;

   if(pila_apilar(pila, &numero)){ //Como devuelve -1 si falla(que es lo que estoy buscando), el true significa que hubo un error.
    printf("Error, intento apilar sin crear una pila.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}

int DadaUnaPilaVacia_CuandoSePideElTope_EntoncesDevuelveNull(pila_t* pila){
  pila=pila_crear();
  if(pila_vacia(pila)){
    if(!pila_tope(pila)){
      printf("Error, no hay elementos en la pila.\n");
      printf("Prueba pasada :)\n");
      pila_destruir(pila);
      return FUNCIONO;
    }else{
      printf("Prueba no pasada :(\n");
      pila_destruir(pila);
      return FALLO;
    }
  }else{
    printf("Prueba no pasada :(\n");
    pila_destruir(pila);
    return FALLO;
  }
}
int DadoUnPunteroAUnaPilaSinCrear_CuandoSePreguntaLaCantidadDeElementos_EntoncesDevuelvoCero(pila_t* pila){
    pila=NULL;

   if(!pila_cantidad(pila)){
    printf("Error, como la pila no existe, no existen elementos apilados.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadoUnPunteroAUnaPilaSinCrear_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(pila_t* pila){
    pila=NULL;

   if(pila_vacia(pila)){
    printf("Error, como la pila no existe, no puede estar vacia.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadaUnaPilaCreada_CuandoSePideCantidadDeElementos_EntoncesDevuelve0(pila_t* pila){
  pila=pila_crear();
  if(!pila_cantidad(pila)){ //Como devuelve 0, lo niego para que el true sea si la cantidad de elementos es 0
    printf("No hay elementos en la pila.\n");
    printf("Prueba pasada :)\n");
    pila_destruir(pila);
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    pila_destruir(pila);
    return FALLO;
  }
}
int DadoUnPunteroAUnaPilaSinCrear_CuandoCreoUnaPila_EntoncesDevuelveSuDireccionDeMemoria(pila_t* pila){
  pila=pila_crear();
  if(pila==NULL){
    printf("Prueba no pasada :(\n");
    pila_destruir(pila);
    return FALLO;
  }else{
    printf("La pila se creo exitosamente.\n");
    printf("Prueba pasada :)\n");
    pila_destruir(pila);
    return FUNCIONO;
  }
}

int main(){
  int pruebas_totales=0,pruebas_pasadas=0;
  pila_t* pila=NULL;
  printf(" Prueba 1   Se apilan elementos, y se van imprimiendo por pantalla al desapilarlos.La pila debe quedar vacia.\n");
  pruebas_pasadas+=DadaUnaPilaVacia_CuandoSeApilanElementosYLuegoSeDesapilanTodosImprimiendoCadaElemento_EntoncesLaPilaQuedaVacia(pila);
  pruebas_totales++;  
  printf(" Prueba 2   Se intenta desapilar en una pila vacia.\n");
  pruebas_pasadas+=DadaUnaPilaVacia_CuandoSeIntentaDesapilar_EntoncesNoPuedoDesapilar(pila);
  pruebas_totales++;
  printf(" Prueba 3   Se apilan los primeros 100 numeros. El tope deberia ser el 100.\n");
  pruebas_pasadas+=DadaUnaPilaVacia_CuandoSeApilanLosPrimerosCienNumeros_EntoncesElTopeEsElNumero100(pila);
  pruebas_totales++;
  printf(" Prueba 4   Se intenta apilar sin tener una pila creada.\n");
  pruebas_pasadas+=DadoUnPunteroAUnaPilaSinCrear_CuandoSeApilaSinCrearLaPila_EntoncesNoPuedoAPilar(pila);
  pruebas_totales++;
  printf(" Prueba 5   Pido el elemento tope de una pila vacia. No deberia devolver nada. \n");
  pruebas_pasadas+=DadaUnaPilaVacia_CuandoSePideElTope_EntoncesDevuelveNull(pila);
  pruebas_totales++;
  printf(" Prueba 6   Pido la cantidad de elementos de una pila sin crear. No deberia devolver nada. \n");
  pruebas_pasadas+=DadoUnPunteroAUnaPilaSinCrear_CuandoSePreguntaLaCantidadDeElementos_EntoncesDevuelvoCero(pila);
  pruebas_totales++;
  printf(" Prueba 7   Pregunto si una pila sin crear esta vacia. Deberia devolver true segun el .h. \n");
  pruebas_pasadas+=DadoUnPunteroAUnaPilaSinCrear_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(pila);
  pruebas_totales++;
  printf(" Prueba 8   Pido la cantidad de elementos de una pila vacia. Deberia devolver cero. \n");
  pruebas_pasadas+=DadaUnaPilaCreada_CuandoSePideCantidadDeElementos_EntoncesDevuelve0(pila);
  pruebas_totales++;
  printf(" Prueba 9   Creo una pila. Esta se crea exitosamente \n");
  pruebas_pasadas+=DadoUnPunteroAUnaPilaSinCrear_CuandoCreoUnaPila_EntoncesDevuelveSuDireccionDeMemoria(pila);
  pruebas_totales++;
  printf("Pasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
  return 0;
}
