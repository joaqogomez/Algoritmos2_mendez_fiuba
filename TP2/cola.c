#include <stdlib.h>
#include <stdbool.h>
#define FUNCIONO 0
#define ERROR -1
#define CANTIDAD_INICIAL_ELEMENTOS 0

typedef void (*cola_destructor)(void*);

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

typedef struct cola {
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	int cantidad;
	cola_destructor destructor;
} cola_t;
/* 
 * Crea una cola reservando la memoria necesaria
 * para almacenar la estructura.
 * Devuelve un puntero a la estructura cola_t creada.
 */
cola_t* cola_crear(cola_destructor destructor){
	cola_t* cola=malloc(sizeof(cola_t));
	if(cola==NULL){
		return NULL;
	}
	cola->nodo_inicio=NULL;
	cola->nodo_fin=NULL;
	cola->cantidad=CANTIDAD_INICIAL_ELEMENTOS;
	cola->destructor=destructor;
	return cola;
}

/* 
 * Determina si la cola está vacia.
 * Devuelve true si está vacía y false si no.
 * Si la cola no existe devolverá true.
 */
bool cola_vacia(cola_t* cola){
	if(cola==NULL){
		return true;
	}
	return ((cola->cantidad)==0);
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento){
	if(cola==NULL){
		return ERROR;
	}
	nodo_t* nuevo_nodo=malloc(sizeof(nodo_t));
	if (nuevo_nodo==NULL){
		return ERROR;
	}
	nuevo_nodo->elemento=elemento;
	if (cola_vacia(cola)){
		nuevo_nodo->siguiente=cola->nodo_inicio;
		cola->nodo_inicio=nuevo_nodo;
		cola->nodo_fin=nuevo_nodo;
	}else{
		cola->nodo_fin->siguiente=nuevo_nodo;
		cola->nodo_fin=nuevo_nodo;
	}
	(cola->cantidad)++;
	return FUNCIONO;
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola){
	if((cola==NULL)||(cola_vacia(cola))){
		return ERROR;
	}
	nodo_t* aux;
	aux=cola->nodo_inicio;
	if(cola->destructor!=NULL){
		cola->destructor(aux->elemento);
	}
	cola->nodo_inicio=cola->nodo_inicio->siguiente;
	free(aux);
	(cola->cantidad)--;
	return FUNCIONO;
}

/* 
 * Devuelve la cantidad de elementos almacenados en la cola.
 * Si la cola no existe devolverá 0.
 */
int cola_cantidad(cola_t* cola){
	if(cola==NULL){
		return 0;
	}
	return (cola->cantidad);
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 * Si la cola no existe devolverá NULL.
 */
void* cola_primero(cola_t* cola){
	if((cola==NULL)||(cola_vacia(cola))){
		return NULL;
	}
	return (cola->nodo_inicio->elemento);
}

/* 
 * Destruye la cola liberando toda la memoria reservada
 * por la cola.
 */
void cola_destruir(cola_t* cola){
	if (cola!=NULL){
		while(cola_desencolar(cola)==0);
		free(cola);
	}
}
