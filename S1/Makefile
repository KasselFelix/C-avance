
GCC_FLAGS = -Wall
all:  tests_tableaux sort

utilitaires_tableaux.o	: utilitaires_tableaux.c
	gcc $(GCC_FLAGS) -c utilitaires_tableaux.c

tris.o	: tris.c 
	gcc $(GCC_FLAGS) -c tris.c

main_tests.o	: main_tests.c
	gcc $(GCC_FLAGS) -c main_tests.c

tests_tableaux	: main_tests.o tris.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o tests_tableaux main_tests.o tris.o utilitaires_tableaux.o

main_sort.o	: main_sort.c
	gcc $(GCC_FLAGS) -c main_sort.c

sort	: main_sort.o tris.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o sort main_sort.o tris.o utilitaires_tableaux.o


clean	:
	rm -f *.o sort tests_tableaux
