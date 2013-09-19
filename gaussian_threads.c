#include "gaussian_threads.h"

/**
 * Gaussian addition.
 * 
 * @param arguments Thread data arguments.
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
 *
 * @param start The number to start our computations.
 * @param end The number to end our computations.
 * @return The number of threads to produce.
 */
int find_number_of_threads(int start, int end) {
  int threads = (end - start) / CHUNK_SIZE;

  if (CHUNK_SIZE * threads < end - start) {
    threads++;
  }

  return threads > MAXIMUM_THREADS ? MAXIMUM_THREADS : threads;
}