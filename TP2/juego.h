#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "abb.h"
#include "cola.h"

typedef struct juego {
	int cantidad_casas_vivas;
	abb_t* casas_vivas;
	cola_t* casas_extintas;
} juego_t;

/*
 * Crea el juego y reserva la memoria necesaria de la estructura.
 * Devuelve un puntero al juego creado o NULL en caso de error.
 */
juego_t* crear_juego(juego_t* juego);

/*
* La funcion recibe los años a simular y simula esa cantidad de años.
* Devuelve por pantalla quien fue el ganador.
*/
void realizar_simulacion(juego_t* juego,int anios_a_simular);

/*
* La funcion recibe un archivo de casas y las agrega al arbol del juego.
* Devuelve 0 si se produjo algun error o 1 si funciono correctamente.
*/
int ingresar_casas(juego_t* juego,char* nombre_archivo);

/*
* La funcion imprime por pantalla las casas que tienen personas, en orden descendente segun la cantidad de personas.
*/
void listar_casas(juego_t* juego);

/*
* La funcion imprime por pantalla las casas que no tienen personas, en el orden en que se quedaron sin personas.
*/
void mostrar_casas_extintas(juego_t* juego);

/*
 * Destruye el juego liberando la memoria reservada por el mismo.
 * Adicionalmente destruye todas las estructuras y elementos
 */
void destruir_juego(juego_t* juego);

#endif /* __JUEGO_H__ */