# Dynamic Routing Implementation.

_**Static Routing follows user defined routing and routing table is not changed until network administrator changes it. Static Routing requires consistent human intervention with an increased overhead of manpower as the network grows. To effectively solve this problem, we resort to an adaptive approach which is known as Dynamic routing. As its name suggests, it changes the routing table once any change to network occurs or network topology changes. During network change, dynamic routing sends a signal to router, recalculates the routes and send the updated routing information.**_

* **Compile**:    
  * gcc testApp.c topologies.c graph.c distanceVector.c networking.c
* **Run**:
  * ./a.out
* * **graph.h**
  * Contains Required Data Structure to represent topology and corresponding functions.
* **networking.h**:
  * Contains Networking Properties of Routers such as IP Addresses, MAC Addresses and Interfaces.
* **topologies.c**
  * This file contains all the networking topologies on which we have worked.
  * Random graph can be generated on the basis of number of vertices and edges.
* **distanceVector.h**:
  * Contains functionality of Distance Vector Routing Protocol.
  * Uses Bellman Ford Algorithm to find the optimal path to route traffic.
* **testApp.c**:
  * Contains Main Function