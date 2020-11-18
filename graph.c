#include "graph.h"
#include "css.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int index_for_storing_edges =0;
void
init_udp_socket(node *node);


graph *createGraph(int vertex,int edges){

    graph* topology = (graph*) malloc(sizeof(graph));
    topology->numVertex = vertex;
    topology->numEdges = edges;

    topology->routersArray = (node*) malloc(vertex* sizeof(node));		// array of nodes
    
    topology->edgesArray =   (edge*) malloc(edges* sizeof(edge));	// array holding edges
    
    for(int i=0;i<vertex;i++){
        

        // Giving Name to each Router.
        char name[NAME_SIZE] = "Router";
        int index = 6;
        int num = i;
        char str[NAME_SIZE];

        if(my_itoa(num, str) != NULL){

            for(int j = 0; str[j] != '\0'; j++){
            
                char ch = str[j];
                name[index++] = ch;
            }
        }
        
        // if(i<10)
        //     name[6] = i+'0';
        createGraphNodes(&topology->routersArray[i], name);
        createRoutingTable(&topology->routersArray[i].rt, topology->numVertex);
    }

    return topology;
}


void createGraphNodes(node* router, char *name){
    strncpy(router->routerName,name,32);
    router->routerName[NAME_SIZE-1] = '\0';

    init_udp_socket(router);

    char ip[16] = "127.0.0.1";
    strncpy(router->loopbackIPAddress.ip,ip,16);
    router->loopbackIPAddress.ip[15] = '\0';
}



edge* addEdge(graph *topology ,node* node1 , node* node2, char* from_, char* to_, int cost){

    edge *link = (edge*) malloc(sizeof(edge));

    // Setting name of each interface in the edge structure.
    strncpy(link->intf1.interfaceName, from_ ,NAME_SIZE);
    link->intf1.interfaceName[NAME_SIZE-1] = '\0';
    strncpy(link->intf2.interfaceName, to_ ,NAME_SIZE);
    link->intf2.interfaceName[NAME_SIZE-1] = '\0';

    link->intf1.attachedEdge = link;          // Setting back pointer to the edge structure.
    link->intf2.attachedEdge = link;        // this will help in determining the neighbour of the each interface;

    link->intf1.attachedNode = node1;
    link->intf2.attachedNode = node2;

    link->cost = cost;

    int emptyInterfaceSlot;
    emptyInterfaceSlot = getEmptyInterfaceSlot(node1);
    if(emptyInterfaceSlot == -1){
        printf("Cannot add more edges to this Node.");
        exit(0);
    }
    node1->intf[emptyInterfaceSlot] = &link->intf1;
    
    emptyInterfaceSlot = getEmptyInterfaceSlot(node2);
    if(emptyInterfaceSlot == -1){
        printf("Cannot add more edges to this Node.");
        exit(0);
    }
    node2->intf[emptyInterfaceSlot] = &link->intf2;
    topology->edgesArray[index_for_storing_edges++] = *link;

    return link;
}



int getEmptyInterfaceSlot(node *router){

    for(int i=0 ; i<MAXIMUM_INTERFACE_PER_NODE;i++){
        if(router->intf[i] != NULL)
            continue;
        return i;
    }
    return -1;
}


void printGraph(graph* topology){
    int v = topology->numVertex;
    int e = MAXIMUM_INTERFACE_PER_NODE;
    interface *intf;

    printf("\n\n Traversing Network Topology:\n");
    for(int i=0;i<v;i++){
        printf("%s ->\n",topology->routersArray[i].routerName);   // printing router name;
        for(int j=0;j<e;j++){
            intf = topology->routersArray[i].intf[j];
            if(!intf)
                break;
            printInterface(intf);                   // function to print details of connected Interface.
        }
    }
}



void printInterface(interface *intf){

    edge *link = intf->attachedEdge;
    node *neighbourNode = getNeighbourNode(intf);

    // printf("%s",intf->interfaceProperties.ip.ip);
    // printf("%d",intf->interfaceProperties.subnetMask);
    printf(ANSI_COLOR_YELLOW"\tInterface Name : %s \n\t IP Address: %s/%d,\n\t Neighbour Node: %s,\n\t cost = %u\n\n"ANSI_COLOR_RESET,
            intf->interfaceName,intf->interfaceProperties.ip.ip,intf->interfaceProperties.subnetMask,neighbourNode->routerName, link->cost);
}



void printEdges(graph* topology,int numEdges){

    printf("\n\nPrinting All the Edges:\n");
    for(int i=0;i<numEdges;i++){
        edge link = topology->edgesArray[i];
        printf("\n\tNode Name : %s ::\n\t Neighbour Node: %s,\n\t cost = %u\n",
               link.intf1.attachedNode->routerName,link.intf2.attachedNode->routerName, link.cost);
   }
}


node *getNeighbourNode(interface *intf) {    // Each edge has two ends which means 2 nodes, so this function returns the node that is on other end of the edge.
   
    edge *link = intf->attachedEdge;
   
    if(&link->intf1 == intf)
        return link->intf2.attachedNode;
    else
        return link->intf1.attachedNode;
}


int getIndexOfNode(node* router,graph* topology){

    int v = topology->numVertex;

    for(int i=0;i<v;i++){
        if(&(topology->routersArray[i]) == router){
            return i;
        }
    }
    return -1;
}

interface * get_node_if_by_name(node *router, char *if_name){

    int i ;
    interface *intf;

    for( i = 0 ; i < MAXIMUM_INTERFACE_PER_NODE; i++){
        intf = router->intf[i];
        if(!intf) return NULL;
        if(strncmp(intf->interfaceName, if_name, NAME_SIZE) == 0){
            return intf;
        }
    }
    return NULL;
}


char *my_itoa(int num, char *str)
{
        if(str == NULL){
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}



