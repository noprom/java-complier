#
# Makefile for Java
#

CC = g++

CFLAGS = 

OBJS = main.o util.o lex.o

lexer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o lexer

main.o: main.cpp globals.h util.h lexer.h
	$(CC) $(CFLAGS) -c main.cpp

util.o: util.cpp util.h
	$(CC) $(CFLAGS) -c util.cpp

lex.o: lexer.cpp lexer.h
	$(CC) $(CFLAGS) -c lexer.cpp

clean:
	-rm lexer
	-rm $(OBJS)

all: lexer