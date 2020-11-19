#include "graph.h"
#include "css.h"
#include "distanceVector.h"
#include "linkState.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


void
network_start_pkt_receiver_thread(graph *topo);

int
send_pkt_out(char *pkt, unsigned int pkt_size, interface *intf);

interface * get_node_if_by_name(node *router, char *if_name);           



graph* buildRandomGeneratedTopology(){

        int value=1;
        int numVertex;
        int numEdges;

        printf("Enter number of vertices: ");
        scanf("%d",&numVertex);
        printf("Enter number of edges: ");
        scanf("%d",&numEdges);

        graph *topology = createGraph(numVertex,numEdges);

        node* routers[numVertex];
        int indexForRouters =0;

        for(int i =0; i<numVertex; i++){

            node *router = & (topology->routersArray[i]);
            routers[indexForRouters++] = router;
        }


        srand(time(0));
        for(int i = 0; i < numEdges; i++){

            int indexFromRouter = rand() % numVertex;
            int indexToRouter   = rand() % numVertex;

            // printf("\n%d    %d\n",indexFromRouter,indexToRouter);

            if(indexFromRouter == indexToRouter){
                i--;
                continue;
            }

            node* fromRouter = routers[ indexFromRouter ];
            node* toRouter   = routers[ indexToRouter ];

            int cost = rand() % 100;

            char intf1[NAME_SIZE] = "eth0/";
            char intf2[NAME_SIZE] = "eth0/";

            int index1 = 5;
            int index2 = 5;

            int num1 = i;
            int num2 = (i+1) % numEdges;

            char str1[NAME_SIZE];
            char str2[NAME_SIZE];


            // printf("%s  %s\n",str1,str2);

            if(my_itoa(num1, str1) != NULL){
                
                for(int j = 0; str1[j] != '\0'; j++){
                
                    char ch = str1[j];
                    intf1[index1++] = ch;
                }
            }
            
            if(my_itoa(num2, str2) != NULL){

                for(int j = 0; str2[j] != '\0'; j++){
                
                    char ch = str2[j];
                    intf2[index2++] = ch;
                }
            }

            edge *link = addEdge(topology,fromRouter,toRouter,intf1,intf2,cost);

            char ip1[16] = "10.10.1.1";
            char ip2[16] = "10.10.1.2";

            if(value>9){
                int x = value%10;
                value = value/10;
                ip1[3] = x+'0';
                ip2[3] = x+'0';
            }
            
            ip1[1] = value+'0';
            ip2[1] = value+'0';

            value++;
            setInterfaceProperties(link, ip1, ip2,24);
        }

        

      /*   printGraph(topology);
        initializeRoutingTables(topology);
        // printRoutingTables(topology);
        activateTopology(topology);
        // printRoutingTables(topology);

        clock_t t; 
        t = clock();
        
        updatedBellmanFord(topology,numVertex,numEdges,0);

         t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        
	    // printRoutingTables(topology);

        printf("Time taken : %f\n", time_taken);


        // changing edge cost

        // indexForRouters =0;
        // for(int i=0;i<10;i++){
        //     node *router = routers[indexForRouters++];
        //     router->intf[0]->attachedEdge->cost = rand()%100;

        //     clock_t t; 
        //     t = clock();
            
        //     // activateTopology(topology);
        //     int count = updatedBellmanFord(topology,numVertex,numEdges,0);

        //     t = clock() - t; 
        //     double time_taken = ((double)t)/CLOCKS_PER_SEC;
        //     // printRoutingTables(topology);
        //     printf("Time taken : %f\t%d\n", time_taken,count);
        // }        */

        return topology;

}


