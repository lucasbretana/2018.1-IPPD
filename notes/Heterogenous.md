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

### Common names
* Compute Unit  
* Processing Elements 
* host 
* device 
* kernel: code that run on the GPU  
* working item: threads (but w/ the same task)  
* workgroup 
* NDRange 

### Goals
- multiplataform!   

- teach the concepts necessary to use fully use the architecture providen by the OpenCL model   

- the __heterogenous__ model comes from mixing many:
  * CPU programming model (in general MIMD)   
  * GPU programming model (in general SIMD)   

### Architecture in layers

App
  kernel
API | OpenCL C

### Architectue notes

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
