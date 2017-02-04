//============================================================================
// Name        : selection-sort.cpp
// Author      : Joseph Martinsen
// Date        :
// Copyright   :
// Description : Implementation of selection sort in C++
//============================================================================

// sources used:
// https://www.youtube.com/watch?v=f8hXR_Hvybo

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
    /* Complete this function with the implementation of selection sort algorithm
    Record number of comparisons in variable num_cmps of class Sort
    */
    // Used for tracking index of current smallest element
    int minPos = 0;
    // Used during swaping
    int temp = 0;
    this->num_cmps = 0;

    for (int i = 0; i < size-1; i++)
    {
        // Set current index as min
        minPos = i;

        // Iterate from i to n looking for the smallest element
        for (int j = i + 1; j < size; j++)
        {
            // Check if a smaller value has been found
            num_cmps++;
            if (A[j] < A[minPos])
            {
                minPos = j;
            }
        }

        this->num_cmps++;
        // Check if a smaller value to swap has been found
        if (i != minPos)
        {
            temp = A[i];
            A[i] = A[minPos];
            A[minPos] = temp;
        }
    }
}
