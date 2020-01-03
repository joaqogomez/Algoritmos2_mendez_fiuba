#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2
#define MAYOR 1
#define IGUALES 0
#define MENOR -1
#define FUNCIONO 0
#define ERROR -1

#include <stdbool.h>
#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*abb_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*abb_liberar_elemento)(void*);


typedef struct nodo_abb {
  void* elemento;
  struct nodo_abb* izquierda;
  struct nodo_abb* derecha;
} nodo_abb_t;

typedef struct abb{
  nodo_abb_t* nodo_raiz;
  abb_comparador comparador;
  abb_liberar_elemento destructor;
} abb_t;

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* arbol=malloc(sizeof(abb_t));
	if (arbol==NULL){
		return NULL;
	}
	arbol->nodo_raiz=NULL;
	if(comparador!=NULL){
		arbol->comparador=comparador;
	}else{
		free(arbol);
		return NULL;
	}
	arbol->destructor=destructor;
	return arbol;
}

/*
 * Determina si el árbol está vacío. 
 * Devuelve true si lo está, false en caso contrario.
 */

bool arbol_vacio(abb_t* arbol){
	if (arbol==NULL){
 		return true;
 	}
 	return (arbol->nodo_raiz==NULL);
}

/*
 * La funcion inserta un elemento en el arbol.
*/

void* insertar_rec(nodo_abb_t* nodo_actual,nodo_abb_t* nodo_a_insertar,abb_comparador comparador){
	if (nodo_actual==NULL){
		return nodo_a_insertar;
	}
	if (comparador(nodo_a_insertar->elemento,nodo_actual->elemento)==MENOR){
		nodo_actual->izquierda=insertar_rec(nodo_actual->izquierda,nodo_a_insertar,comparador);
	}else if (comparador(nodo_a_insertar->elemento,nodo_actual->elemento)==MAYOR){
		nodo_actual->derecha=insertar_rec(nodo_actual->derecha,nodo_a_insertar,comparador);
	}else{
		nodo_actual->derecha=insertar_rec(nodo_actual->derecha,nodo_a_insertar,comparador); //si son iguales va a derecha
	}
	return nodo_actual;
}

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */

 int arbol_insertar(abb_t* arbol, void* elemento){
 	if (arbol==NULL){
 		return ERROR;
 	}
 	nodo_abb_t* nodo=malloc(sizeof(nodo_abb_t));
 	if (nodo==NULL){
 		return ERROR;
 	}
 	nodo->elemento=elemento;
 	nodo->izquierda=NULL;
 	nodo->derecha=NULL;
 	if (arbol_vacio(arbol)){
 		arbol->nodo_raiz=nodo;
 	}else{
 		insertar_rec(arbol->nodo_raiz, nodo, arbol->comparador);
 	}
 	return FUNCIONO;
 }

 /*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 * 
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */

void* buscar_rec (nodo_abb_t* nodo, void* elemento,abb_comparador comparador){
	if (nodo==NULL){
		return NULL;
	}
	if (comparador(elemento,nodo->elemento)==MENOR){
		return buscar_rec(nodo->izquierda,elemento,comparador);
	}
	if (comparador(elemento,nodo->elemento)==MAYOR){
		return buscar_rec(nodo->derecha,elemento,comparador);
	}
	return nodo->elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if (arbol==NULL){
 		return NULL;
 	}
 	return buscar_rec(arbol->nodo_raiz,elemento,arbol->comparador);
}

