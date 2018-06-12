# IPPD

## Intro
|---------|  |---------|  |---------|
| proc. 1 |  | proc. 2 |  | proc. 3 |
|---------|  |---------|  |---------|
  ||           ||           ||
|-----------------------------------|
|             memory                |
|-----------------------------------|
Fig 1.: The parallel model  
Here there is only one memory that is accessed by all the processes using some connection:  
  - network  
  - bus  
  - ...


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

Fig 2.: The distributed model
On this model all process have its own memory, and commucate through some connection:  
  - message passing  
  - tuple space  
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

# Performance

