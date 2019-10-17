//
//  main.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include "Manager.h"

int main(int argc, const char * argv[]) {
    
    struct Manager m = Manager.new();
    m.start(&m);
    
    return 0;
}
