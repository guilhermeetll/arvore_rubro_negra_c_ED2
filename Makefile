all: tree.o

	gcc tree.o main.c -o main

func.o: func.h
	gcc -c func.c

clean:
	rm -rf *.o

run:
	./main