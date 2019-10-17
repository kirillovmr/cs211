//
//  Node.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

static void destroy(struct Node *this) {
    free(this->name);
    free(this);
}

static struct Node* new(char p_name[30], int p_burgers, int p_salads, boolean inRest) {
    struct Node *n = NULL;
    n = (struct Node*)malloc(sizeof(struct Node));
    
    n->name = (char*)malloc(sizeof(char) * 31);
    n->name = p_name;
    n->burgers = p_burgers;
    n->salads = p_salads;
    n->inRestaurant = inRest;
    n->next = NULL;
    
    n->destroy = &destroy;
    
    return n;
}

static struct Node* newEmpty() {
    struct Node *n = NULL;
    n = (struct Node*)malloc(sizeof(struct Node));
    
    n->next = NULL;
    n->name = (char*)malloc(sizeof(char) * 31);
    n->destroy = &destroy;
    
    return n;
}


const struct NodeClass Node = {
    .new = &new,
    .newEmpty = &newEmpty,
};
