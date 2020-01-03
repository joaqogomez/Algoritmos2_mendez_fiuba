#include <stdbool.h>
#include "hash.h"
#include "abb.h"
#include "struct_hash.h"

/* Iterador externo para el HASH */
typedef struct hash_iter hash_iterador_t;

struct hash_iter{	
	hash_t* hash;
	void** elementos;
	size_t posicion_actual;
};

typedef struct par_clave_valor{
	const char* clave;
	void* valor;
	void (*hash_destruir_dato_t)(void*);
}par_clave_valor_t;

/*
 * La funcion se encarga de insertar los elementos de los arboles del hash en un vector
 * Al terminar de iterar un arbol se llama al vector desde la primera posicion donde no hay elementos
 * Devuelve el vector con todos los elementos
 */
void insertar_elementos_en_el_vector(hash_t* hash,void** vector){
	int elementos=0;	
	for (int i = 0; i < hash->capacidad; ++i){
		elementos+=arbol_recorrido_inorden(hash->tabla_hash[i],vector+elementos,(int)hash->cantidad_claves);
	}
}


/*
 * Crea un iterador de claves para el hash reservando la memoria
 * necesaria para el mismo. El iterador creado es válido desde su
 * creación hasta que se modifique la tabla de hash (insertando o
 * removiendo elementos);
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
hash_iterador_t* hash_iterador_crear(hash_t* hash){
	if (hash==NULL){
		return NULL;
	}	
	hash_iterador_t* iterador=malloc(sizeof(hash_iterador_t));
	if (iterador==NULL){
		return NULL;
	}
	iterador->posicion_actual=0;
	iterador->hash=hash;
	iterador->elementos=calloc(hash->cantidad_claves,sizeof(void*));
	if (iterador->elementos==NULL){
		return NULL;
	}
	insertar_elementos_en_el_vector(iterador->hash,iterador->elementos);
	return iterador;
}

/*
 * Devuelve la próxima clave almacenada en el hash y avanza el iterador.
 * Devuelve la clave o NULL si no habia mas.
 */
void* hash_iterador_siguiente(hash_iterador_t* iterador){
	if (iterador==NULL){
		return NULL;
	}
	par_clave_valor_t* aux=NULL;	
	if ((iterador->posicion_actual)<(iterador->hash->cantidad_claves)){
		aux=(par_clave_valor_t*)(iterador->elementos[(iterador->posicion_actual)]);
		(iterador->posicion_actual)++;
		return (void*)aux->clave;
	}else{
		return NULL;
	}
}

/*
 * Devuelve true si quedan claves por recorrer o false en caso
 * contrario.
 */
bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
	if (iterador==NULL){
		return false;
	}
	return ((iterador->posicion_actual)<(iterador->hash->cantidad_claves));
}

/*
 * Destruye el iterador del hash.
 */
void hash_iterador_destruir(hash_iterador_t* iterador){
	if (iterador!=NULL){
		free(iterador->elementos);
		free(iterador);
	}
}
