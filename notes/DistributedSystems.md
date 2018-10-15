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

#### Fundamentals models
##### Thinc client - fat server
- thin cliente: or dummy client, doesn't do much, everything is computed on ther server side
- fat server: is resposible for doing all the processing, common in the past and "kinda" comming back now (_cloud_)

##### Brokerage and proxy service
- used to mask the final service server
	* is a middle server that have the real location of the final server
	* the middle server can perform task of balance load and failuer recover, simplifying it for the client 

#### Fundamentals notes
- the network is always a problem!
- how to sync message passing between server?!
- how to have a clock?!- 

- client ----> | ~~network~~ |	-----> server
									*
									* abstraction layer for communication
									* can be secure or not, if  not then should be secure at application level
