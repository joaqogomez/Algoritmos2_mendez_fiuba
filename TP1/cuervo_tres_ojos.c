#include <stdlib.h>
#include "cuervo_tres_ojos.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define CANTIDAD_INICIAL_VISIONES 0
#define FUNCIONO 0
#define FALLO -1
#define PASADO 'P'
#define FUTURO 'F'


cuervo_tres_ojos_t* invocar_cuervo(char* nombre){
	cuervo_tres_ojos_t* cuervo;
	cuervo=malloc(sizeof(cuervo_tres_ojos_t));
	if (!cuervo){
		return NULL;
	}
	strcpy(cuervo->nombre,nombre);
	cuervo->visiones_del_pasado=NULL;
	cuervo->visiones_del_futuro=NULL;
	cuervo->cantidad_visiones_pasado=CANTIDAD_INICIAL_VISIONES;
	cuervo->cantidad_visiones_futuro=CANTIDAD_INICIAL_VISIONES;
	return cuervo;
}

cuervo_aprendiz_t* invocar_aprendiz(char* nombre){
	cuervo_aprendiz_t* cuervo;
	cuervo=malloc(sizeof(cuervo_aprendiz_t));
	if (!cuervo){
		return NULL;
	}
	strcpy(cuervo->nombre,nombre);
	cuervo->visiones_adquiridas=NULL;
	cuervo->cantidad_visiones=CANTIDAD_INICIAL_VISIONES;
	return cuervo;
}
//Precondiciones: La funcion recibe un puntero, la cantidad de visiones y la vision.
//Postcondicion: La funcion crea la memoria y les asigna el valor de la vision, de no poder hacerlo, devuelve -1
int crear_memoria_y_copiar_vision(vision_t** puntero_visiones,int (*cantidad_visiones),vision_t vision){
		vision_t* aux;
		aux=realloc(*puntero_visiones,sizeof(vision_t)*(size_t)((*cantidad_visiones)+1));
		if(aux==NULL){
			return FALLO;
		}
		(*puntero_visiones)=aux;
		(*puntero_visiones)[(*cantidad_visiones)]=vision;
		(*cantidad_visiones)++;
		return FUNCIONO;
}

int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){
	int agrego=-1;
	if (vision.epoca==PASADO){
		agrego=crear_memoria_y_copiar_vision(&(cuervo->visiones_del_pasado),&(cuervo->cantidad_visiones_pasado),vision);
		return agrego;
	}else if(vision.epoca==FUTURO){
		agrego=crear_memoria_y_copiar_vision(&(cuervo->visiones_del_futuro),&(cuervo->cantidad_visiones_futuro),vision);
		return agrego;
	}else{
		return agrego;
	}
}
//Precondicion: Recibe la vision que queremos transmitir y cada una de las visiones que estan en el vector de visiones del aprendiz.
//Postcondicion: Devuelve true si ambas visiones son iguales, es decir, si los 4 campos son iguales.
bool son_visiones_iguales(vision_t vision1,vision_t vision2){
	return((strcmp(vision1.protagonista,vision2.protagonista)==0)&&(strcmp(vision1.casa_protagonista,vision2.casa_protagonista)==0)&&(strcmp(vision1.descripcion,vision2.descripcion)==0)&&(vision1.epoca==vision2.epoca));
}
//Precondicion: Recibe la vision que queremos transmitir y el vector de visiones del aprendiz.
//Postcondicion: Devuelve true si la vision esta en el vector de visiones.
bool es_vision_repetida(cuervo_aprendiz_t* aprendiz,vision_t vision){
	bool es_repetida=false;
	if (aprendiz->cantidad_visiones==CANTIDAD_INICIAL_VISIONES){
		return es_repetida;
	}else{
		for (int i = 0; i < aprendiz->cantidad_visiones; ++i){
			if(son_visiones_iguales(aprendiz->visiones_adquiridas[i],vision)){
				es_repetida=true;
			}
		}
	}
	return es_repetida;
}
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
	int transmitio=0;
	for (int i = 0; i < (cuervo->cantidad_visiones_pasado); ++i){
		if((es_transmisible(cuervo->visiones_del_pasado[i]))&&(!es_vision_repetida(aprendiz,cuervo->visiones_del_pasado[i]))){
			transmitio=crear_memoria_y_copiar_vision(&(aprendiz->visiones_adquiridas),&(aprendiz->cantidad_visiones),cuervo->visiones_del_pasado[i]);
		}
	}
	for (int i = 0; i < (cuervo->cantidad_visiones_futuro); ++i){
		if((es_transmisible(cuervo->visiones_del_futuro[i]))&&(!es_vision_repetida(aprendiz,cuervo->visiones_del_futuro[i]))){
			transmitio=crear_memoria_y_copiar_vision(&(aprendiz->visiones_adquiridas),&(aprendiz->cantidad_visiones),cuervo->visiones_del_futuro[i]);
		}
	}
	return transmitio;
}
// Precondicion: La funcion recibe una vision listable
// Postcondicion: Se imprime por pantalla la vision listable
void imprimir_vision(vision_t vision){
	printf("Visión sobre %s: %s.\n",vision.protagonista,vision.descripcion);
}
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t)){
	for (int i = 0; i < aprendiz.cantidad_visiones; ++i){
		if(es_listable(aprendiz.visiones_adquiridas[i])){
			imprimir_vision(aprendiz.visiones_adquiridas[i]);
		}
	}
}

int destruir_cuervo(cuervo_tres_ojos_t* cuervo){
	int pudo_liberar=0;
	if(cuervo->visiones_del_pasado!=NULL){
		free(cuervo->visiones_del_pasado);
	}else if(cuervo->cantidad_visiones_pasado!=CANTIDAD_INICIAL_VISIONES){
		pudo_liberar=FALLO;
	}
	if(cuervo->visiones_del_futuro!=NULL){
		free(cuervo->visiones_del_futuro);
	}else if(cuervo->cantidad_visiones_futuro!=CANTIDAD_INICIAL_VISIONES){
		pudo_liberar=FALLO;
	}
	if(cuervo!=NULL){
		free(cuervo);
	}else{
		pudo_liberar=FALLO;
	}
	return pudo_liberar;
}

int destruir_aprendiz(cuervo_aprendiz_t* aprendiz){
	int pudo_liberar=0;
	if(aprendiz->visiones_adquiridas!=NULL){
		free(aprendiz->visiones_adquiridas);
	}else if(aprendiz->cantidad_visiones!=CANTIDAD_INICIAL_VISIONES){
		pudo_liberar=FALLO;
	}
	if(aprendiz!=NULL){
		free(aprendiz);
	}else{
		pudo_liberar=FALLO;
	}	
	return pudo_liberar;
}