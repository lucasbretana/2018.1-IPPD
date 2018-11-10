SHELL = /bin/bash

CC = gcc
CFLAG = -Wall -Wextra -Werror -g

RM = rm

N_THREADS ?= 4

.PHONY: all clean test question3 question4
all: question3.out question4.out

question3.out: question3.c
	mpicc $(CFLAG) question3.c -o question3.out

.PHONY: runQ3
runQ3: question3.out
	mpirun -n $(N_THREADS) ./question3.out

question4.out: question4.c
	$(CC) $(CFLAG) -fopenmp question4.c -o question4.out

.PHONY: runQ3
runQ4: question4.out
	./question4.out

clean:
	$(RM) *.out || true
