CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: tp2.c
	$(CC) $(CFLAGS)  tp2.c abb.c abb.h lista.c lista.h cola.c cola.h mergesort.c mergesort.h juego.c juego.h -o tp2


run: compile
	./tp2

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./tp2


