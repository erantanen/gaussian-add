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