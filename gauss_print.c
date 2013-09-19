#include <stdio.h>
#include "gauss_print.h"

/**
 * Output version information.
 */
void version_print() {
  printf("\n gaussian-add v0000.1 18 Sep 2013\n\n");
}

/**
 * Output helpful information for the uninformed.
 */
void help_print() {
  printf("\nThis is simple program to add up a list of numbers\n");
  printf("\"From the story of Gauss\'s childhood\"\n");
  printf("\nExample: 1 to 100 added \n 1+100=101\n 2+99=101 \n 3+98=101\n ...\n 50+51=101\n");
  printf("\nTo work the sum of the total list needs to be even\n\n");
}

/**
 * Output usage information.
 */
void usage_print() {
  printf("Usage:\n \tgaussian-add -h\n \tgaussian-add -s num -e num\n\n");
  printf("\tExample: gaussian-add -s 1 -e 100\n\n");
}

/**
 * Output a summary of the findings.
 *
 * @param numberOfThreads The total number of threads used in the processing.
 * @param sum The sum of all the threaded results.
 * @param start The number to start our computations.
 * @param end The number to end our computations.
 */
void summary_print(int numberOfThreads, unsigned long long sum, int start, int end) {
	printf("Threads: %d\n", numberOfThreads);
	printf("Sum: %llu\n", sum);
	printf("\nA shortened version of the result: \"(number of lines) * (initial sum) = total sum\"\n"); 
	printf(
		"%d * %d = %llu\n", 
		((end - start) / 2) + 1, 
		(end + start), 
		(unsigned long long)(((end - start) / 2) + 1)  * (end + start));
}