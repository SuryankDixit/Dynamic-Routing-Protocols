#include "graph.h"
#include "distanceVector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


void updatedBellmanFord(graph *topology, int numVertex, int numEdges){
     
    //  int index = getIndexOfNode(sourceNode,topology);
     int v = topology->numVertex;
     int e = MAXIMUM_INTERFACE_PER_NODE;
     interface *intf;
     int indexForRoutingTable =0;

     for(int times =0; times <v; times++){
        for(int i =0; i<v; i++){

            node *currentNode = &(topology->routersArray[i]);

            for(int j=0; j<e; j++){

                for(int k = 0; k < v; k++){

                    // int index = getIndexOfNode(neighbourNode,topology);

                    intf = topology->routersArray[i].intf[j];
                    if(!intf)
                        break;
                    node* neighbourNode = getNeighbourNode(intf);
                    int distanceFromCurrentToNeighbourNode = intf->attachedEdge->cost;
                    
                    // printf("\n%s  %s\n",currentNode->routerName,neighbourNode->routerName);
                    
                    if(neighbourNode->rt.costArray[k] != INT_MAX && currentNode->rt.costArray[k] > neighbourNode->rt.costArray[k] + distanceFromCurrentToNeighbourNode){

                        currentNode->rt.costArray[k] = neighbourNode->rt.costArray[k] + distanceFromCurrentToNeighbourNode;
                        currentNode->rt.viaRouters[k] = *neighbourNode;
                    }
                }
            }
        }
     }
}


void bellmanFord(graph *topology, int numVertex, int numEdges, node* sourceNode,int index){

    int distance[numVertex];
    for(int i=0;i<numVertex;i++){
        distance[i] = INT_MAX;
    }

    distance[index] =0;

    for(int i =0;i <numVertex-1; i++){          // looping n-1 times
        for(int j =0; j<numEdges; j++){         // looping over arrayEdges

            edge link = topology->edgesArray[j];
            int fromNode = getIndexOfNode(link.intf1.attachedNode,topology);
            int toNode   = getIndexOfNode(link.intf2.attachedNode,topology);
            int dis      = link.cost;

            if(distance[fromNode] != INT_MAX && distance[toNode] > distance[fromNode] + dis){
                distance[toNode] = distance[fromNode] + dis;
            }

            if(distance[toNode] != INT_MAX && distance[fromNode] > distance[toNode] + dis){
                distance[fromNode] = distance[toNode] + dis;
            }
        }
    }

    for(int i =0; i<numEdges; i++){
        edge link = topology->edgesArray[i];
            int fromNode = getIndexOfNode(link.intf1.attachedNode,topology);
            int toNode   = getIndexOfNode(link.intf2.attachedNode,topology);
            int dis      = link.cost;

            if(distance[fromNode] != INT_MAX && distance[toNode] > distance[fromNode] + dis){
                printf("Negative Weight Cycle is Present. Inspect your Topology.");
                exit(0);
            }

            if(distance[toNode] != INT_MAX && distance[fromNode] > distance[toNode] + dis){
                printf("Negative Weight Cycle is Present. Inspect your Topology.");
                exit(0);
            }
    }

    printf("\nRouting Table for %s:\n",sourceNode->routerName);
    // for(int i =0;i <numVertex; i++){
    //     printf("Cost: %d\n",distance[i]);
    // }
    for(int i =0;i <numVertex; i++){
        topology->routersArray[index].rt.costArray[i] = distance[i];
        // printf("hi %d\n",i);
        printf("\t%s      %d\n",
                topology->routersArray[index].rt.destinationRouters[i].routerName, topology->routersArray[index].rt.costArray[i]);
    }
}
