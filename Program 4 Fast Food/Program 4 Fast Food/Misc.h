//
//  Misc.h
//  Program 4 Fast Food
//
//  Created by Viktor Kirillov on 10/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Misc_h
#define Misc_h

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

// Read in until the first \n is read
void getStringInput(char *dest);

// Clear input until next End of Line Character - \n
void clearToEoln(void);

#endif /* Misc_h */
