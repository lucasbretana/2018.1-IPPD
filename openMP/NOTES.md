API de programação paralela utilizando o modelo de memória compartilhada.

Toda thread tem acesso a toda a memória.

(img slide 3?)

Várias CPUs e mesma memória.

Utiliza instruções pré-processadas pra tornar o código paralelo utilizando pthreads.

Adiciona funcionalidades a linguagem C, presentes na lib omp.h.

Compiladores que não suportam os pragmas os ignoram.

#pragma

Esse modelo de programação é 

__team__: é a coleção de threads
__master__: é a _thread_ inicial
__slaces__: são as _threads_ adicionais

Para portabilidade:

#ifdef _OPENMP
#include <omp.h>
#endif


Escopo
Aqui definimos como escopo o número de threads que podem acessar a variável em um bloco paralelo.
__Escopo compartilhado__ é quando o __team__ todo tem acesso ao dado.
__Escopo privado__ é quando somente a thread tem acesso ao dado.

Clausula de redução
O operador de redução é uma operação binária.
Uma redução é uma computação que é aplicada repetidas vezes pra obter um resultado único no final.
Todos os resultados temporarios são armazenados na variável de redução, que requer sincronização

#pragma omp parallel num_threads(thread_count) reduction (+; finalResult)
  finalResult += f(...)

Fork paralelo
Serve para paralelizar loops for, onde cada thread se responsabiliza por diferentes iterações do loop
#pragma omp parallel for

Dependencia de dados
