#include <iostream>
#include <vector>
#include <algorithm>
#include "Quicksort.h"
#include "SortUtils.h"

typedef int sort_type;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Input a size" << std::endl;
        return -1;
    }
    int size = atoi(argv[1]);
    int num_threads = Threadpool::get_num_threads();
    if (argc >= 3) {
        num_threads = atoi(argv[2]);
    }
    Threadpool::set_num_threads(num_threads);
    std::chrono::high_resolution_clock::time_point start, end;
    {
        std::cout << "RUNNING PARALLEL ARRAY:" << std::endl;
        auto arr = new sort_type[size];
        randomize(arr, size);
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
                         end - start)
                         .count()
                  << " seconds" << std::endl;
        delete[] arr;
    }
    {
        std::cout << "RUNNING PARALLEL VECTOR:" << std::endl;
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
                         end - start)
                         .count()
                  << " seconds" << std::endl;
    }
    {
        std::cout << "RUNNING std::sort VECTOR:" << std::endl;
        std::vector<sort_type> v;
        v.resize(size);
        randomize(v);
        start = std::chrono::high_resolution_clock::now();
        std::sort(v.begin(), v.end());
        end = std::chrono::high_resolution_clock::now();
        if (!is_sorted(v)) {
            std::cout << "FAILURE" << std::endl;
        } else {
            std::cout << "SUCCESS" << std::endl;
        }
        std::cout << "std::sort VECTOR TIME: "
                  << std::chrono::duration_cast<std::chrono::duration<float> >(
                         end - start)
                         .count()
                  << " seconds" << std::endl;
    }
    return 0;
}
