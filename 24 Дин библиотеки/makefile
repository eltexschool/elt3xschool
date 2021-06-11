add.o: add.c
	gcc -fPIC -c add.c

subtract.o: subtract.c
	gcc -fPIC -c subtract.c

multiply.o: multiply.c
	gcc -fPIC -c multiply.c

divide.o: divide.c
	gcc -fPIC -c divide.c

libmycalc.so: add.o subtract.o multiply.o divide.o
	gcc -shared add.o subtract.o multiply.o divide.o -o libmycalc.so && rm *.o

main: mycalc.h main.c libmycalc.so
	gcc main.c -L. -lmycalc -o main
