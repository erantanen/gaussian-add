/**
 * Compiled using GCC version 4.8.1
 * Linux: gcc -pthread -o gaussian-add gaussian-add.c gauss_print.h
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "gauss_print.h"

void *gaussian_add (void *arguments);
int find_number_of_threads (int start, int end);
void validate_input (int start, int end);

const int CHUNK_SIZE = 1000;
const int MAXIMUM_THREADS = 1000;

/**
 * Thread data structure.
 */
typedef struct {
  int start;
  int stop;
  unsigned long long result;
} ThreadData;

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
  while ((option = getopt(argc, argv, "hvs:e:")) != -1) {
    switch (option) {
      case 's':
        start = atoi(optarg);
        break;

      case 'e':
        end = atoi(optarg);
        break;

      case 'v':
        version_print();
        exit(EXIT_FAILURE);

       case 'h':
        help_print();
        exit(EXIT_FAILURE);

       default:
        usage_print();
        exit(EXIT_FAILURE);
    }
  }

  // Validate our input.
  validate_input(start, end);

  // Create an arrays for threading.
  int threadCount = find_number_of_threads(start, end);
  ThreadData data[threadCount];
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

    if (pthread_create(&threadIds[i], NULL, &gaussian_add, (void *)&data[i]) != 0) {
      printf("Could not create thread #%d.", i);
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
 * Gaussian addition.
 */
void *gaussian_add(void *arguments) {
  ThreadData *data = (ThreadData *)arguments;
  int a = data->start;
  int b = data->stop;
  int iterations = ((b - a) / 2) + 1;
  int i = 0;

  data->result = 0;

  for (i = 0; i < iterations; i++) {
    int sum = --b + ++a;
    data->result += sum;
  }

  return 0;
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