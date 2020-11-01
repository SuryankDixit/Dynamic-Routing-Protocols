#ifndef __COMM__
#define __COMM__

#define MAX_PACKET_BUFFER_SIZE   2048

typedef struct Node node;
typedef struct Interface interface;


/* API to send the packet out of the interface.
 * Nbr node must receieve the packet on other end
 * of the link*/
int
send_pkt_out(char *pkt, unsigned int pkt_size, interface *intf);

/*API to recv packet from interface*/
int
pkt_receive(node *router, interface *intf, 
            char *pkt, unsigned int pkt_size);

/* API to flood the packet out of all interfaces
 * of the node*/
int
send_pkt_flood(node *router, char *pkt, unsigned int pkt_size);

#endif /* __COMM__ */
