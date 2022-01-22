#include "psort.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>

void SequentialSort(uint32_t *data, uint32_t n) {
  if (n == 1)
    return;
  uint32_t nl = n / 2, nr = (n + 1) / 2;
  uint32_t left[nl], right[nr];
  memcpy(left, data, nl * sizeof(uint32_t));
  memcpy(right, data + nl, nr * sizeof(uint32_t));
  SequentialSort(left, nl);
  SequentialSort(right, nr);
  uint32_t l = 0, r = 0, i = 0;
  while (l < nl && r < nr) {
    if (left[l] <= right[r])
      data[i++] = left[l++];
    else
      data[i++] = right[r++];
  }
  if (l < nl)
    memcpy(data + i, left + l, (n - i) * sizeof(uint32_t));
  if (r < nr)
    memcpy(data + i, right + r, (n - i) * sizeof(uint32_t));
}

void ParallelSort(uint32_t *data, uint32_t n, int p) {
  // Entry point to your sorting implementation.
  // Sorted array should be present at location pointed to by data.
}
