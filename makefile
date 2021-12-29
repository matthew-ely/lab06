
compile:
	gcc -Wall -pedantic-errors -o cat cat.c
run:
	./cat a.txt b.txt c.txt
clean:
	rm -f cat
	rm -f *.o
