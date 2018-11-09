## Sample test for ippd - 2018/2

### Question #1: explain the Amdahl's law.
Is an estimative of how a computacional system will improve its perfomance if there is an improvment in a single part of it.
In the parallesl compution field, it is used to predict the performance improvment in extracting concurrency from the application.

### Question #2: exemplify and justify why a problem better fits the shared memory model and heterogenous architecture.
Any problem that uses the SIMD model with small data portion (like big matrixes multiplication) can be nicelly fit into an heterogenous architecture.
Therefore it uses the shared memory model, wich better will have a faster syncrony than sending many, many messages (distributed memory model mainly uses message passing for syncronization or some abstraction for this model).

### Question #3: using MPI create an application to caculate prime numbers. It should be possible to define (at compile or runtime) the numbers of primes to find.
Answer in question3.{c,h}

### Question #4: using OpenMP create an application to caculate prime numbers. It should be possible to define (at compile or runtime) the numbers of primes to find.
Answer in question4.{c,h}
