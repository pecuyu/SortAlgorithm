//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_SELECTIONSORT_H
#define SORTALGORITHM_SELECTIONSORT_H

#include "SortAlgorithm.h"

namespace SortAlgorithm{

    class SelectionSort{

    public:
        /**
         * 选择排序
         * @param array
         * @param length
         * @param compare 比较函数
         */
        template<typename T>
        static void selectionSort(T *array, int length,
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

    };

}

#endif //SORTALGORITHM_SELECTIONSORT_H
