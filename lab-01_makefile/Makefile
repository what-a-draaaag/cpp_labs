all: lab-01_makefile

obj/main.o:src/main.c
	mkdir -p obj
	gcc -c src/main.c -I "include/" -o obj/main.o

obj/util.o:src/util.c
	gcc -c src/util.c -I "include/" -o obj/util.o

obj/io.o:src/io.c
	gcc -c src/io.c -I "include/" -o obj/io.o

obj/algorithm.o:src/algorithm.c
	gcc -c src/algorithm.c -I "include/" -o obj/algorithm.o

lab-01_makefile: obj/main.o obj/util.o obj/io.o obj/algorithm.o
	gcc obj/* -o lab-01_makefile


clean:
	rm -rf obj lab-01_makefile