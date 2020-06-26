all: mem.o pmem.o init.o
	gcc mem.o pmem.o init.o -o all
mem.o: mem.c
	gcc -c mem.c -o mem.o
pmem.o: pmem.c
	gcc -c pmem.c -o pmem.o
init.o: init.c
	gcc -c init.c -o init.o

.PHONY:clean
clean:
	rm -rf *.o
