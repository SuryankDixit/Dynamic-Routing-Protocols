#include "graph.h"
// #include "networking.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>


void createRoutingTable(routing_table* rt,int numVertex){

    rt->destinationRouters = (node*) malloc(numVertex * sizeof(node));
    rt->costArray = (int *) malloc(numVertex * sizeof(int));
    rt->viaRouters = (node *) malloc(numVertex * sizeof(node));
}



void initializeRoutingTables(graph* topology){
    int v = topology->numVertex;

    for(int i=0;i<v;i++){
        // printf("\n%s->\n",topology->routersArray[i].routerName);
        for(int j=0;j<v;j++) {
            topology->routersArray[i].rt.destinationRouters[j] = (topology->routersArray[j]);
            topology->routersArray[i].rt.costArray[j] = INT_MAX;
            // topology->routersArray[i].rt.viaRouters[j] = NULL;
        }
    }
}


void activateTopology(graph* topology){

    int v = topology->numVertex;
    int e = MAXIMUM_INTERFACE_PER_NODE;
    interface* intf;
    
    for(int i=0; i<v; i++){             // iterating over all routers
        // int indexForRoutingTable =0;
        topology->routersArray[i].rt.costArray[i] = 0;
        for(int j=0; j<e;j++){          // iterating over all edges

            intf = topology->routersArray[i].intf[j];
            if(!intf)
                break;
            node* neighbourNode = getNeighbourNode(intf); 
            // printf("%s   %s\n",topology->routersArray[i].routerName,neighbourNode->routerName); 
            int index = getIndexOfNode(neighbourNode,topology);
            int dis = intf->attachedEdge->cost;

            topology->routersArray[i].rt.costArray[index] = dis;
            topology->routersArray[i].rt.viaRouters[index] = *neighbourNode; 
            // indexForRoutingTable++;
        }
    }
}


void printRoutingTables(graph* topology){
    int v = topology->numVertex;
    for(int i=0;i<v;i++){
//        printf("%s",topology->routersArray[i].routerName);
        printf("\nRouting Table for %s \n",topology->routersArray[i].routerName);
        printf("\n\tPath to                 Distance                Via Router(Next Hop)\n\n");
        for(int j=0;j<v;j++){
            printf("\t%s                %d                      %s\n",topology->routersArray[i].rt.destinationRouters[j].routerName, topology->routersArray[i].rt.costArray[j], topology->routersArray[i].rt.viaRouters[j].routerName);
        }
    }
}


void initializeNetworkProperties(intf_properties* intf_prop){

    memset(intf_prop->mac.mac , 0 , 32);
    memset(intf_prop->ip.ip, 0, 16);
    intf_prop->subnetMask = 0;

}


void setInterfaceProperties(edge* link,char* ip1, char* ip2, int mask){

    if(link->intf1.attachedEdge != link  || link->intf2.attachedEdge != link)
        printf("Not matched");

    strncpy(link->intf1.interfaceProperties.ip.ip , ip1, 16);
    link->intf1.interfaceProperties.ip.ip[15] = '\0';
    // printf("%s  %s\n",intf1.interfaceProperties->ip.ip,intf1.attachedNode->routerName);

    strncpy(link->intf2.interfaceProperties.ip.ip , ip2, 16);
    link->intf2.interfaceProperties.ip.ip[15] = '\0';
    // printf("%s  %s\n",intf2.interfaceProperties->ip.ip,intf2.attachedNode->routerName);

    link->intf1.interfaceProperties.subnetMask = mask;
    link->intf2.interfaceProperties.subnetMask = mask;

    // setMacAddressForInterface();

}
