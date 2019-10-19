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
    int timeToPrepareBurger;
    int timeToPrepareSalad;
};

extern const struct ManagerClass {
    struct Manager (*new)(void);
    
    void (*help)(void);
    void (*start)(struct Manager *this);
    void (*addOrder)(struct Manager *this, char type);
    void (*waiting)(struct Manager *this);
    void (*retrieve)(struct Manager *this);
    void (*listOrders)(struct Manager *this);
    void (*estimateTime)(struct Manager *this);
    void (*displayOrders)(struct Manager *this);
} Manager;

#endif /* Manager_h */
