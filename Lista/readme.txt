El archivo zip entregado tiene la implementacion de una lista con nodos simplemente enlazados, el .h entregado por la catedra,
,una serie de pruebas hechas por mi y la biblioteca con funciones para chequear los resultados de las pruebas.
Una lista es un TDA que se utiliza para agrupar elementos. Se caracterizan principalmente porque cada elemento tiene un sucesor (salvo el ultimo elemento) 
y un predecesor (salvo el primero). Otra caracteristica que la difencia con respecto a los tda antes implementados es que uno puede insertar y eliminar elementos
de la posicion que se desee (siempre que sea posible hacerlo obviamente).
La lista fue implementada con un puntero al primer nodo y otro al ultimo. Esto se hizo de esta forma para que las funciones lista_insertar y lista_ultimo sean O(1).
Pese a que no es una gran optimizacion, si se hubiera puesto solo un puntero al primer nodo (como vimos en clase), estas dos funciones hubiesen sido O(N).

A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

Las pruebas agregadas tienen el objetivo de probar el correcto funcionamiento del TDA . Las pruebas enviadas van a probar diferentes casos.
Hay dos tipos de pruebas:
-Pruebas_catedra: se tomaron las pruebas dadas por la catedra y se fueron haciendo distintos chequeos de este que es un caso ideal.
-Pruebas_casos_borde: se chequearon los casos borde que tienen las funciones de este TDA
Las pruebas imprimen por pantalla:
-Una explicacion de lo que quieren probar.
-Estado de la prueba (si paso o no).
Al final de todo, aparecera un contador con el numero de pruebas que paso el programa.

Aclaracion: Los nombres que se imprimen por pantalla de las pruebas de los casos borde intentan explicar que funcion intentaron realizar,
al decir funciono significa que las funciones devuelven lo esperado segun el .h enviado por la catedra
