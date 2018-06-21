CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = SpellChecker.o linkedlist.o processarray.o fileio.o
EXEC = SpellChecker

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) check.o -o $(EXEC)

SpellChecker.o : SpellChecker.c SpellChecker.h linkedlist.h check.h
	$(CC) SpellChecker.c -c $(CFLAGS)

fileio.o : fileio.c fileio.h SpellChecker.h linkedlist.h
	$(CC) fileio.c -c $(CFLAGS)
	
processarray.o : processarray.c processarray.h SpellChecker.h linkedlist.h
	$(CC) processarray.c -c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) linkedlist.c -c $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
