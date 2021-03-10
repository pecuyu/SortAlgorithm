//
// Created by pecuyu on 2021/3/10.
//

#ifndef SORTALGORITHM_SORTALGORITHM_H
#define SORTALGORITHM_SORTALGORITHM_H

#include <cstdio>
#include "cassert"
#include "algorithm"

namespace SortAlgorithm {

    template <typename T>
    void swap(T &one, T &another) {
        T temp = one;
        one = another;
        another = temp;
    }

    template<typename T>
    bool less(T &one, T &another){
        return one < another;
    }

    template<typename T>
    bool more(T &one, T &another){
        return one > another;
    }

    template<typename T>
    void selectionSort(T *array, int length,
                       bool(*compare)(T &one, T &another) = SortAlgorithm::less/* 默认比较函数*/) {
        assert(array != nullptr);
        assert(length > 0);

        for (int i = 0; i < length; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < length; ++j) {
                if (compare(array[j], array[minIndex])) { // 比较
                    minIndex = j;
                }
            }

            if (i != minIndex) {
                swap(array[i], array[minIndex]);
            }
        }
    }


}

#endif //SORTALGORITHM_SORTALGORITHM_H
