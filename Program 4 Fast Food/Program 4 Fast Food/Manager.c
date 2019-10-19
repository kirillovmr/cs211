//
//  Manager.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Manager.h"
#include "Misc.h"

void _displayAddOrderError(char type, int name, struct Node *n) {
    if (!name)
        printf ("Error: %s command requires an integer value of at least 0\n", type=='a'?"Add":"Call-ahead");
    else
        printf ("Error: %s command requires a name to be given\n", type=='a'?"Add":"Call-ahead");
    printf ("%s command is of form: a <# burgers> <# salads> <name>\n", type=='a'?"Add":"Call-ahead");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    Node.destroy(n);
    if (!name)
        clearToEoln();
}

void _retrieveOrderError() {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
}

static void start(struct Manager *this) {
    printf ("Starting Fast Food Order Management Program\n");
    
    while(TRUE) {
        printf ("\nEnter command: ");
        char command = getchar();
        
        switch (command) {
            case 'q':
                exit(-1);
                break;
            case '?':
                Manager.help();
                clearToEoln();
                break;
            case 'a':
                Manager.addOrder(this, 'a');
                break;
            case 'c':
                Manager.addOrder(this, 'c');
                break;
            case 'w':
                Manager.waiting(this);
                break;
            case 'r':
                Manager.retrieve(this);
                clearToEoln();
                break;
            case 'l':
                Manager.listOrders(this);
                break;
            case 't':
                Manager.estimateTime(this);
                break;
            case 'd':
                Manager.displayOrders(this);
                clearToEoln();
                break;
            default:
                printf ("%c - in not a valid command\n", command);
                printf ("For a list of valid commands, type ?\n");
                clearToEoln();
                break;
        }
    }
}

static void addOrder(struct Manager *this, char type) {
    struct Node *n = Node.newEmpty();
    
    scanf("%d", &n->burgers);
    if (n->burgers < 0) { _displayAddOrderError(type, 0, n); return; }
    
    scanf("%d", &n->salads);
    if (n->salads < 0) { _displayAddOrderError(type, 0, n); return; }
    
    getStringInput(n->name);
    if (n->name[0] == '\0') { _displayAddOrderError(type, 1, n); return; }

    if (Queue.search(&this->q, n->name) != NULL) {
        printf ("Error: Order for \"%s\" already exists\n", n->name);
        Node.destroy(n);
        return;
    }
    
    printf ("Adding %s order for \"%s\": %d burgers and %d salads\n",
            type=='a'?"In-restaurant":"Call-ahead", n->name, n->burgers, n->salads);
    
    n->inRestaurant = type=='a' ? YES : NO;
    Queue.push( &this->q, n );
}

static void waiting(struct Manager *this) {
    char name[30];
    getStringInput(name);
    
    struct Node *res = Queue.search(&this->q, name);
    if (res == NULL) {
        printf ("Error: There is no Call-ahead order for \"%s\"\n", name);
        return;
    }
    
    printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
    res->inRestaurant = YES;
}

static void retrieve(struct Manager *this) {
    int PreparedBurgers, PreparedSalads;
    
    scanf("%d", &PreparedBurgers);
    if (PreparedBurgers < 0) { _retrieveOrderError(); return; }

    scanf("%d", &PreparedSalads);
    if (PreparedSalads < 0) { _retrieveOrderError(); return; }

    printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n",
            PreparedBurgers ,PreparedSalads);
    
    struct Node *t = Queue.front(&this->q);
    while(t != NULL) {
        if (PreparedBurgers >= t->burgers && PreparedSalads >= t->salads && t->inRestaurant == YES)
            break;
        t = t->next;
    }
    
    if (t == NULL) {
        printf ("Error: There are no orders waiting for that amount of burgers & salads\n");
        return;
    }
    
    printf ("Order was given to \"%s\": %d burgers and %d salads\n", t->name, t->burgers, t->salads);
    if (Queue.delete(&this->q, t->name) == 0) {
        printf("ERROR: Order was not deleted from queue\n");
    }
}

static void listOrders(struct Manager *this) {
    char name[30];
    
    getStringInput(name);
    if (Queue.search(&this->q, name) == NULL) {
        printf ("Error: There is no order for \"%s\"\n", name);
        return;
    }
    
    printf ("Order for \"%s\" is behind the following orders\n", name);
    
    struct Node *t = Queue.front(&this->q);
    while(t != NULL) {
        if (strcmp(t->name, name) == 0)
            break;

        printf(" *%s* - %d burgers and %d salads for \"%s\"\n",
               t->inRestaurant==YES?"In-rest":"Call-ahead", t->burgers, t->salads, t->name);
        t = t->next;
    }
}

static void estimateTime(struct Manager *this) {
    char name[30];
    int minutesToWait = 0;
    
    getStringInput(name);
    if (Queue.search(&this->q, name) == NULL) {
        printf ("Error: There is no order for \"%s\"\n", name);
        return;
    }
    
    struct Node *t = Queue.front(&this->q);
    while(t != NULL) {
        minutesToWait += t->burgers * this->timeToPrepareBurger
                        + t->salads * this->timeToPrepareSalad;
        if (strcmp(t->name, name) == 0)
            break;
        t = t->next;
    }
    
    printf ("Estimated waiting time for \"%s\" is %d minutes\n", name, minutesToWait);
}

static void displayOrders(struct Manager *this) {
    printf ("There are %d orders in a queue:\n", Queue.size(&this->q));
    struct Node *t = Queue.front(&this->q);
    while(t != NULL) {
        printf(" *%s* - %d burgers and %d salads for \"%s\"\n",
               t->inRestaurant==YES?"In-rest":"Call-ahead", t->burgers, t->salads, t->name);
        t = t->next;
    }
}

static void help() {
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("a <# burgers> <# salads> <name> - to add your order to the order list\n");
    printf ("c <# burgers> <# salads> <name> - to add a call-ahead order to the order list\n");
    printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
    printf ("r <# burgers> <# salads> - to retrieve the first waiting group whose order matches the items on the counter\n");
    printf ("l <name> - list how many orders are ahead of the named order\n");
    printf ("d - display the order list information\n");
    printf ("t <name> - display an estimated wait time for the given order name\n");
}

static struct Manager new() {
    return (struct Manager) {
        .q = Queue.new(),
        .timeToPrepareBurger = 10,
        .timeToPrepareSalad = 5,
    };
}

const struct ManagerClass Manager = {
    .new = &new,
    
    .help = &help,
    .start = &start,
    .addOrder = &addOrder,
    .waiting = &waiting,
    .retrieve = &retrieve,
    .listOrders = &listOrders,
    .estimateTime = &estimateTime,
    .displayOrders = &displayOrders,
};
