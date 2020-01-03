#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool comparador_enteros(int elemento1,int elemento2){
	return (elemento1==elemento2);
}

bool comparador_char(char elemento1, char elemento2){
	return (elemento1==elemento2);
}

bool comparador_string(char* elemento1, char* elemento2){
	return (strcmp(elemento1,elemento2)==0);
}

bool comparador_bool(bool elemento1, bool elemento2){
	return (elemento1==elemento2);
}

int resultados_prueba(bool condicion){
   if(condicion){
    printf("Funciono\n");
    return 1;
  }else{
    printf("No funciono\n");
    return 0;
  }
}