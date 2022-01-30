#include "psort.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <stdint.h>

void check_sorted(uint32_t *data, uint32_t *data_copy, int n) {
  for (int i = 0; i < n; i++) {
    if (data[i] != data_copy[i]) {
      std::cout << data[i] << ' ' << data_copy[i] << ' ' << i << '\n';
      std::cout << "Data is not sorted.\n";
      return;
    }
  }

  std::cout << "Data is sorted.\n";
  return;
}

void SortData(uint32_t *data, uint32_t n, int p, int n_threads) {
#pragma omp parallel num_threads(n_threads)
  {
#pragma omp single
    ParallelSort(data, n, p);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Insufficient Arguments\n"; // <datafile> <n_threads>
    return 0;
  }

  std::fstream fs(argv[1], std::ios::in | std::ios::binary);

  // Reading data
  uint32_t n, d = 0;
  int p, n_threads = atoi(argv[2]);

  fs.read((char *)&n, sizeof(n));
  fs.read((char *)&p, sizeof(p));

  uint32_t *data = new uint32_t[n], *data_copy = new uint32_t[n];

  std::cout << "n_threads = " << n_threads << std::endl;
  std::cout << "N = " << n << " p = " << p << std::endl;

  for (d = 0; d < n; d++) {
    fs.read((char *)&data[d], sizeof(uint32_t));
  }

  fs.close();
  memcpy(data_copy, data, n * sizeof(uint32_t));

  // Sorting
  auto begin = std::chrono::high_resolution_clock::now();
  SortData(data, n, p, n_threads);
  auto end = std::chrono::high_resolution_clock::now();
  double duration =
      (1e-6 *
       (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin))
           .count());

  std::sort(data_copy, data_copy + n);
  check_sorted(data, data_copy, n);
  std::cout << "Time taken for sorting " << n << " elements with " << p
            << " buckets = " << duration << "ms" << std::endl;

  // Clean-up
  delete[] data;
  delete[] data_copy;

  return 0;
}
