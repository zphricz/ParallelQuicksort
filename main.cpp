#include <cstdlib>
#include <iostream>
#include "qsort.h"

void randomize(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Input a size" << endl;
        return -1;
    }
    srand(time(NULL));
    int size = atoi(argv[1]);
    int *arr = new int[size];
    randomize(arr, size);
    std::chrono::high_resolution_clock::time_point start, end;
    start = std::chrono::high_resolution_clock::now();
    qsort(arr, size);
    end = std::chrono::high_resolution_clock::now();
    if (!is_sorted(arr, size)) {
        cout << "FAILURE" << endl;
    } else {
        cout << "SUCCESS" << endl;
    }

    delete[] arr;
    cout << "TIME: "
         << std::chrono::duration_cast<std::chrono::duration<float> >(
                end - start).count() << " seconds" << endl;

    return 0;
}
