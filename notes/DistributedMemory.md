## Distributed memory model 

|---------|  |---------|  |---------|
| proc. 1 |  | proc. 2 |  | proc. 3 |
|---------|  |---------|  |---------|
  ||           ||           ||
|-----------------------------------|
|             memory                |
|-----------------------------------|

On distributed memory model, each thread has its own address space  
  - no __locks__  
The communication must be done using some kind of message passing 

The library that is goind to be used there is an abstraction layer for the location of the workers. 


### MPI
Is a __Message Parsing Interface__  used on distributed memory models.  
Each task is a __process__ on a _possibly_ different computer.  
  - could be implemented as an thread   

#### MPI implementations
- MPICH   
- Open MPI  
- Microsoft MPI   
- Boost MPI  

### MPI consult
Use the manual and the MPI reference card.  

### MPI commom terms
**Virtual Machine**: the MPI app is executed inside a virtual machine, build to execute an specific aplication  
**Process**: a process is a virtual node on a MPI architecture. 
  - consist in an instance of the MPI program,  
  - a unix process becomes an MPI process when it execures the **MPI\_Init** 
**Task**: many times is used as an synonm of process  
**Sync/Assync**: functions can be synced on assynced  
  - is necessary to understand what it means inside the function  

**Blocking**: a function is said blocking when its call return only when the associate service is done  
**Non-Blocking**: a function is said non-blocking when its call returns after the call
  - the service associated not necessary is finished  
  - the function call is used to start the service  
**Requisition**: represented by an object, a requisition is found associated to a service initialized with a funcion call non-blocking  

**Local**: a procedure is said local when its operation does not depends on an interation with remote process   
**Non-loal**: a procedure is said non-local when its operation depends on an interation with a remore process   
**Collective**: if a procedure is said collective when its interation involdes all process in a group   
**Pre-defined**: a primitive datatype that the MPI can manipulate   
**Derivate**: a new datatype build with the primitives datatypes  
**Portable**: a datatype is said portable is it is a pre-defined type or it derivated a pre-defined typed, using enumarate constructors (arrays, blocks, ...)   

### Coninuing on MPI ...  

##### Merge Sort
  - we gonnna implement this example on many technologies,  
  - starting with the MPI version  

##### Implement the Merge Sort using MPI  
  - remember, it is a distrubuted memory, no sharing  

#### Time mesuring  
  - create a sheet with:  
    * total time  
    * tempo per processor  
      - start using 1 processor and increase until N/2 processors  
    * time per array size  
      - start with 10, increase until 1 000 000 000  
      - generated random entrys  
    * mesure time consumed copying data  

###### Task deliver on AVA
  - code,  
  - sheet with graphs.  
