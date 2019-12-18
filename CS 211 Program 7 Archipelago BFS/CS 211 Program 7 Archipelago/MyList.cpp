//
//  MyList.cpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "MyList.hpp"
#include "Island.hpp"

MyList::MyList(): m_head(NULL), m_tail(NULL), m_size(0) {
    
}

void MyList::push(Island *island) {
    Node *node = new Node(island);
    
    if (m_tail == NULL)
        m_head = node;
    else
        m_tail->next = node;
    m_tail = node;
    m_size++;
}

Island* MyList::top() {
    return m_head->elem;
}

void MyList::pop() {
    if (m_size == 0)
        return;
    
    if (m_size == 1) {
        delete m_head;
        m_head = m_tail = NULL;
    }
    
    if (m_size > 1) {
        Node *tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }
    
    m_size--;
}

bool MyList::search(Island *island) {
    Node *tmp = m_head;
    
    while(tmp != NULL) {
        if (tmp->elem->getId() == island->getId())
            return true;
        tmp = tmp->next;
    }
        
    return false;
}

bool MyList::empty() {
    return m_size == 0;
}

bool MyList::searchAndDelete(Island *island) {
    Node *prev = NULL;
    Node *cur = m_head;
    
    while(cur != NULL) {
        if (cur->elem->getId() == island->getId()) {
            
            // If elem is head
            if (prev == NULL) {
                m_head = cur->next;
                delete cur;
                if (m_head == NULL)
                    m_tail = NULL;
            }
            else {
                prev->next = cur->next;
                delete cur;
                // If element is tail
                if (prev->next == NULL)
                    m_tail = prev;
            }
            m_size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
        
    return false;
}

void MyList::printContents() {
    Node *tmp = m_head;
    while (tmp != NULL) {
        printf("%d ", tmp->elem->getId());
        tmp = tmp->next;
    }
}
