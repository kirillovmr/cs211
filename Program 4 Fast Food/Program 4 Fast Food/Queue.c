//
//  Queue.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include "Queue.h"
#include "Node.h"

static void push(struct Queue *this, struct Node *node) {
    if (this->_Head == NULL)
        this->_Head = node;
    else
        this->_Tail->next = node;
    
    this->_Tail = node;
    this->_size += 1;
}

static void pop(struct Queue *this) {
    if (this->_size == 0)
        return;
    
    struct Node *next = this->_Head->next;
    this->_Head->destroy(this->_Head);
    
    this->_Head = next;
    if(this->_size == 1)
        this->_Tail = NULL;
    
    this->_size -= 1;
}

static struct Node* front(struct Queue *this) {
    return this->_Head;
}

static struct Node* back(struct Queue *this) {
    return this->_Tail;
}

static int size(struct Queue *this) {
    return this->_size;
}

static int empty(struct Queue *this) {
    return this->_size == 0 ? 1 : 0;
}

static struct Queue new(void) {
    return (struct Queue) {
        ._Head = NULL,
        ._Tail = NULL,
        ._size = 0,
        
        .push   = &push,
        .pop    = &pop,
        .front  = &front,
        .back   = &back,
        .size   = &size,
        .empty  = &empty
    };
}

const struct QueueClass Queue = { .new = &new };
