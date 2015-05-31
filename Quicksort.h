#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Threadpool.h"

/*
 * An implementation of a parallel quicksort that uses my threadpool. Run it
 * with the qsort() function.
 */

// The size of list for which the parallel quicksort switches to a serial
// quicksort
constexpr int SERIAL_CUTOFF = 6240;
// The size of list for which the serial quicksort swiches to a serial
// insertion sort
constexpr int INSERTION_CUTOFF = 32;

template <typename T>
void insertion(T &list, int start, int end) {
  for (int i = start + 1; i <= end; ++i) {
    auto key = list[i];
    int k = i;
    while (k > 0 && key < list[k - 1]) {
      list[k] = list[k - 1];
      k--;
    }
    list[k] = key;
  }
}

template <typename T>
void partition(T &list, int start, int end, int &run_start, int &run_end) {
  auto pval = list[(end + start) / 2];
  int i = start;
  run_start = start;
  run_end = end;
  while (i <= run_end) {
    if (list[i] < pval) {
      std::swap(list[i], list[run_start]);
      run_start++;
      i++;
    } else if (list[i] > pval) {
      std::swap(list[i], list[run_end]);
      run_end--;
    } else {
      i++;
    }
  }
}

template <typename T>
void serial_qsort(T &list, int start, int end) {
  if (end - start < INSERTION_CUTOFF) {
    insertion(list, start, end);
    return;
  }
  int run_start;
  int run_end;
  partition(list, start, end, run_start, run_end);
  serial_qsort(list, start, run_start - 1);
  serial_qsort(list, run_end + 1, end);
}

template <typename T>
void parallel_qsort(T &list, int start, int end) {
  if (end - start < SERIAL_CUTOFF) {
    serial_qsort(list, start, end);
    return;
  }
  int run_start;
  int run_end;
  partition(list, start, end, run_start, run_end);
  Threadpool::submit_task(parallel_qsort<T>, std::ref(list),
                          start, run_start - 1);
  Threadpool::submit_task(parallel_qsort<T>, std::ref(list),
                          run_end + 1, end);
}

template <typename T>
void qsort(T &list, int size) {
  parallel_qsort(list, 0, size - 1);
  Threadpool::wait_for_all_jobs();
}

// T must implement the size() method to work
template <typename T>
void qsort(T &list) {
  qsort(list, list.size());
}

#endif
