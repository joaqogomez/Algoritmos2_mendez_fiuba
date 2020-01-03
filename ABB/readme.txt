El archivo zip entregado tiene la implementacion de un arbol binario de busqueda (ABB), el .h entregado por la catedra,
,una serie de pruebas hechas por mi y la biblioteca con funciones para chequear los resultados de las pruebas.
Un arbol binario de busqueda es un TDA conformado por un nodo que va a tener un puntero a un nodo a derecha y otro a izquierda, cada nodo teniendo un elemento.
La caracteristica de este tipo de arbol es que se encuentran ordenados segun un criterio, para luego poder realizar la busqueda de elementos de forma eficiente, siendo esta, por lo general, O(log2 N). El criterio que voy a seguir en mi implementacion es que los elementos menores se encuentran a izquierda y los mayores o iguales se van a encontrar a la derecha.

A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

Las pruebas agregadas tienen el objetivo de probar el correcto funcionamiento del TDA . Las pruebas enviadas van a probar diferentes casos.
Hay dos tipos de pruebas:
-Pruebas_casos_borde: se chequearon los casos borde que tienen las funciones de este TDA (se las subdividio en casos_arbol_null,casos_arbol_vacio y casos_borde_recorridos)
-Pruebas_elementos_NULL: se chequeo el caso en el cual se ingresa un elemento NULL
-Pruebas_caso_promedio: se chequean varias funciones imitando lo que haria un usuario promedio de este TDA
-Pruebas_volumen: se chequea un caso en el que se ingresan 1000 elementos

Las pruebas imprimen por pantalla:
-Una explicacion de lo que quieren probar.
-Estado de la prueba (si paso o no).
Al final de todo, aparecera un contador con el numero de pruebas que paso el programa.

Aclaracion: Los nombres que se imprimen por pantalla de las pruebas de los casos borde intentan explicar que funcion intentaron realizar,
al decir funciono significa que las funciones devuelven lo esperado segun el .h enviado por la catedra
