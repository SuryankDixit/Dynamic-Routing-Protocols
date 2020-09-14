#include "graph.h"

void buildTopology(){

    int vertex = 3;
    int edges = 3;
    graph *topology = createGraph(vertex,edges);  	// Graph creation

    /*
				   
				   +----------+
		              0/2 |   R0      | 0/0
		 +----------------+           +--------------------------+
		 |     	   | 	       |                          |
		 |                +-----------+                          |
		 |                                                       |
		 |                                                       |
		 |                                                       |
		 |                                            	   |
		 |0/2                                                    |0/1
	     +---+---+                                              +----+-----+
	     |       |0/1                                        0/2|          |
	     | R2    +----------------------------------------------+    R1    |
	     |       |                      	      		      |          |
	     +-------+                                              +----------+
	   						

*/
    node *router0 = & (topology->routersArray[0]);
    node *router1 = & (topology->routersArray[1]);
    node *router2 = & (topology->routersArray[2]);
    
    
    addEdge(topology,router0,router1,"eth0/0","eth0/1",10);
    addEdge(topology,router1,router2,"eth0/2","eth0/1",15);
    addEdge(topology,router2,router0,"eth0/2","eth0/2",20);
    
    printEdges(topology,edges);

    printGraph(topology);
    
    
}

