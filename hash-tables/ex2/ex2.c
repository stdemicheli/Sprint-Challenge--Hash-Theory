#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
    HashTable *ht = create_hash_table(16);
    char **route = malloc(length * sizeof(char *));
    
    Ticket *startingTicket = malloc(sizeof(Ticket));

    for (int i = 0; i < length; i++) {
        Ticket *ticket = tickets[i];
        hash_table_insert(ht, ticket->source, ticket->destination);
        printf("insert key: %s, value: %s\n", ticket->source, ticket->destination);
        
        if (strcmp(ticket->source, "NONE") == 0) {
            startingTicket = ticket;
        }
        
    }
    
    printf("starting airport: %s\n", startingTicket->destination);
    char *currentDestination = startingTicket->destination;
    
    // Starting with the first airport, add routes to the route list via hash table lookup
    for (int i = 0; i < length; i++) {
        char *nextDestination = hash_table_retrieve(ht, currentDestination);
        
        if (nextDestination) {
            route[i] = currentDestination;
            printf("next airport: %s\n", nextDestination);
            currentDestination = nextDestination;
        }
    }

    return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
