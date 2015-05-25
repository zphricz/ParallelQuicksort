#ifndef QSORT_H
#define QSORT_H

#include "Threadpool.h"

using namespace std;

constexpr int SERIAL_CUTOFF = 1024;
constexpr int INSERTION_CUTOFF = 32;

template <typename T>
void partition(T *l, int start, int end, int &run_start, int &run_end) {
  T pval = l[(end + start) / 2];
  int i = start;
  run_start = start;
  run_end = end;
  while (i <= run_end) {
    if (l[i] < pval) {
      swap(l[i], l[run_start]);
      run_start++;
      i++;
    } else if (l[i] > pval) {
      swap(l[i], l[run_end]);
      run_end--;
    } else {
      i++;
    }
  }
}

template <typename T>
void insertion(T *l, int size) {
  for (int i = 1; i < size; ++i) {
    T key = l[i];
    int k = i;
    while (k > 0 && key < l[k - 1]) {
      l[k] = l[k - 1];
      k--;
    }
    l[k] = key;
  }
}

template <typename T>
void serial_qsort_help(T *l, int start, int end) {
  int run_start;
  int run_end;
  if (end - start <= INSERTION_CUTOFF - 1) {
    insertion(l + start, end - start + 1);
    return;
  }
  partition(l, start, end, run_start, run_end);
  serial_qsort_help(l, start, run_start - 1);
  serial_qsort_help(l, run_end + 1, end);
}

template <typename T>
void qsort_help(T *l, int start, int end) {
  if (end - start <= SERIAL_CUTOFF - 1) {
    serial_qsort_help(l, start, end);
    return;
  }
  int run_start;
  int run_end;
  partition(l, start, end, run_start, run_end);
  submit_task(qsort_help<T>, l, start, run_start - 1);
  submit_task(qsort_help<T>, l, run_end + 1, end);
}

template <typename T>
void qsort(T *l, int size) {
  qsort_help(l, 0, size - 1);
  wait_for_all_jobs();
}

template <typename T>
bool is_sorted(T *l, int size) {
  for (int i = 0; i < size - 1; ++i) {
    if (l[i] > l[i + 1])
      return false;
  }
  return true;
}

#endif
