#ifndef GRAPH
#define GRAPH

#include "networking.h"

#define NAME_SIZE 32
#define MAXIMUM_INTERFACE_PER_NODE 1000

typedef struct Node node;
typedef struct Interface interface;
typedef struct Edge edge;
typedef struct Graph graph;



typedef struct Node{

    char routerName[NAME_SIZE];
    interface *intf[MAXIMUM_INTERFACE_PER_NODE];

    routing_table rt;
    ip_add loopbackIPAddress;

}node;



typedef struct Interface{

    char interfaceName[NAME_SIZE];
    node *attachedNode;
    edge *attachedEdge;

    intf_properties interfaceProperties;        // IP address, MAC Address and Subnet Mask;

}interface;


typedef struct Edge{

    interface intf1;
    interface intf2;
    int cost;
}edge;

typedef struct Graph{

    int numVertex,numEdges;
    node *routersArray;
    edge *edgesArray;

}graph;




// Creating Topology
graph* createGraph(int vertex,int edges);

void createGraphNodes(node* router, char *name);

edge* addEdge(graph* topology,node* node1 , node* router2, char* name1, char* name2, int cost);

void printGraph(graph* topology);

void printInterface(interface *intf);

void printEdges(graph* topology,int numEdges);




// Helper Functions

int getEmptyInterfaceSlot();

int getIndexOfNode(node* router,graph* topology);

char *my_itoa(int num, char *str);

node *getNeighbourNode(interface *intf);

#endif

