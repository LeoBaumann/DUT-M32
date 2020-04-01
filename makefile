all: main

utils.o: utils.h utils.c
	gcc -c -Wall utils.c

aes.o: aes.c aes.h
	gcc -c aes.c -Wall

main: main.c utils.o aes.o
	gcc -o main utils.o main.c aes.o -Wall

clean:
	rm *.o
