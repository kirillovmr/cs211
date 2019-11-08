//
//  main.cpp
//  CS 211 Infix Evaluator
//
//  Created by Viktor Kirillov on 11/6/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Evaluator.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    
    bool debug = false;
    if (argc > 1)
        if (strncmp(argv[1], "-d", 2) == 0)
            debug = true;
    
    Evaluator ev(debug);
    ev(std::cin);
    
    return 0;
}
