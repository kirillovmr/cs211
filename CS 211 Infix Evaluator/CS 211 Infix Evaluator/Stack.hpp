//
//  Stack.hpp
//  CS 211 Infix Evaluator
//
//  Created by Viktor Kirillov on 11/6/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>

class MyStack {
private:
    int *data;
    int size;
    int capacity;
    
public:
    MyStack();
    
    // Return trueif the stack has no members
    bool isEmpty();
    
    // Add the data to the top of stack; grow dynamic array if needed
    void push(int);
    
    // Return the data value on the top of the stack
    int top();
    
    // Remove the data value from the top of the stack
    void pop();
    
    // Remove and return top element
    int popTop();
    
    // “clear” the stack to remove any values it contains
    void reset();
};

#endif /* Stack_hpp */
