#
# Makefile for Java
#

CC = g++

CFLAGS = 

OBJS = main.o util.o lex.o

lexer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o lexer

main.o: main.c globals.h util.h lexer.h
	$(CC) $(CFLAGS) -c main.cpp

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.cpp

lex.o: lexer.cpp lexer.h
	$(CC) $(CFLAGS) -c lexer.cpp

clean:
	-rm lexer
	-rm $(OBJS)

all: lexer