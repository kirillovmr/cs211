//
//  MyStack.hpp
//  CS 211 Program 7 Archipelago BFS
//
//  Created by Viktor Kirillov on 12/2/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef MyStack_hpp
#define MyStack_hpp

#include "MyList.hpp"

class MyStack: MyList {
    void push(Island *island) {
        Node *node = new Node(island);
        node->next = m_head;
        m_head = node;
        
        if (m_tail == NULL)
            m_tail = node;
        
        m_size++;
        
    }
};

#endif /* MyStack_hpp */
