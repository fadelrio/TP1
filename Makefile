CFLAGS=-Wall -std=c99 -pedantic -g -lm

all: MonoBridge

MonoBridge: malla.o main.o nodo.o resorte.o lista.o vector.o simulador.o
	gcc malla.o main.o nodo.o resorte.o lista.o vector.o simulador.o -o MonoBridge -lSDL2 -lm
main.o: main.c malla.h config.h
	gcc $(CFLAGS) -lSDL2 -c main.c
malla.o: malla.c malla.h nodo.h resorte.h lista.h vector.h simulador.h config.h
	gcc $(CFLAGS) -lSDL2 -c malla.c
nodo.o: nodo.c nodo.h
	gcc $(CFLAGS) -c nodo.c
resorte.o: resorte.c resorte.h nodo.h config.h
	gcc $(CFLAGS) -c resorte.c
lista.o: lista.c lista.h
	gcc $(CFLAGS) -c lista.c
vector.o: vector.c vector.h
	gcc $(CFLAGS) -c vector.c
simulador.o: simulador.c simulador.h malla.h nodo.h resorte.h vector.h lista.h
	gcc $(CFLAGS) -c simulador.c
clean: 
	rm -vf *.o MonoBridge
