/**
 * Compiled using GCC version 4.8.1
 * gcc -pthread -o add_list_1_forloop add_list_1_forloop.c
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *guassian_add (void *arguments);
void help_print (void);
void usage_print (void);
void validate_input (int start, int end);

/**
 * Thread data structure.
 */
struct ThreadData {
  int start;
  int stop;
  unsigned long long result;
};

/**
 * Main entry point.
 */
int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("\nThis program needs some arguments ...  \n Try add_list -h \n\n");
  }

  int option = 0;
  int start = -1;
  int end = 0;

  // Handle command line arguments.
  while ((option = getopt(argc, argv, "hs:e:")) != -1) {
    switch (option) { 
       case 'h':
        help_print();
        break;

       case 's':
        start = atoi(optarg);
        break;

       case 'e':
        end = atoi(optarg);
        break;

       default:
        usage_print();
        exit(EXIT_FAILURE);
    }
  }

  // Validate our input.
  validate_input(start, end);

  // Create an array of thread data.
  struct ThreadData data[1];
  data[0].start = start;
  data[0].stop = end;

  // Spawn a single thread.
  pthread_t threadIds[1];
  if (pthread_create(&threadIds[0], NULL, &guassian_add, (void *)&data[0]) != 0) {
    printf("Could not create thread.");
    return -1;
  }

  // Wait for the thread to finish.
  pthread_join(threadIds[0], NULL);

  // Inform the user of the results and of the short cut.
  printf("Sum: %d\n", data[0].result);
  printf("\nA shortened version of the result: \"(number of lines) * (initial sum) = total sum\"\n"); 
  printf(
    "%d * %d = %llu \n\n", 
    ((end - start) / 2) + 1, 
    (end + start), 
    (((end - start) / 2) + 1)  * (end + start));

  return 0;
}

/**
 * Guassian addition.
 */
void *guassian_add(void *arguments) {
  struct ThreadData *data = (struct ThreadData *)arguments;
  int a = data->start;
  int b = data->stop;
  int iterations = ((b - a) / 2) + 1;
  int i = 0;

  data->result = 0;

  for (i = 0; i < iterations; i++) {
    int sum = --b + ++a;
    data->result = data->result + sum;
  }
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
  printf("Usage:\n \tadd_list -h\n \tadd_list -s num -e num\n\n");
  printf("\texample ->  add_list -s 1 -e 100\n\n");
}

/**
 * Validate user input.
 */
void validate_input(int start, int end) {
  if (end <= start || end <= 1) {
    usage_print();
    exit(EXIT_FAILURE);
  }

  if ((start + (end - 1)) % 2 != 0) {
    printf("\nThe sum of your list is not an even numbered set\n");
    printf("Example:\n 1 to 100\n 11 to 40\n 200 to 399 \n\n");
    exit(EXIT_FAILURE);
  }
}