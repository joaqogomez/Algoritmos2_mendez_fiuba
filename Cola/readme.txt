El archivo zip entregado tiene la implementacion de una cola con nodos enlazados, el .h entregado por la catedra,
y una serie de pruebas hechas por mi.
Una cola es un TDA que se utiliza para agrupar elementos. La cola tiene un unico canal de entrada y salida. 
Solo permite la insersion o eliminacion de un elemento por sus extremos, siguiendo el concepto de FIFO,
es decir, el primer elemento que entra es el primero que luego se va a retirar.
Un ejemplo de algo de la vida cotidiana que funcione asi podria ser la cola del supermercado o un peaje en una autopista.
A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

Las pruebas agregadas tienen el objetivo de probar el correcto funcionamiento del TDA cola. Las pruebas enviadas van a probar diferentes casos.
La prueba numero 2 es un caso de los denominados "caso feliz", ya que el usuario hace un correcto funcionamiento de la pila.
Algunas pruebas como la 1 y la 3 testean lo que se llama "casos borde". Estos son casos en los que, por ejemplo, la cola no fue creada o se intentan hacer operaciones
que no son posibles, como por ejemplo eliminar un elemento cuando no hay elementos.
Por ultimo, hay otras pruebas que testean que haya sido todo inicializado correctamente como las pruebas 7 y 8.
Las pruebas imprimen por pantalla:
-Una explicacion de lo que quieren probar.
-El resultado por pantalla de lo que hizo.
-Estado de la prueba (si paso o no).
Al final de todo, aparecera un contador con el numero de pruebas que paso el programa.
Si quiere agregar una prueba, debera agregarla en el archivo pruebas_cola_ne.c y seguir el siguiente formato:
-La funcion debera de ser de tipo int y devolver 0 si no se paso la prueba o 1 si se paso.
-Al agregar una prueba, debera sumar uno al contador de pruebas totales.
-La linea para poner la prueba debera ser: pruebas_pasadas+= una_funcion(variables).
-El nombre de la funcion en la que se realiza la prueba debe ser escrita de la siguiente forma:
	-int Given_When_Then().
	-En given van las condiciones iniciales de la prueba.
	-En when van las acciones que se van a realizar.
	-En then van los resultados esperados.
	-Ejemplo: int DadaUnaColaVacia_CuandoSeApila_EntoncesAumentaLaCantidadDeElementos.
-Las pruebas se organizan en 3 partes:
	-En la primera, se organizan los datos iniciales.
	-En la segunda, se realizan las acciones.
	-En la tercera, verifico los resultados.
-Aclaracion: las funciones de la cola por lo general devuelven 0 o true al funcionar correctamente
y -1 o false de funcionar incorrectamente. Para hacer verificar las funciones que devuelven 0 o -1
se va a utilizar !funcion, para que el true del if sea si funciono y el false sea si no funciono correctamente.