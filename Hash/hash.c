#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "hash.h"
#include "struct_hash.h"

#define FUNCIONO 0
#define ERROR -1
#define CANTIDAD_INICIAL_CLAVES 0
#define FACTOR_DE_CARGA_MAXIMO 6
#define FACTOR_DE_AUMENTO_REHASH 2
#define FACTOR_DE_DISMINUCION_REHASH 2


typedef struct par_clave_valor{
	void* clave;
	void* valor;
	hash_destruir_dato_t destructor;
}par_clave_valor_t;

void destruir_par_clave_valor(void* elemento){
  if(elemento){
  	par_clave_valor_t* aux=(par_clave_valor_t*)elemento;
  	if(aux->destructor!=NULL){
  		aux->destructor(aux->valor);
  	}
  	free(aux->clave);
    free(elemento);
  }
}


int comparar_claves(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2){
        return 0;
    }    
    if((strcmp((((par_clave_valor_t*)elemento1)->clave),(((par_clave_valor_t*)elemento2)->clave)))>0){
        return 1;
    }else if((strcmp((((par_clave_valor_t*)elemento1)->clave),(((par_clave_valor_t*)elemento2)->clave)))<0){
        return -1;
    }else{
        return 0;
    }
}

void destruir_solo_par_y_clave(void* elemento){
  	if(elemento){
  		par_clave_valor_t* aux=(par_clave_valor_t*)elemento;
  		free(aux->clave);
  		free(elemento);
	}
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento);
void hash_destruir(hash_t* hash);
extern char* strdup(const char*);

/*
 * Crea el hash reservando la memoria necesaria para el.
 * Destruir_elemento es un destructor que se utilizará para liberar
 * los elementos que se eliminen del hash.
 * Capacidad indica la capacidad minima inicial con la que se crea el hash.
 * Devuelve un puntero al hash creado o NULL en caso de no poder crearlo.
 */
hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
	hash_t* hash=malloc(sizeof(hash_t));
	if (hash==NULL)	{
		return NULL;
	}
	hash->destructor=destruir_elemento;
	hash->capacidad=capacidad;
	hash->cantidad_claves=CANTIDAD_INICIAL_CLAVES;
	hash->tabla_hash=malloc(sizeof(abb_t*)*hash->capacidad);
	if (hash->tabla_hash==NULL){
		free(hash);
		return NULL;
	}
	int i=0;
	while(i<hash->capacidad){
		hash->tabla_hash[i]=arbol_crear(comparar_claves,destruir_par_clave_valor);
		if (hash->tabla_hash[i]==NULL){
			for (int j = 0; j < i-1 ; ++i){
				arbol_destruir(hash->tabla_hash[j]);
			}
			free(hash->tabla_hash);
			free(hash);
			return NULL;
		}
		i++;
	}
	return hash;
}

/*
 * Crea el par clave elemento reservando la memoria necesaria para el.
 * Devuelve un puntero al par creado o NULL en caso de no poder crearlo.
 */
par_clave_valor_t* crear_par_clave_valor(void* clave, void* valor,hash_destruir_dato_t destructor){
    par_clave_valor_t* par_clave_valor=malloc(sizeof(par_clave_valor_t));
    if(par_clave_valor!=NULL){
        par_clave_valor->valor=valor;
        par_clave_valor->clave=clave;
        par_clave_valor->destructor=destructor;
    }
    return par_clave_valor;
}

/*
 * La funcion realiza la funcion hash, devuelve la posicion en el vector que le corresponde a esa clave
 */
size_t funcion_hash(const char* clave, size_t capacidad){
	const unsigned char* puntero;
	size_t valor_hash=0;
  	for (puntero = (const unsigned char *) clave; *puntero; puntero++){
    	valor_hash = *puntero + 31 * valor_hash;
	}
	valor_hash=valor_hash%capacidad;
	return valor_hash;
}

/*
 * La funcion se encarga de insertar los elementos de los arboles del hash en un vector
 * Al terminar de iterar un arbol se llama al vector desde la primera posicion donde no hay elementos
 * Devuelve el vector con todos los elementos
 */
void insertar_elementos_en_el_vector_rehash(hash_t* hash,void** vector){
	int elementos=0;	
	for (int i = 0; i < hash->capacidad; ++i){
		elementos+=arbol_recorrido_inorden(hash->tabla_hash[i],vector+elementos,(int)hash->cantidad_claves);
	}
}


/*
 * La funcion se encarga de realizar el rehash
 * Se crea un nuevo hash y se le insertan los elementos del viejo 
 * Devuelve el hash con su nuevo tamaño y con los elementos en su nueva posicion
 * Devuelve 0 si funciono correctamente  o -1 si no.
 */

