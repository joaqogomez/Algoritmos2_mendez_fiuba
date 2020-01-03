#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <time.h>

typedef struct alumno{
    int padron;
    char nombre[10];
}alumno_t;

alumno_t* crear_alumno(int padron){
    alumno_t* alumno= (alumno_t*)malloc(sizeof(alumno_t));
    if(alumno!=NULL){
        alumno->padron = padron;
    }
     return alumno;
}

void destruir_alumno(alumno_t* alumno){
    if(alumno!=NULL){
        free(alumno);
    }
}

int comparar_alumnos(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2){
        return 0;
    }    
    if(((alumno_t*)elemento1)->padron>((alumno_t*)elemento2)->padron){
        return 1;
    }else if(((alumno_t*)elemento1)->padron<((alumno_t*)elemento2)->padron){
        return -1;
    }else{
        return 0;
    }
}

void destructor_de_alumnos(void* elemento){
    if(elemento==NULL){
        return;
    }
    destruir_alumno((alumno_t*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
  extra=extra; 
  if(elemento)
    printf("%i ", ((alumno_t*)elemento)->padron);
  return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
  extra=extra; 
  if(elemento){
    printf("%i ", ((alumno_t*)elemento)->padron);
    if(((alumno_t*)elemento)->padron == 5)
      return true;
  }
  return false;
}

void mostrar_arbol(abb_t* arbol, nodo_abb_t* nodo_arbol, int contador){
    if(nodo_arbol == NULL){
        for(int i=0; i<contador;i++){
        printf("   ");
        }printf("N\n");
        return;
    }
    mostrar_arbol(arbol,nodo_arbol->derecha, contador+1);
    for(int i=0; i<contador;i++){
        printf("   ");
    }
    printf("%i\n", ((alumno_t*)nodo_arbol->elemento)->padron);
    mostrar_arbol(arbol,nodo_arbol->izquierda, contador+1);
}

int casos_arbol_null(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    int elemento=0;
    int vector[2];//el tamaño del vector puede ser cualquier valor, ya que se quiere chequear otras cosas
    int tamanio=2;
    printf("Pruebas con el arbol sin crear: \n");
    printf("Intento insertar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_insertar(arbol,&elemento),-1)));
    (*pruebas_totales)++;
    printf("Intento borrar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_borrar(arbol,&elemento),-1)));
    (*pruebas_totales)++; 
    printf("Intento buscar un elemento: ");
    pruebas_pasadas+=resultados_prueba(arbol_buscar(arbol,&elemento)==NULL);
    (*pruebas_totales)++; 
    printf("Intento ver cual es la raiz del arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol_raiz(arbol)==NULL);
    (*pruebas_totales)++; 
    printf("Chequeo que el arbol este vacio: ");
    pruebas_pasadas+=resultados_prueba(arbol_vacio(arbol));
    (*pruebas_totales)++;
    printf("Intento recorrer el arbol:\n");
    printf("Inorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_inorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++; 
    printf("Preorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_preorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++; 
    printf("Postorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_postorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++;
    return pruebas_pasadas;
}

int casos_arbol_vacio(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    int elemento=0;
    int vector[2];//el tamaño del vector puede ser cualquier valor, ya que se quiere chequear otras cosas
    int tamanio=2;
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Pruebas con el arbol vacio: \n");
    printf("Intento borrar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_borrar(arbol,&elemento),-1)));
    (*pruebas_totales)++; 
    printf("Intento buscar un elemento: ");
    pruebas_pasadas+=resultados_prueba(arbol_buscar(arbol,&elemento)==NULL);
    (*pruebas_totales)++; 
    printf("Intento ver cual es la raiz del arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol_raiz(arbol)==NULL);
    (*pruebas_totales)++; 
    printf("Chequeo que el arbol este vacio: ");
    pruebas_pasadas+=resultados_prueba(arbol_vacio(arbol));
    (*pruebas_totales)++;
    printf("Intento recorrer el arbol:\n");
    printf("Inorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_inorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++; 
    printf("Preorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_preorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++; 
    printf("Postorden: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(arbol_recorrido_postorden(arbol,(void**)vector,tamanio),0)));
    (*pruebas_totales)++;
    arbol_destruir(arbol);
    return pruebas_pasadas;
}
int casos_borde_recorridos(abb_t* arbol,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\n");
    printf("Chequeo los recorridos\n");
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Inserto 7 elementos y el tope de mi array es 5\n");
    alumno_t* elementos[5];
    arbol_insertar(arbol, crear_alumno(4));
    arbol_insertar(arbol, crear_alumno(2));
    arbol_insertar(arbol, crear_alumno(6));
    arbol_insertar(arbol, crear_alumno(1));
    arbol_insertar(arbol, crear_alumno(3));
    arbol_insertar(arbol, crear_alumno(5));
    arbol_insertar(arbol, crear_alumno(7));
    printf("Pruebo que no se recorrieron todos los elementos e imprimo el recorrido\n");
    printf("Recorrido inorden: ");
    int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 5);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("No se recorrieron todos los elementos: ");
     pruebas_pasadas+=resultados_prueba(!comparador_enteros(cantidad,7));
    (*pruebas_totales)++;
    printf("Recorrido preorden: ");
    cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 5);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("No se recorrieron todos los elementos: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros(cantidad,7));
    (*pruebas_totales)++;
    printf("Recorrido postorden: ");
    cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 5);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("No se recorrieron todos los elementos: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros(cantidad,7));
    (*pruebas_totales)++;
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int pruebas_casos_borde(abb_t* arbol,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\nPrimero, chequeo casos borde: \n");
    pruebas_pasadas+=casos_arbol_null(arbol,pruebas_totales);
    pruebas_pasadas+=casos_arbol_vacio(arbol,pruebas_totales);
    pruebas_pasadas+=casos_borde_recorridos(arbol,pruebas_totales);
    return pruebas_pasadas;
}

int pruebas_elementos_NULL(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    printf("\nChequeo un caso con elementos NULL: \n");
    printf("Creo un arbol con destructor NULL\n");
    arbol=arbol_crear(comparar_alumnos, NULL);
    printf("Se creo correctamente el arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol!=NULL);
    (*pruebas_totales)++;
    printf("El destructor es NULL: ");
    pruebas_pasadas+=resultados_prueba(arbol->destructor==NULL);
    (*pruebas_totales)++;
    printf("Inserto un elemento NULL: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_insertar(arbol,NULL)),0));
    (*pruebas_totales)++;
    printf("El arbol no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!arbol_vacio(arbol));
    (*pruebas_totales)++;
    printf("NULL es la raiz del arbol:  ");
    pruebas_pasadas+=resultados_prueba(arbol_raiz(arbol)==NULL);
    (*pruebas_totales)++;
    printf("Busco el elemento NULL:  ");
    pruebas_pasadas+=resultados_prueba(arbol_buscar(arbol,NULL)==NULL);
    (*pruebas_totales)++;
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int pruebas_caso_promedio(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    alumno_t* auxiliar = crear_alumno(1);
    printf("\nChequeo un caso promedio: \n");
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Se creo correctamente el arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol!=NULL);
    (*pruebas_totales)++;
    printf("Inserto varios elementos\n");
    arbol_insertar(arbol, crear_alumno(4));
    arbol_insertar(arbol, crear_alumno(2));
    arbol_insertar(arbol, crear_alumno(6));
    arbol_insertar(arbol, crear_alumno(1));
    arbol_insertar(arbol, crear_alumno(3));
    arbol_insertar(arbol, crear_alumno(5));
    arbol_insertar(arbol, crear_alumno(7));
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("El arbol no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!arbol_vacio(arbol));
    (*pruebas_totales)++;
    printf("El 4 es la raiz del arbol: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros(((alumno_t*)arbol_raiz(arbol))->padron,4));
    (*pruebas_totales)++;
    printf("El 1 esta en el arbol: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros(((alumno_t*)arbol_buscar(arbol,auxiliar))->padron,1));
    (*pruebas_totales)++;
    printf("Elimino la raiz: ");
    auxiliar->padron = 4;
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_borrar(arbol,auxiliar)),0));
    (*pruebas_totales)++;
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("El 4 ya no es la raiz del arbol: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros(((alumno_t*)arbol_raiz(arbol))->padron,4));
    (*pruebas_totales)++;
    printf("Elimino el 6: ");
    auxiliar->padron = 6;
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_borrar(arbol,auxiliar)),0));
    (*pruebas_totales)++;
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("El 6 ya no esta en el arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol_buscar(arbol,auxiliar)==NULL);
    (*pruebas_totales)++;
    printf("Inserto varios elementos\n");
    arbol_insertar(arbol, crear_alumno(0));
    arbol_insertar(arbol, crear_alumno(2));
    arbol_insertar(arbol, crear_alumno(12));
    arbol_insertar(arbol, crear_alumno(6));
    arbol_insertar(arbol, crear_alumno(10));
    arbol_insertar(arbol, crear_alumno(11));
    arbol_insertar(arbol, crear_alumno(9));
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Elimino el 2: ");
    auxiliar->padron = 2;
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_borrar(arbol,auxiliar)),0));
    (*pruebas_totales)++;
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Elimino el 11: ");
    auxiliar->padron = 11;
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_borrar(arbol,auxiliar)),0));
    (*pruebas_totales)++;
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Elimino el 12: ");
    auxiliar->padron = 12;
    pruebas_pasadas+=resultados_prueba(comparador_enteros((arbol_borrar(arbol,auxiliar)),0));
    (*pruebas_totales)++;
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Pruebo los recorridos\n");
    alumno_t* elementos[10];
    printf("Recorrido inorden: ");
    int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Recorrido preorden: ");
    cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Recorrido postorden: ");
    cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Pruebo el iterador interno\n");
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");
    printf("Recorrido preorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
    printf("\n");    
    printf("Recorrido postorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
    printf("\n");
    free(auxiliar);
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int pruebas_volumen(abb_t* arbol,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\n");
    printf("Chequeo un caso en el que se insertan muchos elementos: \n");
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Se creo correctamente el arbol: ");
    pruebas_pasadas+=resultados_prueba(arbol!=NULL);
    (*pruebas_totales)++;
    printf("Inserto 1000 elementos\n");
    for (int i = 0; i < 1000; ++i){
        arbol_insertar(arbol, crear_alumno(rand()%50));
    }
    printf("El arbol no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!arbol_vacio(arbol));
    (*pruebas_totales)++;
    printf("Pruebo los recorridos, mostrando solo 10 elementos\n");
    alumno_t* elementos[10];
    printf("Recorrido inorden: ");
    int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Recorrido preorden: ");
    cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Recorrido postorden: ");
    cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
    printf("%i ", elementos[i]->padron);
    printf("\n");
    printf("Pruebo el iterador interno\n");
    printf("Recorro hasta que encuentre el numero 5\n");
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    printf("\n");
    printf("Recorrido preorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    printf("\n");    
    printf("Recorrido postorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    printf("\n");  
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int main(){
    int pruebas_totales=0;
    int pruebas_pasadas=0;
    abb_t* arbol = NULL;
    printf("\t\t\t\tPruebas ABB\n\n");
    pruebas_pasadas+=pruebas_casos_borde(arbol,&pruebas_totales);
    pruebas_pasadas+=pruebas_elementos_NULL(arbol,&pruebas_totales);
    pruebas_pasadas+=pruebas_caso_promedio(arbol,&pruebas_totales);
    pruebas_pasadas+=pruebas_volumen(arbol,&pruebas_totales);
    arbol_destruir(arbol);
    printf("\nFin de las pruebas\n");
    printf("\nPasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
    return 0;
}
