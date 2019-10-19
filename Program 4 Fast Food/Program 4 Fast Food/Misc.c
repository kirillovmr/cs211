//
//  Misc.c
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include "Misc.h"

void getStringInput(char *dest) {
    int i = 0, begin = 0; char c;
    while(TRUE) {
        c = getchar();
        if (c == 10) { break; }
        if (c != ' ' && !begin) { begin = 1; }
        if (begin) { dest[i++] = c; }
    }
    dest[i+1] = '\0';
}

void clearToEoln() {
    int ch;
    do { ch = getc(stdin); }
    while ((ch != '\n') && (ch != EOF));
}
