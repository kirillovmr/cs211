//
//  Queue.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <string.h>
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
    Node.destroy(this->_Head);
    
    this->_Head = next;
    if(this->_size-- == 1)
        this->_Tail = NULL;
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

static struct Node* search(struct Queue *this, char *key) {
    struct Node *temp = this->_Head;
    while(temp != NULL) {
        if (this->debug)
            Node.print(temp);
        if (strcmp(temp->name, key) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

static int delete(struct Queue *this, char *key) {
    if (this->_size == 0)
        return 0;
    
    // If key in Head
    if (strcmp(this->_Head->name, key) == 0) {
        Queue.pop(this);
        return 1;
    }
    
    struct Node *parent = NULL;
    struct Node *temp = this->_Head;
    
    while(temp != NULL) {
        if (strcmp(temp->name, key) == 0)
            break;
        parent = temp;
        temp = temp->next;
    }
    
    if (temp == NULL)
        return 0;
    
    parent->next = temp->next;
    
    // If we deleted Tail
    if (temp->next == NULL)
        this->_Tail = parent;
        
    Node.destroy(temp);
    this->_size -= 1;
    
    return 1;
}

static struct Queue new(boolean debug) {
    return (struct Queue) {
        ._Head = NULL,
        ._Tail = NULL,
        ._size = 0,
        .debug = debug,
    };
}

const struct QueueClass Queue = {
    .new = &new,
    
    .push   = &push,
    .pop    = &pop,
    .front  = &front,
    .back   = &back,
    .size   = &size,
    .empty  = &empty,
    
    .search = &search,
    .delete = &delete,
};