/*
 * La funcion se encarga de encontrar el mayor de los menores y pone en ese lugar al elemento que estaba queriendo borrar
*/
void* busco_mayor_de_los_menores_e_intercambio(nodo_abb_t* nodo,void* elemento){
	if (nodo->derecha==NULL){
		void* aux=nodo->elemento;
		nodo->elemento=elemento;
		return aux;
	}else{
		return busco_mayor_de_los_menores_e_intercambio(nodo->derecha,elemento);
	}
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.  
 */

void* borrar_rec(nodo_abb_t* nodo,void* elemento,abb_comparador comparador,abb_liberar_elemento destructor){
	if (nodo==NULL){
		return NULL;
	}
	if (comparador(elemento,nodo->elemento)==MENOR){
		nodo->izquierda=borrar_rec(nodo->izquierda,elemento,comparador,destructor);
		return nodo;
	}
	if (comparador(elemento,nodo->elemento)==MAYOR){
		nodo->derecha=borrar_rec(nodo->derecha,elemento,comparador,destructor);
		return nodo;
	}
	if ((nodo->izquierda==NULL)&&(nodo->derecha==NULL)){		// Caso nodo hoja
		if (destructor!=NULL){
			destructor(nodo->elemento);
		}
		free(nodo);
		return NULL;
	}else if ((nodo->izquierda!=NULL)&&(nodo->derecha!=NULL)){		// Caso tiene 2 hijos
		void* elemento_mayor_de_los_menores=busco_mayor_de_los_menores_e_intercambio(nodo->izquierda,nodo->elemento);
		nodo->elemento=elemento_mayor_de_los_menores;
		nodo->izquierda=borrar_rec(nodo->izquierda,elemento,comparador,destructor);
		return nodo;
	}else if ((nodo->izquierda!=NULL)||(nodo->derecha!=NULL)){		// Caso tiene un solo hijo 
		nodo_abb_t* nodo_aux=NULL;
		if(nodo->izquierda!=NULL){
			nodo_aux=nodo->izquierda;
		}else{
			nodo_aux=nodo->derecha;
		}
		if (destructor!=NULL){
			destructor(nodo->elemento);
		}
		free(nodo);
		return nodo_aux;
	}
	return nodo;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.  
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */

int arbol_borrar(abb_t* arbol, void* elemento){
	if (arbol==NULL){
 		return ERROR;
 	}
 	if (arbol_buscar(arbol,elemento)==NULL){
 		return ERROR;
 	}
 	arbol->nodo_raiz=borrar_rec(arbol->nodo_raiz,elemento,arbol->comparador,arbol->destructor);
 	return FUNCIONO;
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío.
 */

void* arbol_raiz(abb_t* arbol){
    if ((arbol==NULL)||(arbol_vacio(arbol))){
        return NULL;
    }
    return (arbol->nodo_raiz->elemento);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */

int arbol_recorrido_inorden_rec(nodo_abb_t* nodo, void** array, int tope, int cantidad_elementos){
	if (nodo==NULL){
		return cantidad_elementos;
	}
	cantidad_elementos=arbol_recorrido_inorden_rec(nodo->izquierda,array,tope,cantidad_elementos);
	if(cantidad_elementos<tope){
		array[cantidad_elementos]=nodo->elemento;
		cantidad_elementos++;
	}else{
		return tope;
	}
	cantidad_elementos=arbol_recorrido_inorden_rec(nodo->derecha,array,tope,cantidad_elementos);
	return cantidad_elementos;
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if ((arbol==NULL)||(arbol_vacio(arbol))){
 		return 0;
 	}
 	return	arbol_recorrido_inorden_rec(arbol->nodo_raiz, array, tamanio_array,0);
 }

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */

int arbol_recorrido_preorden_rec(nodo_abb_t* nodo, void** array, int tope, int cantidad_elementos){
	if (nodo==NULL){
		return cantidad_elementos;
	}
	if(cantidad_elementos<tope){
		array[cantidad_elementos]=nodo->elemento;
		cantidad_elementos++;
	}else{
		return tope;
	}
	cantidad_elementos=arbol_recorrido_preorden_rec(nodo->izquierda,array,tope,cantidad_elementos);
	cantidad_elementos=arbol_recorrido_preorden_rec(nodo->derecha,array,tope,cantidad_elementos);
	return cantidad_elementos;
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if ((arbol==NULL)||(arbol_vacio(arbol))){
 		return 0;
 	}
 	return	arbol_recorrido_preorden_rec(arbol->nodo_raiz, array, tamanio_array,0);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */

int arbol_recorrido_postorden_rec(nodo_abb_t* nodo, void** array, int tope, int cantidad_elementos){
	if (nodo==NULL){
		return cantidad_elementos;
	}
	cantidad_elementos=arbol_recorrido_postorden_rec(nodo->izquierda,array,tope,cantidad_elementos);
	cantidad_elementos=arbol_recorrido_postorden_rec(nodo->derecha,array,tope,cantidad_elementos);
	if(cantidad_elementos<tope){
		array[cantidad_elementos]=nodo->elemento;
		cantidad_elementos++;
	}else{
		return tope;
	}
	return cantidad_elementos;
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if ((arbol==NULL)||(arbol_vacio(arbol))){
 		return 0;
 	}
 	return	arbol_recorrido_postorden_rec(arbol->nodo_raiz, array, tamanio_array,0);
}

/*
 * Destruye los nodos del arbol liberando la memoria reservada para ellos.
 * Ademas llama al destructor con cada elemento
 */

void recorrer_postorden_y_eliminar_nodos(nodo_abb_t* nodo,abb_liberar_elemento destructor){
	if (nodo==NULL){
		return;
	}
	recorrer_postorden_y_eliminar_nodos(nodo->izquierda,destructor);
	recorrer_postorden_y_eliminar_nodos(nodo->derecha,destructor);
	if (destructor!=NULL){
		destructor(nodo->elemento);
	}
	free(nodo);
}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */

void arbol_destruir(abb_t* arbol){
	if (arbol!=NULL){
		if (!arbol_vacio(arbol)){
			recorrer_postorden_y_eliminar_nodos(arbol->nodo_raiz,arbol->destructor);
		}
		free(arbol);
	}
}
/*
 * Las funciones se van a encargar de iterar segun el recorrido correspondiente
*/

bool iterador_recorrido_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if (nodo==NULL){
		return true;
	}
	if (!iterador_recorrido_inorden(nodo->izquierda,funcion,extra)){
		return false;
	}
	if((*funcion)(nodo->elemento,extra)){
		return false;
	}
	if (!iterador_recorrido_inorden(nodo->derecha,funcion,extra)){
		return false;
	}			
	return true;
}

bool iterador_recorrido_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if (nodo==NULL){
		return true;
	}
	if((*funcion)(nodo->elemento,extra)){
		return false;
	}
	if (!iterador_recorrido_preorden(nodo->izquierda,funcion,extra)){
		return false;
	}
	if (!iterador_recorrido_preorden(nodo->derecha,funcion,extra)){
		return false;
	}
	return true;
}

bool iterador_recorrido_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if (nodo==NULL){
		return true;
	}
	if (!iterador_recorrido_postorden(nodo->izquierda,funcion,extra)){
		return false;
	}
	if (!iterador_recorrido_postorden(nodo->derecha,funcion,extra)){
		return false;
	}			
	if((*funcion)(nodo->elemento,extra)){
		return false;
	}
	return true;
}



/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el 
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if ((arbol==NULL)||(arbol_vacio(arbol))){
 		return;
 	}
 	switch(recorrido){
 		case ABB_RECORRER_INORDEN:
 		iterador_recorrido_inorden(arbol->nodo_raiz,(*funcion),extra);
 		break;
 		case ABB_RECORRER_PREORDEN:
		iterador_recorrido_preorden(arbol->nodo_raiz,(*funcion),extra);
 		break;
 		case ABB_RECORRER_POSTORDEN:
 		iterador_recorrido_postorden(arbol->nodo_raiz,(*funcion),extra);
 		break;
 		default:
 		return;
 	}
}