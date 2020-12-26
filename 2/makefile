CFLAGS = -c


hijo:p2-hijo.o
	$(CC) p2-hijo.o -o hijo

p2-padre.o:p2-padre.c
	$(CC) $(CFLAGS) p2-padre.c


p2-hijo.o:p2-hijo.c
	$(CC) $(CFLAGS) p2-hijo.c


clean:
	$(RM) *o. padre hijo padre.o hijo.o core

