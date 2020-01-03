El archivo zip entregado tiene la implementacion del tp 2, las bibliotecas con funciones para que funcione el programa y algunos archivos de texto a modo de ejemplo.
A su vez, tambien se entregara un makefile para poder compilar y ejecutar. 
-Para compilar el programa debera ejecutar en su terminal el comando: "make compile".
-Para ejecutarlo: "make run".
-Para correrlo con valgrind: "make valgrind".

El objetivo del tp es demostrar la correcta utilizacion de los TDA implementados durante el cuatrimestre. Para eso, se realiza una simulacion.
En esta se ingresa un archivo de texto con casas y sus integrantes. Las casas se guardan en ABBs mientras que los integrantes se guardan en listas.
Si una casa, durante la simulacion, se queda sin integrantes, esta casa se guarda en una cola.

Aclaracion: Con el objetivo de evitar la mayor cantidad de errores a la hora de leer archivos, se decidio implementar con codigo robusto la funcion agregar_casa, motivo por el cual esta funcion tiene una extension demasiado larga.

Al ejecutar el programa, los datos del archivo "SDA.txt" ya se encuentran cargados. Siempre se debe ejecutar el programa con algun archivo de casas ingresado.
Luego, el usuario podra ir ingresando comandos para realizar acciones:

-S: Se simula la cantidad de años que ingrese el usuario. Durante cada año, se aumenta la edad de las personas segun un factor propio de cada casa, si esta supera un valor maximo estas mueren y se borran.A su vez, luego nacen personas segun un factor propio de cada casa. Al finalizar, se informa que casa se queda con el trono.
Aclaracion: en caso de empate tambien se informa que gana una sola casa, esto depende de su orden en un vector.

-L: Se listan las casas segun la cantidad de personas, en orden descendente.

-A: Se agrega casas desde un archivo que ingresa el usuario. En caso de que haya casas repetidas, solamente se le agregan las personas.
El archivo debe seguir el siguiente formato de ejemplo:

C; nombre_de_la_casa1;factor_de_envejecimiento;factor_de_nacimiento
I;nombre_persona_1;edad
I;nombre_persona_2;edad
I;nombre_persona_3;edad
...
I;nombre_persona_N;edad
C; nombre_de_la_casa2;factor_de_envejecimiento;factor_de_nacimiento
I;nombre_persona_1;edad
...

En el zip, se encuentran los archivos "SDA.txt","casas.txt" y "datos.dat" tanto para usar en la simulacion como para ver como ejemplo

-E: Se listan las casas que se quedaron sin personas, en el orden que se extinguieron.

-Q: Para finalizar la ejecucion.

Solo con el archivo "SDA.txt", los resultados esperados al simular son:

-Sin simular:
Casa 'Stark' --> Cantidad de personas: 37
Casa 'Martell' --> Cantidad de personas: 35
Casa 'Arryn' --> Cantidad de personas: 35
Casa 'Tyrell' --> Cantidad de personas: 33
Casa 'Baratheon' --> Cantidad de personas: 29
Casa 'Lannister' --> Cantidad de personas: 22

-5 años:
Casa 'Martell' --> Cantidad de personas: 37
Casa 'Stark' --> Cantidad de personas: 34
Casa 'Arryn' --> Cantidad de personas: 31
Casa 'Tyrell' --> Cantidad de personas: 28
Casa 'Baratheon' --> Cantidad de personas: 22
Casa 'Lannister' --> Cantidad de personas: 20

-10 años:
Casa 'Martell' --> Cantidad de personas: 32
Casa 'Stark' --> Cantidad de personas: 30
Casa 'Arryn' --> Cantidad de personas: 27
Casa 'Tyrell' --> Cantidad de personas: 22
Casa 'Lannister' --> Cantidad de personas: 16
Casa 'Baratheon' --> Cantidad de personas: 13

-20 años:
Casa 'Stark' --> Cantidad de personas: 27
Casa 'Martell' --> Cantidad de personas: 27
Casa 'Arryn' --> Cantidad de personas: 18
Casa 'Tyrell' --> Cantidad de personas: 12
Casa 'Lannister' --> Cantidad de personas: 10
Extintas:  Casa Baratheon

-25 años:
Casa 'Stark' --> Cantidad de personas: 27
Casa 'Martell' --> Cantidad de personas: 27
Casa 'Arryn' --> Cantidad de personas: 18
Casa 'Lannister' --> Cantidad de personas: 10
Casa 'Tyrell' --> Cantidad de personas: 5
Extintas:  Casa Baratheon

-50 años:
Casa 'Stark' --> Cantidad de personas: 27
Casa 'Martell' --> Cantidad de personas: 27
Casa 'Arryn' --> Cantidad de personas: 18
Casa 'Lannister' --> Cantidad de personas: 10
Extintas:  Casa Baratheon y Casa Tyrell
(a partir de aca se mantienen estables los valores)



