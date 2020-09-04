#ifndef GRAPH
#define GRAPH

#define NAME_SIZE 32
#define MAXIMUM_INTERFACE_PER_NODE 10

typedef struct Node node;
typedef struct Interface interface;
typedef struct Edge edge;

typedef struct Node{

    char routerName[NAME_SIZE];
    interface *intf[MAXIMUM_INTERFACE_PER_NODE];
}node;

typedef struct Interface{

    char interfaceName[NAME_SIZE];
    node *attachedNode;
    edge *attachedEdge;
//    char ipAddress[16];
//    char macAddress[16];
}interface;

typedef struct Edge{

    interface intf1;
    interface intf2;
    int cost;
}edge;

typedef struct Graph{

    int numVertex,numEdges;
    node *routersArray;

}graph;


// Function Declarations in graph.c
graph* createGraph(int vertex,int edges);

void createGraphNodes(node* router, char *name);

void printGraph(graph* topology);

void printInterface(interface *intf);

node *getNeighbourNode(interface *intf);

void addEdge(node* node1 , node* router2, char* name1, char* name2, int cost);

int getEmptyInterfaceSlot();

#endif