int rehash(hash_t* hash_a_rehashear,size_t nueva_capacidad){
	hash_t* aux=hash_crear(hash_a_rehashear->destructor, nueva_capacidad);
	if(aux==NULL){
		return ERROR;
	}
	void** elementos_hash=calloc(hash_a_rehashear->cantidad_claves,sizeof(void*));
	if (elementos_hash==NULL){
		hash_destruir(aux);
		return ERROR;
	}
	insertar_elementos_en_el_vector_rehash(hash_a_rehashear,elementos_hash);
	for (int i = 0; i < hash_a_rehashear->cantidad_claves; ++i){
		par_clave_valor_t* par=(par_clave_valor_t*)(elementos_hash[i]);
		if(hash_insertar(aux,par->clave,par->valor)){ //De funcionar correctamente, devolveria 0 y no haria el return error
			hash_destruir(aux);
			free(elementos_hash);
			return ERROR;
		}
	}	
	abb_t** auxiliar_tabla=NULL;
	auxiliar_tabla=hash_a_rehashear->tabla_hash;
	hash_a_rehashear->tabla_hash=aux->tabla_hash;
	aux->tabla_hash=auxiliar_tabla;
	aux->capacidad=hash_a_rehashear->capacidad;	
	for(int j=0;j < aux->capacidad; j++){
		aux->tabla_hash[j]->destructor = destruir_solo_par_y_clave;
	}
	hash_destruir(aux);
	free(elementos_hash);
	hash_a_rehashear->capacidad=nueva_capacidad;
	return FUNCIONO;
}

/*
 * Inserta un elemento reservando la memoria necesaria para el mismo.
 * Devuelve 0 si pudo guardarlo o -1 si no pudo.
 */
int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	if (hash==NULL){
		return ERROR;
	}
	if (clave==NULL){
		return ERROR;
	}
	size_t posicion=0;
	int inserto=0;
	size_t factor_de_carga=hash->cantidad_claves/hash->capacidad;
	if(factor_de_carga<FACTOR_DE_CARGA_MAXIMO){
		void* aux_clave=strdup(clave);
		par_clave_valor_t* par=crear_par_clave_valor(aux_clave,elemento,hash->destructor);
		if(par==NULL){
			return ERROR;
		}
		posicion=funcion_hash(clave,hash->capacidad);
		if(arbol_buscar(hash->tabla_hash[posicion],par)==NULL){
			inserto=arbol_insertar(hash->tabla_hash[posicion],par);
			(hash->cantidad_claves)++;
		}else{
			arbol_borrar(hash->tabla_hash[posicion],par);
			inserto=arbol_insertar(hash->tabla_hash[posicion],par);
		}
	}else{	//Caso rehash
		int funciono_rehash=rehash(hash,(hash->capacidad)*FACTOR_DE_AUMENTO_REHASH);
		if(!funciono_rehash){ //Lo niego ya que FUNCIONO tiene valor 0
			return hash_insertar(hash,clave,elemento);
		}else{
			inserto=ERROR;
		}
	}
	return inserto;	
}

/*
 * Quita un elemento del hash e invoca la funcion destructora
 * pasandole dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 si no pudo.
 */
int hash_quitar(hash_t* hash, const char* clave){
	if (hash==NULL){
		return ERROR;
	}
	size_t posicion=0;
	int borro=0;
	void* aux_clave=strdup(clave);
	par_clave_valor_t* aux=crear_par_clave_valor(aux_clave,NULL,hash->destructor);
	posicion=funcion_hash(clave,hash->capacidad);	
	if ((arbol_buscar(hash->tabla_hash[posicion],aux))==NULL){
		borro=ERROR;
		free(aux);
	}else{
		borro=arbol_borrar(hash->tabla_hash[posicion],aux);
		free(aux);
		(hash->cantidad_claves)--;
	}
	if((((hash->cantidad_claves)*2)<(hash->capacidad))&&(borro==FUNCIONO)){//Caso rehash
		int funciono_rehash=rehash(hash,(hash->capacidad)/FACTOR_DE_DISMINUCION_REHASH);
		if(!funciono_rehash){ //Lo niego ya que FUNCIONO tiene valor 0
			borro=FUNCIONO;
		}else{
			borro=ERROR;
		}
	}
	free(aux_clave);
	return borro;
}

/*
 * Devuelve un elemento del hash con la clave dada o NULL si dicho
 * elemento no existe.
 */
void* hash_obtener(hash_t* hash, const char* clave){
	if (hash==NULL){
		return NULL;
	}
	size_t posicion=0;
	void* aux_clave=strdup(clave);
	par_clave_valor_t* aux=crear_par_clave_valor(aux_clave,NULL,hash->destructor);
	posicion=funcion_hash(clave,hash->capacidad);
	void* elemento=arbol_buscar(hash->tabla_hash[posicion],aux);
	free(aux_clave);
	free(aux);
	if (elemento==NULL){
		return NULL;
	}else{
		return ((par_clave_valor_t*)elemento)->valor;
	}
}

/*
 * Devuelve true si el hash contiene un elemento almacenado con la
 * clave dada o false en caso contrario.
 */
bool hash_contiene(hash_t* hash, const char* clave){
	return (hash_obtener(hash,clave)!=NULL);  //Por como esta implementado hash_obtener, si hash es NULL, retorna NULL.
}

/*
 * Devuelve la cantidad de elementos almacenados en el hash.
 */
size_t hash_cantidad(hash_t* hash){
	if (hash==NULL){
		return 0;
	}
	return (hash->cantidad_claves);
}

/*
 * Destruye el hash liberando la memoria reservada y asegurandose de
 * invocar la funcion destructora con cada elemento almacenado en el
 * hash.
 */
void hash_destruir(hash_t* hash){
	if (hash!=NULL){
		for (int i = 0; i < hash->capacidad; ++i){
			arbol_destruir(hash->tabla_hash[i]);			
		}
		free(hash->tabla_hash);
		free(hash);
	}
}
