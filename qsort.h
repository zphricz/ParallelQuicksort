#ifndef QSORT_H
#define QSORT_H

#include <random>
#include "Threadpool.h"

constexpr int SERIAL_CUTOFF = 1024;
constexpr int INSERTION_CUTOFF = 32;

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
void serial_qsort_help(T &list, int start, int end) {
  int run_start;
  int run_end;
  if (end - start <= INSERTION_CUTOFF - 1) {
    insertion(list, start, end);
    return;
  }
  partition(list, start, end, run_start, run_end);
  serial_qsort_help(list, start, run_start - 1);
  serial_qsort_help(list, run_end + 1, end);
}

template <typename T>
void qsort_help(T &list, int start, int end) {
  if (end - start <= SERIAL_CUTOFF - 1) {
    serial_qsort_help(list, start, end);
    return;
  }
  int run_start;
  int run_end;
  partition(list, start, end, run_start, run_end);
  submit_task(qsort_help<T>, std::ref(list), start, run_start - 1);
  submit_task(qsort_help<T>, std::ref(list), run_end + 1, end);
}

template <typename T>
void qsort(T &list, int size) {
  qsort_help(list, 0, size - 1);
  wait_for_all_jobs();
}

// T must implement the size() method to work
template <typename T>
void qsort(T &list) {
  qsort(list, list.size());
}

template <typename T>
bool is_sorted(T &list, int size) {
  for (int i = 0; i < size - 1; ++i) {
    if (list[i] > list[i + 1])
      return false;
  }
  return true;
}

template <typename T>
bool is_sorted(T &list) {
  return is_sorted(list, list.size());
}

template <typename T>
void randomize(T &list, int size) {
  std::mt19937 gen;
  std::uniform_int_distribution<int> dis;
  for (int i = 0; i < size; ++i) {
    list[i] = dis(gen);
  }
}

template <typename T>
void randomize(T &list) {
  randomize(list, list.size());
}

#endif
