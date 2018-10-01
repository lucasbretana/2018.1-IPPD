## Heterogeous architectures
- machines with differents types of processors  
  * they are made to solve different kind of problems   
  * indicates the necessity to converge to a single programming "model"/protocol  
- CPU with _multicore_  
- GPU with multiple processing units, _manycore_  

- **Heterogenous plataforms**  
  - CPU: used to execute general task and control  
  - GPU: used to execute task for data parallelism (**massive** parallelism)  

### GPU - Graphical Processing Unit
- outs second processor   
  * is goind to be used along side the normal CPU   

- the Graphic Card became from the need for graphical computing   
  * the CPU could be used, but the performance is crap!   

- it is __not__ supposed to be used for every problem   
  * no silver bullet  

Typiccal architecture for CPUs:  
|-------------------------------------||-------------------||-------------------|   
|                                     ||       ALU         ||        ALU        |   
|           **control**               ||-------------------||-------------------|   
|              ctrl                   ||-------------------||-------------------|   
|                                     ||       ALU         ||        ALU        |   
|-------------------------------------||-------------------||-------------------|   
|-------------------------------------------------------------------------------|   
|                                                                               |   
|                                    Cache                                      |   
|                                                                               |   
|-------------------------------------------------------------------------------|   
|-------------------------------------------------------------------------------|   
|                                                                               |   
|                                    DRAM                                       |   
|                                                                               |   
|-------------------------------------------------------------------------------|   

Typical GPU architecture    
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
| ctrl  ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  |   
|-------||       ||       ||       ||       ||       ||       ||       ||       |   
| cache ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
| ctrl  ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  |   
|-------||       ||       ||       ||       ||       ||       ||       ||       |   
| cache ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
| ctrl  ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  |   
|-------||       ||       ||       ||       ||       ||       ||       ||       |   
| cache ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
| ctrl  ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  ||  ALU  |   
|-------||       ||       ||       ||       ||       ||       ||       ||       |   
| cache ||       ||       ||       ||       ||       ||       ||       ||       |   
|-------||-------||-------||-------||-------||-------||-------||-------||-------|   
|-------------------------------------------------------------------------------|   
|                                                                               |   
|                                    DRAM                                       |   
|                                                                               |   
|-------------------------------------------------------------------------------|   

### Models
#### SIMD - Single Instruction Multiple Data
- in this model the same operation is applied to many differents data   
  * a[0] + b[0] = c[0]  
  * a[1] + b[1] = c[1]  
- this is the __GPU__ model 
#### MIMD - Multiple Instruction Multiple Data
- neste modelo temos instruções diferentes sendo aplicadas  
- this is the __CPU__ model 

### Data Parallelism
- consist in dividing the data to different _threads_, __but__ the same algorithm is used   
- __CPU__ very similiar to the SIMD   

## OpenCL
- is an open source library/framework to program in heterogenous architectures  
- developed by Khronos, and defined by many!: Nvidia, AMD, Intel, ....   

### CUDA and OpenCL, terminologies
|                CUDA                 |             OpenCL          |
|-------------------------------------|-----------------------------|    
|   Streamming Multiprocessor  (SM)   |   Compute Unit (CU)         |
|   Streamming Processor (SP)         |   Processing Element (PE)   |
|              host                   |          host               |
|              device                 |          device             |
|              kernel                 |          kernel             |
|              thread                 |          workitem           |
|              block                  |          workgroup          |
|              grid                   |          NDRange            |

### Goals
- __Multiplataform__: available for many differents HW and OS   
- __Portable code__: between architectures (Nvidia, AMD, Intel, Appĺe, IBM)   
- __SIMD__ and __MIMD__ parallelism   
- __C__ and __Cpp__ bases   
- __floating point operations__ standarts   
- __intgegration__ with others tech, e.g., _openGL_   

- teach the concepts necessary to use fully use the architecture providen by the OpenCL model   

- the __heterogenous__ model comes from mixing many:
  * CPU programming model (in general MIMD)   
  * GPU programming model (in general SIMD)   

### OpenCL - layer and tiers on OpenCl
|--------------------------------|   
|           Aplication           |   
|              ------------------|   
|              |    kernel       |   
|--------------------------------|   
|     API      |    OpenCL C     |   
|--------------------------------|   
|       OpenCL platform layer    |   
|--------------------------------|   
|       OpenCL runtime           |   
|--------------------------------|   
|           Driver               |   
|--------------------------------|   
|             HW                 |   
|       (CPU, GPU, ...)          |   
|--------------------------------|   

OpenCL is a framwork that includes a programming language _OpenCL C_, an _API C_, some _libraries_ and a _runtime system_  

### Basic kernel example
```c
__kernel void arrayDiff(__global const int a[], __global cont int b[], __global int c[]) {
  int id = get_global_id(0);
  c[id] = a[id] - b[id];
}
```

### Architectue notes
- do note that the architecture have many level of "memory" (caches) and those fill up very quicly
  * and to access higher level caches the data will pass for the middle level (private memory << local memory << global memory)

- making a good use of the cache is __vital__!

- the main task for the programmer is to **keep the pipeline filled!**

- on the __kernel__ there is no need to know the size of the data set   
- this is OpenCL _runtime_'s responsabilitie   

- the runtime is developed to allow the programmer to enqueue commands to be executed one after another   
  * so the runtime is responsible by managing the avaible resources (processing and memory)   

- the app uses the OpenCL C APi to communicate with the Plataform Layer wich will sent the commands to the runtime
- the kernel is the part of the application that is supposed to run on the GPU  
  * written in OpenC

- the host (CPU) is responsable for making all sort of control   
- the device (GPU) is resposable for the massive computation  

Note: the OpenCL can run even without a GPU on the computer, it uses the CPU    

### General Notes
- in a kernel there is no loop to iterate over and array  
- normally the code is focused on a single processing unit work  
- the _runtime_ is in charge of creating as many instances of the __kernel__ as nedded  
- the size of the data set is not informed to the __kernel__, the _runtime_ takes care of that  
- in a OpenCL system command and enqueued to be executed on the __device__  
- it is the programmer's responsabilitie to manage memory usage and available computing
