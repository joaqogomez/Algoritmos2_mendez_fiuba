#include "cola.h"
#include <stdio.h>
#define FALLO 0
#define FUNCIONO 1

int DadaUnaColaVacia_CuandoSeIntentaDesencolar_EntoncesNoPuedoDesencolar(cola_t* cola){
  bool no_desencolo=false;
  cola = cola_crear();
  if(cola_desencolar(cola)){
    no_desencolo=true;
    printf("No se puede desencolar.\n");
  }
  cola_destruir(cola);

  if(no_desencolo){
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadaUnaColaVacia_CuandoSeEncolanLosPrimerosDiezNumeros_EntoncesElPrimeroEsElNumero1(cola_t* cola){
  int numero[10]={1,2,3,4,5,6,7,8,9,10};

  cola = cola_crear();
  for (int i = 0; i < 10; ++i){
    cola_encolar(cola, &numero);
  }
  printf("El primer elemento es %i. \n",*(int*)(cola_primero(cola)) );
  if((*(int*)(cola_primero(cola)))==1){
    printf("Prueba pasada :)\n");
    cola_destruir(cola);
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    cola_destruir(cola);
    return FALLO;
  }
}
int DadoUnPunteroAUnaColaSinCrear_CuandoSeEncolaSinCrearLaCola_EntoncesNoPuedoEncolar(cola_t* cola){
    cola=NULL;
    int numero=1;

   if(cola_encolar(cola, &numero)){ //Como devuelve -1 si falla(que es lo que estoy buscando), el true significa que hubo un error.
    printf("Error, intento encolar sin crear una cola.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}

int DadaUnaColaVacia_CuandoSePideElPrimero_EntoncesDevuelveNull(cola_t* cola){
  cola=cola_crear();
  if(cola_vacia(cola)){
    if(!cola_primero(cola)){
      printf("Error, no hay elementos en la cola.\n");
      printf("Prueba pasada :)\n");
      cola_destruir(cola);
      return FUNCIONO;
    }else{
      printf("Prueba no pasada :(\n");
      cola_destruir(cola);
      return FALLO;
    }
  }else{
    printf("Prueba no pasada :(\n");
    cola_destruir(cola);
    return FALLO;
  }
}
int DadoUnPunteroAUnaColaSinCrear_CuandoSePreguntaLaCantidadDeElementos_EntoncesDevuelvoCero(cola_t* cola){
    cola=NULL;

   if(!cola_cantidad(cola)){
    printf("Error, como la cola no existe, no existen elementos encolados.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadoUnPunteroAUnaColaSinCrear_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(cola_t* cola){
    cola=NULL;

   if(cola_vacia(cola)){
    printf("Error, como la cola no existe, no puede estar vacia.\n");
    printf("Prueba pasada :)\n");
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    return FALLO;
  }
}
int DadaUnaColaCreada_CuandoSePideCantidadDeElementos_EntoncesDevuelve0(cola_t* cola){
  cola=cola_crear();
  if(!cola_cantidad(cola)){ //Como devuelve 0, lo niego para que el true sea si la cantidad de elementos es 0
    printf("No hay elementos en la cola.\n");
    printf("Prueba pasada :)\n");
    cola_destruir(cola);
    return FUNCIONO;
  }else{
    printf("Prueba no pasada :(\n");
    cola_destruir(cola);
    return FALLO;
  }
}
int DadoUnPunteroAUnaColaSinCrear_CuandoCreoUnaCola_EntoncesDevuelveSuDireccionDeMemoria(cola_t* cola){
  cola=cola_crear();
  if(cola==NULL){
    printf("Prueba no pasada :(\n");
    cola_destruir(cola);
    return FALLO;
  }else{
    printf("La cola se creo exitosamente.\n");
    printf("Prueba pasada :)\n");
    cola_destruir(cola);
    return FUNCIONO;
  }
}

int main(){
  int pruebas_totales=0,pruebas_pasadas=0;
  cola_t* cola=NULL;
  printf(" Prueba 1   Se intenta desencolar en una cola vacia.\n");
  pruebas_pasadas+=DadaUnaColaVacia_CuandoSeIntentaDesencolar_EntoncesNoPuedoDesencolar(cola);
  pruebas_totales++;
  printf(" Prueba 2   Se encolan los primeros 10 numeros. El primero deberia ser el 1.\n");
  pruebas_pasadas+=DadaUnaColaVacia_CuandoSeEncolanLosPrimerosDiezNumeros_EntoncesElPrimeroEsElNumero1(cola);
  pruebas_totales++;
  printf(" Prueba 3   Se intenta encolar sin tener una cola creada.\n");
  pruebas_pasadas+=DadoUnPunteroAUnaColaSinCrear_CuandoSeEncolaSinCrearLaCola_EntoncesNoPuedoEncolar(cola);
  pruebas_totales++;
  printf(" Prueba 4   Pido el elemento tope de una cola vacia. No deberia devolver nada. \n");
  pruebas_pasadas+=DadaUnaColaVacia_CuandoSePideElPrimero_EntoncesDevuelveNull(cola);
  pruebas_totales++;
  printf(" Prueba 5   Pido la cantidad de elementos de una cola sin crear. No deberia devolver nada. \n");
  pruebas_pasadas+=DadoUnPunteroAUnaColaSinCrear_CuandoSePreguntaLaCantidadDeElementos_EntoncesDevuelvoCero(cola);
  pruebas_totales++;
  printf(" Prueba 6   Pregunto si una cola sin crear esta vacia. Deberia devolver true segun el .h. \n");
  pruebas_pasadas+=DadoUnPunteroAUnaColaSinCrear_CuandoSePreguntaSiEstaVacia_EntoncesDevuelveTrue(cola);
  pruebas_totales++;
  printf(" Prueba 7   Pido la cantidad de elementos de una cola vacia. Deberia devolver cero. \n");
  pruebas_pasadas+=DadaUnaColaCreada_CuandoSePideCantidadDeElementos_EntoncesDevuelve0(cola);
  pruebas_totales++;
  printf(" Prueba 8   Creo una cola. Esta se crea exitosamente \n");
  pruebas_pasadas+=DadoUnPunteroAUnaColaSinCrear_CuandoCreoUnaCola_EntoncesDevuelveSuDireccionDeMemoria(cola);
  pruebas_totales++;
  printf("Pasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
  return 0;
}