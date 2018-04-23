/**
 * @Name: Lucas Eduardo Bretana
 * @Github: lucasbretana
 * @Email: lebretana@inf.ufpel.edu.br
 * @Desc: makes a consumer/producer example using MPI
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>

#define DEF_SIZE 10
#define MAX_SIZE 100

#ifdef __linux__

#define GREEN "\x1B[32m"
#define BLUE  "\x1B[34m"
#define NCL   "\033[0m"

#define PRINT_MAIN(MSG) do { \
  printf("%sMain process says: %s\n%s", GREEN, MSG, NCL); \
} while(0); 

#define PRINT(RANK, MSG) do { \
  printf("%sProcess n. %d says: %s\n%s", BLUE, RANK, MSG, NCL); \
} while(0);
#elif

#define PRINT_MAIN(MSG) do { \
  printf("Main process says: %s\n", MSG); \
} while(0);

#define PRINT(RANK, MSG) do { \
  printf("Process n. %d says: %s\n", RANK, MSG); \
} while(0);
#endif


typedef struct task_ {
  int *buf;
  int siz;
}task_t;

/**
 * Sorts a task array
 * tast_t * - the pointer to the task
 */
void sort(task_t *task) {
  task = task;
}

/**
 * Creates task, the array will have the given size
 * int    - the size, should be strict positive, i.e., > 0
 * return - the pointer to the new task
 */
task_t *createTask(int s){
  assert(s > 0);
  task_t *new = calloc(1, sizeof(task_t));
  assert(new != NULL);
  new->siz = s;
  new->buf = calloc(s, sizeof(int));
  assert(new->buf != NULL);
  for(int i=0 ; i<s ; ++i)
    new->buf[i] = rand();
  return new;
}

/**
 * Destroy a task
 * task_t * - the pointer to the task
 */
void destroyTask(task_t *task) {
  if(task != NULL) {
    if(task->buf != NULL) 
      free(task->buf);
    free(task);
  }
}

/**
 * How to do a prod-cons using message passing
 * -> a consumer request a task, sending its rank
 *
 * -> the producer receive a request with a rank, then send the task to the given process' rank
 **/
int main(int argc, char **argv){
  srand(time(NULL));
  int my_rank = 0;
  int comm_size = 0;
  task_t *task = NULL;
  int req = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);


  //--------------------------------
  // Creating a new MPI_Datatype
  MPI_Datatype MPI_task_t;

  int sizes[] = {DEF_SIZE, 1};  // number of blocks
  MPI_Aint address[] = {offsetof(task_t, buf), offsetof(task_t, siz)}; // offset of each block
  MPI_Datatype types[] = {MPI_INT, MPI_INT};  // size of each type of block

  // creates a new type based on:
  // how many types of blocks there are, 
  // the size of each array of blocks, 
  // the types of each block
  if(MPI_Type_create_struct(2, sizes, address, types, &MPI_task_t) != MPI_SUCCESS) {
    fprintf(stderr, "Error creating the new type\n");
    exit(1);
  }

  if(MPI_Type_commit(&MPI_task_t) != MPI_SUCCESS) {
    fprintf(stderr, "Error commiting the new type\n");
    exit(2);
  }

  //--------------------------------


  if(my_rank == 0){
    for(int i=0 ; i<(comm_size-1) * 10 ; ++i) {
      PRINT_MAIN("waiting request");
      MPI_Recv(&req, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // -- receive a request with the rank of the requester
      //Create a task, and send it
      assert((req > 0) && (req < comm_size));
      task = createTask(DEF_SIZE);
      PRINT_MAIN("sending task");
      MPI_Send(task, 1, MPI_task_t, req, 0, MPI_COMM_WORLD); // -- send the task to the process
      destroyTask(task);
    }
    PRINT_MAIN("done with tasks");
    task = malloc(sizeof(task_t));
    task->siz = 0;
    for(int i=1 ; i<comm_size ; ++i) {
      PRINT_MAIN("Killing processes");
      MPI_Send(task, 1, MPI_task_t, i, 0, MPI_COMM_WORLD);
    }
    free(task);
  } else {
    task = malloc(sizeof(task_t));
    do {
      MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // -- send the rank, requesting a new task

      PRINT(my_rank, "waiting task");
      MPI_Recv(task, 1, MPI_task_t, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // -- get the new task
      sort(task);
    } while(task->siz != 0);
    PRINT(my_rank, "finished");
  }
  MPI_Type_free(&MPI_task_t);

  MPI_Finalize();

  printf("\n");
  return 0;
}

