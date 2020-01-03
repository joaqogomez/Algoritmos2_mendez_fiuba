#include <stdbool.h>
#include <stdlib.h>
#define FUNCIONO 0
#define ERROR -1
#define CANTIDAD_INICIAL_ELEMENTOS 0
#define TAMANIO_INICIAL 4
typedef struct pila {
	int tope;
	void** elementos;
	int tamanio;
} pila_t;

/* 
 * Crea una pila, reservando la memoria necesaria para almacenar la
 * estructura.
 * Devuelve un puntero a la estructura pila_t creada o NULL si no pudo
 * crearla.
 */
pila_t* pila_crear(){
	pila_t* pila=malloc(sizeof(pila_t));
	if(pila==NULL){
		return NULL;
	}
	pila->elementos=malloc(TAMANIO_INICIAL*sizeof(void*));
	if (pila->elementos==NULL){
		free(pila);
		return NULL;
	}
	pila->tope=CANTIDAD_INICIAL_ELEMENTOS;
	pila->tamanio=TAMANIO_INICIAL;
	return pila;
}
//La funcion se encarga de acortar o alagar el vector segun se necesite.
//Devuelve 0 si funciono correctamente o -1 si hubo algun error
int redimensionar_vector(void*** vector, int nuevo_tamanio){
	void** aux;
	aux=realloc(*vector,(unsigned)nuevo_tamanio*sizeof(void*));
	if (aux==NULL){
		return ERROR;
	}
	(*vector)=aux;
	return FUNCIONO;
}
/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 * Si no hay espacio para poner un nuevo elemento, se duplica el tamaño del vector.
 */
int pila_apilar(pila_t* pila, void* elemento){
	if(pila==NULL){
		return ERROR;
	}
	if((pila->tamanio)==(pila->tope)){
		if(!redimensionar_vector(&(pila->elementos),((pila->tamanio)*2))){
			(pila->tamanio)*=2;
		}else{
			return ERROR;
		}
	}
	pila->elementos[(pila->tope)]=elemento;
	(pila->tope)++;
	return FUNCIONO;
}

/* 
 * Determina si la pila está vacia.
 * Devuelve true si está vacía, false en caso contrario.
 * Si la pila no existe devolverá true.
 */
bool pila_vacia(pila_t* pila){
	if(pila==NULL){
		return true;
	}
	return ((pila->tope)==0);
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 * Al desapilar, si el vector esta ocupado en un 25%, este se achica a la mitad.
 */
int pila_desapilar(pila_t* pila){
	if((pila==NULL)||(pila_vacia(pila))){
		return ERROR;
	}
	if((pila->tamanio)>=(pila->tope*4)){
		if(!redimensionar_vector(&(pila->elementos),((pila->tamanio)/2))){
			(pila->tamanio)/=2;
		}else{
			return ERROR;
		}
	}
	(pila->tope)--;
	return FUNCIONO;
}

/* 
 * Devuelve la cantidad de elementos almacenados en la pila.
 * Si la pila no existe devolverá 0.
 */
int pila_cantidad(pila_t* pila){
	if(pila==NULL){
		return 0;
	}
	return (pila->tope);
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 * Si la pila no existe devolverá NULL.
 */
void* pila_tope(pila_t* pila){
	if(pila==NULL){
		return NULL;
	}
	if(pila_vacia(pila)){
		return NULL;
	}else{
		return (pila->elementos[(pila->tope)-1]);
	}
}

/* 
 * Destruye la pila liberando la memoria reservada para la misma.
 */
void pila_destruir(pila_t* pila){
	if(pila!=NULL){
		free(pila->elementos);
		free(pila);
	}
}


