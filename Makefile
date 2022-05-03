all:
	gcc -c libpilha.c -o libpilha.o
	gcc -c libfila.c -o libfila.o
	gcc -c liblista.c -o liblista.o
	gcc -std=c90 -Wall libpilha.o liblista.o libfila.o ru_na_pandemia.c -o ru_na_pandemia 

clean:
	-rm -f *~ *.o