graph* buildFirstTopology(){

    int vertex = 3;
    int edges = 3;
    graph *topology = createGraph(vertex,edges);  	// Graph creation

        printf("\n\n");
	printf(ANSI_COLOR_YELLOW"						      +-----------+\n");
        printf("				                  0/2 |   R0      | 0/0		\n");
        printf("				    +-----------------+           +--------------------------+\n");
        printf("				    |     	      | 	  |                          |\n");
        printf("				    |                 +-----------+                          |\n");
        printf("				30  |                                                        | 10\n");
        printf("				    |                                                        |\n");
        printf("				    |                                                        |\n");
        printf("				    |0/2                                                     |0/1\n");
        printf("				  +-----+---+                                              +----+-----+\n");
        printf("				  |         |0/1                                        0/2|          |\n");
        printf("				  |   R2    +----------------------------------------------+    R1    |\n");
        printf("				  |         |               15       	      	           |          |\n");
        printf("				  |         |                      	      	           |          |\n");
        printf("				  +---------+                                              +----------+\n"ANSI_COLOR_RESET);

    /*
				          +-----------+
		              0/2 |   R0      | 0/0					10
		 +----------------+           +--------------------------+
		 |     	          | 	      |                          |
		 |                +-----------+                          |
	30	 |                                                       |
		 |                                                       |
		 |                                                       |
		 |                                            	   |
		 |0/2                                                    |0/1
	     +---+---+                                              +----+-----+
	     |       |0/1                                        0/2|          |
	     | R2    +----------------------------------------------+    R1    |
	     |       |               15       	      	            |          |
	     +-------+                                              +----------+
	   						

*/
    node *router0 = & (topology->routersArray[0]);
    node *router1 = & (topology->routersArray[1]);
    node *router2 = & (topology->routersArray[2]);
    
    
    edge *link1 = addEdge(topology,router0,router1,"eth0/0","eth0/1",10);
    edge *link2 = addEdge(topology,router1,router2,"eth0/2","eth0/1",15);
    edge *link3 = addEdge(topology,router2,router0,"eth0/2","eth0/2",30);


    setInterfaceProperties(link1, "10.1.1.1", "10.1.1.2", 24);
    setInterfaceProperties(link2, "20.1.1.1", "20.1.1.2", 24);
    setInterfaceProperties(link3, "30.1.1.1", "30.1.1.2", 24);

/*    printGraph(topology);

    // distance vector

     initializeRoutingTables(topology);
     activateTopology(topology);
     printRoutingTables(topology);

     updatedBellmanFord(topology,vertex,edges,0);

	 printRoutingTables(topology);


    // Link State

    // initializeRoutingTables(topology);
    // activateTopology(topology);

    // doReliableFlooding(topology);
    // int v = topology->numVertex;

    // for(int i=0;i<v;i++){
    //     printRoutingTableForSpecificRouter(topology->routersArray[i].linkStateDatabase, i);
    // }

    */

    return topology;

    
    
}



