#! /bin/bash

Uapp : displaymenu.o main.o device.o 
	gcc -o Uapp displaymenu.o main.o device.o

device.o : device.c headers.h prototypes.h 
	gcc -c device.c
displaymenu.o : displaymenu.c headers.h prototypes.h 
	gcc -c displaymenu.c
main.o : main.c headers.h prototypes.h
	gcc -c main.c

clean:
	rm *.o Uapp	
