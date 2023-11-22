runme: source.o
	gcc -o runme source.o

source.o: source.c
	gcc -o source.o -c source.c

.PHONY: clean
clean:
	rm -f runme source.o
