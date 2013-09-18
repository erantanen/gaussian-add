/**
 * Compiled using GCC version 4.8.1
 * Linux: gcc -pthread -o add_list_1_forloop add_list_1_forloop.c
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *guassian_add (void *arguments);
int find_number_of_threads (int start, int end);
void help_print (void);
void usage_print (void);
void validate_input (int start, int end);

const int CHUNK_SIZE = 1000;
const int MAXIMUM_THREADS = 1000;

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

  // Create an arrays for threading.
  int threadCount = find_number_of_threads(start, end);
  struct ThreadData data[threadCount];
  pthread_t threadIds[threadCount];
  int i = 0;

  // Spawn threads.
  for (i = 0; i < threadCount; i++) {
    data[i].start = start + (i * CHUNK_SIZE);
    data[i].stop = data[i].start + CHUNK_SIZE - 1;
    data[i].result = 0;

    // If we've exceeded the end amount or reached our maximum threads then set the stop to the actual end.
    if ((data[i].stop > end) || (data[i].stop < end && i + 1 == threadCount)) {
      data[i].stop = end;
    }

    //// NOTE: Uncomment to view what ranges each thread is responsible for.
    //printf("%d: %d to %d\n", i + 1, data[i].start, data[i].stop);

    if (pthread_create(&threadIds[i], NULL, &guassian_add, (void *)&data[i]) != 0) {
      printf("Could not create thread #%d.", i);
      return -1;
    }
  }

  // Wait for the threads to finish.
  unsigned long long sum = 0;
  for (i = 0; i < threadCount; i++) {
    if (pthread_join(threadIds[i], NULL) != 0) {
      printf("Could not join thread #%d\n", i + 1);
    }

    sum += data[i].result;
  }

  // Inform the user of the results and of the short cut.
  printf("Threads: %d\n", threadCount);
  printf("Sum: %llu\n", sum);
  printf("\nA shortened version of the result: \"(number of lines) * (initial sum) = total sum\"\n"); 
  printf(
    "%d * %d = %llu\n\n", 
    ((end - start) / 2) + 1, 
    (end + start), 
    (unsigned long long)(((end - start) / 2) + 1)  * (end + start));

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
    data->result += sum;
  }
}

/**
 * Find the number of threads to be used.
 */
int find_number_of_threads(int start, int end) {
  int threads = (end - start) / CHUNK_SIZE;

  if (CHUNK_SIZE * threads < end - start) {
    threads++;
  }

  return threads > MAXIMUM_THREADS ? MAXIMUM_THREADS : threads;
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