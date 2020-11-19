#include "graph.h"
#include "distanceVector.h"
#include "linkState.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include "css.h"


graph* buildFirstTopology();
// graph* printRoutingTables(graph*);
graph* buildSecondTopology();
graph* buildThirdTopology();
graph* buildFourthTopology();
graph* buildRandomGeneratedTopology();

int main(){

    while(1){
        system("clear");
        printf(ANSI_COLOR_YELLOW "CHOOSE A TOPOLOGY:\n\n1. FIRST TOPOLOGY\n2. SECOND TOPOLOGY\n3. THIRD TOPOLOGY\n4. FOURTH TOPOLOGY\n5. Generate Random Topologyy based on Number of Vertices and Edges.\n6. EXIT."ANSI_COLOR_RESET);
        int choice;	
        printf("\n\nENTER YOUR CHOICE : ");
        scanf("%d",&choice);
        graph* topo;
        switch(choice)
        {
            case 1: printf(ANSI_COLOR_GREEN"\nFIRST TOPOLOGY BUILT SUCCESSFULLY."ANSI_COLOR_RESET);
                topo=buildFirstTopology();
                break;
            case 2: printf(ANSI_COLOR_GREEN"\nSECOND TOPOLOGY BUILT SUCCESSFULLY AND ROUTING TABLES INITIALIZED!!!"ANSI_COLOR_RESET);
                topo=buildSecondTopology();
                break;
            case 3: printf(ANSI_COLOR_GREEN"\nTHIRD TOPOLOGY BUILT SUCCESSFULLY AND ROUTING TABLES INITIALIZED!!!"ANSI_COLOR_RESET);
                topo=buildThirdTopology();
                break;
            case 4: printf(ANSI_COLOR_GREEN"\nFOURTH TOPOLOGY BUILT SUCCESSFULLY.\n"ANSI_COLOR_RESET);
                topo=buildFourthTopology();
                break;
            case 5:
                topo=buildRandomGeneratedTopology();
                break;
            case 6: exit(1);
                break;
            default: printf(ANSI_COLOR_RED"\nPLEASE ENTER CORRECT CHOICE!!!!\n"ANSI_COLOR_RESET);
                     exit(1);
        }
        int v = topo->numVertex;
        int e = topo->numEdges;
        initializeRoutingTables(topo);
        activateTopology(topo);

        while(1){
            // system("clear");
            printf(ANSI_COLOR_CYAN"\n1. View Topology.\n2. Choose Routing Protocol to configure your topology.\n3. View Routing Tables.\n4. Go to Main Menu.\n\n"ANSI_COLOR_RESET);
            int option;
            scanf("%d",&option);
            if(option==1){
                printf("\n");
                sleep(1);
                printGraph(topo);
                sleep(5);
            }else if(option==2){
                
                printf(ANSI_COLOR_CYAN"\na. Distance Vector Routing Protocol.\nb. Link State Routing Protocol.\n\n"ANSI_COLOR_RESET);
                char proto;
                scanf("%s",&proto);

                clock_t t; 
                
                if(proto=='a'){
                    initializeRoutingTables(topo);
                    activateTopology(topo);
                    t = clock();
                    updatedBellmanFord(topo,v,e,0);
                    t = clock() - t; 
                }
                else if(proto=='b'){
                    initializeRoutingTables(topo);
                    activateTopology(topo);
                    doReliableFlooding(topo);
                    t = clock();
                    linkState(topo);
                    t = clock() - t; 
                    initializeRoutingTables(topo);
                    activateTopology(topo);
                    updatedBellmanFord(topo,v,e,0);
                }
                double time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf(ANSI_COLOR_GREEN"\nRouting Tables Updated.\n"ANSI_COLOR_RESET);
                printf(ANSI_COLOR_RED"Time taken to Update: %f\n"ANSI_COLOR_RESET,time_taken);
                sleep(2);
            }else if(option==3){
                int ch;
                printf(ANSI_COLOR_CYAN"\n\n1. Show Routing Table of a Specific Router.\n2. Show all Routing Tables.\n"ANSI_COLOR_RESET);
                scanf("%d",&ch);
                if(ch==2){
                    printRoutingTables(topo);
                }else{
                    for(int i=0;i<v;i++){
                        printf(ANSI_COLOR_YELLOW"\n%d. Show IP Route Router %d\n"ANSI_COLOR_RESET,i,i);
                    }
                    printf("Choose Command: ");
                    int x;
                    scanf("%d",&x);
                    if(x>=0 && x<v){
                        printRoutingTableForSpecificRouter(topo,x);
                    }else{
                        printf(ANSI_COLOR_RED"Check command Again !!"ANSI_COLOR_RESET);
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
