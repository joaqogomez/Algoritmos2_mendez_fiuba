
El archivo zip entregado tiene la implementacion de una pila como vector dinamico, el .h entregado por la catedra,
y una serie de pruebas de las cuales esta una dada por la catedra y el resto hechas por mi.
A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".
Las pruebas imprimen por pantalla:
-Una explicacion de lo que quieren probar.
-El resultado por pantalla de lo que hizo.
-Estado de la prueba (si paso o no).
Al final de todo, aparecera un contador con el numero de pruebas que paso el programa.

Si quiere agregar una prueba, debera agregarla en el archivo pruebas_pila_vd.c y seguir el siguiente formato:
-La funcion debera de ser de tipo int y devolver 0 si no se paso la prueba o 1 si se paso.
-Al agregar una prueba, debera sumar uno al contador de pruebas totales.
-La linea para poner la prueba debera ser: pruebas_pasadas+= una_funcion(variables).
-El nombre de la funcion en la que se realiza la prueba debe ser escrita de la siguiente forma:
	-int Given_When_Then().
	-En given van las condiciones iniciales de la prueba.
	-En when van las acciones que se van a realizar.
	-En then van los resultados esperados.
	-Ejemplo: int DadaUnaPilaVacia_CuandoSeApila_EntoncesAumentaLaCantidadDeElementos.
-Las pruebas se organizan en 3 partes:
	-En la primera, se organizan los datos iniciales.
	-En la segunda, se realizan las acciones.
	-En la tercera, verifico los resultados.
-Aclaracion: las funciones de la pila por lo general devuelven 0 o true al funcionar correctamente
y -1 o false de funcionar incorrectamente. Para hacer verificar las funciones que devuelven 0 o -1
se va a utilizar !funcion, para que el true del if sea si funciono y el false sea si no funciono correctamente.