graph* buildSecondTopology(){

    int vertex = 10;
    int edges = 45;
    graph *topology = createGraph(vertex,edges);  	// Graph creation

    node *router0 = & (topology->routersArray[0]);
    node *router1 = & (topology->routersArray[1]);
    node *router2 = & (topology->routersArray[2]);
    node *router3 = & (topology->routersArray[3]);
    node *router4 = & (topology->routersArray[4]);
    node *router5 = & (topology->routersArray[5]);
    node *router6 = & (topology->routersArray[6]);
    node *router7 = & (topology->routersArray[7]);
    node *router8 = & (topology->routersArray[8]);
    node *router9 = & (topology->routersArray[9]);
    
    edge *link1=addEdge(topology,router0,router1,"eth0/1","eth1/1",1);
    edge *link2=addEdge(topology,router0,router2,"eth0/2","eth2/1",3);
    edge *link3=addEdge(topology,router0,router3,"eth0/3","eth3/1",5);
    edge *link4=addEdge(topology,router0,router4,"eth0/4","eth4/1",7);
    edge *link5=addEdge(topology,router0,router5,"eth0/5","eth5/1",9);
    edge *link6=addEdge(topology,router0,router6,"eth0/6","eth6/1",11);
    edge *link7=addEdge(topology,router0,router7,"eth0/7","eth7/1",13);
    edge *link8=addEdge(topology,router0,router8,"eth0/8","eth8/1",15);
    edge *link9=addEdge(topology,router0,router9,"eth0/9","eth9/1",17);
    edge *link10=addEdge(topology,router1,router2,"eth1/2","eth2/2",19);
    edge *link11=addEdge(topology,router1,router3,"eth1/3","eth3/2",21);
    edge *link12=addEdge(topology,router1,router4,"eth1/4","eth4/2",23);
    edge *link13=addEdge(topology,router1,router5,"eth1/5","eth5/2",26);
    edge *link14=addEdge(topology,router1,router6,"eth1/6","eth6/2",29);
    edge *link15=addEdge(topology,router1,router7,"eth1/7","eth7/2",32);
    edge *link16=addEdge(topology,router1,router8,"eth1/8","eth8/2",35);
    edge *link17=addEdge(topology,router1,router9,"eth1/9","eth9/2",38);
    edge *link18=addEdge(topology,router2,router3,"eth2/3","eth3/3",5);
    edge *link19=addEdge(topology,router2,router4,"eth2/4","eth4/3",10);
    edge *link20=addEdge(topology,router2,router5,"eth2/5","eth5/3",15);
    edge *link21=addEdge(topology,router2,router6,"eth2/6","eth6/3",20);
    edge *link22=addEdge(topology,router2,router7,"eth2/7","eth7/3",25);
    edge *link23=addEdge(topology,router2,router8,"eth2/8","eth8/3",30);
    edge *link24=addEdge(topology,router2,router9,"eth2/9","eth9/3",35);
    edge *link25=addEdge(topology,router3,router4,"eth3/4","eth4/4",40);
    edge *link26=addEdge(topology,router3,router5,"eth3/5","eth5/4",4);
    edge *link27=addEdge(topology,router3,router6,"eth3/6","eth6/4",8);
    edge *link28=addEdge(topology,router3,router7,"eth3/7","eth7/4",12);
    edge *link29=addEdge(topology,router3,router8,"eth3/8","eth8/4",16);
    edge *link30=addEdge(topology,router3,router9,"eth3/9","eth9/4",20);
    edge *link31=addEdge(topology,router4,router5,"eth4/5","eth5/5",24);
    edge *link32=addEdge(topology,router4,router6,"eth4/6","eth6/5",28);
    edge *link33=addEdge(topology,router4,router7,"eth4/7","eth7/5",32);
    edge *link34=addEdge(topology,router4,router8,"eth4/8","eth8/5",36);
    edge *link35=addEdge(topology,router4,router9,"eth4/9","eth9/5",40);
    edge *link36=addEdge(topology,router5,router6,"eth5/6","eth6/6",6);
    edge *link37=addEdge(topology,router5,router7,"eth5/7","eth7/6",12);
    edge *link38=addEdge(topology,router5,router8,"eth5/8","eth8/6",18);
    edge *link39=addEdge(topology,router5,router9,"eth5/9","eth9/6",24);
    edge *link40=addEdge(topology,router6,router7,"eth6/7","eth7/7",30);
    edge *link41=addEdge(topology,router6,router8,"eth6/8","eth8/7",36);
    edge *link42=addEdge(topology,router6,router9,"eth6/9","eth9/7",42);
    edge *link43=addEdge(topology,router7,router8,"eth7/8","eth8/8",7);
    edge *link44=addEdge(topology,router7,router9,"eth7/9","eth9/8",14);
    edge *link45= addEdge(topology,router8,router9,"eth8/9","eth9/9",21);


    setInterfaceProperties(link1, "192.168.1.1", "192.168.1.2", 24);
    setInterfaceProperties(link2,"192.168.2.1", "192.168.2.2", 24);
    setInterfaceProperties(link3,"192.168.3.1", "192.168.3.2", 24);
    setInterfaceProperties(link4,"192.168.4.1", "192.168.4.2", 24);
    setInterfaceProperties(link5,"192.168.5.1", "192.168.5.2", 24);
    setInterfaceProperties(link6,"192.168.6.1", "192.168.6.2", 24);
    setInterfaceProperties(link7,"192.168.7.1", "192.168.7.2", 24);
    setInterfaceProperties(link8,"192.168.8.1", "192.168.8.2", 24);
    setInterfaceProperties(link9,"192.168.9.1", "192.168.9.2", 24);
    setInterfaceProperties(link10,"192.168.10.1", "192.168.10.2", 24);
    setInterfaceProperties(link11,"192.168.11.1", "192.168.11.2", 24);
    setInterfaceProperties(link12,"192.168.12.1", "192.168.12.2", 24);
    setInterfaceProperties(link13,"192.168.13.1", "192.168.13.2", 24);
    setInterfaceProperties(link14,"192.168.14.1", "192.168.14.2", 24);
    setInterfaceProperties(link15,"192.168.15.1", "192.168.15.2", 24);
    setInterfaceProperties(link16,"192.168.16.1", "192.168.16.2", 24);
    setInterfaceProperties(link17,"192.168.17.1", "192.168.17.2", 24);
    setInterfaceProperties(link18,"192.168.18.1", "192.168.18.2", 24);
    setInterfaceProperties(link19,"192.168.19.1", "192.168.19.2", 24);
    setInterfaceProperties(link20,"192.168.20.1", "192.168.20.2", 24);
    setInterfaceProperties(link21,"192.168.21.1", "192.168.21.2", 24);
    setInterfaceProperties(link22,"192.168.22.1", "192.168.22.2", 24);
    setInterfaceProperties(link23,"192.168.23.1", "192.168.23.2", 24);
    setInterfaceProperties(link24,"192.168.24.1", "192.168.24.2", 24);
    setInterfaceProperties(link25,"192.168.25.1", "192.168.25.2", 24);
    setInterfaceProperties(link26,"192.168.26.1", "192.168.26.2", 24);
    setInterfaceProperties(link27,"192.168.27.1", "192.168.27.2", 24);
    setInterfaceProperties(link28,"192.168.28.1", "192.168.28.2", 24);
    setInterfaceProperties(link29,"192.168.29.1", "192.168.29.2", 24);
    setInterfaceProperties(link30,"192.168.30.1", "192.168.30.2", 24);
    setInterfaceProperties(link31,"192.168.31.1", "192.168.31.2", 24);
    setInterfaceProperties(link32,"192.168.32.1", "192.168.32.2", 24);
    setInterfaceProperties(link33,"192.168.33.1", "192.168.33.2", 24);
    setInterfaceProperties(link34,"192.168.34.1", "192.168.34.2", 24);
    setInterfaceProperties(link35,"192.168.35.1", "192.168.35.2", 24);
    setInterfaceProperties(link36,"192.168.36.1", "192.168.36.2", 24);
    setInterfaceProperties(link37,"192.168.37.1", "192.168.37.2", 24);
    setInterfaceProperties(link38,"192.168.38.1", "192.168.38.2", 24);
    setInterfaceProperties(link39,"192.168.39.1", "192.168.39.2", 24);
    setInterfaceProperties(link40,"192.168.40.1", "192.168.40.2", 24);
    setInterfaceProperties(link41,"192.168.41.1", "192.168.41.2", 24);
    setInterfaceProperties(link42,"192.168.42.1", "192.168.42.2", 24);
    setInterfaceProperties(link43,"192.168.43.1", "192.168.43.2", 24);
    setInterfaceProperties(link44,"192.168.44.1", "192.168.44.2", 24);
    setInterfaceProperties(link45,"192.168.45.1", "192.168.45.2", 24);

 /*   initializeRoutingTables(topology);
    // printRoutingTables(topology);
    activateTopology(topology);
    // printRoutingTables(topology);

    // printRoutingTables(topology);

    // printGraph(topology);

    // printRoutingTables(topology);

    // printEdges(topology,edges);

	// bellmanFord(topology,vertex,edges,router9,9);

    updatedBellmanFord(topology,vertex,edges,0);

	printRoutingTables(topology);

    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router0,0);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router1,1);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router2,2);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router3,3);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router4,4);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router5,5);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router6,6);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router7,7);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router8,8);
    // initializeRoutingTables(topology);          bellmanFord(topology,vertex,edges,router9,9);

    */
   
   return topology;
    
}


