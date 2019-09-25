//
//  main.c
//  CS 211 Project 1
//
//  Created by Viktor Kirillov on 9/4/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h> // free

// Function prototypes
void growArray(int*);
void makeArrayCopy(int*, int**, int);
void mergeSort(int*, int, int);
void merge(int*, int, int, int);
int TwoSumFunction(int*, int, int, int*, int*);

// Global variables
int arrSize = 0;
int arrCapacity = 100;

int main (int argc, char** argv) {
    int *darr, val, res, index1, index2, i;
    darr = (int *) malloc( arrCapacity * sizeof(int) );
    
    printf ("Enter in a list of numbers ito be stored in a dynamic array.\n");
    printf ("End the list with the terminal value of -999\n");
    
    scanf ("%d", &val);
    while (val != -999) {
        if (arrSize > arrCapacity)
            growArray(darr);
        
        darr[arrSize] = val;
        arrSize += 1;
        
        scanf("%d", &val);
    }
    
    // Making copy of array
    int *newArr = NULL;
    makeArrayCopy(darr, &newArr, arrSize);
    
    // Sorting
    mergeSort(newArr, 0, arrSize-1);
    
    printf ("Enter in a list of numbers to use for searching.  \n");
    printf ("End the list with a terminal value of -999\n");
    scanf ("%d", &val);
    
    printf("\nList: ");
    for(i=0; i<arrSize; i++)
        printf("%d ", darr[i]);
    printf("\nTarget: ");
    
    while (val != -999) {
        // call function to perform target sum operation
        res = TwoSumFunction(newArr, arrSize, val, &index1, &index2);
        
        // print out info about the target sum results
        res > 0 ? printf("%d Yes! ", val) : printf("%d No! ", val);
        
        // get next value
        scanf("%d", &val);
    }
    
    printf ("\nGood bye\n");
    return 0;
}

void growArray(int *arr) {
    int *temp = arr;
    arr = (int *) malloc ( arrCapacity * 2 * sizeof(int) );
    int i;
    for (i = 0 ; i < arrSize; i++)
        arr[i] = temp[i];
    free(temp);
    arrCapacity = arrCapacity * 2;
}

void makeArrayCopy(int *fromArray, int **toArray, int size) {
    *toArray = (int *) malloc( size * sizeof(int) );
    int i;
    for (i=0; i<size; i++)
        (*toArray)[i] = fromArray[i];
}

void mergeSort(int arr[], int lIndex, int rIndex) {
    if (lIndex < rIndex) {
        int mIndex = lIndex+(rIndex-lIndex)/2;
        
        // Sort first and second halves
        mergeSort(arr, lIndex, mIndex);
        mergeSort(arr, mIndex+1, rIndex);
        
        merge(arr, lIndex, mIndex, rIndex);
    }
}

void merge(int *arr, int lIndex, int mIndex, int rIndex) {
    int i, j, k;
    int n1 = mIndex - lIndex + 1;
    int n2 = rIndex - mIndex;
    
    // Temporary arrays
    int L[n1], R[n2];
    
    // Copying data into temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[lIndex + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mIndex + 1+ j];
    
    // Merging temp arrays back
    i = 0;
    j = 0;
    k = lIndex;
    while (i < n1 && j < n2)
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    
    // Copying the remaining elements
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

int TwoSumFunction(int *arr, int size, int target, int *index1, int *index2) {
    int a,b;
    for (*index1=0; (*index1)<size; (*index1)++) {
        a = arr[*index1];
        
        if (a >= target)
            return -1;
        
        for (*index2=(*index1)+1; (*index2)<size; (*index2)++) {
            b = arr[*index2];
            
            if (a + b == target)
                return 1;
            else if (a + b > target)
                return -1;
        }
    }
    
    return -1;
}
