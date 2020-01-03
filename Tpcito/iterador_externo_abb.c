#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"

typedef struct abb_iterador abb_iterador_t;

struct abb_iterador{
	nodo_abb_t* corriente;
	nodo_abb_t* nodo_sin_visitar;
	abb_t* abb;
	pila_t* pila;
	bool visite_raiz;
	bool primera_iteracion;
};

/*
 * La funcion se encarga de apilar los hijos izquierdos de un nodo en una pila.
 * Si el nodo no tiene hijos izquierdos, devuelve false. Si tiene, los apila y devuelve true
 */
bool apilar_hijos_izquierdos(pila_t* pila,nodo_abb_t* corriente){
	bool apilo=false;
	nodo_abb_t* aux=corriente;	
	while (aux!=NULL){
		if (aux->izquierda!=NULL){
			pila_apilar(pila,(void*)aux->izquierda);
			apilo=true;	
		}
		aux=aux->izquierda;				
	}
	return apilo;
}

/*
 * Crea un iterador para un abb. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique el abb iterado (agregando o quitando
 * elementos del abb).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
abb_iterador_t* abb_iterador_crear(abb_t* abb){
	if(abb==NULL){
		return NULL;
	}
	abb_iterador_t* iterador=malloc(sizeof(abb_iterador_t));
	if (iterador==NULL){
		return NULL;
	}
	iterador->visite_raiz=false;
	iterador->primera_iteracion=true;
	iterador->abb=abb;
	iterador->corriente=iterador->abb->nodo_raiz;
	iterador->pila=pila_crear();
	if(iterador->pila==NULL){
		free(iterador);
		return NULL;
	}
	if(!arbol_vacio(iterador->abb)){
		if(apilar_hijos_izquierdos(iterador->pila,iterador->corriente)){
			iterador->corriente=pila_tope(iterador->pila);
		}
	}
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador){
	if (iterador==NULL){
		return false;
	}
	if(arbol_vacio(iterador->abb)){
		return false;
	}
	if (pila_vacia(iterador->pila)&&(iterador->corriente->derecha==NULL)&&(!iterador->primera_iteracion)){
		return false;
	}else{
		return true;
	}
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* abb_iterador_siguiente(abb_iterador_t* iterador){
	if(iterador==NULL){
		return NULL;
	}
	if(arbol_vacio(iterador->abb)){
		return NULL;
	}
	if(!abb_iterador_tiene_siguiente(iterador)){
		return NULL;
	}
	if(!iterador->primera_iteracion){
		if(iterador->corriente->derecha==NULL){
			pila_desapilar(iterador->pila);
			if (pila_cantidad(iterador->pila)!=0){
				iterador->corriente=pila_tope(iterador->pila);
			}else{
				if(!iterador->visite_raiz){
					iterador->corriente=iterador->abb->nodo_raiz;
					iterador->visite_raiz=true;
					iterador->nodo_sin_visitar=iterador->abb->nodo_raiz->derecha;
				}else{
					iterador->corriente=iterador->nodo_sin_visitar;
				}			
			}
		}else{
			iterador->corriente=iterador->corriente->derecha;
			if (apilar_hijos_izquierdos(iterador->pila,iterador->corriente)){
				iterador->nodo_sin_visitar=iterador->corriente;
				iterador->corriente=pila_tope(iterador->pila);
			}
		}
		void* elemento=iterador->corriente->elemento;
		return elemento;
	}else{
		void* elemento=iterador->corriente->elemento;
		iterador->primera_iteracion=false;
		return elemento;
	}
}

/*
 * Libera la memoria reservada por el iterador.
 */
void abb_iterador_destruir(abb_iterador_t* iterador){
	if(iterador!=NULL){
		pila_destruir(iterador->pila);
		free(iterador);
	}
}