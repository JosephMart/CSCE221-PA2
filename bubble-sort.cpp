//============================================================================
// Name        : bubble-sort.cpp
// Author      : Joseph Martinsen
// Date        : 4 Febuary
// Copyright   : JMM 2017
// Description : Implementation of bubble sort in C++
//============================================================================

// Sources Used
// https://www.youtube.com/watch?v=8Kp-8OGwphY
#include "sort.h"

void
BubbleSort::sort(int A[], int size)			// main entry point
{
    /* Complete this function with the implementation of bubble sort algorithm
     Record number of comparisons in variable num_cmps of class Sort
    */
    // Temp value used during swaping
    int temp = 0;
    this->num_cmps = 0;

    // Begin iterating from 0th element to last element
    for (int i = 0; i < size; ++i)
    {
        // Iterate from 0 to lasat element that has been sorted
        // The last element sorted will be the max of that pass through
        for (int j = 0; j < size - i - 1; ++j)
        {
            // Compare the current element and the next element
            // If the current is bigger, swap the two elements
            num_cmps++;
            if (A[j] > A[j + 1])
            {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}
