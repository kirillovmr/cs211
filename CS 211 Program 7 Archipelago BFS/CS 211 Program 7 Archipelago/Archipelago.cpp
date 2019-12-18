//
//  Archipelago.cpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Archipelago.hpp"

bool extractIntegers(int &val1, int &val2) {
    char* next = strtok (NULL, " \n\t");
    if ( next == NULL ) {
        printf ("Integer value expected\n");
        return false;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0) {
        printf ("Integer value expected\n");
        return false;
    }
    
    if (val2 != -1) {
        next = strtok (NULL, " \n\t");
        if ( next == NULL ) {
            printf ("Integer value expected\n");
            return false;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0) {
            printf ("Integer value expected\n");
            return false;
        }
    }
    
    return true;
}


Archipelago::Archipelago(unsigned numOfIslands): m_numOfIslands(numOfIslands)
{
    _constructIslands();
}

void Archipelago::_constructIslands() {
    m_islands = (Island**) malloc(m_numOfIslands * sizeof(Island*));
       for (unsigned i=0; i<m_numOfIslands; i++)
           m_islands[i] = new Island(i+1);
}

void Archipelago::_deconstructIslands() {
    for (unsigned i=0; i<m_numOfIslands; i++)
        delete m_islands[i];
    delete m_islands;
}

void Archipelago::depthFirstSearchHelper(int x, int y) {
    for (unsigned i=0; i<m_numOfIslands; i++)
        m_islands[i]->setVisited(false);
    
    if (dfs(x, y))
        printf("You can get from island %d to island %d in one or more ferry rides\n", x, y);
    else
        printf("You can NOT get from island %d to island %d in one or more ferry rides\n", x, y);
}

bool Archipelago::dfs(int a, int b) {
    for (Island *c : m_islands[a-1]->getConnections()) {
        if (c->getId() == b)
            return true;
        if (c->getVisited() == false) {
            c->setVisited(true);
            if (dfs(c->getId(), b)) {
                return true;
            }
        }
    }
    return false;
}

MyList Archipelago::breadthFirstSearch(int x, int y) {
    for (unsigned i=0; i<m_numOfIslands; i++) {
        m_islands[i]->setVisited(false);
        m_islands[i]->setPrev(NULL);
    }
    
    MyList islandQueue;
    islandQueue.push(m_islands[x-1]);
    if (bfs(y, islandQueue) == false) {
        printf("You can NOT get from island %d to island %d in one or more ferryrides", x, y);
        return MyList();
    }
    else {
        printf("You can get from island %d to island %d in one or more ferryrides", x, y);
        MyList pathList;
        Island *cur = m_islands[y-1];
        pathList.push(cur);
        do {
            cur = cur->getPrev();
            pathList.push(cur);
        } while (cur->getId() != x);
        return pathList;
    }
}

bool Archipelago::bfs(int b, MyList &islandQueue) {
    while (!islandQueue.empty()) {
        Island *a = islandQueue.top();
        islandQueue.pop();
        
        for (Island *c : a->getConnections()) {
            if (c->getVisited() == false) {
                c->setVisited(true);
                c->setPrev(a);
                if (c->getId() == b)
                    return true;
                islandQueue.push(c);
            }
        }
    }
    return false;
}

void Archipelago::doShortestPath(char *input) {
    int val1 = 0, val2 = 0;
    extractIntegers(val1, val2);
    if (val1 <= 0 || val1 > m_numOfIslands || val2 <= 0 || val2 > m_numOfIslands) {
        printf("Error. There are only islands 1-%d\n", m_numOfIslands);
        return;
    }
    MyList path = breadthFirstSearch(val1, val2);
    
    int pathArr[path.size()];
    int i=0;
    for (Island *c: path)
        pathArr[i++] = c->getId();
    
    printf("\nPath: ");
    for(i=path.size()-1; i>=0; i--)
        printf("%d ", pathArr[i]);
    printf("\n");
}

