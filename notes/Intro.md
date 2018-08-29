# IPPD

## Arquitetura	
- ...   
## Porque fazer programas paralelos?	
- ...   
## Como escrever programas paralelos?	
- divisão de tarefas  
  - divide o problema em 
- divisão de dados  
  - divide o problema em partes 

### Coordenação
- coordenar trabalho entre cores
- comunicação entre cores
- bal. carga trabalho igual
- sinc. 

### Modelo de comunicação
- Memória **compartilhada**   
  - comunicação com base num mesmo espaço de endereçamento, compartilhado, utilizando mecânismos de exclusão mutua, e.g. **pthread**, **openmp**  
|---------|  |---------|  |---------|
| proc. 1 |  | proc. 2 |  | proc. 3 |
|---------|  |---------|  |---------|
  ||           ||           ||
|-----------------------------------|
|             memory                |
|-----------------------------------|

- Memória **distribuída** 
  - comunicação por troca de mensagens, e.g. **mpi**  
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
