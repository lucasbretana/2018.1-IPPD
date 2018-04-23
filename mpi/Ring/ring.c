#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){
  int   comm_sz = 0;
  int   my_rank = 0;
  int   token = 0; 

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  if(my_rank == 0)
    printf("BEGIN\n");

  if(my_rank == 0) {
    printf("First.\tIt's me, process n. %d\n", token++);
    MPI_Send(&token, 1, MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
  } else {
    MPI_Recv(&token, 1, MPI_INT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if(token == my_rank) {
      printf("It's me, process n. %d\n", token++);
      if(my_rank < comm_sz - 1)
        MPI_Send(&token, 1, MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();

  if(my_rank == 0)
    printf("END\n");
  return 0;
}

