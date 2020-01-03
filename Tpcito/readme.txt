El archivo zip entregado tiene la implementacion del tp final, las bibliotecas con funciones para que funcione el programa y un archivo con pruebas(llamado tpfinal.c).
A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

El objetivo del tp es implementar un iterador externo para un abb. En mi caso, lo itere siguiendo el recorrido inorden.Para lograr el objetivo, se utilizo el TDA pila.
Se eligio una pila para poder ir guardando los hijos izquierdos de los nodos. Al llegar a un nodo sin hijo izquierdo pero con hijo derecho,se lo procesa y luego se pasa el corriente del iterador a este hijo derecho y si tiene hijos izquierdos, se los apilan. Al llegar a un nodo hoja (sin hijos) se lo procesa, y se utiliza la pila, para volver
atras y poder continuar.
Al pasar al subarbol derecho del nodo raiz, tuve que guardar un nodo al que llame nodo_a_visitar, ya que como no puedo guardar nodos derechos en la pila, necesitaba poder guardar nodos derechos de alguna forma (ya que en este subarbol no voy a poder comenzar por el extremo como lo hice en el subarbol izquierdo). Tambien se guardo un booleano para saber cuando se pasa del subarbol izquierdo al derecho del nodo_raiz para poder justamante tener en cuenta este cambio de funcionamiento. 
Para la primer iteracion, tuve que crear un booleano ya que cuando creo el iterador, muevo el corriente a donde debo comenzar, por lo tanto solo necesito en esa primera iteracion devolver el elemento. Tambien funciona para salvar del caso de que haya un solo elemento en el arbol.


En las pruebas se probaron los casos borde, tanto con casos null, como con arboles vacios y ademas se utilizaron dos casos:
	-En el primero,se imprimieron los elementos del arbol utilizando el iterador externo. En este caso elegi valores cualquiera y los introduje en un orden tal que se genere un caso complejo para poder probar correctamente el funcionamiento.
	-En el segundo,se utilizo el iterador externo tanto para imprimir los elementos, como para sumarlos. En este caso elegi valores chicos para poder hacer la suma rapidamente.

