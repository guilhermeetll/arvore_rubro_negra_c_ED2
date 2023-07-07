all: tree.o

	gcc tree.c main.c -o trab

func.o: func.h
	gcc -c func.c

clean:
	rm -rf *.o

run:
	./trab