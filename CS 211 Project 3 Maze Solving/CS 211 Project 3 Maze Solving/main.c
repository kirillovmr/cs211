//
//  main.c
//  CS 211 Project 3 Maze Solving
//
//  Created by Viktor Kirillov on 10/4/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int debugMode = FALSE;

typedef struct mazeStruct {
    char **arr;
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} Maze;

typedef struct nodeStruct {
    int posX, posY;
    struct nodeStruct *next;
} Node;



Node* initializeStack(int x, int y) {
    Node *head = NULL;
    head = (Node*)malloc(sizeof(Node));
    head->posX = x;
    head->posY = y;
    head->next = NULL;
    
    return head;
}

void push(Node **head, int posX, int posY) {
    Node *node = NULL;
    node = (Node*)malloc(sizeof(Node));
    
    node->posX = posX;
    node->posY = posY;
    node->next = *head;
    *head = node;
}

int pop(Node **head, int *posX, int *posY) {
    Node *next_node = NULL;
    *posX = *posY = -1;

    if (*head == NULL)
        return 0;
    
    next_node = (*head)->next;
    *posX = (*head)->posX;
    *posY = (*head)->posY;
    free(*head);
    *head = next_node;
    return 1;
}

void initializeMaze(Maze *maze) {
    int i, j;
    
    // Allocating 2d array
    maze->arr = (char**)malloc((maze->xsize+2) * sizeof(char *));
    for (i = 0; i < maze->xsize+2; i++)
        maze->arr[i] = (char*)malloc((maze->ysize+2) * sizeof(char));
    
    // initialize the maze to empty
    for (i = 0; i < maze->xsize+2; i++)
        for (j = 0; j < maze->ysize+2; j++)
            maze->arr[i][j] = '.';
    
    // mark the borders of the maze with *'s
    for (i=0; i < maze->xsize+2; i++) {
       maze->arr[i][0] = '*';
       maze->arr[i][maze->ysize+1] = '*';
    }
    for (i=0; i < maze->ysize+2; i++) {
       maze->arr[0][i] = '*';
       maze->arr[maze->xsize+1][i] = '*';
    }
    
    // mark the starting and ending positions in the maze
    maze->arr[maze->xstart][maze->ystart] = 's';
    maze->arr[maze->xend][maze->yend] = 'e';
}

void getBlocks(Maze *maze, FILE **src) {
    int xpos, ypos;
    
    while (fscanf (*src, "%d %d", &xpos, &ypos) != EOF) {
        if (maze->arr[xpos][ypos] == '.' && xpos > 0 && xpos <= maze->xsize && ypos > 0 && ypos <= maze->ysize)
            maze->arr[xpos][ypos] = '*';
        else if (debugMode)
            printf("STANDARD ERROR in getBlocks (%d,%d)\n", xpos, ypos);
    }
}

void displayMaze(Maze *maze) {
    printf("Maze of the size %dx%d\n", maze->xsize, maze->ysize);
    printf("Start position: (%d,%d)\n", maze->xstart, maze->ystart);
    printf("End position: (%d,%d)\n", maze->xend, maze->yend);
    for (int i = 0; i < maze->xsize+2; i++) {
        for (int j = 0; j < maze->ysize+2; j++)
            printf ("%c", maze->arr[i][j]);
        printf("\n");
    }
}

