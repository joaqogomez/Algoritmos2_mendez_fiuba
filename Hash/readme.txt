El archivo zip entregado tiene la implementacion de un hash abierto, el .h entregado por la catedra,
,una serie de pruebas hechas por mi y la biblioteca con funciones para chequear los resultados de las pruebas.
Un hash es un TDA conformado por elementos a los que se puede acceder mediante una clave.Segun la clave, estos se van a poner de forma tal que al aplicarle la funcion hash, uno pueda obtener su elemento. En mi caso particular, utilice un vector de abbs debido a que son mucho mas eficientes que las listas. A la hora de rehashear, decidi tomar la convencion de duplicar o achicar a la mitad el vector segun corresponda.
Se duplica el vector cuando hay 6 veces mas elementos que arboles y se achica a la mitad cuando hay el doble de arboles que de elementos.


A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

Las pruebas agregadas tienen el objetivo de probar el correcto funcionamiento del TDA . Las pruebas enviadas van a probar diferentes casos.
Hay dos tipos de pruebas:
-Pruebas_casos_borde: se chequearon los casos borde que tienen las funciones de este TDA (se las subdividio en casos_hash_null y casos_hash_vacio )
-Pruebas_elementos_NULL: se chequeo el caso en el cual se ingresa un elemento NULL
-Pruebas_caso_promedio: se chequean varias funciones imitando lo que haria un usuario promedio de este TDA (se utilizaron las mini
pruebas de la catedra como referencia)
-Pruebas_rehash: para probar que este se realice correctamente
-Pruebas_volumen: se chequea un caso en el que se ingresan 1000 elementos


Las pruebas imprimen por pantalla:
-Una explicacion de lo que quieren probar.
-Estado de la prueba (si paso o no).
Al final de todo, aparecera un contador con el numero de pruebas que paso el programa.

Aclaracion: Los nombres que se imprimen por pantalla de las pruebas de los casos borde intentan explicar que funcion intentaron realizar,
al decir funciono significa que las funciones devuelven lo esperado segun el .h enviado por la catedra
