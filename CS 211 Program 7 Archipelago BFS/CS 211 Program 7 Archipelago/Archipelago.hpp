//
//  Archipelago.hpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Archipelago_hpp
#define Archipelago_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <functional>
#include "Island.hpp"
#include "MyList.hpp"

class Archipelago {
private:
    unsigned m_numOfIslands;
    Island **m_islands;
    FileList m_fList;
    
public:
    Archipelago(unsigned numOfIslands);
    
    void showCommands();
    void eventLoop(FILE* inFile);

private:
    void _constructIslands();
    void _deconstructIslands();
    
    void depthFirstSearchHelper(int x, int y);
    bool dfs(int a, int b);
    
    MyList breadthFirstSearch(int x, int y);
    bool bfs(int b, MyList &islandQueue);
    
    void doShortestPath(char *input);
    void doTravel(char *input);
    void doResize(char *input);
    void doInsert(char *input);
    void doDelete(char *input);
    void doList();
    void doFile();
    
};

#endif /* Archipelago_hpp */
