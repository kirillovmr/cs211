//
//  Node.h
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Node_h
#define Node_h

struct Node {
    char *name;
    int burgers, salads;
    struct Node *next;
    
    void (*destroy)(struct Node *this);
};

extern const struct NodeClass {
    struct Node* (*new)(char p_name[30], int p_burgers, int p_salads);
    struct Node* (*newEmpty)(void);
} Node;

#endif /* Node_h */
