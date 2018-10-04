## OpenCL

### install
- each plataform has its Instable Client Driver (ICD) implementation, along with an OpenCL ssytem implementation
- find the one for your HW
  * for _nvidia_: nvidia-opencl-icd
  * for _intel_: pocl-opencl-icd (common implementation for intel CPUs, I think mesa have an implementation too)

### architecure
- each computer have one or more **plataforms**
  * Portable Computing Language (for intel)
  * NVidia CUDA

- every plataform can have many devices
  * POCL OpenCL - pthread-Intel i7 4710MQ
  * CUDA NVIDIA - GTX 950M

- those devices have important caractheristcs (GTX 950M, intel i7 4710MQ)
  * Global memory size (2GB, 9GB)
  * num max de WI in a WG -- related to how many Processing Elements there are
  * max dimensions size -- the maximum size for the NDRange dimensions

WI: Working Item, is a kernel executing (thread)
WG: Working Group, a group of WI
  * have an ID for the group
  * every WI have a unique ID inside that group ID

### programming

- to create an OpenCL program first the aplication must be dived into parts that should be executed in SIMD architecure (for the OpenCL)
  * __kernel__: funtion written in OpenCL C, will be executed in the device
  * usually uses the global/local WI's ID to access the data

- once there is a code to execure in the OpenCL architecture now continue

- every kernel is executed inseide a __context__, which contains:
  * kernel
  * a queue of commands to be executed
  * an OpenCL device w/ an NDRange and Working Groups

- the NDRange is grid from (0..3) dimensions used to operate over the data
  * 1D -> used to sum array, perform some filter in an audio
  * 2D -> multiply matrixes, perform some filder in an image
  * 3D -> God now what ...

- now the NDRange must created based on the application

- the Working Group sizes can be:
  - defined mannually, in this case the must "break evenly" the NDRange and fit the corresponding application
    * each WG will be executed at once, 
    * the WI among the same WG can be synronized between them
    * WI in differents WG cannot be synconized
  - defined by the OpenCL runtime, in this case NULL should be informed on the corresponding function

- now every thread/WI should be carreful to not acces a invalid memory position
  * e.g. id = 2040 and array size = 1024
    * array[id]

- the memory of the device cannot be access by the host
  * only throw opencl functions (for read/write)


#### General script for an app
- first discover how many plataforms and devices there are

- create a context for execution 

- create program and kernels

- give commands to the OpenCL runtime

- give data to be process

- execute the kernel

- read results
