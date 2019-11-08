//
//  main.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//
//  Assume the user (the cashier) knows:
//   • how to properly enter commands
//
//  Assume the user will enter commands when:
//   • An order is given in the restaurant
//   • Someone calls the restaurant
//   • An order is ready for pick up
//   • Someone wants to know their estimated wait time
//

#include <stdio.h>
#include <string.h>
#include "Manager.h"

int main(int argc, const char *argv[]) {
    
    boolean debug = argc > 1 && strcmp(argv[1], "-d") == 0 ? 1 : 0;
    
    struct Manager m = Manager.new(debug);
    Manager.start(&m);
    
    return 0;
}
