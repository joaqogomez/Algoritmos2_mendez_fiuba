CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: pruebas_cola_ne.c
	$(CC) $(CFLAGS)  pruebas_cola_ne.c cola.c cola.h -o cola_ne


run: compile
	./cola_ne

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_ne


