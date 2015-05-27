#include <iostream>
#include <vector>
#include "Quicksort.h"

typedef int sort_type;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Input a size" << std::endl;
    return -1;
  }
  int size = atoi(argv[1]);
  auto arr = new sort_type[size];
  randomize(arr, size);
  std::chrono::high_resolution_clock::time_point start, end;
  start = std::chrono::high_resolution_clock::now();
  qsort(arr, size);
  end = std::chrono::high_resolution_clock::now();
  if (!is_sorted(arr, size)) {
    std::cout << "FAILURE" << std::endl;
  } else {
    std::cout << "SUCCESS" << std::endl;
  }
  std::cout << "ARRAY TIME: "
     << std::chrono::duration_cast<std::chrono::duration<float> >(
        end - start).count() << " seconds" << std::endl;
  delete[] arr;

  std::vector<sort_type> v;
  v.resize(size);
  randomize(v);
  start = std::chrono::high_resolution_clock::now();
  qsort(v);
  end = std::chrono::high_resolution_clock::now();
  if (!is_sorted(v)) {
    std::cout << "FAILURE" << std::endl;
  } else {
    std::cout << "SUCCESS" << std::endl;
  }
  std::cout << "VECTOR TIME: "
     << std::chrono::duration_cast<std::chrono::duration<float> >(
        end - start).count() << " seconds" << std::endl;
  for (int i = 0; i < size; ++i) {
    if (v[i] != arr[i]) {
      std::cout << "FANFKASNFJKAS" << std::endl;
      return 1;
    }
  }
  return 0;
}
