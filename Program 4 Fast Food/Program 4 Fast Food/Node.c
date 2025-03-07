//
//  Node.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

static struct Node* new(char p_name[30], int p_burgers, int p_salads, int p_inRest) {
    struct Node *n = (struct Node*)malloc(sizeof(struct Node));
    n->name = (char*)malloc(sizeof(char) * 31);
    
    n->name = p_name;
    n->burgers = p_burgers;
    n->salads = p_salads;
    n->inRestaurant = p_inRest;
    n->next = NULL;
    
    return n;
}

static struct Node* newEmpty() {
    struct Node *n = (struct Node*)malloc(sizeof(struct Node));
    
    n->name = (char*)malloc(sizeof(char) * 31);
    n->next = NULL;
    
    return n;
}

static void print(struct Node *this) {
    printf("-> %s order for \"%s\": %d burgers, %d salads.\n",
           this->inRestaurant ? "In-rest" : "Call-ahead",
           this->name, this->burgers, this->salads);
}

static void destroy(struct Node *this) {
    free(this->name);
    free(this);
}

const struct NodeClass Node = {
    .new = &new,
    .newEmpty = &newEmpty,
    
    .print = &print,
    .destroy = &destroy,
};
