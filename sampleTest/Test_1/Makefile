SHELL = /bin/bash

CC = gcc
CFLAG = -Wall -Wextra -Werror -g

RM = rm

BIN = bin
SRC = src
DOC = doc

.PHONY: all clean test question3 question4
all: question3.out

question3.out: question3.c
	mpicc $(CFLAG) question3.c -o question3.out

.PHONY: test
test: question3.out
	./question3.out

clean:
	$(RM) *.out
