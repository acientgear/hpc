FLAGS= -Wall -lm -fopenmp

det: det.c funciones.o
	gcc $(FLAGS) -o det det.c funciones.o

funciones.o: funciones.c
	gcc -c $(FLAGS) funciones.c

clear:
	rm -f *.o det



