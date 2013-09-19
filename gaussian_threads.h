#ifndef GAUSS_THREADS_H
#define GAUSS_THREADS_H

// Define some configurable variables used for threading thresholds.
#define CHUNK_SIZE 1000
#define MAXIMUM_THREADS 1000

// Method prototypes.
void *gaussian_add (void *arguments);
int find_number_of_threads (int start, int end);

// Thread data structure.
typedef struct _ThreadData {
  int start;
  int stop;
  unsigned long long result;
} ThreadData;

#endif