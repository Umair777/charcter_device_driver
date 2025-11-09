#! /bin/bash

app: main.o OpenDevice.o displaymenu.o Writedevice.o
	gcc -o app main.o OpenDevice.o displaymenu.o Writedevice.o
main.o: main.c declarations.h header.h
	gcc -c main.c
OpenDevice.o: OpenDevice.c declarations.h header.h
	gcc -c OpenDevice.c
displaymenu.o: displaymenu.c declarations.h header.h
	gcc -c displaymenu.c
WriteDevice.o: WriteDevice.c declarations.h header.h
	gcc -c WriteDevice.c
