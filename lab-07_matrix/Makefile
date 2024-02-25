all: lab-07_matrix

flag = -g3 -c -I "include"

obj/main.o: src/main.cpp
	mkdir obj
	g++ $(flag) src/main.cpp -o obj/main.o
obj/matrix.o: src/matrix.cpp
	g++ $(flag) src/matrix.cpp -o obj/matrix.o

lab-07_matrix: obj/main.o obj/matrix.o
	g++ obj/main.o obj/matrix.o -o lab-07_matrix

clean:
	rm -rf obj/ lab-07_matrix

