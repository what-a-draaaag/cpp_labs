all: mergesort

obj/main.o:src/main.c
	mkdir obj
	gcc -c src/main.c -I "include" -o obj/main.o

obj/mergesort.o:src/mergesort.c
	gcc -c src/mergesort.c -I "include" -o obj/mergesort.o

mergesort: obj/main.o obj/mergesort.o
	gcc obj/main.o obj/mergesort.o -o lab-03_mergesort

clean:
	rm -rf obj lab-03_mergesort