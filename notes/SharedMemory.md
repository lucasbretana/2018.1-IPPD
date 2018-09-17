## Shared Memory model
Every __thread__ have access to "all" memory allocated  
The communication between thread is made by mutually exclusive access to some memory address  

The library used to study this model the the __OpenMP__ and in other classes we used __pthread__  

### OpenMP
Using the OpenMP API  
Projected to every thread/process have access to "all" memory allocated to that process   
|---------|  |---------|  |---------|
| proc. 1 |  | proc. 2 |  | proc. 3 |
|---------|  |---------|  |---------|
  ||           ||           ||
|-----------------------------------|
|             memory                |
|-----------------------------------|
Fig 1.: The shared memory model  
Here there is only one memory that is accessed by all the processes using some sync. mechanism  
  - mutex   
  - tuple space (coordination)  

Some commom terms are used on OpenMP world:   
  __team__: is a thread collection  
  __master__: main/first thread   
  __slaces__: others/additional threads   

To ensure the portability use the \_OPENMP\_ macro:
```
#include <omp.h>
#ifdef \_OPENMP\_
  omp_get...
#endif
```

The variables are divided in two main scopes, that define how the threads see them:
__Shared scope__ we say that a variable is _shared_ when all the __team__ have access to it   
  - more shared spaces -> more concurrencie and more sync todo  
__Private scope__ we say that a varible is _private_ when just one thread have access to it   
  - more private spaces -> more memory used   

### Programming
Using __pragmas__   
  - compilers that don't support the funcionalities just ignore them

Those directives are used in compile time to transform the code to a concurrent version using the old-but-gold __pthread__  

Extends the C functionalities   
  - needs to modifie the compiler to work   

The code should be done to support any number of thread   
  - even if it is __one__ (sequential)   

#### Primitives

Says that a section should be executed in parallel, i.e., one time by each thread   
```
#pragma omp parallel
  {...} 
```

Those pragms sometimes can receive _clauses_
Some examples of clause:
  - num\_threads (<num_threads>)
    * defines the number of threads to use on the section

##### Reduction clause  
The reduction operation is a binary operation   
    - one variable  
    - one operation   
  - a reduction is one computation that is applied many times to obtaing the final result   
  - this requires syncronization  

```
#pragma omp parallel num_threads(thread_count) reduction (+; finalResult)
  finalResult += f(...)
```

##### For
To parallelize the loop we use the __for__ directive, that makes each thread get one iteration each time  
  creates a __team__ to work the for iterations   
```
#pragma omp parallel for
  for (...) {...}
```
Note: the for semantics is restricted   
  - the initialization must be constant   
  - the test must be using the basics operation (<,>,<=,>=)   
  - the increment part should use one of the:   
    * i++   
    * ++i   
    * i += c  
    * i = i + c   

##### Scope
On the __for__ primitive there are some extra _clauses_ to change the scope of some variables   
  * private (a, ...)   
  * shared (b, ...)   
There is also the possibility to define the default option  
  * default (none|private|public)   

##### Task Scheduling
There are also some others _clauses_ to define the work scheduling to be used on the for  
  * __static__: the task are agruped in chunks that are staticaly atributed to each thread  
  * __dynamic__: the chunks are atributed dynamicaly, when one thread finishes its chunk it will get a new chunks   
  * __guided__: creates chunks with different sizes, making the first chunks bigger (more iterations) that the last ones
    - this approach assumes that the task gets more **hard** with time  
  * __runtime__: the decision is made in runtime by the omp system (OMP\_SCHEDULE macro)   

##### Atomic and Barrier
  - __atomic__ can only execute one simple atribution (normally use a machine level instruction to perform the atribution)  
  - __barrier__ used to protected a region (has more overhead)  

##### Lock
  - the OpenMP also offers the __lock__ tool  
  - does not implies in a section, we need to explicit say to start/finish a lock   
  - do note that every lock should be created and destroyed a single time   
    * ```omp_set_lock(&lock_t)```

### Trapezoidal rule
  - calculate the area under some curve using aproximative sums   
  - just like the Riemmans sum, but using "grotesc" rectangles  


### Producer & Consumer
  - many producers, creating problems   
  - many consumers, solving problems  

###### Time mesuring  

###### Task deliver on AVA
  - code,  
  - sheet with graphs.  
