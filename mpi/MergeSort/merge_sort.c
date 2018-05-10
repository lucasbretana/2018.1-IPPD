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

void print(int *, int , int );

int my_rank = 0;
int sz_comm = 0;
int main(int argc, char **argv){
  int ite = 0;
  int *array = NULL;
  int low = 0, high = ARRAY_SIZE - 1;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &sz_comm);
  assert(sz_comm > 1 && "Must execute with 2+ processes");

  if(my_rank == 0) {
    srand(SEED);

    // generate array
    array = malloc(sizeof(int) * ARRAY_SIZE);
    assert(array);

    for(int i=low ; i<=high ; ++i) 
      array[i] = rand() % ARRAY_SIZE;
    // end array generation

    print(array, low, high);
    int child = (int) CHILD_ID;
    
    //-- send second half of the array
    debug();
    int med = (high/2)+1;
    fprintf(stderr, "(%d) Sending: array [%d, %d] to %d\n", my_rank, med, high, child);
    MPI_Send(&ite, 1, MPI_INT, child, 0, MPI_COMM_WORLD);
    MPI_Send(&array[med], high-med+1, MPI_INT, child, 0, MPI_COMM_WORLD);
    fprintf(stderr, "(%d) DONE: sending: array [%d, %d] to %d\n", my_rank, med, high, child);
    ++ite;
    
    fprintf(stderr, "(%d) Mergesort: array [%d,%d]\n", my_rank, low, med-1);
    mergesort(array, low, med-1); // keep dividing
    fprintf(stderr, "(%d) DONE: mergesort: array [%d,%d]\n", my_rank, low, med-1);

    fprintf(stderr, "(%d) Receiving: array [%d,%d] from %d\n", my_rank, med, high, child);
    MPI_Recv(&array[med], high-med+1, MPI_INT, child, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    fprintf(stderr, "(%d) DONE: receiving: array [%d,%d] from %d\n", my_rank, med, high, child);

    fprintf(stderr, "(%d) Merge: array1 [%d,%d] with array2 [%d,%d]\n", my_rank, low, med-1, med, high);
    merge(array, low, med, high);
    fprintf(stderr, "(%d) DONE: merge: array1 [%d,%d] with array2 [%d,%d]\n", my_rank, low, med-1, med, high);
    
    print(array, low, high);
    /*
    printf("\n(%d) THE END: ", my_rank);
    print(array, 0, high);
    printf("\n");
    */

  } else { 
    int size = ARRAY_SIZE / (pow(2, ite + 1));
    array = malloc(sizeof(int) * size);
    assert(array);
    MPI_Status deliver;

    fprintf(stderr, "(%d) Receiving first part\n", my_rank);
    debug();
    MPI_Recv(&ite, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &deliver);
    MPI_Recv(array, ARRAY_SIZE, MPI_INT, deliver.MPI_SOURCE, 0, MPI_COMM_WORLD, &deliver);
    MPI_Get_count(&deliver, MPI_INT, (int *)&high);
    --high;
    fprintf(stderr, "(%d) Received: array [0,%d] from %d\n", my_rank, high, deliver.MPI_SOURCE);
    ++ite;
    fprintf(stderr, "(%d) Mergesort: array [0,%d]\n", my_rank, high);
    mergesort(array, 0, high); // keep dividing
    fprintf(stderr, "(%d) DONE: mergesort: array [0,%d]\n", my_rank, high);

    fprintf(stderr, "(%d) Sending: array [%d, %d] to %d\n", my_rank, 0, high, deliver.MPI_SOURCE);
    MPI_Send(array, high+1, MPI_INT, deliver.MPI_SOURCE, 0, MPI_COMM_WORLD);
    fprintf(stderr, "(%d) DONE: sending: array [%d, %d] to %d\n", my_rank, 0, high, deliver.MPI_SOURCE);

  }
  /*
    if(array != NULL) {
    printf("(%d) I'm freeing my array %p\n", my_rank, array);
    free(array);
    printf("(%d) I've freed my array %p\n", my_rank, array);
  }
  */
  free(array);

  MPI_Finalize();

  fprintf(stderr, "\n");
  return 0;
}

