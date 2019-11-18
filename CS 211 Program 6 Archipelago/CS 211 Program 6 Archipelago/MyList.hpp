//
//  MyList.hpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef MyList_hpp
#define MyList_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>

class Island;

struct Node {
    Island *elem;
    Node *next;
    
    Node(Island *island): elem(island), next(NULL) {}
};

class MyList {
private:
    Node *m_head;
    Node *m_tail;
    unsigned m_size;
    
public:
    MyList();
    
    // Iterator functions
    class Iterator;
    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return Iterator(nullptr); }
    
    void push(Island *island);
    bool search(Island *island);
    
    bool searchAndDelete(Island *island);
    
    void printContents();
    
    // Iterator class
    class Iterator {
    private:
        Node *m_pCurrentNode;
    public:
        Iterator(Node *pNode) noexcept: m_pCurrentNode(pNode) {}
        Iterator& operator=(Node *pNode) {
            m_pCurrentNode = pNode;
            return *this;
        }

        // Prefix ++ overload
        Iterator& operator++() {
            if (m_pCurrentNode)
                m_pCurrentNode = m_pCurrentNode->next;
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator!=(const Iterator& iterator) {
            return m_pCurrentNode != iterator.m_pCurrentNode;
        }

        Island* operator*() {
            return m_pCurrentNode->elem;
        }
    };
};



struct FileNode {
    char *fileName;
    FileNode *next;
    
    FileNode(char *name, FileNode *nextNode) {
        fileName = name;
        next = nextNode;
    }
};

struct FileList {
    FileNode *m_head;
    FileList(): m_head(NULL) {}
    
    void push(char *name) {
        FileNode *node = new FileNode(name, m_head);
        m_head = node;
    }
    void pop() {
        if (m_head) {
            delete m_head;
            m_head = m_head->next;
        }
    }
    bool search(char *name) {
        FileNode *tmp = m_head;
        while(tmp != NULL) {
            if (strcmp(tmp->fileName, name) == 0)
                return true;
            tmp = tmp->next;
        }
        return false;
    }
};


#endif /* MyList_hpp */
