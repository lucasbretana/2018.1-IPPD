## Clock sync
- how problematic is to sync some compuer?
	* using the cpu clock is a problem, since the didn't start at the same time and have different clock frequency
	* bank appliation really relly on clock syncronization

- the simpler solutins just ask some specific server the time
	* and add some dealy time (mesured using an avarage travel time) 

- the __NTP__ uses the same previous ideia but using a tree of server, increasing the avarage precision

- a simple view of clock syncronization used onlu stamps for every action/message
- this way we stablish the __Happen Before__ relation as a corelation between action and consequence
	* this view is enough for many systems

### Happen Before relation
- every server starts with an empty stamp (zero stamp)
- on every message the server +1 on its counter

- now the happen before relation is given by comparing those stamps

- on every message received the server update its stamp witch the function
	* stamp = MAX(old-stamp, recv-stamp) + 1

- this relation is not total! i.e., for action that do not have the happen before relation there is no information about its execution relation

#### The Arrays of time stamps
- those stamps are different for each server and when messageing each other only one number have to be transmited

- in the array of time stamps every server have the time stamp of every server
	* those stamps are updated one-by-one for every message exchanging using the same rule

- this approach give us information about action that happen "in parallel"
	* just need to compare their arrays
