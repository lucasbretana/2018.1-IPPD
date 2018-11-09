SHELL = /bin/bash

CC = gcc
CFLAG = -Wall -Wextra -Werror -g

RM = rm

N_THREADS ?= 4

.PHONY: all clean test question3 question4
all: question3.out

question3.out: question3.c
	mpicc $(CFLAG) question3.c -o question3.out

.PHONY: runQ3
runQ3: question3.out
	mpirun -n $(N_THREADS) ./question3.out

clean:
	$(RM) *.out || true
