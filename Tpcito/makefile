CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: tpfinal.c
	$(CC) $(CFLAGS)  tpfinal.c abb.c abb.h pila.c pila.h iterador_externo_abb.c iterador_externo_abb.h testing.c testing.h -o tpfinal


run: compile
	./tpfinal

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./tpfinal


