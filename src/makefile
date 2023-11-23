hanoi: source.o
	gcc -o hanoi source.o

source.o: src/source.c
	gcc -c src/source.c -o source.o

.PHONY: clean
clean:
	rm -f hanoi source.o
