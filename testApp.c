#include "graph.h"
#include "distanceVector.h"
#include "linkState.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

graph* buildFirstTopology();
// graph* printRoutingTables(graph*);
graph* buildSecondTopology();
graph* buildThirdTopology();
graph* buildFourthTopology();
graph* buildRandomGeneratedTopology();

int main(){

    while(1){
        system("clear");
        printf("CHOOSE A TOPOLOGY:\n\n1. FIRST TOPOLOGY\n2. SECOND TOPOLOGY\n3. THIRD TOPOLOGY\n4. FOURTH TOPOLOGY\n5. Generate Random Topologyy based on Number of Vertices and Edges.\n6. EXIT.");
        int choice;	
        printf("\n\nENTER YOUR CHOICE : ");
        scanf("%d",&choice);
        graph* topo;
        switch(choice)
        {
            case 1: printf("\nFIRST TOPOLOGY BUILT SUCCESSFULLY.");
                topo=buildFirstTopology();
                break;
            case 2: printf("\nSECOND TOPOLOGY BUILT SUCCESSFULLY AND ROUTING TABLES INITIALIZED!!!");
                topo=buildSecondTopology();
                break;
            case 3: printf("\nTHIRD TOPOLOGY BUILT SUCCESSFULLY AND ROUTING TABLES INITIALIZED!!!");
                topo=buildThirdTopology();
                break;
            case 4: printf("\nFOURTH TOPOLOGY BUILT SUCCESSFULLY.\n");
                topo=buildFourthTopology();
                break;
            case 5:
                topo=buildRandomGeneratedTopology();
                break;
            case 6: exit(1);
                break;
            default: printf("\nPLEASE ENTER CORRECT CHOICE!!!!");
        }
        int v = topo->numVertex;
        int e = topo->numEdges;
        initializeRoutingTables(topo);
        activateTopology(topo);

        while(1){
            // system("clear");
            printf("\n1. View Topology.\n2. Choose Routing Protocol to configure your topology.\n3. View Routing Tables.\n4. Go to Main Menu.\n\n");
            int option;
            scanf("%d",&option);
            if(option==1){
                printf("\n");
                sleep(1);
                printGraph(topo);
                sleep(5);
            }else if(option==2){
                
                printf("\na. Distance Vector Routing Protocol.\nb. Link State Routing Protocol.\n\n");
                char proto;
                scanf("%s",&proto);


                if(proto=='a'){
                    updatedBellmanFord(topo,v,e,0);
                }else{
                    doReliableFlooding(topo);
                    // dijkstra(fourth_topo,0) ;
                }
                printf("\nRouting Tables Updated.\n");
                sleep(2);
            }else if(option==3){
                int ch;
                printf("\n\n1. Show Routing Table of a Specific Router.\n2. Show all Routing Tables.\n");
                scanf("%d",&ch);
                if(ch==2){
                    printRoutingTables(topo);
                }else{
                    for(int i=0;i<v;i++){
                        printf("\n%d. Show IP Route Router %d\n",i,i);
                    }
                    printf("Choose Command: ");
                    int x;
                    scanf("%d",&x);
                    if(x>=0 && x<v){
                        printRoutingTableForSpecificRouter(topo,x);
                    }else{
                        printf("Check command Again !!");
                    }
                    sleep(2);
                }
            }else{
                break;
            }
    }   
    
}
return 0;
}
