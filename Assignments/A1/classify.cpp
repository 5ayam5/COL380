#include "classify.h"
#include <omp.h>

Data classify(
    Data &D, const Ranges &R,
    unsigned int numt) { // Classify each item in D into intervals (given by R).
                         // Finally, produce in D2 data sorted by interval
  assert(numt < MAXTHREADS);
  Counter counts[R.num()]; // I need on counter per interval. Each counter can
                           // keep pre-thread subcount.
  int len = D.ndata / numt;
#pragma omp parallel num_threads(numt)
  {
    int tid = omp_get_thread_num(); // I am thread number tid
    int r = (tid == numt - 1 ? D.ndata : (tid + 1) * len);
    for (int i = tid * len; i < r;
         i++) { // Threads together share-loop through all of Data
      int v = D.data[i].value = R.range(
          D.data[i].key); // For each data, find the interval of data's key,
                          // and store the interval id in value. D is changed.
      counts[v].increase(tid); // Found one key in interval v
    }
  }

  // Accumulate all sub-counts (in each interval's counter) into rangecount
  unsigned int *rangecount = new unsigned int[R.num()]();
  for (int r = 0; r < R.num(); r++) { // For all intervals
    for (int t = 0; t < numt; t++)    // For all threads
      rangecount[r] += counts[r].get(t);
  }

  // indices array for almost equal division
  unsigned int *indices = new unsigned int[numt + 1]();
  unsigned int count = 0, idx = 0;

  // Compute prefx sum on rangecount.
  for (int i = 1; i < R.num(); i++) {
    rangecount[i] += rangecount[i - 1];
    if (rangecount[i] - count >= len)
      indices[++idx] = i - 1, count = rangecount[i - 1];
  }
  indices[numt] = R.num();

  // Now rangecount[i] has the number of elements in intervals before the ith
  // interval.

  Data D2 = Data(D.ndata); // Make a copy

#pragma omp parallel num_threads(numt)
  {
    int tid = omp_get_thread_num();
    for (int r = indices[tid]; r < indices[tid + 1];
         r++) { // Thread together share-loop through the intervals
      int rcount = (r == 0 ? 0 : rangecount[r - 1]);
      for (int d = 0; d < D.ndata;
           d++) // For each interval, thread loops through all of data and
        if (D.data[d].value == r) // If the data item is in this interval
          D2.data[rcount++] =
              D.data[d]; // Copy it to the appropriate place in D2.
    }
  }

  return D2;
}
