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

static void start(struct Manager *this) {
    printf ("Starting Fast Food Order Management Program\n");
    
    while(1) {
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
                this->addOrder(this);
                break;
            case 'c':
                break;
            case 'w':
                break;
            case 'r':
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
        if (command != 'a')
            Manager.clearToEoln();
    }
}

void addOrder(struct Manager *this) {
    struct Node *n = Node.newEmpty();
    
    scanf("%d %d", &n->burgers, &n->salads);
//    fgets(n->name, sizeof(n->name), stdin);
//    n->name[strcspn(n->name, "\n")] = 0;
//    strtok(n->name, "\n");
    
    int i = 0, begin = 0;
    char c;
    while(1) {
        c = getchar();
//        printf("Char %d", c);
        if (c == 10)
            break;
        if (begin) {
            n->name[i] = c;
            i++;
        }
        else if (c == ' ')
            begin = 1;
    }
    n->name[i+1] = '\0';
    
    this->q.push( &this->q, n );
}

void displayOrders(struct Manager *this) {
    printf ("There are %d orders in a list\n", this->q.size(&this->q));
    struct Node *t = this->q.front(&this->q);
    while(t != NULL) {
        printf("%s %d %d\n", t->name, t->burgers, t->salads);
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
        .displayOrders = &displayOrders,
    };
}

const struct ManagerClass Manager = {
    .new = &new,
    .help = &help,
    .clearToEoln = &clearToEoln,
};
