//============================================================================
// Name        : radix-sort.cpp
// Author      : Gabriel Stella
// Date        : 2 Feb 2017
// Copyright   : me only
// Description : Implementation of radix sort in C++
//============================================================================

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

	int numbits = sizeof(int) * CHAR_BIT;
	int sectionSize = 8;

	int mask = 0;
	int possibilities = 1;
	for(int i = 0; i < sectionSize; i++) {
		mask = mask << 1;
		mask++;
		possibilities *= 2;
	}

	int rem = numbits % sectionSize;
	if(rem != 0) {
		throw std::runtime_error{"Invalid integral size. Don't you use bytes?"};
	}
	int sections = numbits / sectionSize;

	int c[possibilities] = {};
	int b[size];
	
	for(int section = 0; section < sections; section++) {

		for(int i = 0; i < possibilities; i++) {
			c[i] = 0;
		}

		for(int i = 0; i < size; i++) {
			int val = A[i];
			val = (val >> (section * sectionSize)) & mask;
			c[val]++;
		}

		for(int i = 1; i < possibilities; i++) {
			c[i] = c[i] + c[i - 1];
		}

		for(int i = size - 1; i >= 0; i--) {
			int val = A[i];
			int partVal = (val >> (section * sectionSize)) & mask;
			int index = c[partVal];
			c[partVal]--;
			b[index - 1] = val;
		}

		for(int i = 0; i < size; i++) {
			A[i] = b[i];
		}
	}
}
