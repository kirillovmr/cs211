//
//  Manager.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Manager.h"

void getStringInput(char *dest) {
    int i = 0, begin = 0; char c;
    while(TRUE) {
        c = getchar();
        if (c == 10) { break; }
        if (begin) { dest[i++] = c; }
        else if (c == ' ') { begin = 1; }
    }
    dest[i+1] = '\0';
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
                break;
            case 'a':
                this->addOrder(this, 'a');
                break;
            case 'c':
                this->addOrder(this, 'c');
                break;
            case 'w':
                this->waiting(this);
                break;
            case 'r':
                this->retrieve(this);
                break;
            case 'l':
                break;
            case 't':
                break;
            case 'd':
                this->displayOrders(this);
                break;
            default:
                printf ("%c - in not a valid command\n", command);
                printf ("For a list of valid commands, type ?\n");
                break;
        }
        if (command != 'a' && command != 'c')
            Manager.clearToEoln();
    }
}

static void addOrder(struct Manager *this, char type) {
    struct Node *n = Node.newEmpty();
    
    scanf("%d", &n->burgers);
    if (n->burgers < 0) {
        printf ("Error: %s command requires an integer value of at least 0\n", type=='a'?"Add":"Call-ahead");
        printf ("%s command is of form: a <# burgers> <# salads> <name>\n", type=='a'?"Add":"Call-ahead");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        n->destroy(n);
        Manager.clearToEoln();
        return;
    }
    
    scanf("%d", &n->salads);
    if (n->salads < 0) {
        printf ("Error: %s command requires an integer value of at least 0\n", type=='a'?"Add":"Call-ahead");
        printf ("%s command is of form: a <# burgers> <# salads> <name>\n", type=='a'?"Add":"Call-ahead");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        n->destroy(n);
        Manager.clearToEoln();
        return;
    }
    
    getStringInput(n->name);
    if (n->name[0] == '\0') {
        printf ("Error: %s command requires a name to be given\n", type=='a'?"Add":"Call-ahead");
        printf ("%s command is of form: a <# burgers> <# salads> <name>\n", type=='a'?"Add":"Call-ahead");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        n->destroy(n);
        return;
    }

    if (this->q.search(&this->q, n->name) != NULL) {
        printf ("Error: Order for \"%s\" already exists\n", n->name);
        n->destroy(n);
        return;
    }
    
    n->inRestaurant = type=='a' ? YES : NO;
    
    printf ("Adding %s order for \"%s\": %d burgers and %d salads\n",
            type=='a'?"In-restaurant":"Call-ahead", n->name, n->burgers, n->salads);
    this->q.push( &this->q, n );
}

static void waiting(struct Manager *this) {
    
}

static void retrieve(struct Manager *this) {
    int PreparedBurgers;
    scanf("%d", &PreparedBurgers);
    if (PreparedBurgers < 0) {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }

    int PreparedSalads;
    scanf("%d", &PreparedSalads);
    if (PreparedSalads < 0) {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }

    printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n",
            PreparedBurgers ,PreparedSalads);
    
    struct Node *t = this->q.front(&this->q);
    while(t != NULL) {
        if (PreparedBurgers >= t->burgers && PreparedSalads >= t->salads)
            break;
        t = t->next;
    }
    
    if (t == NULL) {
        printf ("Error: There are no orders waiting for that amount of burgers & salads\n");
        return;
    }
    
    printf ("Order was given to \"%s\": %d burgers and %d salads\n", t->name, t->burgers, t->salads);
    if (this->q.delete(&this->q, t->name) == 0) {
        printf("ERROR: Order was not deleted from queue\n");
    }
}

static void displayOrders(struct Manager *this) {
    printf ("There are %d orders in a queue:\n", this->q.size(&this->q));
    struct Node *t = this->q.front(&this->q);
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

static void clearToEoln() {
    int ch;
    do { ch = getc(stdin); }
    while ((ch != '\n') && (ch != EOF));
}

static struct Manager new() {
    return (struct Manager) {
        .q = Queue.new(),
        
        .start = &start,
        .addOrder = &addOrder,
        .waiting = &waiting,
        .retrieve = &retrieve,
        .displayOrders = &displayOrders,
    };
}

const struct ManagerClass Manager = {
    .new = &new,
    .help = &help,
    .clearToEoln = &clearToEoln,
};