graph* buildThirdTopology(){

    int vertex = 5;
    int edges = 5;
    graph *topology = createGraph(vertex,edges);  	// Graph creation

    node *router0 = & (topology->routersArray[0]);
    node *router1 = & (topology->routersArray[1]);
    node *router2 = & (topology->routersArray[2]);
    node *router3 = & (topology->routersArray[3]);
    node *router4 = & (topology->routersArray[4]);
    
    edge *link1=addEdge(topology,router0,router1,"eth0/0","eth0/1",1);
    edge *link2=addEdge(topology,router1,router2,"eth0/2","eth0/1",6);
    edge *link3=addEdge(topology,router2,router3,"eth0/2","eth0/2",2);
    edge *link4=addEdge(topology,router3,router4,"eth0/2","eth0/2",4);
    edge *link5=addEdge(topology,router4,router1,"eth0/2","eth0/2",3);


    setInterfaceProperties(link1, "192.168.1.1", "192.168.1.2", 24);
    setInterfaceProperties(link2,"192.168.2.1", "192.168.2.2", 24);
    setInterfaceProperties(link3,"192.168.3.1", "192.168.3.2", 24);
    setInterfaceProperties(link4,"192.168.4.1", "192.168.4.2", 24);
    setInterfaceProperties(link5,"192.168.5.1", "192.168.5.2", 24);

  /*  initializeRoutingTables(topology);
    activateTopology(topology);
    // printGraph(topology);
    // printRoutingTables(topology);
    // printEdges(topology,edges);
    // bellmanFord(topology,vertex,edges,router0,0);
    updatedBellmanFord(topology,vertex,edges,0);
	printRoutingTables(topology);

    */
   return topology;
}