void Archipelago::doTravel(char *input) {
    int val1 = 0, val2 = 0;
    extractIntegers(val1, val2);
    if (val1 <= 0 || val1 > m_numOfIslands || val2 <= 0 || val2 > m_numOfIslands) {
        printf("Error. There are only islands 1-%d\n", m_numOfIslands);
        return;
    }
    depthFirstSearchHelper(val1, val2);
}

void Archipelago::doResize(char *input) {
    int val1 = 0, val2 = -1;
    extractIntegers(val1, val2);
    if (val1 <= 0) {
        printf("Expected value > 0\n");
        return;
    }
    _deconstructIslands();
    m_numOfIslands = val1;
    _constructIslands();
}

void Archipelago::doInsert(char *input) {
    int val1 = 0, val2 = 0;
    extractIntegers(val1, val2);
    if (val1 <= 0 || val1 > m_numOfIslands || val2 <= 0 || val2 > m_numOfIslands) {
        printf("Error. There are only islands 1-%d\n", m_numOfIslands);
        return;
    }
    if (!m_islands[val1-1]->isConnected(m_islands[val2-1]))
        m_islands[val1-1]->connect(m_islands[val2-1]);
}

void Archipelago::doDelete(char *input) {
    int val1 = 0, val2 = 0;
    extractIntegers(val1, val2);
    if (val1 <= 0 || val1 > m_numOfIslands || val2 <= 0 || val2 > m_numOfIslands) {
        printf("Error. There are only islands 1-%d\n", m_numOfIslands);
        return;
    }
    m_islands[val1-1]->disconnect(m_islands[val2-1]);
}

void Archipelago::doList() {
    for (unsigned i=0; i<m_numOfIslands; i++) {
        printf("Island %d -> ", m_islands[i]->getId());
        for (Island *island : m_islands[i]->getConnections()) {
            printf("%d ", island->getId());
        }
        printf("\n");
    }
}

void Archipelago::doFile() {
    char *fname = strtok(NULL, " \n\t");
    if (fname == NULL) {
        printf ("Filename expected\n");
        return;
    }
    
    // Remove \r at the end
    if (fname[strlen(fname)-1] == '\r')
        fname[strlen(fname)-1] = '\0';
    
    if (m_fList.search(fname) == false) {
        FILE *inFile = fopen(fname, "r");
        printf ("Performing the File command with file: %s\n", fname);
        m_fList.push(fname);
        eventLoop(inFile);
        m_fList.pop();
    }
}


void Archipelago::eventLoop(FILE* inFile) {
    char buffer[300], *input, *command;

    input = fgets(buffer, 300, inFile);
    while (input != NULL) {
        command = strtok (input, " \n\t");
        
        // Remove \r at the end
        if (command[strlen(command)-1] == '\r')
            command[strlen(command)-1] = '\0';

        printf ("*%s*\n", command);

        if ( command == NULL )
            printf ("Blank Line\n");

        else if ( strcmp (command, "q") == 0)
            exit(1);

        else if ( strcmp (command, "?") == 0)
            showCommands();
        
        else if ( strcmp (command, "s") == 0)
            doShortestPath(input);

        else if ( strcmp (command, "t") == 0)
            doTravel(input);

        else if ( strcmp (command, "r") == 0)
            doResize(input);

        else if ( strcmp (command, "i") == 0)
            doInsert(input);

        else if ( strcmp (command, "d") == 0)
            doDelete(input);

        else if ( strcmp (command, "l") == 0)
            doList();

        else if ( strcmp (command, "f") == 0)
            doFile();

        else if ( strcmp (command, "#") == 0)
            ;

        else
            printf ("Command is not known: %s\n", command);

        input = fgets (buffer, 300, inFile);
    }
}

void Archipelago::showCommands() {
    printf ("The commands for this project are:\n");
    printf ("  q \n");
    printf ("  ? \n");
    printf ("  # \n");
    printf ("  s <int1> <int2> \n");
    printf ("  t <int1> <int2> \n");
    printf ("  r <int> \n");
    printf ("  i <int1> <int2> \n");
    printf ("  d <int1> <int2> \n");
    printf ("  l \n");
    printf ("  f <filename> \n");
}
