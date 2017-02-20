//============================================================================
// Name        : selection-sort.cpp
// Author      : Joseph Martinsen
// Date        : 4 Febuary 2017
// Copyright   : JMM 2017
// Description : Implementation of selection sort in C++
//============================================================================

// sources used:
// https://www.youtube.com/watch?v=f8hXR_Hvybo

#include "sort.h"
#include <iostream>

void SelectionSort::sort(int A[], int size)				// main entry point
{
    /* Complete this function with the implementation of selection sort algorithm
    Record number of comparisons in variable num_cmps of class Sort
    */
    for (int k = 0; (num_cmps++, k < size-1); k++) {
    	int index = k;
		for (int i = k+1; (num_cmps++, i < size); i++) {
			if (A[i] < A[index], num_cmps++) {
				index = i;
			}
		int tmp = A[k];
		A[k] = A[index];
		A[index] = tmp;
		}
    }
}
