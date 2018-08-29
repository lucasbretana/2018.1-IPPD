## Ganho de desempenho
**linear** gain   
  - Tp = Ts / p   

**speedup** max   
  - S = Ts / Tp   

E = S / p = Ts / (p * Tp)   

##### **Note:** eficiency != performance  
##### **Eficiency**: good use of the available HW  
##### **Performance**: speed   

## Data size
A common behavior of parallel algorithms is to have its best performance when there is **enough data** to be worked on  

## Overhead
Tp = Ts / p + T(overhead)   
  - this eq. can be used to predict future performance behavior   
  - think about is it worth it?   

## Amdahl
It law is used to find the best improvment expected in a wole system by improving just one part of it.  
  - is common used to predicat max. speedup   
