/**
 * @Name: Lucas Eduardo Bretana
 * @Github: lucasbretana
 * @Email: lebretana@inf.ufpel.edu.br
 * @Desc: Makes a parallel merge sort
 */
/**
 * How to make a parallel merge sort?
 *
 * Using: childID = 2^i + rank < comm_size
 * i: interaction
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#ifndef SEED
#define SEED 313
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 10
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#define CHILD_ID pow(2, ite) + my_rank

void debug(void);

/**
 * Divide part
 * #Parameters
 * array: array of the function, this array is going to be splited in half (dont touch it)
 * b: index begin
 * e: index end
 */
void mergesort(int *, int, int);

/**
 * Conquer part
 * #Parameters
 * int *: array to merge into another
 * int: left boundarie
 * int: middle boundaries (NOTE: this should be index of the first element on second array, and NOT be a valid index for the first array)
 * int: the right boundaries
 */
void merge(int *, int, int, int);

/**
 * Just print an array
 * int *: the array address
 * int: low boundarie (inclusive)
 * int: high bondarie (inclusive)
 */
void print(FILE *, int *, int , int );

int my_rank = 0;
int sz_comm = 0;
int ite = 0;
double tp_time = 0.0L;
double mp_time = 0.0L;
double mc_time = 0.0L;
int main(int argc, char **argv){
  int *array = NULL;
  int low = 0, high = ARRAY_SIZE - 1;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &sz_comm);
  assert(sz_comm > 1 && "Must execute with 2+ processes");

  double l_start = 0.0L;
  mp_time = MPI_Wtime();
  if(my_rank == 0) {
    tp_time = MPI_Wtime();
    srand(SEED);

    // generate array
    array = malloc(sizeof(int) * ARRAY_SIZE);
    assert(array);

    for(int i=low ; i<=high ; ++i) 
      array[i] = rand() % ARRAY_SIZE;
    // end array generation

    fprintf(stderr, "TODO:\n");
    print(stderr, array, low, high);
    int child = (int) CHILD_ID;
    
    //-- send second half of the array
    debug();
    int med = (high/2)+1;
    l_start = MPI_Wtime();
    MPI_Send(&ite, 1, MPI_INT, child, 0, MPI_COMM_WORLD);
    MPI_Send(&array[med], high-med+1, MPI_INT, child, 0, MPI_COMM_WORLD);
    mc_time += MPI_Wtime() - l_start;
    ++ite;
    
    mergesort(array, low, med-1); // keep dividing

    l_start = MPI_Wtime();
    MPI_Recv(&array[med], high-med+1, MPI_INT, child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    mc_time += MPI_Wtime() - l_start;

    merge(array, low, med, high);
    
    fprintf(stderr, "DONE:\n");
    print(stderr, array, low, high);
  } else { 
    int size = ARRAY_SIZE / (pow(2, ite + 1));
    array = malloc(sizeof(int) * size);
    assert(array);
    MPI_Status deliver;

    debug();
    MPI_Recv(&ite, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &deliver);
    MPI_Recv(array, ARRAY_SIZE, MPI_INT, deliver.MPI_SOURCE, 0, MPI_COMM_WORLD, &deliver);
    MPI_Get_count(&deliver, MPI_INT, (int *)&high);
    --high;
    ++ite;
    mergesort(array, 0, high); // keep dividing

    l_start = MPI_Wtime();
    MPI_Send(array, high+1, MPI_INT, deliver.MPI_SOURCE, 0, MPI_COMM_WORLD);
    mc_time += MPI_Wtime() - l_start;
  }
  free(array);

  mp_time = MPI_Wtime() - mp_time;
  printf("%d, %d, %lf, %lf\n", sz_comm, my_rank, mp_time * 1000, mc_time * 1000);
  MPI_Finalize();
  if(my_rank == 0)
    printf("%d, %lf\n", sz_comm, (MPI_Wtime() - tp_time) * 1000);

  return 0;
}

void print(FILE *stream, int *vet, int s, int f){
  if(!DEBUG) return;
  for(int i=s ; i<=f ; ++i) 
    fprintf(stream, "[%d] > array[%d] = %d;\n", my_rank, i, vet[i]);
  fprintf(stream, "\n");
}

/**
 * Conquer part
 * This will receive the part and merge them
 * #Parameters
 * int *: array to merge into another
 * int: left boundarie
 * int: middle boundaries (NOTE: this should be index of the first element on second array, and NOT be a valid index for the first array)
 * int: the right boundaries
 */
void merge(int array[], int a, int c, int d) {
  // left boundaries [a,b]
  // right boundaries [c,d]
  int b = c-1;
  int left = a, right = c;

  int mark = 0;
  int sz_res = d-a+1, *res = malloc(sizeof(int) * sz_res);
  assert(res);
  
  // compare
  while((left<=b) && (right <= d)) {
    if(array[left] < array[right]) 
      res[mark++] = array[left++];
    else
      res[mark++] = array[right++];
  }

  // left
  while((left<=b) && (mark <= sz_res))
    res[mark++] = array[left++];

  //right
  while((right<=d) && (mark <= sz_res))
    res[mark++] = array[right++];

  //copy back
  for(int i=a, mark=0;i<=d && mark<=sz_res;++i, ++mark)
    array[i] = res[mark];

  free(res);

}

/**
 * Divide part
 * If there is any child process waiting yet, then send a message to one of them with
 *  -> half of the array,
 * Then call recursion for first half
 * #Parameters
 * array: array of the function, this array is going to be splited in half (dont touch it)
 * b: index begin
 * e: index end
 */
void mergesort(int array[], int b, int e) {
  if(e <= b) { // single element array, return
    return;
  }

  int fstArray2 = ((e-b)/2)+1 + b;
  int childID = (int)CHILD_ID;
  if(childID < sz_comm - 1) {
    // send the second half to child
    double l_start = MPI_Wtime();
    MPI_Send(&ite, 1, MPI_INT, childID, 0, MPI_COMM_WORLD);
    MPI_Send(&array[fstArray2], e-fstArray2+1, MPI_INT, childID, 0, MPI_COMM_WORLD);
    mc_time += MPI_Wtime() - l_start;
    ++ite;

    // call for the first half
    mergesort(array, b, fstArray2-1);

    // receive back the work
    l_start = MPI_Wtime();
    MPI_Recv(&array[fstArray2], e-fstArray2+1, MPI_INT, childID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    mc_time += MPI_Wtime() - l_start;
  } else {
    // call for the first half
    mergesort(array, b, fstArray2-1);
    // call mergesort for the second half
    mergesort(array, fstArray2, e);
  }

  merge(array, b, fstArray2, e);

}

/**
 * Enter debug mode, waiting to some debbuger connect
 */
void debug(void) {
  if(!DEBUG) return;

  int i = 0;
  char hostname[256];
  gethostname(hostname, 256);
  printf("(%d) Is waiting connection. PID: %d, hostname: %s\n", my_rank, getpid(), hostname);

  while(i == 0)
    sleep(5);

}
