all: lab-05_c-io

flag = -c -I "include"

obj/main.o: src/main.c
	mkdir obj
	gcc $(flag) src/main.c -o obj/main.o
obj/clist.o: src/clist.c
	gcc $(flag) src/clist.c -o obj/clist.o
obj/point_list.o:src/point_list.c
	gcc $(flag) src/point_list.c -o obj/point_list.o
lab-05_c-io: obj/main.o obj/clist.o obj/point_list.o
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab-05_c-io

clean:
	rm -rf obj lab-05_c-io