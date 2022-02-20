#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int count = 50;
#pragma omp parallel num_threads(4)
#pragma omp single
  {
    while (count > 0) {
#pragma omp task
      {
        int count2 = count;
        if (count == 10) {
          sleep(1);
#pragma omp atomic read
          count = count;
          printf("Task10: %d,%d\n", count, count2);
        }
      } // end task
      count--;
#pragma omp flush
    } // end while
  }   // end single, parallel
}
