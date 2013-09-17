#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*****************************************************/
// Gauss list addition with 1 for  loop
//
// This is some very basic code if it breaks
// your machine ... 
//
// Have fun with it. 
//
//
// Created: 11 Sep 2013
// By: Ed Rantanen
//
//

  void help_print() {
        printf("\nThis is simple program to add up a list of numbers\n");
        printf("\"From the story of Gauss\'s childhood\"\n");
        printf("\nExample: 1 to 100 added \n 1+100=101\n 2+99=101 \n 3+98=101\n ...\n 50+51=101\n");
        printf("\nTo work the sum of the total list needs to be even\n\n");
   }

  void usage_print(){
        printf("Usage:\n \tadd_list -h\n \tadd_list -s num -e num\n\n");
        printf("\texample ->  add_list -s 1 -e 100\n\n");
     }



 int main(int argc, char *argv[]) {
      // initial set up

  if(argc == 1) {
       printf("\nThis program needs some arguments ...  \n Try add_list -h \n\n");
    }

 

     int option = 0;
     int add_start = -1, add_end = 0;

     while((option=getopt(argc, argv, "hs:e:")) != -1) {
   
          switch (option) { 
                 case 'h' : help_print(); 
                     break;
                 case 's': add_start = atoi(optarg);
                     break;
                 case 'e': add_end = atoi(optarg);
                     break; 
                 default: usage_print();
                      exit(EXIT_FAILURE); 
             } //swtich
      } //while

   /***********************************************************/

      // number checking
 
   if(add_end <= add_start || add_end <= 1){
     usage_print();
     exit(EXIT_FAILURE);
    }

   if((add_start + (add_end-1)) % 2 != 0){
       printf("\nThe sum of your list is not an even numbered set\n");
       printf("Example:\n 1 to 100\n 11 to 40\n 200 to 399 \n\n");
       exit(EXIT_FAILURE);
   }


   /***********************************************************/

    int incr_element=0;
    int incr_list=0;
    int sum_end=0;
    int sum_start=0;
    unsigned long long  result =0;

    for(incr_list = add_start; incr_list <= add_end; incr_list+=2){

       sum_end = add_end - incr_element;
       sum_start = add_start + incr_element;
       result = result + (sum_end + sum_start);

       printf("%d + %d = %d  %llu \n", sum_end, sum_start,  (sum_end + sum_start), result);
      // printf("%d \n", incr_element);
       incr_element++;
     }

       printf("\n A shortened version of the result\n");
       printf(" (number of lines) * (initial sum) = total sum\n"); 
       printf(" %d * %d = %llu \n\n", incr_element, (sum_end + sum_start), incr_element  * (sum_end + sum_start));
 
 return(0);

}

