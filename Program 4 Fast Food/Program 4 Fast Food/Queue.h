//
//  Queue.h
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include "Node.h"

struct Queue {
    struct Node *_Head;
    struct Node *_Tail;
    int _size;
};

extern const struct QueueClass {
    struct Queue (*new)(void);
    
    void (*push)(struct Queue *this, struct Node *node);
    void (*pop)(struct Queue *this);
    struct Node* (*front)(struct Queue *this);
    struct Node* (*back)(struct Queue *this);
    int (*size)(struct Queue *this);
    int (*empty)(struct Queue *this);
    
    struct Node* (*search)(struct Queue *this, char *key);
    int (*delete)(struct Queue *this, char *key);
} Queue;

#endif /* Queue_h */
