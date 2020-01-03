#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "abb.h"
#include "cola.h"
#include "lista.h"
#include "juego.h"
#include "mergesort.h"

#define MAX_NOMBRES 100
#define FUNCIONO 1
#define ERROR 0
#define LECTURA "r"
#define PERSONA 'I'
#define CASA 'C'
#define FORMATO_CASA "C; %[^;];%i;%i"
#define FORMATO_PERSONA "I; %[^;];%zu"
#define MAX_CARACTERES_A_LEER 500
#define EDAD_MAXIMA 60
#define CANTIDAD_CAMPOS_PERSONA 2
#define CANTIDAD_CAMPOS_CASA 3

typedef struct casa{
	char nombre[MAX_NOMBRES];
	int factor_nacimiento;
	int factor_envejecimiento;
	lista_t* listado_personas;
} casa_t;

typedef struct persona{
	char nombre[MAX_NOMBRES];
	size_t edad;
} persona_t;

// Comparador del arbol, compara casas segun su nombre
int comparar_casas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2){
        return 0;
    }
    char* aux1=((casa_t*)elemento1)->nombre;
	char* aux2=((casa_t*)elemento2)->nombre;
    if((strcmp(aux1,aux2))>0){
        return 1;
    }else if((strcmp(aux1,aux2))<0){
        return -1;
    }else{
        return 0;
    }
}

//Destruye los elementos de la lista de personas
void destruir_persona(void* elemento){
	if(elemento!=NULL){
		free(elemento);
	}
}

void destruir_casa(casa_t* casa){
	if (casa==NULL){
		return;
	}
	if(!lista_vacia(casa->listado_personas)){
    	lista_con_cada_elemento(casa->listado_personas,destruir_persona);
    }
    lista_destruir(casa->listado_personas);
    free(casa);
}

//Destruye los elementos del arbol de casas
void destructor_de_casas(void* elemento){
    if(elemento==NULL){
        return;
    }
    destruir_casa((casa_t*)elemento);
}

//Comparador para el mergesort. Compara casas segun la cantidad de personas que tienen
int es_mayor_int(void* elemento1, void* elemento2){
    lista_t* aux1=((casa_t*)elemento1)->listado_personas;
	lista_t* aux2=((casa_t*)elemento2)->listado_personas;
	int personas1=((int)lista_elementos(aux1));
	int personas2=((int)lista_elementos(aux2));
	return personas1 > personas2;
}

juego_t* crear_juego(juego_t* juego){
	juego=malloc(sizeof(juego_t));
	if(juego==NULL){
		return NULL;
	}
	juego->casas_vivas=arbol_crear(comparar_casas,destructor_de_casas);
	if(juego->casas_vivas==NULL){
		free(juego);
		return NULL;
	}
	juego->casas_extintas=cola_crear(destructor_de_casas);
	if(juego->casas_extintas==NULL){
		free(juego);
		free(juego->casas_vivas);
		return NULL;
	}
	juego->cantidad_casas_vivas=0;
	return juego;
}

/*
 * Crea una casa y reserva la memoria necesaria de la estructura.
 * Devuelve un puntero a la casa creada o NULL en caso de error.
 */
casa_t* crear_casa(char* nombre,int factor_envejecimiento,int factor_nacimiento){
	casa_t* casa=malloc(sizeof(casa_t));
    if(casa!=NULL){
        strcpy(casa->nombre,nombre);
        casa->factor_nacimiento=factor_nacimiento;
        casa->factor_envejecimiento=factor_envejecimiento;
        casa->listado_personas=lista_crear();
        if (casa->listado_personas==NULL){
        	free(casa);
        	casa=NULL;
        }
    }
    return casa;
}
/*
 * Crea una persona y reserva la memoria necesaria de la estructura.
 * Devuelve un puntero a la persona creada o NULL en caso de error.
 */
persona_t* crear_persona(char* nombre,size_t edad){
	persona_t* persona=malloc(sizeof(persona_t));
    if(persona!=NULL){
        strcpy(persona->nombre,nombre);
        persona->edad=edad;
    }
    return persona;
}

/*
 * La funcion se encarga de aumentar la edad de las personas de una lista segun el factor
 */
void envejecer_persona(lista_t* lista, int factor){
	if(lista!=NULL){
		lista_iterador_t* iterador=lista_iterador_crear(lista);
		if (iterador!=NULL){
			while ( lista_iterador_tiene_siguiente(iterador) ){
				void * elemento = lista_iterador_siguiente(iterador);
				persona_t* aux=(persona_t*)elemento;
				aux->edad+=(size_t)factor;
			}
			lista_iterador_destruir(iterador);
		}			
	}
}

/*
 * La funcion se encarga de llamar a la funcion para aumentar la edad de las personas con cada lista 
*/
void aumentar_edad(juego_t* juego){
	casa_t* casas[(juego->cantidad_casas_vivas)];
	arbol_recorrido_inorden(juego->casas_vivas,(void**)casas,(juego->cantidad_casas_vivas));
	for (int i = 0; i < (juego->cantidad_casas_vivas); ++i){
		envejecer_persona(casas[i]->listado_personas,casas[i]->factor_envejecimiento);
	}
}

/*
 * La funcion recibe una lista y arma dos listas, una con las personas que siguen vivas y otro con las que mueren.
 * Devuelve la lista de las personas que siguen vivas y destruye las otras dos.
 * En caso de error, devuelve la lista original
*/
lista_t* matar_personas(lista_t* lista_original){
	lista_t* lista_personas_vivas=lista_crear();
	if(lista_personas_vivas==NULL){
		return lista_original;
	}
	lista_t* lista_personas_muertas=lista_crear();
	if(lista_personas_muertas==NULL){
		free(lista_personas_vivas);
		return lista_original;
	}
	lista_iterador_t* iterador=lista_iterador_crear(lista_original);
	if (iterador!=NULL){
		while ( lista_iterador_tiene_siguiente(iterador) ){
			void * elemento = lista_iterador_siguiente(iterador);
			persona_t* aux=(persona_t*)elemento;
			if ((aux->edad)>=EDAD_MAXIMA){
				lista_insertar(lista_personas_muertas,elemento);
			}else{
				lista_insertar(lista_personas_vivas,elemento);
			}
		}
	}else{
		free(lista_personas_vivas);
		free(lista_personas_muertas);
		return lista_original;
	}
	lista_iterador_destruir(iterador);
	lista_con_cada_elemento(lista_personas_muertas,destruir_persona);
	lista_destruir(lista_personas_muertas);
	lista_destruir(lista_original);
	return lista_personas_vivas;
}

/*
 * La funcion se encarga de llamar a la funcion para eliminar a las personas que no cumplen con los requisitos.
 * Si la lista queda vacia, se encarga de borrar la casa del arbol y agregarla la cola
*/
void matar_personas_y_destruir_casas(juego_t* juego){
	if(juego!=NULL){
		casa_t* casas[(juego->cantidad_casas_vivas)];
		arbol_recorrido_inorden(juego->casas_vivas,(void**)casas,(juego->cantidad_casas_vivas));
		for (int i = 0; i < (juego->cantidad_casas_vivas); ++i){
			casas[i]->listado_personas=matar_personas(casas[i]->listado_personas);
			if(lista_vacia(casas[i]->listado_personas)){
				char nombre[MAX_NOMBRES];
				strcpy(nombre,casas[i]->nombre);
				casa_t* aux=crear_casa(nombre,0,0);
				if(aux!=NULL){
					cola_encolar(juego->casas_extintas,aux);
					arbol_borrar(juego->casas_vivas,(void*)casas[i]);
					(juego->cantidad_casas_vivas)--;
				}			
			}
		}
	}	
}

/*
 * La funcion calcula cuanta gente debe nacer segun el factor y luego inserta esa cantidad de personas en la lista.
*/
void nacen_personas(lista_t* lista,int factor){
	if(lista!=NULL){
		size_t personas_a_nacer=0;
		if (factor!=0){
			personas_a_nacer=lista_elementos(lista)/((size_t)factor);
		}
		for (int i = 0; i < personas_a_nacer; ++i){
			char nombre[MAX_NOMBRES];
			int numero= rand();
			sprintf(nombre,"%d", numero);
			persona_t* aux=crear_persona(nombre,0);
			if (aux!=NULL){
				lista_insertar(lista,aux);
			}
		}
	}		
}

/*
 * La funcion se encarga de llamar a la funcion para que nazcan las personas por cada lista.
*/
void nacimientos(juego_t* juego){
	casa_t* casas[(juego->cantidad_casas_vivas)];
	arbol_recorrido_inorden(juego->casas_vivas,(void**)casas,(juego->cantidad_casas_vivas));
	for (int i = 0; i < (juego->cantidad_casas_vivas); ++i){
		nacen_personas(casas[i]->listado_personas,casas[i]->factor_nacimiento);
	}
}

/*
 * La funcion se encarga de decidir quien se queda con el trono segun la cantidad de personas.
 * Imprime por pantalla el resultado
*/
void determinar_ganador(juego_t* juego){
	if(juego!=NULL){
		if(!arbol_vacio(juego->casas_vivas)){
			casa_t* casas[(juego->cantidad_casas_vivas)];
			arbol_recorrido_inorden(juego->casas_vivas,(void**)casas,(juego->cantidad_casas_vivas));
			mergesort((void**)casas,(juego->cantidad_casas_vivas),es_mayor_int);
			char nombre[MAX_NOMBRES];
			strcpy(nombre,casas[0]->nombre);
			int cantidad_personas=((int)lista_elementos(casas[0]->listado_personas));
			printf("El trono de hierro esta en posesion de la casa '%s' que tiene %i personas.\n",nombre,cantidad_personas);
		}else{
			printf("No hay casas vivas, el trono queda vacante\n");
		}
	}
}

void realizar_simulacion(juego_t* juego,int anios_a_simular){
	if ((juego!=NULL)&&(juego->cantidad_casas_vivas!=0)){
		for (int i = 1; i < anios_a_simular+1; ++i){
			printf("Simulando año: %i\n",i);
			aumentar_edad(juego);
			matar_personas_y_destruir_casas(juego);
			nacimientos(juego);		
		}
	}
	printf("\n\nLuego de simular %i años, \n",anios_a_simular);
	determinar_ganador(juego);
}

