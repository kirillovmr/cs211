//
//  Manager.h
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Manager_h
#define Manager_h

#include "Queue.h"
#include "Node.h"

struct Manager {
    struct Queue q;
    
    void (*start)(struct Manager *this);
    void (*addOrder)(struct Manager *this, char type);
    void (*waiting)(struct Manager *this);
    void (*retrieve)(struct Manager *this);
    void (*listOrders)(struct Manager *this);
    void (*displayOrders)(struct Manager *this);
};

extern const struct ManagerClass {
    struct Manager (*new)(void);
    
    void (*help)(void);
    void (*clearToEoln)(void);
} Manager;

#endif /* Manager_h */
