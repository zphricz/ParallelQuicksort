#ifndef SORTUTILS_H
#define SORTUTILS_H

#include <random>

template <typename T> bool is_sorted(T &list, int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (list[i] > list[i + 1])
            return false;
    }
    return true;
}

// T must implement the size() method to work
template <typename T> bool is_sorted(T &list) {
    return is_sorted(list, list.size());
}

template <typename T> void randomize(T &list, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis;
    for (int i = 0; i < size; ++i) {
        list[i] = dis(gen);
    }
}

// T must implement the size() method to work
template <typename T> void randomize(T &list) { randomize(list, list.size()); }

#endif
