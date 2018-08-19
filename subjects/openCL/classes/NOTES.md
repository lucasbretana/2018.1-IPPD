OpenCL  

CPU with _multicore_  
GPU with multiple processing units, _manycore_  

**Heterogenous plataforms**  

CPU: used to execute general task and control  
GPU: used to execute task for data parallelism (**massive** parallelism)  

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

## OpenCL
- __Multiplataform__: available for many differents HW and OS   
- __Portable code__: between architectures (Nvidia, AMD, Intel, Appĺe, IBM)   
- __SIMD__ and __MIMD__ parallelism   
- __C__ and __Cpp__ bases   
- __floating point operations__ standarts   
- __intgegration__ with others tech, e.g., _openGL_   


## CUDA and OpenCL, terminologies
             CUDA               |             OpenCL    
--------------------------------|---------------------------------    
Streamming Multiprocessor  (SM) |       Compute Unit (CU)   
Streamming Processor (SP)       |   Processing Element (PE)   
            host                |              host   
           device               |             device    
           kernel               |             kernel    
           thread               |            workitem   
           block                |           workgroup   
           grid                 |            NDRange

#### Basic kernel example
```c
__kernel void arrayDiss(__global const int a[], __global cont int b[], __global int c[]) {
  int id = get_global_id(0);
  c[id] = a[id] - b[id];
}
```
## OpenCL - layer and tiers on OpenCl

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

##### General Notes
- in a kernel there is no loop to iterate over and array  
- normally the code is focused on a single processing unit work  
- the _runtime_ is in charge of creating as many instances of the __kernel__ as nedded  
- the size of the data set is not informed to the __kernel__, the _runtime_ takes care of that  
- in a OpenCL system command and enqueued to be executed on the __device__  
- it is the programmer's responsabilitie to manage memory usage and available computing
