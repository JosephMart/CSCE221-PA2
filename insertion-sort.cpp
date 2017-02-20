//============================================================================
// Name        : insertion-sort.cpp
// Author      : Nnaedoziem Aririele
// Date        : 02/17/2017
// Copyright   : 2017
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"

void
InsertionSort::sort(int A[], int size)				// main entry point
{
  /* Complete this function with the implementation of insertion sort algorithm
  Record number of comparisons in variable num_cmps of class Sort
  */

  int sizea = size;
  for (int i = 0; i < sizea - 1; i++) {
  	int min = i;
	for (int j = i+1; j < sizea; j++) {
		if (A[min] > A[j]) {
			min = j;
		}
	}
	if (min != i) {
		int temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
 	}
}
