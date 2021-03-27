//
// Created by pecuyu on 2021/3/27.
//

#ifndef SORTALGORITHM_HEAPSORT_H
#define SORTALGORITHM_HEAPSORT_H

#include "SortAlgorithm.h"
#include "MaxHeap.h"


namespace SortAlgorithm {

    class HeapSort {
    public:
        /**
         * @tparam T 
         * @param array 
         * @param length 
         * @param asc  是否升序
         */
        template<typename T>
        static void heapSort(T array[], int length, bool asc) {
            assert(array != nullptr);
            assert(length > 0);

            // 将数组元素填入最大堆
            MaxHeap<T> maxHeap(length);
            for (int i = 0; i < length; ++i) { // 数组元素插入最大堆
                maxHeap.insert(array[i]);
            }

            // 依次取出最大堆的最大元素重新写回原数组
            for (int i = 0; i < length; ++i) {
                T max = maxHeap.extractMax();
                array[asc ? (length - 1 - i) : i] = max;
            }
        }
    };
    
}
#endif //SORTALGORITHM_HEAPSORT_H
