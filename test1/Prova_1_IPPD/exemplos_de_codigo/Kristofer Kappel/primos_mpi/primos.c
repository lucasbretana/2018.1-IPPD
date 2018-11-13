/* C Example */
//mpicc primos.c -o mpi
//mpirun -np 2 ./mpi
#include <mpi.h>
#include <stdio.h>
 
int main (int argc, char* argv[])
{
	int rank, size;
	int n_primos;
	int i = 0, j = 0;
	int flag;

	scanf("%d", &n_primos);
	int n_task;

	MPI_Init (&argc, &argv);      /* starts MPI */
  	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

	if(rank == 0)
	{
		for(i=1; i<size;i++)
			MPI_Send(&n_primos, 1, MPI_INT, i, 0, MPI_COMM_WORLD); 
	}
	else
		MPI_Recv(&n_primos, 1, MPI_INT, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

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

	

	printf("thread %d, start: %d, end: %d, resto: %d, task: %d, size:%d, primos: %d\n\n", rank, range_start, range_end, resto, n_task, size, n_primos);

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
				printf("%d é primo\n", i); 
			}
		}
	}

	MPI_Finalize();
 
	return 0;
}
