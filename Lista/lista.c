#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#define FUNCIONO 0
#define ERROR -1
#define CANTIDAD_INICIAL_ELEMENTOS 0
typedef struct lista lista_t;
typedef struct lista_iterador lista_iterador_t;

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

struct lista{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	int cantidad_elementos;
};
struct lista_iterador{
	nodo_t* corriente;
	lista_t* lista;
};
/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	lista_t* lista=malloc(sizeof(lista_t));
	if(lista==NULL){
		return NULL;
	}
	lista->nodo_inicio=NULL;
	lista->nodo_fin=NULL;
	lista->cantidad_elementos=CANTIDAD_INICIAL_ELEMENTOS;
	return lista;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(lista==NULL){
		return true; //Como no existe, esta vacia, ya que no hay elementos guardados en ningun lado
	}
	return ((lista->cantidad_elementos)==0);
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(lista==NULL){
		return ERROR;
	}
	nodo_t* nuevo_nodo=malloc(sizeof(nodo_t));
	if (nuevo_nodo==NULL){
		return ERROR;
	}
	nuevo_nodo->elemento=elemento;
	nuevo_nodo->siguiente=NULL;
	if (lista_vacia(lista)){
		nuevo_nodo->siguiente=lista->nodo_inicio;
		lista->nodo_inicio=nuevo_nodo;
		lista->nodo_fin=nuevo_nodo;
	}else{
			lista->nodo_fin->siguiente=nuevo_nodo;
			lista->nodo_fin=nuevo_nodo;
	}
	(lista->cantidad_elementos)++;
	return FUNCIONO;
}

/*
 * Recorre los nodos hasta llegar al nodo donde se necesita realizar las diferentes operaciones
 */
void recorrer_lista(nodo_t** nodo, int posicion){
    for (int i = 0; i < posicion; ++i){
    	if ((*nodo)!=NULL){
        	(*nodo)=(*nodo)->siguiente;
        }
    }
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(lista==NULL){
		return ERROR;
	}
	if((int)posicion>((lista->cantidad_elementos)-1)){
		int inserto=lista_insertar(lista,elemento);
		return inserto;
	}
	nodo_t* nuevo_nodo=malloc(sizeof(nodo_t));
	if (nuevo_nodo==NULL){
		return ERROR;
	}
	nuevo_nodo->siguiente=NULL;
	nuevo_nodo->elemento=elemento;
	if (posicion==0){
		nuevo_nodo->siguiente=lista->nodo_inicio;
		lista->nodo_inicio=nuevo_nodo;
	}else{
		nodo_t* aux=lista->nodo_inicio;
		recorrer_lista(&aux,(int)posicion-1);
		nuevo_nodo->siguiente=aux->siguiente;
		aux->siguiente=nuevo_nodo;
	}
	(lista->cantidad_elementos)++;
	return FUNCIONO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if((lista==NULL)||(lista_vacia(lista))){
		return ERROR;
	}
	nodo_t* aux=lista->nodo_inicio;
	recorrer_lista(&aux,(lista->cantidad_elementos)-2);
	if(lista->cantidad_elementos==1){
		free(aux);
		lista->nodo_inicio=NULL;
		lista->nodo_fin=NULL;
		(lista->cantidad_elementos)--;
		return FUNCIONO;
	}
	lista->nodo_fin=aux;	
	free(aux->siguiente);
	lista->nodo_fin->siguiente=NULL;
	(lista->cantidad_elementos)--;
	return FUNCIONO;		
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if((lista==NULL)||(lista_vacia(lista))){
		return ERROR;
	}
	if(posicion>=((lista->cantidad_elementos)-1)){
		int borro=lista_borrar(lista);
		return borro;
	}
	nodo_t* aux=lista->nodo_inicio;
	if (posicion==0){
		lista->nodo_inicio=aux->siguiente;
		free(aux);		
	}else{
		recorrer_lista(&aux,(int)posicion-1);
		nodo_t* nodo_a_borrar=aux->siguiente;
		aux->siguiente=nodo_a_borrar->siguiente;
		free(nodo_a_borrar);
	}
	(lista->cantidad_elementos)--;
	return FUNCIONO;
}


/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if((lista==NULL)||(lista_vacia(lista))){
		return NULL;
	}
	if(posicion>((lista->cantidad_elementos)-1)){
		return NULL;
	}
	nodo_t* aux=lista->nodo_inicio;
	if (posicion==0){
		return aux->elemento;
	}else{
		recorrer_lista(&aux,(int)posicion);
		return aux->elemento;
	}
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if((lista==NULL)||(lista_vacia(lista))){
		return NULL;
	}
	return (lista->nodo_fin->elemento);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(lista==NULL){
		return 0;
	}
	return (size_t)(lista->cantidad_elementos);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	if(lista!=NULL){
		while((!lista_vacia(lista))&&(lista_borrar(lista)==0));
		free(lista);
	}
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(lista==NULL){
		return NULL;
	}
	lista_iterador_t* iterador=malloc(sizeof(lista_iterador_t));
	if (iterador==NULL){
		return NULL;
	}
	iterador->lista=lista;
	iterador->corriente=lista->nodo_inicio;
	return iterador;
}	

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if (iterador!=NULL){
		return (iterador->corriente!=NULL);
	}else{
		return false; //Como el iterador no existe, no puede tener siguiente.
	}
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if (iterador!=NULL){
		if (lista_iterador_tiene_siguiente(iterador)){
			void* elemento=iterador->corriente->elemento;
			iterador->corriente=iterador->corriente->siguiente;
			return elemento;
		}else{
			return NULL;
		}
	}else{
		return NULL;
	}

}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	lista_iterador_t* iterador=lista_iterador_crear(lista);
	if (iterador!=NULL){
	while ( lista_iterador_tiene_siguiente(iterador) ){
			void * elemento = lista_iterador_siguiente(iterador);
			funcion(elemento);
		}
	}
	lista_iterador_destruir(iterador);
}