void processInput(Maze *maze, const char *filename) {
    FILE *src;
    int *x = NULL, *y = NULL;
    
    /* Try to open the input file. */
    if ( ( src = fopen( filename, "r" )) == NULL ) {
      printf ( "Can't open input file: %s", filename );
      exit(-1);
    }
    
    /* read in the size of the maze */
    int i=0;
    while(maze->xsize <= 0 || maze->ysize <= 0) {
        if (i++ > 0 && debugMode)
            printf("STANDARD ERROR in arraySize (%d,%d)\n", maze->xsize, maze->ysize);
        
        if (fscanf (src, "%d %d", &(*maze).xsize, &(*maze).ysize) == EOF) {
            printf("STANDARD ERROR EOF\n");
            exit(-1);
        }
    }
    
    /* read in starting and ending positions in the maze */
    for (int i=1; i<3;) {
        if      (i==1) { x = &(*maze).xstart;     y = &(*maze).ystart; }
        else if (i==2) { x = &(*maze).xend;       y = &(*maze).yend;   }
        
        fscanf (src, "%d %d", x, y);
        if (*x > 0 && *x <= maze->xsize && *y > 0 && *y <= maze->ysize)
            i++;
        else if (debugMode)
            printf("STANDARD ERROR in %s position (%d,%d)\n", (i==1?"start":"end"), *x, *y);
    }
    
    initializeMaze(maze);
    getBlocks(maze, &src);
    
    fclose(src);
}

char** copyArr(char ***arr, int x, int y) {
    int i, j;
    
    char **arr2 = (char**)malloc(x * sizeof(char *));
    for (i = 0; i < x; i++) {
        arr2[i] = (char*)malloc(y * sizeof(char));
        for (j = 0; j < y; j++)
            arr2[i][j] = (*arr)[i][j];
    }
    
    return arr2;
}

void displayArr(char ***arr, int x, int y) {
    for(int i=0; i<x; i++) {
        for (int j=0; j<y; j++)
            printf("%c", (*arr)[i][j]);
        printf("\n");
    }
}

void DFS(Maze *maze) {
    Node *stack = initializeStack(maze->xstart, maze->ystart);
    int x = maze->xstart, y = maze->ystart, newX = 0, newY = 0, i;
    
    // Copy of array to work with
    char **arr = copyArr(&maze->arr, maze->xsize+2, maze->ysize+2);
    arr[x][y] = 'V';
    
    while (stack != NULL) {
        // Path was found
        if (stack->posX == maze->xend && stack->posY == maze->yend)
            break;
        
        // If current position has unvisited neighbour
        for (i=0; i<4; i++) {
            newX = x; newY = y;
            
            if      (i==0) { newY = y+1; }
            else if (i==1) { newX = x+1; }
            else if (i==2) { newY = y-1; }
            else if (i==3) { newX = x-1; }
            
            if (arr[newX][newY] != 'V' && arr[newX][newY] != '*') {
                x = newX; y = newY;
                push(&stack, x, y);
                arr[x][y] = 'V';
                break;
            }
            
            // If no available neighbour
            if (i==3)
                pop(&stack, &x, &y);
        }
    }
    
    if (debugMode) { // Display path array
        printf("\n");
        displayArr(&arr, maze->xsize+2, maze->ysize+2);
    }
    
    if (stack == NULL)
        printf("\nSolution was not found\n");
    else {
        printf("\nSolution was found\n");
        // Writing path on original maze array
        while(pop(&stack, &x, &y)) {
            maze->arr[x][y] = '>';
//            displayArr(&maze->arr, maze->xsize+2, maze->ysize+2);
        }
        displayArr(&maze->arr, maze->xsize+2, maze->ysize+2);
    }
    
    // Clearing
    for(i=0; i<maze->xsize+2; i++) {
        free(arr[i]);
        free(maze->arr[i]);
    }
    free(arr);
    free(maze->arr);
}

int main(int argc, const char * argv[]) {
    Maze maze;
    int filenameArgI;
    
    /* verify the proper number of command line arguments were given */
    if(argc < 2 || (argc==2 && strncmp(argv[1], "-d", 2)==0 )) {
       printf("Usage: %s <input file name> <-d>\n", argv[0]);
       exit(-1);
    }
    else {
        filenameArgI = strncmp(argv[1], "-d", 2)==0 && argc > 2 ? 2 : 1;
        debugMode = argc > 2 ? TRUE : FALSE;
    }
    
    processInput(&maze, argv[filenameArgI]);
    displayMaze(&maze);
    DFS(&maze);
    
    return 0; 
}
