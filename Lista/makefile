CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: pruebas_lista_se.c
	$(CC) $(CFLAGS)  pruebas_lista_se.c lista.c lista.h testing.c testing.h -o lista_se


run: compile
	./lista_se

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se


