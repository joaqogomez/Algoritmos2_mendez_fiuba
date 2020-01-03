#include "hash.h"
#include "hash_iterador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testing.h"
#include "struct_hash.h"
#include <time.h>
#define MAX_CLAVE 500
#define MAX_LETRAS 26

int casos_hash_null(hash_t* hash,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    const char* elemento="abc";
    printf("Pruebas con el hash sin crear: \n");
    printf("Intento insertar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(hash_insertar(hash,elemento,NULL),-1)));
    (*pruebas_totales)++;
    printf("Intento borrar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(hash_quitar(hash,elemento),-1)));
    (*pruebas_totales)++; 
    printf("Intento buscar un elemento: ");
    pruebas_pasadas+=resultados_prueba(hash_obtener(hash,elemento)==NULL);
    (*pruebas_totales)++; 
    printf("Intento ver si el hash contiene un elemento: ");
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash,elemento));
    (*pruebas_totales)++; 
    printf("Chequeo que la cantidad de elementos sea 0: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros((int)hash_cantidad(hash),0)));
    (*pruebas_totales)++;
    printf("Intento crear un iterador: ");
    pruebas_pasadas+=resultados_prueba(hash_iterador_crear(hash)==NULL);
    (*pruebas_totales)++; 
    printf("Pruebas con el iterador sin crear: \n");
    hash_iterador_t* iterador=NULL;
    printf("Intento pedir la siguiente clave: ");
    pruebas_pasadas+=resultados_prueba(hash_iterador_siguiente(iterador)==NULL);
    (*pruebas_totales)++; 
    printf("Intento  ver si hay siguiente clave: ");
    pruebas_pasadas+=resultados_prueba(!hash_iterador_tiene_siguiente(iterador));
    (*pruebas_totales)++; 
    return pruebas_pasadas;
}

int casos_hash_vacio(hash_t* hash,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    const char* elemento="abc";
    printf("Pruebas con el hash vacio: \n");
    printf("Creo un hash\n");
    hash=hash_crear(NULL, 1);
    printf("Intento borrar un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(hash_quitar(hash,elemento),-1)));
    (*pruebas_totales)++; 
    printf("Intento buscar un elemento: ");
    pruebas_pasadas+=resultados_prueba(hash_obtener(hash,elemento)==NULL);
    (*pruebas_totales)++; 
    printf("Intento ver si el hash contiene un elemento: ");
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash,elemento));
    (*pruebas_totales)++; 
    printf("Chequeo que la cantidad de elementos sea 0: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros((int)hash_cantidad(hash),0)));
    (*pruebas_totales)++;
    printf("Creo un iterador: ");
    hash_iterador_t* iterador=hash_iterador_crear(hash);
    pruebas_pasadas+=resultados_prueba(iterador!=NULL);
    (*pruebas_totales)++;
    printf("Intento pedir la siguiente clave: ");
    pruebas_pasadas+=resultados_prueba(hash_iterador_siguiente(iterador)==NULL);
    (*pruebas_totales)++; 
    printf("Intento  ver si hay siguiente clave: ");
    pruebas_pasadas+=resultados_prueba(!hash_iterador_tiene_siguiente(iterador));
    (*pruebas_totales)++; 
    hash_iterador_destruir(iterador); 
    hash_destruir(hash);
    return pruebas_pasadas;
}

int pruebas_casos_borde(hash_t* hash,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\nPrimero, chequeo casos borde: \n");
    pruebas_pasadas+=casos_hash_null(hash,pruebas_totales);
    pruebas_pasadas+=casos_hash_vacio(hash,pruebas_totales);
    return pruebas_pasadas;
}

int pruebas_elementos_NULL(hash_t* hash,int* pruebas_totales){
    printf("\n");
    int pruebas_pasadas=0;
    const char* clave="abc";
    printf("\nChequeo un caso con elementos NULL: \n");
    printf("Creo un hash con destructor NULL\n");
    hash=hash_crear(NULL,1);
    printf("Se creo correctamente el hash: ");
    pruebas_pasadas+=resultados_prueba(hash!=NULL);
    (*pruebas_totales)++;
    printf("El destructor es NULL: ");
    pruebas_pasadas+=resultados_prueba((hash->destructor)==NULL);
    (*pruebas_totales)++;
    printf("Inserto un elemento NULL: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_insertar(hash,clave,NULL)),0));
    (*pruebas_totales)++;
    printf("El hash no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)(hash_cantidad(hash)),0));
    (*pruebas_totales)++;
    printf("El elemento NULL esta en el hash:  ");
    pruebas_pasadas+=resultados_prueba(hash_obtener(hash,clave)==NULL);
    (*pruebas_totales)++;
    hash_destruir(hash);
    return pruebas_pasadas;
}


extern char* strdup(const char*);

void destruir_string(void* elemento){
  if(elemento){
    free(elemento);
  }
}

int pruebas_caso_promedio(hash_t* hash,int* pruebas_totales){
    int pruebas_pasadas=0;
    printf("\nChequeo un caso promedio (por ejemplo, podria utilizarlo un garage): \n");
    printf("Creo un hash \n");
    hash = hash_crear(destruir_string, 5);
    printf("Se creo correctamente el hash: ");
    pruebas_pasadas+=resultados_prueba(hash!=NULL);
    (*pruebas_totales)++;
    printf("Inserto un elemento: ");
    pruebas_pasadas+=resultados_prueba((comparador_enteros(hash_insertar(hash, "AC123BD",strdup("Auto de Mariano")),0)));
    (*pruebas_totales)++;
    printf("El hash no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)(hash_cantidad(hash)),0));
    (*pruebas_totales)++;
    printf("Inserto 10 elementos mas\n");
    hash_insertar(hash, "OPQ976", strdup("Auto de Lucas"));
    hash_insertar(hash, "A421ACB", strdup("Bici de Manu"));
    hash_insertar(hash, "AA442CD", strdup("Auto de Guido"));
    hash_insertar(hash, "AC152AD", strdup("Auto de Agustina"));
    hash_insertar(hash, "DZE443", strdup("Auto de Jonathan"));
    hash_insertar(hash, "AA436BA", strdup("Auto de Gonzalo"));
    hash_insertar(hash, "QDM443", strdup("Auto de Daniela"));
    hash_insertar(hash, "BD123AC", strdup("Auto de Pablo"));
    hash_insertar(hash, "CD442AA", strdup("Auto de Micaela"));
    hash_insertar(hash, "PQO697", strdup("Auto de Juan"));
    printf("El hash tiene 11 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),11));
    (*pruebas_totales)++;
    printf("Verifico que este el vehiculo patente QDM443: ");   
    pruebas_pasadas+=resultados_prueba(hash_contiene(hash, "QDM443"));
    (*pruebas_totales)++;
    printf("Verifico que este el vehiculo patente OPQ976: ");   
    pruebas_pasadas+=resultados_prueba(hash_contiene(hash, "OPQ976"));
    (*pruebas_totales)++;
    printf("Verifico que este el vehiculo patente AC152AD: ");   
    pruebas_pasadas+=resultados_prueba(hash_contiene(hash, "AC152AD"));
    (*pruebas_totales)++;
    printf("Verifico que este el vehiculo patente CD442AA: ");   
    pruebas_pasadas+=resultados_prueba(hash_contiene(hash, "CD442AA"));
    (*pruebas_totales)++;
    printf("Verifico que este el vehiculo patente BD123AC: ");   
    pruebas_pasadas+=resultados_prueba(hash_contiene(hash, "BD123AC"));
    (*pruebas_totales)++;
    printf("Elimino estos vehiculos\n");
    printf("Elimino QDM443: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_quitar(hash,"QDM443")),0));
    (*pruebas_totales)++;
    printf("Elimino OPQ976: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_quitar(hash,"OPQ976")),0));
    (*pruebas_totales)++;
    printf("Elimino AC152AD: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_quitar(hash,"AC152AD")),0));
    (*pruebas_totales)++;
    printf("Elimino CD442AA: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_quitar(hash,"CD442AA")),0));
    (*pruebas_totales)++;
    printf("Elimino BD123AC: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((hash_quitar(hash,"BD123AC")),0));
    (*pruebas_totales)++;
    printf("Verifico que no este el vehiculo patente QDM443: ");   
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash, "QDM443"));
    (*pruebas_totales)++;
    printf("Verifico que no este el vehiculo patente OPQ976: ");   
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash, "OPQ976"));
    (*pruebas_totales)++;
    printf("Verifico que no este el vehiculo patente AC152AD: ");   
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash, "AC152AD"));
    (*pruebas_totales)++;
    printf("Verifico que no este el vehiculo patente CD442AA: ");   
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash, "CD442AA"));
    (*pruebas_totales)++;
    printf("Verifico que no este el vehiculo patente BD123AC: ");   
    pruebas_pasadas+=resultados_prueba(!hash_contiene(hash, "BD123AC"));
    (*pruebas_totales)++;
    printf("Creo un iterador: ");
    hash_iterador_t* iterador=hash_iterador_crear(hash);
    pruebas_pasadas+=resultados_prueba(iterador!=NULL);
    (*pruebas_totales)++;
    int listados = 0;
    printf("Listo los elementos que contiene el hash: \n");
    while(hash_iterador_tiene_siguiente(iterador)){
      const char* clave = hash_iterador_siguiente(iterador);
      if(clave){
        listados++;
        printf("Patente: %s -- Vehiculo: %s\n", clave, (char*)hash_obtener(hash, clave));
      }
    }
    printf("Tengo la misma cantidad de guardados que de listados: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)hash_cantidad(hash), listados));
    (*pruebas_totales)++;
    hash_iterador_destruir(iterador);
    hash_destruir(hash);
    return pruebas_pasadas;
}

int pruebas_rehash(hash_t* hash,int* pruebas_totales){
    int pruebas_pasadas=0;
    char strings [1000][10];
    for (int i = 0; i < 1000; ++i) {
        sprintf(strings[i],"%d", i);
    }
    printf("\n");
    printf("Chequeo el funcionamiento del rehash: \n");
    printf("Creo un hash con un arbol de capacidad 1 \n");
    hash = hash_crear(NULL, 1);
    printf("Se creo correctamente el hash: ");
    pruebas_pasadas+=resultados_prueba(hash!=NULL);
    (*pruebas_totales)++;
    printf("La capacidad del hash es 1: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)hash->capacidad,1));
    (*pruebas_totales)++;
    printf("Inserto 8 elementos\n");
    for (int i = 0; i < 8; ++i){
        hash_insertar(hash,strings[i], NULL);
    }
    printf("El hash no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)(hash_cantidad(hash)),0));
    (*pruebas_totales)++;
    printf("El hash tiene 8 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),8));
    (*pruebas_totales)++;
    printf("La capacidad del hash no es 1, entonces rehasheo bien: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)hash->capacidad,1));
    (*pruebas_totales)++;
    printf("La capacidad del hash deberia ser 2: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)hash->capacidad,2));
    (*pruebas_totales)++;
    printf("Inserto 100 elementos mas\n");
    for (int i = 8; i < 108; ++i){
        hash_insertar(hash,strings[i], NULL);
    }
    printf("La capacidad del hash no es 2, entonces rehasheo bien: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)hash->capacidad,2));
    (*pruebas_totales)++;
    printf("La capacidad actual del hash es : %i\n",(int)hash->capacidad);
    printf("Elimino 100 elementos\n");
    for (int i = 8; i < 108; ++i){
        hash_quitar(hash,strings[i]);
    }
    printf("La capacidad del hash no es 32 , entonces rehasheo bien: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)hash->capacidad,32));
    printf("La capacidad actual del hash es : %i\n",(int)hash->capacidad);
    (*pruebas_totales)++;
    printf("Elimino 4 elementos\n");
    for (int i = 4; i < 8; ++i){
        hash_quitar(hash,strings[i]);
    }
    printf("La capacidad del hash no es 16 , entonces rehasheo bien: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)hash->capacidad,16));
    printf("La capacidad actual del hash es : %i\n",(int)hash->capacidad);
    (*pruebas_totales)++;
    hash_destruir(hash);
    return pruebas_pasadas;
}


int pruebas_volumen(hash_t* hash,int* pruebas_totales){
    int pruebas_pasadas=0;
    char strings [1000][10];
    for (int i = 0; i < 1000; ++i) {
        sprintf(strings[i],"%d", i);
    }
    printf("\n");
    printf("Chequeo un caso en el que se insertan muchos elementos: \n");
    printf("Creo un hash: \n");
    hash = hash_crear(NULL, 1);
    printf("Se creo correctamente el hash: ");
    pruebas_pasadas+=resultados_prueba(hash!=NULL);
    (*pruebas_totales)++;
    printf("Inserto 1000 elementos\n");
    for (int i = 0; i < 1000; ++i){
        hash_insertar(hash,strings[i], NULL);
    }
    printf("El hash no esta vacio: ");
    pruebas_pasadas+=resultados_prueba(!comparador_enteros((int)(hash_cantidad(hash)),0));
    (*pruebas_totales)++;
    printf("%i\n", (int)(hash_cantidad(hash)));
    printf("El hash tiene 1000 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),1000));
    (*pruebas_totales)++;
    printf("Elimino 500 elementos\n");
    for (int i = 500; i < 1000; ++i){
        hash_quitar(hash,strings[i]);
    }
    printf("El hash tiene 500 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),500));
    (*pruebas_totales)++;
    printf("Elimino 200 elementos\n");
    for (int i = 300; i < 500; ++i){
        hash_quitar(hash,strings[i]);
    }
    printf("El hash tiene 300 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),300));
    (*pruebas_totales)++;
    printf("Elimino 100 elementos\n");
    for (int i = 200; i < 300; ++i){
        hash_quitar(hash,strings[i]);
    }    
    printf("El hash tiene 200 elementos: ");
    pruebas_pasadas+=resultados_prueba(comparador_enteros((int)(hash_cantidad(hash)),200));
    (*pruebas_totales)++;
    hash_destruir(hash);
    return pruebas_pasadas;
}


int main(){
    int pruebas_totales=0;
    int pruebas_pasadas=0;
    hash_t* hash = NULL;
    printf("\t\t\t\tPruebas hash\n\n");
    pruebas_pasadas+=pruebas_casos_borde(hash,&pruebas_totales);
    pruebas_pasadas+=pruebas_elementos_NULL(hash,&pruebas_totales);
    pruebas_pasadas+=pruebas_caso_promedio(hash,&pruebas_totales);
    pruebas_pasadas+=pruebas_rehash(hash,&pruebas_totales);
    pruebas_pasadas+=pruebas_volumen(hash,&pruebas_totales);
    hash_destruir(hash);
    printf("\nFin de las pruebas\n");
    printf("\nPasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
  return 0;
}