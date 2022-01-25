#include "psort.h"
#include <cstdint>
#include <iostream>
#include <omp.h>
#include <string.h>
#include <string>

void SequentialSort(uint32_t *data, uint32_t n) {
  if (n <= 1)
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

uint32_t binary_search(uint32_t *data, uint32_t p, uint32_t val) {
  uint32_t l = 0, r = p;
  while (l < r) {
    uint32_t mid = (l + r) >> 1;
    if (val <= data[(mid + 1) * p])
      r = mid;
    else
      l = mid + 1;
  }
  return r;
}

void print_arr(uint32_t *data, uint32_t n) {
  for (uint32_t j = 0; j < n; j++)
    std::cout << data[j] << ' ';
  std::cout << '\n';
}

void ParallelSort(uint32_t *data, uint32_t n, int p) {
  if (n / p < p) {
    SequentialSort(data, n);
    return;
  }

  uint32_t r[p * p + 1], sz = n / p, offset = (n % p) * (sz + 1);

  for (uint32_t j = 0; j < n % p; j++) {
#pragma omp task shared(p, sz, r, data)
    {
      uint32_t off1 = p * j, off2 = j * (sz + 1);
      for (uint32_t idx = 0; idx < p; idx++)
        r[off1 + idx] = data[off2 + idx];
    }
  }
  for (uint32_t j = n % p; j < p; j++) {
#pragma omp task shared(p, offset, sz, r, data)
    {
      uint32_t off1 = p * j, off2 = offset + (j - n % p) * sz;
      for (uint32_t idx = 0; idx < p; idx++)
        r[off1 + idx] = data[off2 + idx];
    }
  }
#pragma omp taskwait
  SequentialSort(r, p * p);
  r[p * p] = UINT32_MAX;

  uint32_t num_t = omp_get_num_threads(), b_size_t[p + 1][num_t], b_id[n];
  for (uint32_t j = 0; j <= p; j++) {
#pragma omp task shared(b_size_t, num_t)
    memset(b_size_t[j], 0, (num_t) * sizeof(uint32_t));
  }
#pragma omp taskwait
#pragma omp parallel for num_threads(num_t)
  for (uint32_t j = 0; j < n; j++) {
    {
      b_id[j] = binary_search(r, p, data[j]);
      b_size_t[b_id[j] + 1][omp_get_thread_num()]++;
    }
  }

  uint32_t b_size[p + 1];
  for (uint32_t j = 0; j <= p; j++) {
    b_size[j] = 0;
#pragma omp task shared(b_size, b_size_t, num_t)
    for (uint32_t t = 0; t < num_t; t++)
      b_size[j] += b_size_t[j][t];
  }
#pragma omp taskwait
  for (uint32_t j = 1; j < p; j++)
    b_size[j] += b_size[j - 1];

  uint32_t *b = new uint32_t[n];
  for (uint32_t j = 0; j < n; j++) {
    // #pragma omp task shared(data, b_id, b_size, b)
    {
      uint32_t id = b_id[j], idx;
      // #pragma omp atomic capture
      idx = b_size[id]++;
      b[idx] = data[j];
    }
  }
  // #pragma omp taskwait

  memcpy(data, b, n * sizeof(uint32_t));
  delete[] b;
  sz *= 2;
  for (uint32_t j = 0; j < p; j++) {
#pragma omp task shared(b_size, data, sz, p)
    {
      uint32_t nj = (j == 0 ? b_size[j] : b_size[j] - b_size[j - 1]),
               i = b_size[j] - nj;
      if (nj < sz)
        SequentialSort(data + i, nj);
      else if (nj != 0)
        ParallelSort(data + i, nj, p);
    }
  }
#pragma omp taskwait
}
