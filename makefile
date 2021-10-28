all: main.o
	gcc -g -o program main.o
main.o: main.c
	gcc -g -c main.c

run:
	./program
clean:
	rm -rf program main.o
