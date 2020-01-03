#include <stdio.h>
#include <string.h>
#include "juego.h"

#define INICIAR_SIMULACION 'S'
#define AGREGAR_CASA 'A'
#define LISTAR_CASAS 'L'
#define MOSTRAR_EXTINTAS 'E'
#define FINALIZAR_PROGRAMA 'Q'
#define MAX_CARACTERES_A_LEER 500
#define ARCHIVO_CASAS_INICIAL "SDA.txt"
#define LECTURA "r"
#define COMANDO_ESCAPE "Salir"
#define FUNCIONO 1

void mostrar_display(){
	printf("\n\nPara realizar acciones debera ingresar los siguientes comandos: \n");
	printf("\t -S: para realizar la simulacion y ver que casa se queda con el trono. \n");
	printf("\t -A: para agregar mas casas a traves de un archivo de texto. \n");
	printf("\t -L: para listar las casas que siguen vivas de manera descendente segun la cantidad de personas. \n");
	printf("\t -E: para listar las casas extintas en el orden que desaparecieron. \n");
	printf("\t -Q: para salir del programa.\n");
}

void imprimir_error(){
	printf("\n\nOcurrio un error\n");
	printf("Ingrese Q para salir del programa.\n");
}

/*
* La funcion lee lo que el usuario ingresa por teclado
*/
char* leer_instruccion(FILE* archivo){
  static char linea[MAX_CARACTERES_A_LEER];
  char* string=fgets(linea, MAX_CARACTERES_A_LEER, archivo);
  if (string){
  	linea[strlen(linea)-1] = 0;
  }
  return string;
}

/*
* La funcion le pide un archivo al usuario y devuelve un archivo que exista
*/
char* solicitar_archivo(){
	printf("Ingrese un archivo de casas que desea agregar: ");
	char* nombre_archivo=leer_instruccion(stdin);
	FILE* archivo_ingresado=fopen(nombre_archivo,LECTURA);
	bool continuar=true;
	while(archivo_ingresado==NULL&&continuar){
		printf("Ingreso un archivo que no existe,si quiere ingrese otro o ingrese 'Salir' si no desea ingresar un archivo: ");
		nombre_archivo=leer_instruccion(stdin);
		if(strcmp(nombre_archivo,COMANDO_ESCAPE)==0){
			continuar=false;
		}
		archivo_ingresado=fopen(nombre_archivo,LECTURA);
	}
	if(archivo_ingresado!=NULL){
		fclose(archivo_ingresado);
	}
	return nombre_archivo;
}

/*
* La funcion le pide una instruccion al usuario y devuelve la instruccion dada
*/
void solicitar_instruccion(char* comando_ingresado){	
	printf("Ingrese una instruccion: ");
	char* linea=leer_instruccion(stdin);
	(*comando_ingresado)=linea[0];
}

/*
* La funcion llama a la funcion que agrega los datos del archivo al juego.
* Devuelve por pantalla un mensaje acerca del resultado.
*/
void agregar_casa(juego_t* juego){
	int agrego=0;
 	char* archivo_ingresado=solicitar_archivo();
	if(strcmp(archivo_ingresado,COMANDO_ESCAPE)!=0){
 		agrego=ingresar_casas(juego,archivo_ingresado);
 		if(agrego==FUNCIONO){
 			printf("Se agregaron correctamente las casas\n");
 		}else{
 			imprimir_error();
 			destruir_juego(juego);
 		}
 	}
}

/*
* La funcion le pide la cantidad de años a simular usuario y devuelve la instruccion dada
*/
int leer_anios(){
	int anios=0;
	char* linea=leer_instruccion(stdin);
	anios=atoi(linea);
	return anios;
}

/*
* La funcion le pide la cantidad de años a simular usuario hasta que ingrese un valor correcto
* Devuelve ese valor
*/
int solicitar_anios_a_simular(){
	int anios=0;
	printf("Ingrese cuantos años quiere simular: ");
	anios=leer_anios();
	while(anios<1){
		printf("Ingreso una cantidad invalida, ingrese nuevamente: ");
		anios=leer_anios();
	}
	return anios;
}

/*
* La funcion llama a la funcion que pide los años a simular y a la que realiza la simulacion.
*/
void simular(juego_t* juego){
	int anios_a_simular=0;
	anios_a_simular=solicitar_anios_a_simular();
	realizar_simulacion(juego,anios_a_simular);
}

/*
* La funcion realiza la instruccion dada por el usuario
*/
void realizar_instruccion(juego_t* juego,char comando_ingresado){
	switch(comando_ingresado){
 		case INICIAR_SIMULACION:
 		 	system("clear");
 			simular(juego);
 			mostrar_display();
 		 	solicitar_instruccion(&comando_ingresado);
 			realizar_instruccion(juego,comando_ingresado);
 		break;
 		case AGREGAR_CASA:
 		 	system("clear");
 			agregar_casa(juego);
 			mostrar_display();
 			solicitar_instruccion(&comando_ingresado);
 			realizar_instruccion(juego,comando_ingresado);
 		break;
 		case LISTAR_CASAS:
 		 	system("clear");
 			listar_casas(juego);
 			mostrar_display();
 			solicitar_instruccion(&comando_ingresado);
 			realizar_instruccion(juego,comando_ingresado);
 		break;
 		case MOSTRAR_EXTINTAS:
 		 	system("clear");
 			mostrar_casas_extintas(juego);
 			mostrar_display();
 			solicitar_instruccion(&comando_ingresado);
 			realizar_instruccion(juego,comando_ingresado);
 		break;
 		case FINALIZAR_PROGRAMA:
 			return;	
 		break;
 		default:
 		printf("Ingreso una instruccion incorrecta\n");
 		solicitar_instruccion(&comando_ingresado);
 		realizar_instruccion(juego,comando_ingresado);
 		return;
 	}
}

int main(){
	char comando_ingresado=' ';
	juego_t* juego=NULL;
	juego=crear_juego(juego);
	int ingreso=0;
	if(juego!=NULL){
		system("clear");
		printf("Bienvenido a esta simulacion de Game of Thrones\n");
		printf("Aqui podria simular y ver que casa se queda con el trono\n");
		mostrar_display();
		ingreso=ingresar_casas(juego,ARCHIVO_CASAS_INICIAL);
		if (ingreso!=FUNCIONO){
			imprimir_error();
		}
		solicitar_instruccion(&comando_ingresado);
		realizar_instruccion(juego,comando_ingresado);
		destruir_juego(juego);
	}else{
		imprimir_error();
	}
	return 0;
}