//============================================================================
// Name        : sort.cpp
// Author      : TA's
// Date        :
// Copyright   : 
// Description : Read an integer sequence and display the sorted sequence
/*
 *     Usage: ./sort [-a ALGORITHM] [-f INPUTFILE] [-o OUTPUTFILE] [-h] 
 *     [-d] [-p] [-t] [-c] 
 *     Example: ./sort -a S -f input.txt -o output.txt -t -c -d
 *              ./sort -h
 *     Options: 
 *       -a ALGORITHM    Use ALGORITHM to sort. 
 *                       ALGORITHM is a single character representing an algorithm: 
 *                         S   (selection sort) 
 *                         B   (bubble sort) 
 *                         I   (insertion sort) 
 *                         H   (shell sort)
 *                         R   (radix sort) 
 *       -f INPUTFILE    Obtain integers from INPUTFILE instead of STDIN 
 *       -o OUTPUTFILE   Place output message into OUTPUTFILE instead of STDOUT 
 *       -h              Display this help and exit 
 *       -d              Display input: unsorted integer sequence
 *       -p              Display output: sorted integer sequence 
 *       -t              Display running time of the chosen algorithm in milliseconds 
 *       -c              Display number of element comparisons (excluding radix sort)
 *       -n              Specify the number of times to run the sorter
 */
//============================================================================

#include <iostream>
#include <iterator>
#include <ctime>
#include <cstdio>
#include "option.h"
#include "sort.h"
#include <limits>

using namespace std;

/* read input sequence from STDIN */
int readInput(int A[], int& size) {
   /* read integers to sort */
   for (int i = 0; i < size; i++)
      if (!(cin >> A[i])) {
         cerr << "sort: input data error" << endl;
         return 1; //exit abnormally
      }  
   
   return 0; //exit normally
}

/* display elements of array A seperated by new lines */
void printArray(const int A[], int size) {
   copy(A, A+size, ostream_iterator<int>(cout,"\n"));// call standard function
                                                     // "copy" to display
                                                     // the array
   cout << endl;  
}

// returns true if sorted as increasing sequence
// returns false otherwise
bool Sort::testIfSorted(int A[], int size)
{
   for (int i = 1; i < size; ++i)
      if (A[i-1] > A[i]) return false;
   return true;
}

int main(int argc, char** argv)
{

   Option op;
   bool radixsortQ = false;
   
   /* initialize program options */
   try {
      op.init(argc,argv);
   } catch (Option::InvalidArgument& ex) {
      cerr << ex.what() << endl;
      return 1;
   }
   
   /* show help message and exit */
   if (op.showHelp()) {
      op.printUsage();
      const unsigned int max_int = std::numeric_limits<int>::max();
      cout << "NOTE: The Radix Sort sorts " << -(int)((max_int+1)/2) << " to " << (max_int+1)/2-1 << endl;
      return 0; //exit normally
   }
   
   const char *input_file, *output_file;
   
   /* If provided input file, reopen standard input onto that file
      so that we only need to deal with standard input. */
   if ((input_file=op.getInputFile()) &&
       freopen(input_file, "r", stdin) == 0) {
      cerr << "sort: " << input_file << ": no such file" << endl;
      return 1;
   }
   
   /* If provided output file, reopen standard output onto that file
      so that we only need to deal with standard output. */  
   if ((output_file=op.getOutputFile()) &&
       freopen(output_file, "w", stdout) == 0) {
      cerr << "sort: " << output_file << ": No such file" << endl;
      return 1; //exit abnormally
   }
  
   /* read number of integers */
   int size; //number of integers  
   if (!(cin >> size)) return 1; //exit abnormally
  
   /* create an sorting object with appropriate algorithm */
   Sort* s;
   switch(op.getAlg()) 
      {
      case 'S':
         s=new SelectionSort();
         break;
      case 'I':
         s=new InsertionSort();
         break;
      case 'B':
         s=new BubbleSort();
         break;
      case 'H':
         s=new ShellSort();
         break;
      case 'R':
         s=new RadixSort();
         radixsortQ = true;
         break;
      }

   int* A=new int[size]; //stores integers
   int* B = new int[size];

   /* read input integers */
   if (readInput(A,size)) //call global function
      return 1; //exit abnormally

   ////begin running

   clock_t min = -1;
   clock_t max = 0;
   clock_t total = 0;

   int numRunTimes = op.getRunTimes();
   if(numRunTimes != 1) {
      cout << "Running " << numRunTimes << " times" << endl;
   }

   for(int loopNumber = 0; loopNumber < numRunTimes; loopNumber++) {

      s->resetNumCmps();

      for(int index = 0; index < size; index++) {
         B[index] = A[index]; //copy unsorted array
      }

      /* show unsorted input sequence */
      if (op.showInput()) {
         cout << "Unsorted sequence:" << endl;
         printArray(B,size); //call global function to display the array
      }

      /* begin timing the chosen algorithm using time.h library*/
      clock_t start = clock();
   
      /* call sorting function to sort */
      s->sort(B,size);  
      
      /* end timing */
      clock_t finish = clock();

      //timing stuff
      clock_t delta = finish - start;
      if(min < 0 || delta < min) min = delta;
      if(delta > max) max = delta;
      total += delta;
      
      /* output sorted sequence */
      if (op.showOutput()) {
         cout << "Sorted sequence:" << endl;
         printArray(B,size); //call global function to display the array
      }

      /* show number of comparisons in the algorithm */
      if (op.showNumCmps()) {
         if (radixsortQ) {
            cout << "No comparisons for radix sort"
                 << endl;
         } else {
            cout << "# Comparisons: "
                 << s->getNumCmps() << endl;
         }
      }

      if (!s->testIfSorted(B, size)) {
         cerr << "Warning: The sorted sequence IS NOT sorted!\n"
              << endl;
      }

   }

   ////end running
   
   /* show running time of the algorithm to sort input data */
   if (op.showTime()) {
      cout << "Running time: "
           << (double)(total)*1000/CLOCKS_PER_SEC
           << " ms" << endl;
      if(numRunTimes > 1) {
         cout << "Minimum time: "
              << (double)(min)*1000/CLOCKS_PER_SEC
              << " ms" << endl;
         cout << "Maximum time: "
              << (double)(max)*1000/CLOCKS_PER_SEC
              << " ms" << endl;
         cout << "Average time: "
              << (((double)(total))/numRunTimes)*1000/CLOCKS_PER_SEC
              << " ms" << endl;
      }
   }

   // it may be useful for Windows
   // char ch;
   // cin >> ch;
   return 0;
}
