all:
	gcc -c libpilha.c -o libpilha.o
	gcc -std=c90 -Wall libpilha.o ru_na_pandemia.c -o ru_na_pandemia 

clean:
	-rm -f *~ *.o