/*
* La funcion lee la informacion del archivo
*/
char* leer_linea(FILE* archivo){
  static char linea[MAX_CARACTERES_A_LEER];
  char* string=fgets(linea, MAX_CARACTERES_A_LEER, archivo);
  if (string){
  	linea[strlen(linea)-1] = 0;
  }
  return string;
}

int ingresar_casas(juego_t* juego,char* nombre_archivo){
	FILE* archivo=fopen(nombre_archivo,LECTURA);
	char* linea=NULL;
	linea = leer_linea(archivo);
	casa_t* casa_creada=NULL;
	casa_t* casa_aux=NULL;
	persona_t* persona_creada=NULL;
	bool inserte_casa=false;
	int campos_leidos=0;
	while(linea){		
  		if(linea[0] == CASA){
  		char nombre[MAX_NOMBRES];
		int factor_nacimiento=0;
		int factor_envejecimiento=0;
   		campos_leidos=sscanf(linea, FORMATO_CASA, nombre,&factor_envejecimiento,&factor_nacimiento);
   			if(campos_leidos==CANTIDAD_CAMPOS_CASA){
   				casa_creada=crear_casa(nombre,factor_envejecimiento,factor_nacimiento);
   				inserte_casa=true;
   					if(arbol_buscar(juego->casas_vivas,casa_creada)==NULL){   				
   						arbol_insertar(juego->casas_vivas,casa_creada);
   						(juego->cantidad_casas_vivas)++;
		   				casa_aux=casa_creada;   				
		   			}else{
		   				casa_aux=arbol_buscar(juego->casas_vivas,casa_creada);
		   				destruir_casa(casa_creada);
		   			}
		   	}else{
		   		fclose(archivo);
  				return ERROR;
		   	}
  		}else if((linea[0] == PERSONA)&&(inserte_casa)){
  			char nombre[MAX_NOMBRES];
			size_t edad=0;	
    		campos_leidos=sscanf(linea, FORMATO_PERSONA, nombre, &edad);
    		if(campos_leidos==CANTIDAD_CAMPOS_PERSONA){
    			persona_creada=crear_persona(nombre,edad);
    			lista_insertar(casa_aux->listado_personas,persona_creada);
    		}else{
    			fclose(archivo);
  				return ERROR;
    		}
  		}else{
  			fclose(archivo);
  			return ERROR;
  		}
  		linea = leer_linea(archivo);
  	}
	fclose(archivo);
	return FUNCIONO;
}

void listar_casas(juego_t* juego){
	if (juego!=NULL){
		if((juego->cantidad_casas_vivas)!=0){
			casa_t* casas[(juego->cantidad_casas_vivas)];
			arbol_recorrido_inorden(juego->casas_vivas,(void**)casas,(juego->cantidad_casas_vivas));
			mergesort((void**)casas,(juego->cantidad_casas_vivas),es_mayor_int);
			for (int i = 0; i < (juego->cantidad_casas_vivas); ++i){
				char nombre[MAX_NOMBRES];
				strcpy(nombre,casas[i]->nombre);
				int cantidad_personas=((int)lista_elementos(casas[i]->listado_personas));
				printf("Casa '%s' --> Cantidad de personas: %i\n",nombre,cantidad_personas);
				//lista_con_cada_elemento(casas[i]->listado_personas,imprimir_persona);
			}
		}else{
			printf("No hay mas casas vivas\n");
		}
	}
}

/*
 * La funcion recibe una cola y le pasa sus elementos a una cola auxiliar, imprimiendo por pantalla el primero de la cola original
 * antes de desencolar.
 * Devuelve la cola auxiliar(con los mismos elementos que la original) y destruye la original.
 * En caso de error, devuelve NULL.
*/
cola_t* desencolar_y_mostrar(cola_t* cola){
	if (cola==NULL){
		return NULL;
	}
	cola_t* aux=cola_crear(destructor_de_casas);
	if(aux==NULL){
		return NULL;
	}
	void* elemento;
	char nombre[MAX_NOMBRES];
	printf("Se extinguieron las siguientes casas:\n");
	cola->destructor=NULL;
	while(!cola_vacia(cola)){
		elemento=cola_primero(cola);
		cola_desencolar(cola);
		cola_encolar(aux,elemento);
		strcpy(nombre,((casa_t*)elemento)->nombre);
		printf("-Casa %s\n",nombre);
	}
	cola_destruir(cola);
	return aux;
}

void mostrar_casas_extintas(juego_t* juego){
	if(juego!=NULL){
		if(!cola_vacia(juego->casas_extintas)){
			juego->casas_extintas=desencolar_y_mostrar(juego->casas_extintas);
		}else{
			printf("No hay casas extintas.\n");
		}
	}
}

void destruir_juego(juego_t* juego){
	if(juego!=NULL){
		arbol_destruir(juego->casas_vivas);
		cola_destruir(juego->casas_extintas);
		free(juego);
	}
}