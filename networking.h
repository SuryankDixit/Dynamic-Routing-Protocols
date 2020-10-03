#ifndef NETWORK_PROPS
#define NETWORK_PROPS


typedef struct Node node;
typedef struct Interface interface;
typedef struct Edge edge;
typedef struct Graph graph;


typedef struct IPAddress{

    char ip[16];

}ip_add;

typedef struct MACAddress{

    char mac[32];

}mac_add;

typedef struct InterfaceProperties{

    ip_add   ip;
    mac_add  mac;
    int      subnetMask;

}intf_properties;


typedef struct RoutingTable{

    node *destinationRouters;
    int *costArray;
    node *viaRouters;

}routing_table;


//  Routing Tables
void createRoutingTable(routing_table* rt,int numVertex);

void initializeRoutingTables(graph* topology);

void activateTopology(graph* topology);

void printRoutingTables(graph* topology);

void printRoutingTableForSpecificRouter(graph* topology ,int i);


// Interface Properties

void initializeNetworkProperties(intf_properties* intf_prop);
void setInterfaceProperties(edge* link,char* ip1, char *ip2, int mask);


#endif


