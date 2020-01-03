CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: pruebas_hash.c
	$(CC) $(CFLAGS)  pruebas_hash.c hash.c hash.h hash_iterador.c hash_iterador.h testing.c testing.h abb.h abb.c -o hash


run: compile
	./hash

valgrind: compile
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash


