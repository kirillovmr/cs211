//
//  main.cpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <cstdio>

#include "Archipelago.hpp"

int main(int argc, const char * argv[]) {
    FILE *inFile = stdin;
    
    Archipelago arch(10);
    arch.showCommands();
    arch.eventLoop(inFile);
    
    printf ("Goodbye\n");
    return 1;
}
