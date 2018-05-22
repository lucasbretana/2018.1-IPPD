SHELL = bash

NAME = mergesort_mpi
CC = mpicc
C_FLAG = -Wall -Wextra -Werror
EXEC = mpiexec
RSCRIPT ?= generateTables

comp: merge_sort.c 
	$(CC) $(C_FLAG) merge_sort.c -o $(NAME).out -lm

run: comp $(NAME).out $(RSCRIPT).R
	@for((NPROC=10;NPROC<$(MX_PROX);NPROC+=10)); do \
		@echo "Running with "
		for((ASIZE=100;ASIZE<$(MX_SIZE);ASIZE+=10)); do \	
			ifeq ($(DEBUG), 1)
				$(EXEC) -n $(NPROC) $(TARGET).out $(ASIZE) 1> $(LOG).log
			else
				$(EXEC) -n $(NPROC) $(TARGET).out $(ASIZE) 2> /dev/null 1> $(LOG).log
			endif
		done;
	done;


