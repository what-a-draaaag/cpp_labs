all: lab-06_int-vector

flag = -g3 -c -I "include"

obj/main.o: src/main.cpp
	mkdir obj
	g++ $(flag) src/main.cpp -o obj/main.o
obj/my_vector.o: src/my_vector.cpp
	g++ $(flag) src/my_vector.cpp -o obj/my_vector.o

lab-06_int-vector: obj/main.o obj/my_vector.o
	g++ obj/main.o obj/my_vector.o -o lab-06_int-vector

clean:
	rm -rf obj lab-06_int-vector
