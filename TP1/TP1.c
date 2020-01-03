#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cuervo_tres_ojos.h"
#define ARCHIVO_VISIONES "visiones.txt"
#define LECTURA "r"
#define CAMPOS_A_LEER 4
#define FALLO_ARCHIVO 0
#define FALLO -1
#define NO_HAY_VISIONES 0
#define FORMATO_LECTURA_ARCHIVO "%[^;];%[^;];%[^;];%c\n"
#define CASA_STARK "Stark"
#define LARGO_MAX_DESCRIPCION 40
#define PASADO 'P'
#define JON "Jon Snow"


bool es_de_casa_stark(vision_t vision){
	return (strcmp(CASA_STARK,vision.casa_protagonista)==0);
}
bool es_vision_corta(vision_t vision){
	return (strlen(vision.descripcion)<=LARGO_MAX_DESCRIPCION);
}
bool es_vision_pasada(vision_t vision){
	return vision.epoca==PASADO;
}
bool es_Jon_Snow_protagonista(vision_t vision){	
	return (strcmp(JON,vision.protagonista)==0);
}

int main (){
	int vision_a_leer;
	int vision_agregada=0;
	int transmitio_visiones=0;
	int destrui_cuervo,destrui_aprendiz;
	vision_t vision_leida;
	FILE* archivo_visiones=fopen(ARCHIVO_VISIONES,LECTURA);
	if(archivo_visiones==NULL){
		printf("Hubo un error al intentar abrir el archivo.\n");
		return FALLO_ARCHIVO;
	}
	cuervo_tres_ojos_t* cuervo_viejo=invocar_cuervo("Harry");
	cuervo_aprendiz_t* cuervo_nuevo=invocar_aprendiz("Potter");
	vision_a_leer=fscanf(archivo_visiones,FORMATO_LECTURA_ARCHIVO,vision_leida.protagonista,vision_leida.casa_protagonista,vision_leida.descripcion,&vision_leida.epoca);
	while (vision_a_leer==CAMPOS_A_LEER&&vision_agregada==0){
		vision_agregada=agregar_vision(cuervo_viejo,vision_leida);
		if (vision_agregada==0){
			vision_a_leer=fscanf(archivo_visiones,FORMATO_LECTURA_ARCHIVO,vision_leida.protagonista,vision_leida.casa_protagonista,vision_leida.descripcion,&vision_leida.epoca);
		}	
	}
	if (vision_agregada==FALLO){
		printf("Hubo un error al intentar agregar las visiones.\n");
	}else{
		transmitio_visiones=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_Jon_Snow_protagonista);
		transmitio_visiones=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_vision_pasada);
		transmitio_visiones=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_de_casa_stark);
		if(transmitio_visiones==FALLO){
			printf("Hubo un error al intentar transimitir las visiones.\n");
		}else if((cuervo_nuevo->cantidad_visiones)==NO_HAY_VISIONES){
			printf("No hay visiones para transmitir.\n");
		}else{
			printf("Visiones en las que Jon Snow es protagonista: \n");
			listar_visiones_transmitidas(*cuervo_nuevo,es_Jon_Snow_protagonista);
			printf("\nVisiones de menos de 40 caracteres: \n");
			listar_visiones_transmitidas(*cuervo_nuevo,es_vision_corta);
			//Comentadas para que entre en kwyjibo
			//printf("\nVisiones del pasado: \n");
			//listar_visiones_transmitidas(*cuervo_nuevo,es_vision_pasada);
			//printf("\nVisiones de la casa Stark: \n");
			//listar_visiones_transmitidas(*cuervo_nuevo,es_de_casa_stark);
		}
	}
	fclose(archivo_visiones);
	destrui_cuervo=destruir_cuervo(cuervo_viejo);
	destrui_aprendiz=destruir_aprendiz(cuervo_nuevo);
	if((destrui_cuervo==FALLO)||(destrui_aprendiz==FALLO)){
		printf("Hubo un error al intentar liberar la memoria creada.\n");
	}
	return 0;
}