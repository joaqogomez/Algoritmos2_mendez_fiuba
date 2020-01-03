#include "abb.h"
#include "pila.h"
#include "testing.h"
#include "iterador_externo_abb.h"
#include <stdio.h>


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

int casos_null(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    abb_iterador_t* iterador=NULL;
    printf("Pruebas con el arbol sin crear: \n");
    printf("Intento crear un iterador: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_crear(arbol)==NULL);    
    (*pruebas_totales)++;
    printf("Pruebas con el iterador sin crear: \n");
    printf("Intento que me devuelva un elemento: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_siguiente(iterador)==NULL);    
    (*pruebas_totales)++;
    printf("Intento que me devuelva si hay un siguiente: ");
    pruebas_pasadas+=resultados_prueba(!abb_iterador_tiene_siguiente(iterador));
    (*pruebas_totales)++;
    return pruebas_pasadas;
}

int casos_arbol_vacio(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Pruebas con el arbol vacio: \n");
    printf("Creo un iterador, este se crea correctamente: ");
    abb_iterador_t* iterador=abb_iterador_crear(arbol);
    pruebas_pasadas+=resultados_prueba(iterador!=NULL);    
    (*pruebas_totales)++;
    printf("Intento que me devuelva un elemento: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_siguiente(iterador)==NULL);    
    (*pruebas_totales)++;
    printf("Intento que me devuelva si hay un siguiente: ");
    pruebas_pasadas+=resultados_prueba(!abb_iterador_tiene_siguiente(iterador));
    (*pruebas_totales)++;
    abb_iterador_destruir(iterador);
    arbol_destruir(arbol);
    return pruebas_pasadas;
}


int pruebas_casos_borde(abb_t* arbol,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\nPrimero, chequeo casos borde: \n");
    pruebas_pasadas+=casos_null(arbol,pruebas_totales);
    pruebas_pasadas+=casos_arbol_vacio(arbol,pruebas_totales);
    return pruebas_pasadas;
}

int pruebas_primer_caso(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    printf("\nChequeo el primer caso: \n");
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Inserto varios elementos\n");
    arbol_insertar(arbol, crear_alumno(48));
    arbol_insertar(arbol, crear_alumno(29));
    arbol_insertar(arbol, crear_alumno(12));
    arbol_insertar(arbol, crear_alumno(15));
    arbol_insertar(arbol, crear_alumno(79));    
    arbol_insertar(arbol, crear_alumno(75));
    arbol_insertar(arbol, crear_alumno(76));
    arbol_insertar(arbol, crear_alumno(83));
    arbol_insertar(arbol, crear_alumno(51));
    arbol_insertar(arbol, crear_alumno(96));
    arbol_insertar(arbol, crear_alumno(85));
    arbol_insertar(arbol, crear_alumno(18));
    arbol_insertar(arbol, crear_alumno(43));
    arbol_insertar(arbol, crear_alumno(88));
    arbol_insertar(arbol, crear_alumno(89));
    arbol_insertar(arbol, crear_alumno(84));
    arbol_insertar(arbol, crear_alumno(82));
    arbol_insertar(arbol, crear_alumno(5));
    arbol_insertar(arbol, crear_alumno(44));    
    arbol_insertar(arbol, crear_alumno(81));
    arbol_insertar(arbol, crear_alumno(99));
    arbol_insertar(arbol, crear_alumno(98));
    arbol_insertar(arbol, crear_alumno(100));
    arbol_insertar(arbol, crear_alumno(78));
    arbol_insertar(arbol, crear_alumno(4));
    arbol_insertar(arbol, crear_alumno(9));
    arbol_insertar(arbol, crear_alumno(10));
    arbol_insertar(arbol, crear_alumno(1));    
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Pruebo el iterador interno\n");
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");
    printf("Pruebo el iterador externo\n");
    printf("Recorrido inorden iterador externo: ");
    abb_iterador_t* iterador=abb_iterador_crear(arbol);
    while (abb_iterador_tiene_siguiente(iterador)){
        void* elemento=abb_iterador_siguiente(iterador);
        mostrar_elemento(elemento,NULL);        
    }
    printf("\n");
    printf("Ya itere todos los elementos\n");
    printf("Caso borde: Intento iterar uno mas, deberia dar error: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_siguiente(iterador)==NULL);    
    (*pruebas_totales)++;
    abb_iterador_destruir(iterador);
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int pruebas_segundo_caso(abb_t* arbol,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    printf("\nChequeo el segundo caso: \n");
    printf("Creo un arbol\n");
    arbol=arbol_crear(comparar_alumnos, destructor_de_alumnos);
    printf("Inserto los numeros del 1 al 10\n");
    arbol_insertar(arbol, crear_alumno(5));
    arbol_insertar(arbol, crear_alumno(9));
    arbol_insertar(arbol, crear_alumno(2));
    arbol_insertar(arbol, crear_alumno(3));
    arbol_insertar(arbol, crear_alumno(7));    
    arbol_insertar(arbol, crear_alumno(8));
    arbol_insertar(arbol, crear_alumno(6));
    arbol_insertar(arbol, crear_alumno(4));
    arbol_insertar(arbol, crear_alumno(1));
    arbol_insertar(arbol, crear_alumno(10));
    printf("Muestro el arbol\n");
    mostrar_arbol(arbol, arbol->nodo_raiz, 0);
    printf("Pruebo el iterador interno\n");
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");
    printf("Pruebo el iterador externo\n");
    printf("Recorrido inorden iterador externo: ");
    abb_iterador_t* iterador=abb_iterador_crear(arbol);
    while (abb_iterador_tiene_siguiente(iterador)){
        void* elemento=abb_iterador_siguiente(iterador);
        mostrar_elemento(elemento,NULL);       
    }    
    printf("\n");
    printf("Ya itere todos los elementos\n");
    printf("Caso borde: Intento iterar uno mas, deberia dar error: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_siguiente(iterador)==NULL);    
    (*pruebas_totales)++;
    abb_iterador_destruir(iterador);
    iterador=abb_iterador_crear(arbol);
    printf("Sumo los numeros: \n");
    int suma=1+2+3+4+5+6+7+8+9+10;
    printf("Sumando en una variable: %i\n", suma);
    int acumulador=0;
    while (abb_iterador_tiene_siguiente(iterador)){
        void* elemento=abb_iterador_siguiente(iterador);
        int aux=(((alumno_t*)elemento)->padron);
        acumulador+=aux;     
    }  
    printf("Sumando utilizando el iterador externo: %i\n", acumulador);
    printf("Ya itere todos los elementos\n");
    printf("Caso borde: Intento iterar uno mas, deberia dar error: ");
    pruebas_pasadas+=resultados_prueba(abb_iterador_siguiente(iterador)==NULL);    
    (*pruebas_totales)++;
    abb_iterador_destruir(iterador);
    arbol_destruir(arbol);
    return pruebas_pasadas;
}

int main(){
    int pruebas_totales=0;
    int pruebas_pasadas=0;
    abb_t* arbol = NULL;
    printf("\t\t\t\tPruebas TP final\n\n");
    pruebas_pasadas+=pruebas_casos_borde(arbol,&pruebas_totales);
    pruebas_pasadas+=pruebas_primer_caso(arbol,&pruebas_totales);
    pruebas_pasadas+=pruebas_segundo_caso(arbol,&pruebas_totales);
    arbol_destruir(arbol);
    printf("\nFin de las pruebas\n");
    printf("\nPasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
    return 0;
}
