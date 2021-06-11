add.o: add.c
	gcc -c add.c

subtract.o: subtract.c
	gcc -c subtract.c

multiply.o: multiply.c
	gcc -c multiply.c

divide.o: divide.c
	gcc -c divide.c

libmycalc.a: add.o subtract.o multiply.o divide.o
	ar -rcs libmycalc.a add.o subtract.o multiply.o divide.o && rm *.o

main: mycalc.h main.c libmycalc.a
	gcc main.c -L. -lmycalc -o main
