#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ticket node
typedef struct Ticket
{
    char * movie;
    int seats;
    int pending;    // 0 payment done, 1 payment pending
    struct Ticket * next;
} Ticket;

// Info node for ticketList
typedef struct TicketList
{
    int length;
    Ticket * head;
} TicketList;

// properly initializes a ticket List
void TicketListCreate( TicketList ** );
// properly destroys a ticket List
void TicketListDestroy( TicketList * );
// Inserts a ticket inside a given ticket List
void TicketListInsert( TicketList * , char * , int , int);
// Deletes a ticket from the list, if payment is pending ask for confirmation
void TicketListDelete( TicketList * , char *);
// Prints the content of a ticket List
void TicketListPrint( TicketList * );
// Stores the content of a ticketList inside ./Users/username.txt
void TicketListOutput( TicketList *, char * );
// Creates a ticket List from a given username inside ./Users/username.txt
void TicketListInput( TicketList *, char * );


