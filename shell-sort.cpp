//============================================================================
// Name        : shell-sort.cpp
// Author      : Nnaedoziem Aririele
// Date        : 02/17/2017
// Copyright   : 2017
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

inline int next_gap(int gap)
{
	if (gap == 2) return 1;
	else return (int) (gap/2.2);

}

void
ShellSort::sort(int A[], int size)
{
  /* Complete this function with the implementation of shell sort algorithm
  Record number of comparisons in variable num_cmps of class Sort
  */
  int gap = size/2;
  for (; gap > 0; gap = next_gap(gap)){

	for (int i = gap; i<size ; i++){

		int tmp = A[i];
		int j = i;
		while (j >= gap && tmp < A[j-gap]){
			num_cmps++;
			A[j] = A[j-gap];
			j -= gap;
		}
		num_cmps++;
		A[j] = tmp;

	}

  }

}
