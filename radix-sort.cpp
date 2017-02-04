//============================================================================
// Name        : radix-sort.cpp
// Author      : Gabriel Stella
// Date        : 2 Feb 2017
// Copyright   : me only
// Description : Implementation of radix sort in C++
//============================================================================

//sources used:
//
//https://en.wikipedia.org/wiki/Sizeof
//https://en.wikipedia.org/wiki/C_data_types#limits.h
//http://www.cplusplus.com/reference/climits/

#include "sort.h"
#include <iostream>
#include <climits>
#include <stdexcept>

void RadixSort::sort(int A[], int size)
{
	//LSD radix sort

	//customizable - this is the number of bits per bin (used for the underlying counting sort)
	int sectionSize = 8;
	//used to determine how many bins there will be
	int numbits = sizeof(int) * CHAR_BIT;
	//the number of bins
	int sections = numbits / sectionSize;

	//all bits 1, up to the section size
	int mask = 0;
	//the number of values that can be taken by a number <sectionSize> bits long
	int possibilities = 1;

	for(int i = 0; i < sectionSize; i++) {
		//shift the mask then set the LSB to 1
		mask = mask << 1;
		mask++;

		//twice the number of possibilities per bit
		possibilities *= 2;
	}

	//this is just for testing - the bins are all equal size, don't want any bits spilling out
	int rem = numbits % sectionSize;
	if(rem != 0) {
		throw std::runtime_error{"Invalid integral size. Don't you use bytes?"};
	}

	//temporary array, storing the number of elements in each bin
	int c[possibilities];
	//intermediary array for storage between cycles
	int b[size];

	
	for(int section = 0; section < sections; section++) {

		//initialize all of c 0; will count up later
		for(int i = 0; i < possibilities; i++) {
			c[i] = 0;
		}

		//count up the number of items in each bin, store that in c
		for(int i = 0; i < size; i++) {
			int val = A[i];

			//bins are selected based on the current cycle number;
			//need to get rid of extra information
			val = (val >> (section * sectionSize)) & mask;

			c[val]++;
		}

		//c now represents the number of elements "less than or equal to i" in A
		//to be used as position in b (then b -> A)
		for(int i = 1; i < possibilities; i++) {
			c[i] = c[i] + c[i - 1];
		}

		//elements are copied backwards to preserve ordering
		//without a stable counting sort, radix sort does not work
		for(int i = size - 1; i >= 0; i--) {
			int val = A[i];

			//get the index into b, then decrement c (so the next item goes to index - 1, and so on)
			int partVal = (val >> (section * sectionSize)) & mask;
			int index = c[partVal];
			c[partVal]--;

			//go into the correct index in b (temp storage of actual values)
			b[index - 1] = val;
		}

		//copy data from the temporary array b back into A
		for(int i = 0; i < size; i++) {
			A[i] = b[i];
		}
	}
}
