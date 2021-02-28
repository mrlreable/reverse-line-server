# -*- MakeFile -*-

all: main client

main: main.o
	gcc main.o -o main -l ws2_32

main.o: main.c
	gcc -c main.c

client: client.o
	gcc client.o -o client -l ws2_32

client.o: client.c
	gcc -c client.c

clean:
	del *.o main client