void print(int *vet, int s, int f){
  for(int i=s ; i<=f ; ++i) 
    printf("[%d] > array[%d] = %d;\n", my_rank, i, vet[i]);
  printf("\n");
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
  
  /*
    printf("\n(%d) Merging: ", my_rank);
    print(array, a, b);
    printf("\t(%d) with: ", my_rank);
    print(array, c, d);
    printf("\n");
    */

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

  /*
  printf("\n(%d) merged: ", my_rank);
  print(array, a, d);
  printf("\n");
  */

  /*
  printf("(%d) I'm freeing my auxiliar array %p\n", my_rank, res);
  free(res);
  printf("(%d) I've freed my auxiliar array %p\n", my_rank, res);
  */

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

  //fprintf(stderr, "(%d) Inside mergesort: %p [%u, %u]\n", my_rank, array, b, e);
  int fstArray2 = ((e-b)/2)+1 + b;
  //fprintf(stderr, "(%d) DEBUG: array [%d, %d] -> %d\n", my_rank, b, e, fstArray2);
  int childID = (int)CHILD_ID;
  if(childID < sz_comm - 1) {
    // send the second half to child
    fprintf(stderr, "(%d) Inside mergesort: sending (%u, %u) to %d\n", my_rank, fstArray2, e, childID);
    MPI_Send(&ite, 1, MPI_INT, childID, 0, MPI_COMM_WORLD);
    MPI_Send(&array[fstArray2], e-fstArray2+1, MPI_INT, childID, 0, MPI_COMM_WORLD);
    fprintf(stderr, "(%d) Inside mergesort: done sending (%u, %u) to %d\n", my_rank, fstArray2, e, childID);
    ++ite;

    // call for the first half

    fprintf(stderr, "(%d) Inside mergesort: Mergesort: array [%d,%d]\n", my_rank, b, fstArray2-1);
    mergesort(array, b, fstArray2-1);
    fprintf(stderr, "(%d) Inside mergesort: DONE: mergesort: array [%d,%d]\n", my_rank, b, fstArray2-1);

    // receive back the work
    fprintf(stderr, "(%d) Inside mergesort: receiving [%d, %d] from %d\n", my_rank, fstArray2, e, childID);
    MPI_Recv(&array[fstArray2], e-fstArray2+1, MPI_INT, childID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    fprintf(stderr, "(%d) Inside mergesort: DONE receiving [%d, %d] from %d\n", my_rank, fstArray2, e, childID);
  } else {
    // call for the first half
    //fprintf(stderr, "(%d) (1/2) Calling merge for: %p [%u, %u]\n", my_rank, array, b, m-1);
    fprintf(stderr, "(%d) Inside mergesort: Mergesort (1/2): array [%d, %d]\n", my_rank, b, fstArray2-1);
    mergesort(array, b, fstArray2-1);
   // scanf("c%*c");
    fprintf(stderr, "(%d) Inside mergesort: DONE: mergesort (1/2): array [%d,%d]\n", my_rank, b, fstArray2-1);
    // call mergesort for the second half
    //fprintf(stderr, "(%d) (2/2) Calling merge for: %p [%u, %u]\n", my_rank, array, m, e);
    fprintf(stderr, "(%d) Inside mergesort: Mergesort (2/2): array [%d, %d]\n", my_rank, fstArray2, e);
    mergesort(array, fstArray2, e);
   // scanf("c%*c");
    fprintf(stderr, "(%d) Inside mergesort: DONE: mergesort (2/2): array [%d,%d]\n", my_rank, fstArray2, e);
  }

  fprintf(stderr, "(%d) Inside mergesort: Merge: array1 [%d, %d] with array2 [%d,%d]\n", my_rank, b, fstArray2-1, fstArray2, e);
  merge(array, b, fstArray2, e);
  fprintf(stderr, "(%d) Inside mergesort: DONE: merge: array1 [%d, %d] with array2 [%d,%d]\n", my_rank, b, fstArray2-1, fstArray2, e);

}

void debug(void) {
  if(!DEBUG) return;

  int i = 0;
  char hostname[256];
  gethostname(hostname, 256);
  printf("(%d) Is waiting connection. PID: %d, hostname: %s\n", my_rank, getpid(), hostname);

  while(i == 0)
    sleep(5);

}
