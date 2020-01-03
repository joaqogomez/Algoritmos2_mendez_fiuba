#include "lista.h"
#include "testing.h"
#include <stdio.h>

void mostrar_elemento(void* elemento){
  if(elemento)
    printf("%c ", *(char*)elemento);
}

int pruebas_catedra(lista_t* lista,int* pruebas_totales){
  int pruebas_pasadas=0;
  lista = lista_crear();
  char a='a', b='b', c='c', d='d', w='w';
  printf("Creo una lista, chequeo que se cree e inicialice correctamente\n");
  printf("Se creo correctamente la lista: ");
  pruebas_pasadas=resultados_prueba(lista!=NULL);
  (*pruebas_totales)++;
  printf("La lista no tiene elementos: ");
  if (comparador_enteros((int)lista_elementos(lista),0)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Inserto la letra 'a' en la ultima posicion\n");
  lista_insertar(lista, &a);  
  printf("Se inserto correctamente el elemento: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,0),'a')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("La lista no esta vacia: ");
  if (comparador_bool(lista_vacia(lista),false)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Inserto la letra 'c' en la ultima posicion\n");
  lista_insertar(lista, &c);
  printf("Se inserto correctamente el elemento: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,1),'c')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Inserto la letra 'd' en la posicion 100, al no existir, se inserta al final\n");
  lista_insertar_en_posicion(lista, &d, 100);
  printf("Se inserto correctamente el elemento: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,2),'d')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Chequeo que hay en la posicion 100, deberia devolver NULL: ");
  if (lista_elemento_en_posicion(lista,100)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Inserto la letra 'b' en la posicion 1\n");
  lista_insertar_en_posicion(lista, &b, 1);
  printf("Se inserto correctamente el elemento: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,1),'b')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Chequeo que la letra 'c' ahora este en la posicion 2: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,2),'c')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Inserto la letra 'w' en la posicion 3\n");
  lista_insertar_en_posicion(lista, &w, 3);
  printf("Se inserto correctamente el elemento: ");
  if (comparador_char(*(char*)lista_elemento_en_posicion(lista,3),'w')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("La lista tiene 5 elementos: ");
  if (comparador_enteros((int)lista_elementos(lista),5)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("El ultimo elemento de la lista es la letra 'd': ");
  if (comparador_char(*(char*)lista_ultimo(lista),'d')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Borro el elemento de la posicion 3, esta era la letra 'w'\n");
  lista_borrar_de_posicion(lista, 3);
  printf("En la posicion 3 no esta la letra 'w': ");
  if (!comparador_char(*(char*)lista_elemento_en_posicion(lista,3),'w')){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("La lista tiene 4 elementos: ");
  if (comparador_enteros((int)lista_elementos(lista),4)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Elementos en la lista: ");
  for(size_t i=0;i<lista_elementos(lista);i++)
  printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));
  printf("\n");
  printf("Imprimo la lista usando el iterador externo: ");
  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it)){
    printf("%c ", *(char*)lista_iterador_siguiente(it));
  }
  printf("\n");
  lista_iterador_destruir(it);
  printf("Imprimo la lista usando el iterador interno: ");
  lista_con_cada_elemento(lista, mostrar_elemento);
  printf("\n");
  lista_destruir(lista);
  return pruebas_pasadas;
}
int pruebas_casos_borde(lista_t* lista,int* pruebas_totales){
  int pruebas_pasadas=0;
  int elemento=0;
  lista=NULL;
  lista_iterador_t* iterador=NULL;
  printf("\nAhora, chequeo casos borde: \n");
  printf("Pruebas con la lista sin crear : \n");
  printf("Intento insertar un elemento: ");
  if (comparador_enteros(lista_insertar(lista,&elemento),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento insertar un elemento en una posicion: ");
  if (comparador_enteros(lista_insertar_en_posicion(lista,&elemento,2),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento borrar un elemento: ");
  if (comparador_enteros(lista_borrar(lista),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento borrar un elemento de una posicion: ");
  if (comparador_enteros(lista_borrar_de_posicion(lista,2),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento ver un elemento de una posicion: ");
  if (lista_elemento_en_posicion(lista,2)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento ver el ultimo elemento de la lista: ");
  if (lista_ultimo(lista)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Chequeo que la lista este vacia: ");
  if (comparador_bool(lista_vacia(lista),true)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
   printf("Chequeo cuantos elementos hay en la lista, tendria que haber 0: ");
  if (comparador_enteros((int)lista_elementos(lista),0)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento crear un iterador: ");
  if (lista_iterador_crear(lista)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Ahora creo una lista\n");
  lista=lista_crear();
  printf("Intento borrar un elemento sin haber insertado: ");
  if (comparador_enteros(lista_borrar(lista),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento borrar un elemento de una posicion sin haber insertado: ");
  if (comparador_enteros(lista_borrar_de_posicion(lista,2),-1)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento ver un elemento de una posicion sin haber insertado: ");
  if (lista_elemento_en_posicion(lista,2)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Intento ver el ultimo elemento de la lista sin haber insertado ");
  if (lista_ultimo(lista)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Pruebas con el iterador sin crear : \n");
  printf("Chequeo si hay elemento siguiente: ");
  if (comparador_bool(lista_iterador_tiene_siguiente(iterador),false)){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Devuelvo el elemento actual y paso al siguiente: ");
  if (lista_iterador_siguiente(iterador)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  printf("Ahora creo un iterador\n");
  iterador=lista_iterador_crear(lista);
  printf("Sin que haya elementos, intento devolver el elemento actual y pasar al siguiente: ");
  if (lista_iterador_siguiente(iterador)==NULL){
    printf("Funciono\n");
    pruebas_pasadas++;
  }else{
    printf("No funciono\n");
  }
  (*pruebas_totales)++;
  lista_iterador_destruir(iterador);
  lista_destruir(lista);
  return pruebas_pasadas;
}

int main(){
  int pruebas_totales=0;
  int pruebas_pasadas=0;
  lista_t* lista=NULL;
  printf("\t\t\t\tPruebas lista\n\n");
  pruebas_pasadas+=pruebas_catedra(lista,&pruebas_totales);
  pruebas_pasadas+=pruebas_casos_borde(lista,&pruebas_totales);
  printf("\nFin de las pruebas\n");
  printf("\nPasaron %i pruebas de %i totales.\n",pruebas_pasadas,pruebas_totales);
  return 0;
}
