#include <stdio.h>
#include "guass_print.h"




 void version_print() {
        printf("\n guassian-add v0000.1 18 Sep 2013\n\n");
   }


 void help_print() {
        printf("\nThis is simple program to add up a list of numbers\n");
        printf("\"From the story of Gauss\'s childhood\"\n");
        printf("\nExample: 1 to 100 added \n 1+100=101\n 2+99=101 \n 3+98=101\n ...\n 50+51=101\n");
        printf("\nTo work the sum of the total list needs to be even\n\n");
   }

  void usage_print(){
        printf("Usage:\n \tguassian-add -h\n \tguassian-add -v\n \tguassian-add -s num -e num\n\n");
        printf("\texample ->  guassian-add -s 1 -e 100\n\n");
     }

