//
//  main.c
//  CS 211 Proj 2
//
//  Created by Viktor Kirillov on 9/24/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//
// 	abhcgmsopa bqcedpwon abmnpc abcdponm dfajbbmmn cabnmo
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

// // //
// GLOBAL VARIABLES
//
const int arrSize = 4;
int DebugMode = FALSE;
char L [arrSize] = {'a','b','c','d'};
char L2[arrSize] = {'m','n','o','p'};

typedef struct {
	int size, capacity;
	char *arr;
} Stack;


// // //
// WORKING WITH STACK
//
void init(Stack *st) {
	st->size = 0;
	st->capacity = 4;
	st->arr = (char*)malloc(4 * sizeof(char));
}

void grow(Stack *st) {
	char *arrOld = st->arr;
	st->arr = (char*)malloc(st->capacity+4 * sizeof(char));
	
	for (int i=0; i<st->capacity; i++)
		st->arr[i] = arrOld[i];
	
	free(arrOld);
	st->capacity += 4;
}

char top(Stack *st) {
	if (st->size == 0)
		return '#';
	
	return st->arr[st->size - 1];
}

void push(Stack *st, char val) {
	if (st->size == st->capacity)
		grow(st);
	st->arr[st->size++] = val;
}

char pop(Stack *st) {
	if (st->size == 0)
		return '#';
	
	char r = top(st);
	st->size -= 1;
	return r;
}

int is_empty(Stack *st) {
	return st->size == 0 ? 1 : 0;
}

void clearStack(Stack *st) {
	st->size = 0;
}


// // //
// MISC FUNCTIONS
//
int charInArray(char c, char *arr) {
	for (int i=0; i<arrSize; i++)
		if (arr[i] == c)
			return 1;
	return 0;
}

int verifyMapping(char a, char b, char *arr1, char *arr2) {
	for (int i=0; i<arrSize; i++)
		if (arr1[i] == a)
			return (arr2[i] == b) ? 1 : 0;
	return 0;
}

void removeExtraLettersAndPrint(char *encoded, char *alphabet) {
	char decoded[20] = "";
	
	int i = 0;
	char *c = encoded;
	while (*c != '\0') {
		if (charInArray(*c, alphabet)) {
			decoded[i++] = *c;
		}
		
		c++;
	}
	decoded[i] = '\0';
	printf("%s ", decoded);
}

int main(int argc, char const *argv[]) {
	
	// Setting debug mode depending on the flag
	for (int i = 0; i < argc; i++)
		if (strcmp (argv[i], "-d") == 0)
			DebugMode = TRUE;
	
	
	Stack stack;
	init(&stack);

    char input[300];

    /* set up an infinite loop */
    while (1) {
        /* get line of input from standard input */
        printf("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);

        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0') {
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0))
            break;

        printf("Encrypted message: %s\n", input);
        /*Start tokenizing the input into words separated by space
         We use strtok() function from string.h*/
        /*The tokenized words are added to an array of words*/

        char delim[] = " ";
        char *ptr = strtok(input, delim);
        int j = 0;
        char *wordList[15];

        while (ptr != NULL) {
            wordList[j++] = ptr;
            ptr = strtok(NULL, delim);
        }

        /*Run the algorithm to decode the message*/
		printf("Decoded message: ");
		
		// Going through words
		for (int k=0; k<j; k++) {
			clearStack(&stack);
			
			// going through letters
			char *c = wordList[k];
			while (*c != '\0') {
				
				// If char in L
				if (charInArray(*c, L))
					push(&stack, *c);
				
				// If char in L2
				if (charInArray(*c, L2)) {
					
					// If maps correctly
					if (verifyMapping( top(&stack), *c, L, L2 ))
						pop(&stack);
				}
				
				c++;
			}
			
			if (is_empty(&stack))
				removeExtraLettersAndPrint(wordList[k], L);
		}
		printf("\n");
    }

    printf("\nGoodbye\n");
    return 0;
}

