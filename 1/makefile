CFLAGS = -c

OBJECTS = main.o func1.o func2.o

programa:$(OBJECTS)
	$(CC) $(OBJECTS) -o programa

main.o:main.c
	$(CC) $(CFLAGS) main.c

func1.o:func1.c
	$(CC) $(CFLAGS) func1.c

func2.o:func2.c
	$(CC) $(CFLAGS) func2.c

clean:
	$(RM) *o. programa main.o func1.o func2.o core