graph* buildFourthTopology(){

    int vertex = 10;
    int edges = 24;
    graph *topology = createGraph(vertex,edges);  	// Graph creation

    node *router0 = & (topology->routersArray[0]);
    node *router1 = & (topology->routersArray[1]);
    node *router2 = & (topology->routersArray[2]);
    node *router3 = & (topology->routersArray[3]);
    node *router4 = & (topology->routersArray[4]);
    node *router5 = & (topology->routersArray[5]);
    node *router6 = & (topology->routersArray[6]);
    node *router7 = & (topology->routersArray[7]);
    node *router8 = & (topology->routersArray[8]);
    node *router9 = & (topology->routersArray[9]);
    // node *router10 = & (topology->routersArray[10]);
    // node *router11 = & (topology->routersArray[11]);
    // node *router12 = & (topology->routersArray[12]);
    
    edge *link1=addEdge(topology,router0,router1,"eth0/1","eth1/1",1);
    edge *link2=addEdge(topology,router0,router2,"eth0/2","eth2/1",3);
    edge *link3=addEdge(topology,router0,router8,"eth0/8","eth8/1",15);
    edge *link4=addEdge(topology,router0,router9,"eth0/9","eth9/1",17);
    edge *link5=addEdge(topology,router1,router2,"eth1/2","eth2/2",19);
    edge *link6=addEdge(topology,router1,router3,"eth1/3","eth3/2",21);
    edge *link7=addEdge(topology,router1,router9,"eth1/9","eth9/2",15);
    edge *link8=addEdge(topology,router2,router3,"eth2/3","eth3/3",5);
    edge *link9=addEdge(topology,router2,router4,"eth2/4","eth4/3",10);
    edge *link10=addEdge(topology,router2,router7,"eth2/7","eth7/3",15);
    edge *link11=addEdge(topology,router2,router8,"eth2/8","eth8/3",30);
    edge *link12=addEdge(topology,router3,router4,"eth3/4","eth4/4",20);
    edge *link13=addEdge(topology,router3,router5,"eth3/5","eth5/4",4);
    edge *link14=addEdge(topology,router3,router7,"eth3/7","eth7/4",12);
    edge *link15=addEdge(topology,router3,router8,"eth3/8","eth8/4",16);
    edge *link16=addEdge(topology,router4,router5,"eth4/5","eth5/5",24);
    edge *link17=addEdge(topology,router4,router6,"eth4/6","eth6/5",28);
    edge *link18=addEdge(topology,router5,router6,"eth5/6","eth6/6",6);
    edge *link19=addEdge(topology,router5,router7,"eth5/7","eth7/6",12);
    edge *link20= addEdge(topology,router6,router7,"eth6/7","eth7/7",30);
    edge *link21=addEdge(topology,router6,router8,"eth6/8","eth8/7",16);
    edge *link22= addEdge(topology,router7,router8,"eth7/8","eth8/8",7);
    edge *link23= addEdge(topology,router7,router9,"eth7/9","eth9/8",14);
    edge *link24= addEdge(topology,router8,router9,"eth8/9","eth9/9",21);



    setInterfaceProperties(link1, "192.168.1.1", "192.168.1.2", 24);
    setInterfaceProperties(link2,"192.168.2.1", "192.168.2.2", 24);
    setInterfaceProperties(link3,"192.168.3.1", "192.168.3.2", 24);
    setInterfaceProperties(link4,"192.168.4.1", "192.168.4.2", 24);
    setInterfaceProperties(link5,"192.168.5.1", "192.168.5.2", 24);
    setInterfaceProperties(link6,"192.168.6.1", "192.168.6.2", 24);
    setInterfaceProperties(link7,"192.168.7.1", "192.168.7.2", 24);
    setInterfaceProperties(link8,"192.168.8.1", "192.168.8.2", 24);
    setInterfaceProperties(link9,"192.168.9.1", "192.168.9.2", 24);
    setInterfaceProperties(link10,"192.168.10.1", "192.168.10.2", 24);
    setInterfaceProperties(link11,"192.168.11.1", "192.168.11.2", 24);
    setInterfaceProperties(link12,"192.168.12.1", "192.168.12.2", 24);
    setInterfaceProperties(link13,"192.168.13.1", "192.168.13.2", 24);
    setInterfaceProperties(link14,"192.168.14.1", "192.168.14.2", 24);
    setInterfaceProperties(link15,"192.168.15.1", "192.168.15.2", 24);
    setInterfaceProperties(link16,"192.168.16.1", "192.168.16.2", 24);
    setInterfaceProperties(link17,"192.168.17.1", "192.168.17.2", 24);
    setInterfaceProperties(link18,"192.168.18.1", "192.168.18.2", 24);
    setInterfaceProperties(link19,"192.168.19.1", "192.168.19.2", 24);
    setInterfaceProperties(link20,"192.168.20.1", "192.168.20.2", 24);
    setInterfaceProperties(link21,"192.168.21.1", "192.168.21.2", 24);
    setInterfaceProperties(link22,"192.168.22.1", "192.168.22.2", 24);
    setInterfaceProperties(link23,"192.168.23.1", "192.168.23.2", 24);
    setInterfaceProperties(link24,"192.168.24.1", "192.168.24.2", 24);
    

    // Threads Listening in communiction.c:
   network_start_pkt_receiver_thread(topology);

 //   sleep(2);

    // initializeRoutingTables(topology);
    // activateTopology(topology);
   
    // clock_t t; 
    // t = clock();
    
    // updatedBellmanFord(topology,vertex,edges,0); 
    
    // t = clock() - t; 
    // double time_taken = ((double)t)/CLOCKS_PER_SEC;
    // printf("Time taken : %f\n", time_taken);

    // printRoutingTables(topology);


    // interface *oif = get_node_if_by_name(router10,"eth8/9");


    // char msg[]="Hello Neighbour Router";
    // send_pkt_out(msg,strlen(msg),oif);

    // sleep(20);

    // doReliableFlooding(topology);
    //dijkstra(topology,0) ;
    //initializeRoutingTables(router0->linkStateDatabase);
    //activateTopology(router0->linkStateDatabase);
	// printRoutingTables(router0->linkStateDatabase);
    return topology;
    
}
