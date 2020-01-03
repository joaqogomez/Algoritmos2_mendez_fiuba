CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: pruebas_pila_vd.c
	$(CC) $(CFLAGS)  pruebas_pila_vd.c pila.c pila.h -o pila_vd


run: compile
	./pila_vd

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd


