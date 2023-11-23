all: obj/ lab-02_cstrings

obj/:
	mkdir obj

obj/test.o:src/test.c
	gcc -c src/test.c -I "include/" -o obj/test.o

obj/test_str.o:src/test_str.c
	gcc -c src/test_str.c -I "include/" -o obj/test_str.o

obj/str.o:src/str.c
	gcc -c src/str.c -I "include/" -o obj/str.o

lab-02_cstrings:obj/test.o obj/test_str.o obj/str.o
	gcc obj/test.o obj/test_str.o obj/str.o -o lab-02_cstrings

clean:
	rm -rf obj lab-02_cstrings