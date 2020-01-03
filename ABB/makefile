CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: pruebas_abb.c
	$(CC) $(CFLAGS)  pruebas_abb.c abb.c abb.h testing.c testing.h -o abb


run: compile
	./abb

valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb


