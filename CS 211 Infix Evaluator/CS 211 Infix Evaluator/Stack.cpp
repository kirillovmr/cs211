//
//  Stack.cpp
//  CS 211 Infix Evaluator
//
//  Created by Viktor Kirillov on 11/6/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Stack.hpp"

using std::cout;

MyStack::MyStack(): size(0), capacity(2){
    data = new int(capacity);
}

// Return trueif the stack has no members
bool MyStack::isEmpty(){
    return size == 0;
}

// Add the data to the top of stack; grow dynamic array if needed
void MyStack::push(int val){
    if (size == capacity) {
        capacity += 2;
        int *newData = new int(capacity);
        for(int i=0; i<size; i++)
            newData[i] = data[i];
        
        delete data;
        data = newData;
    }
    
    data[size++] = val;
}

// Return the data value on the top of the stack
int MyStack::top(){
    if(size > 0)
        return data[size-1];
    else
        return -1;
}

// Remove the data value from the top of the stack
void MyStack::pop(){
    if (size > 0)
        size -= 1;
}

// Remove and return top element
int MyStack::popTop(){
    if(size > 0)
        return data[--size];
    cout << "Error: Trying to perform a top operation on an empty stack.\n";
    return -999;
}

// “clear” the stack to remove any values it contains
void MyStack::reset(){
    size = 0;
}
