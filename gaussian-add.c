/**
 * Compiled using GCC version 4.8.1
 * Linux: gcc -pthread -o gaussian-add gaussian-add.c gauss_print.h gauss_print.c
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "gauss_print.h"
#include "gaussian_threads.h"

void validate_input (int start, int end);

/**
 * Main entry point.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return The exit code.
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
  summary_print(threadCount, sum, start, end);

  return 0;
}

/**
 * Validate user input.
 *
 * @param start The number to start our computations.
 * @param end The number to end our computations.
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