CFLAGS = -c
CC = gcc

p3-1:p3-1.o
	$(CC) p3-1.o -o p3-1
	
p3-1.o:p3-1.c
	$(CC) $(CFLAGS) p3-1.c
	
p3-2:p3-2.o
	$(CC) p3-2.o -o p3-2
	
p3-3:p3-3.o
	$(CC) p3-3.o -o p3-3

p3-2.o:p3-2.c
	$(CC) $(CFLAGS) p3-2.c

p3-3.o:p3-3.c
	$(CC) $(CFLAGS) p3-3.c
	
p3-4:p3-4.o
	$(CC) p3-4.o -o p3-4
	
p3-4.o:p3-4.c
	$(CC) $(CFLAGS) p3-4.c

clean:
	$(RM) *o. p3-1 p3-2 p3-3 p3-4 p3-1.o p3-4.o p3-2.o p3-3.o core
	
