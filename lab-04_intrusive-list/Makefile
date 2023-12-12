comp = gcc
flag = -c -I "include"
main.o = obj/main.o
clist.o = obj/clist.o
main.c = src/main.c
clist.c = src/clist.c

all: lab-04_intrusive-list

$(main.o): $(main.c)
	mkdir obj
	$(comp) $(flag) $(main.c) -o $(main.o)

$(clist.o): $(clist.c)
	$(comp) $(flag)  $(clist.c) -o $(clist.o)

lab-04_intrusive-list: $(main.o) $(clist.o)
	$(comp) $(main.o) $(clist.o) -o lab-04_intrusive-list

clean:
	rm -rf obj lab-04_intrusive-list