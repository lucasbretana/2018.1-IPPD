...


### Layer and ..

### Client-Server architecture
  - distincts jobs  
  - client share resources available in a server side 

### Peer-to-peer
  - same jobs for everyone
  - self scalable
  - no SPOF
  - it works because the current "domestic computer" are really good!
  - __note__ hard to sync

## Typicall problems
### Task allocation problem
  - the service phisical resources should consider application characteristics
    * communication pattern
    * communication quality
    * node balance

  - main strategies
    * multiple servers w/ layer and tayers: better to development, to recover from failures
    * caching/proxy: most recent access data (proxy is cache server side)
    * mobile code: the app can migrate between servers
    * mobile agents: (basically the same as above)

## Architectures Pattern
### Multiple layer and tiered
      -----------
      |   App   |
      |   MW    |
------|   OS    |------
|     |   HW    |     |
|      plataform      |
-----------------------

- those layer offers an abstraction for each other
- this improves the development process but also includes an overhead

#### Tiered
- vertical layers 
- used to organize the architecture

- 2 taiers: data managment and data visualization
  * low latency in requests
  * server can be overloaded

- 3 tiers: view, data logic and data storage

- thin cliente: ... 
