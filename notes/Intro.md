# IPPD

## Intro
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


|---------|             |---------|
| proc. 1 | ----------- | proc. 3 |
| |=====| |             | |=====| |
| | mem | |             | | mem | |
| |=====| |             | |=====| |
|---------|             |---------|
         \               /
          \             /
           \           /
            \         /
            |---------|
            | proc. 2 |
            | |=====| |
            | | mem | |
            | |=====| |
            |---------|

Fig 2.: The distributed memory model  
On this model all process have its own memory, and communicate through using apropriated mechanism:  
  - message passing    
  - ...  

### Common questions
  - why do we need more performance?  
  - why do we build parallel systems?  
  - why and how do we write parallel programs?  
  - what the difference between the parallel systems?  

**NOTE**: after the time that it got too hard to increase the clock frequency, the performance was increased by improving the processor.  
  + perfomance != clock frequency  

When we get too close from the phisical limits we use more cores, hence the **parallel processing**  
  + this "increse the phisical limit"  
  + but now the problem is on **programming**  

The programming task now, more than ever, must make a good use of the resources available,  
  + memory  
  + malt. CPUs  

Some programs will need to be re-written and re-thinked, other could be automatically changed (**hard** task), ...  

## How to write parallels programs?
- task division  
  - divide the problem in   
- data level division   
  - divide the problem in  

### Coordination
- coordinates the work between cores  
- communication between workind cores   
- carga load equally  
- sync   
