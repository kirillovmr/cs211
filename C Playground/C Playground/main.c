//
//  main.c
//  C Playground
//
//  Created by Viktor Kirillov on 9/25/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
	int i;

	/* allocation and use of a dynamic ONE dimenstional array */

	/* variable declararion */
	int *arr1[20];
	for (i=0; i<20; i++) {
         arr1[i] = (int *)malloc(30 * sizeof(int));
		for (int j=0; j<30; j++) {
			arr1[i][j] = 0;
		}
	}
	/* allocate space for 20 intergers */
//	arr1 = (int*) malloc (sizeof(int) * 20 );

	/* initialize all array locations to contain the value zero */
	for ( i = 0 ; i < 20 ; i++ )
	   arr1[i][i] = 0;

	/* print out all of the values */
	for ( i = 0 ; i < 20 ; i++ )
	   printf ("Position: %3d, value: %3d\n", i, arr1[i][i]);

	/* de-allocated the memory for the array when finished */
	for ( i = 0 ; i < 20 ; i++ )
		free(arr1[i]);

	return 0;
}

//#define b 3
//#define c 12
//#define d 23
//
//struct lnode {
//    char *str; // points to 16 character string
//    struct lnode *next;
//};
//
//struct lnode A[b][c][d];
//int store_ele(int h, int i, int j, struct lnode dest) {
//    A[h][i][j] = dest;
//    return sizeof(A);
//}
//
//int main() {
//    return 0;
//}
