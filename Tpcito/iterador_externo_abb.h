#ifndef __ITERADOR_EXTERNO_ARBOL_BINARIO_DE_BUSQUEDA_H__
#define __ITERADOR_EXTERNO_ARBOL_BINARIO_DE_BUSQUEDA_H__

#include <stdbool.h>
#include <stddef.h>
#include "abb.h"


typedef struct abb_iterador abb_iterador_t;

/*
 * Crea un iterador para un abb. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique el abb iterado (agregando o quitando
 * elementos del abb).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
abb_iterador_t* abb_iterador_crear(abb_t* abb);

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador);

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* abb_iterador_siguiente(abb_iterador_t* iterador);

/*
 * Libera la memoria reservada por el iterador.
 */
void abb_iterador_destruir(abb_iterador_t* iterador);

#endif /* __ITERADOR_EXTERNO_ARBOL_BINARIO_DE_BUSQUEDA_H__ */
