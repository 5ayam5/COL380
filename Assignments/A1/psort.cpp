#include "psort.h"
#include <cstdint>
#include <iostream>
#include <omp.h>
#include <string.h>

void SequentialSort(uint32_t *data, uint32_t n) {
  if (n <= 1)
    return;
  uint32_t nl = n / 2, nr = ((uint64_t)n + 1) / 2;
  uint32_t *left = new uint32_t[nl], *right = new uint32_t[nr];
  memcpy(left, data, nl * sizeof(uint32_t));
  memcpy(right, data + nl, nr * sizeof(uint32_t));
  SequentialSort(left, nl);
  SequentialSort(right, nr);
  uint64_t l = 0, r = 0, i = 0;
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
  delete[] left;
  delete[] right;
}

uint32_t binary_search(uint32_t *data, uint32_t p, uint32_t val) {
  uint32_t l = 0, r = p;
  while (l < r) {
    uint32_t mid = l + ((r - l) >> 1);
    if (val <= data[(mid + 1) * p])
      r = mid;
    else
      l = mid + 1;
  }
  return r;
}

void print_arr(uint32_t *data, uint32_t n, uint32_t padding = 1) {
  for (uint64_t j = 0; j < n; j++)
    std::cout << data[j * padding] << ' ';
  std::cout << '\n';
}

void ParallelSort(uint32_t *data, uint32_t n, int p) {
  if (n / p < p) {
    SequentialSort(data, n);
    return;
  }

  // Steps 1, 2, 3
  uint64_t sz = n / p;
  uint32_t r[p * p + 1], offset = (n % p) * (sz + 1);

  for (uint32_t j = 0; j < n % p; j++) {
    uint32_t off1 = p * j, off2 = j * (sz + 1);
    for (uint32_t idx = 0; idx < p; idx++)
      r[off1 + idx] = data[off2 + idx];
  }

  for (uint32_t j = n % p; j < p; j++) {
    uint32_t off1 = p * j, off2 = offset + (j - n % p) * sz;
    for (uint32_t idx = 0; idx < p; idx++)
      r[off1 + idx] = data[off2 + idx];
  }

  SequentialSort(r, p * p);
  r[p * p] = UINT32_MAX;

  // Step 4
  sz = ((uint64_t)n + p - 1) / p;
  uint32_t num_t = omp_get_num_threads(), b_size_t[num_t][p],
           *b_id = new uint32_t[n];
  for (uint32_t j = 0; j < num_t; j++)
    memset(b_size_t[j], 0, p * sizeof(uint32_t));

  for (uint32_t t = 0; t < p; t++) {
#pragma omp task shared(p, r, data, b_id, b_size_t)
    {
      uint32_t start = t * sz, end = t == p - 1 ? n : (t + 1) * sz,
               tid = omp_get_thread_num();
      for (uint64_t j = start; j < end; j++) {
        b_id[j] = binary_search(r, p, data[j]);
        b_size_t[tid][b_id[j]]++;
      }
    }
  }
#pragma omp taskwait

  uint32_t b_size[p + 1];
  b_size[0] = 0;
  for (uint32_t j = 1; j <= p; j++) {
    b_size[j] = 0;
    for (uint32_t t = 0; t < num_t; t++)
      b_size[j] += b_size_t[t][j - 1];
  }

  uint32_t *b[p];
  for (uint32_t t = 0; t < p; t++) {
#pragma omp task shared(data, b_id, b_size, b)
    {
      b[t] = new uint32_t[b_size[t + 1]];
      uint32_t idx = 0;
      for (uint64_t j = 0; j < n; j++) {
        if (b_id[j] != t)
          continue;
        b[t][idx++] = data[j];
      }
    }
  }
#pragma omp taskwait

  // Step 6
  for (uint32_t j = 1; j <= p; j++)
    b_size[j] += b_size[j - 1];
  sz = 2 * (n / p);

  for (uint32_t j = 0; j < p; j++) {
#pragma omp task shared(b, b_size, data, sz, p)
    {
      uint32_t nj = b_size[j + 1] - b_size[j], i = b_size[j];
      memcpy(data + i, b[j], nj * sizeof(uint32_t));
      if (nj < sz)
        SequentialSort(data + i, nj);
      else if (nj != 0)
        ParallelSort(data + i, nj, p);
    }
  }
#pragma omp taskwait

  for (uint32_t t = 0; t < p; t++)
    delete[] b[t];
  delete[] b_id;
}
