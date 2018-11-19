CC = gcc
CF = -Wall -Wextra -lOpenCL

.PHONY: all
all: a.out

a.out: bretana.c
	$(CC) bretana.c $(CF)

.PHONY: run
run: a.out
	./a.out

.PHONY: clean
clean:
	rm *.out


