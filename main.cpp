#include <iostream>
#include <vector>
#include "qsort.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Input a size" << std::endl;
    return -1;
  }
  int size = atoi(argv[1]);
  int *arr = new int[size];
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

  std::vector<int> v;
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
  return 0;
}
