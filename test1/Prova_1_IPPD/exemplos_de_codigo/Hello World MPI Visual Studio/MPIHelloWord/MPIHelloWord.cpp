// MPIHelloWord.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[]){
	int num_proc, id_proc, contador;

	MPI_Init(NULL,NULL); //inicializa o MPI, dispara os processos
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc); //desobre o numero de processos
	MPI_Comm_rank(MPI_COMM_WORLD, &id_proc); //descobre o id de cada processo

		if (id_proc != 0) {
			MPI_Recv(&contador, 1, MPI_INT, (id_proc-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%d recebe de %d\n", id_proc, id_proc-1);
			
		}
		else {
			contador = - 1;
		}
		MPI_Send(&contador, 1, MPI_INT, (id_proc+1)%num_proc, 0, MPI_COMM_WORLD);
		if (id_proc == 0) {
			MPI_Recv(&contador, 1, MPI_INT, num_proc-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%d recebe de %d\n", id_proc, num_proc-1);
		}

	MPI_Finalize(); //finaliza o MPI
	return 0;
}

