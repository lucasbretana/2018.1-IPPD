/* C Example */
//gcc -fopenmp exopenmp.c
//./a.out
#include <omp.h>
#include <stdio.h>


void primos(int n_primos, int * primos_counter)
{
	int rank= omp_get_thread_num();
	int size= omp_get_num_threads();
	int i = 0, j = 0;
	int flag;
	int n_task;

	n_task = n_primos/size;
	int resto = n_primos%size;

	int range_start;
	int range_end;

	if(rank < resto) 
	{
		range_start = rank * n_task + rank + 1;
		range_end = (rank) * n_task + rank + n_task + 1;
	}
	else
	{
		range_start = rank * n_task + resto + 1;
		range_end = (rank) * n_task + resto + (n_task - 1) + 1;
	}

	

	//printf("thread %d, start: %d, end: %d, resto: %d, task: %d, size:%d, primos: %d\n\n", rank, range_start, range_end, resto, n_task, size, n_primos);

	for(i=range_start; i<= range_end; i++)
	{
		if(i != 0 && i != 1)
		{
			flag = 0;
			for(j=2; j<i; j++)
			{
				if(i%j == 0)
				{
					flag =1;
					break;
				}			
			}
			if (flag == 0)
			{
				#pragma omp critical
				(*primos_counter) ++;
			}
		}
	}

	
}

 
int main (int argc, char* argv[])
{
	int rank, size;
	int n_primos;
	int i = 0, j = 0;
	int counter = 0;

	scanf("%d", &n_primos);
	int n_task;


	#pragma omp parallel num_threads(5)
	primos(n_primos, &counter);
 
 	printf("Numero de primos:  %d\n", counter);
	return 0;
}
