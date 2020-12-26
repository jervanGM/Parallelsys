all: p7-1 p7-2 p7-3 p7-4

p7-1: p7-1.c
	gcc -o p7-1 p7-1.c

p7-2: p7-2.c
	gcc -o p7-2 p7-2.c

p7-3: p7-3.c
	gcc -o p7-3 p7-3.c

p7-4: p7-4.c
	gcc -o p7-4 p7-4.c

clean:
	rm -f p7-1 p7-2 p7-3 p7-4
