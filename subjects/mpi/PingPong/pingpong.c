#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <assert.h>

int main(void){
  char  *greeting = strdup("Ping");
  int   comm_sz = 2;
  int   my_rank = 0;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);  // number of taks
  assert(comm_sz == 2);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  // process rank (id)

  for(int i=0 ; i<10 ; ++i){
    if(my_rank == 0) {
      printf("%s ", greeting);
      fflush(stdout);
      MPI_Send(&"pong", 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else {
      MPI_Recv(greeting, 4, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%s\n", greeting);
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  MPI_Finalize();
  free(greeting);

  return 0;
}
