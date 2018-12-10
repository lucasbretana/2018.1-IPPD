# Distributed systems
  - mainly used over a network
    * this gives some common problems, such as random failures on the network or even on the servers
  - many different uses (over the web)

  - architecture varieties
    * different HW and SW

  - internal problems
    * clock sync
    * data updates conflicts
  
## Common organizations
### Client-Server architecture
  - distinct jobs  
  - client share resources available in a server side 

### Peer-to-peer
  - same jobs for everyone
  - self scalable
  - no SPOF
  - it works because the current "domestic computer" are really good!
  - __note__ hard to sync

## Common techniques for mutual exclusion
### Clint-Server architecture
  - the server makes the synchronization
  - Goods:
    * simple to implement
  - Bads:
    * SPOF
    * load balance, server may be overused

### Ring based algorithm
  - process exchange a token in ring based architecture
  - Goods:
    * simple
    * no SPOF (using some timeout)
  - Bads:
    * N-1 messages to obtain lock (worst case)
    * consumes a lot of bandwidth

### Multicast synchronization
  - this algorithm is based on multicast (send a message to every single one on the network)
    * the multicast may be offer in HW, which will reduce the cost of sending messages

  - every process has a state of: __HELD__, __WANTED__ or __RELEASED__ (default)

- __to enter a critical section__: change to WANTED, and send a request (with a time-stamp and its pid) through broadcast
  - __on a request receive__ 
    * if the current is RELEASED: respond immediately
    * else if is WANTED: check request order (by time-stamp and pid) and either respond or enqueue the request
    * else if HELD: just enqueue the request
  - __on a request confirm__ 
    * if full confirmed (i.e. received a confirm from all others) enter the section, and change to HELD
    * else wait for the others confirmation, and stay WANTED
  - __on a critical session exit__ respond any requests on the queue, and change to RELEASE

#### Measures
  - request to enter: __2(N-1)__ send N-1 messages requesting, receive N-1 messages
  - request to exit: __none__
  - sync. bet. exit and next enter: __0__ message, the finishing process will respond to the first one on the queue

### The bully algorithm
	- based on the premiss that every process has some _priori_ knowledge of others process

	- three types of messages:
		* __election__: sent to announce the start of a election
		* __answer__: response to an election message
		* __coordinator__: identifies the elected process

	- if the process that start the election know it has the highest pid, then it sends a coordinator message to everyone
	- else it sends an election message to everyone that is higher than him

	- T = 2\*T(trans) + T(process)
		* the upper bound of timeout is the the message trip time plus the message processing time
	
	- on a timeout the process assume the other crashed, and act accordingly

### Reliable multicast
	- it uses the B-multicast and B-deliver operation (B = basic)
		* (send) B-multicast(m, g) == for each p in g, sent(m, p)
		* (recv) B-deliver(m) == just receive it

	- R-multicast(m, g): B-multicast(m, g)
	- R-deliver(m) at process q and g = group(m)
		* do note that the sender is included on the destination group
```
	if ( m.notReceived() ) 
	{
		m.setReceived(true)
		if ( q != p) R-multicast(m, g)
		R-deliver(m)
	}	
```

	- the use of the B-multicast using threads include its problems, such as an ACK explosion
		* this can lead to drop ACKs, which will lead to newer messages, and new ACKs....

	- this algorithm is all based on the idea that if one correct process receive the message then all the correct process will eventually receive it

	- this algorithm can be improved using the IP-multicast
		* every message include the process identifier inside the group
		* include the id of the last received message from that sender
	
	- if the message comes with a lower id than expected, then it is discarded
	- if the id is higher, then the message goes to the hold back message	

## Typically problems
### Task allocation problem
  - the service physical resources should consider application characteristics
    * communication pattern
    * communication quality
    * node balance

  - main strategies
    * multiple servers w/ layer and tiers: better to development, to recover from failures
    * caching/proxy: most recent access data (proxy is cache server side)
    * mobile code: the app can migrate between servers
    * mobile agents: (basically the same as above)

## Architectures Pattern
### Multiple layer and tiered
```
      ------------
      |   App    |
      |   MW     |
------|   OS     |------
|     |   HW     |     |
|       platform       |
------------------------
```

- those layer offers an abstraction for each other
- this improves the development process but also includes an overhead

#### Tiered
- vertical layers 
- used to organize the architecture

- 2 tiers: data management and data visualization
  * low latency in requests
  * server can be overloaded

- 3 tiers: view, data logic and data storage

#### Fundamentals models
##### Thin client - fat server
- thin client: or dummy client, doesn't do much, everything is computed on the server side
- fat server: is responsible for doing all the processing, common in the past and "kinda" getting back now (_cloud_)

##### Brokerage and proxy service
- used to mask the final service server
	* is a middle server that have the real location of the final server
	* the middle server can perform task of balance load and failure recover, simplifying it for the client 

#### Fundamentals notes
- the network is always a problem!
- how to sync message passing between server?!
- how to have a clock?!- 

- client ----> | ~~network~~ |	-----> server
									*
									* abstraction layer for communication
									* can be secure or not, if  not then should be secure at application level
