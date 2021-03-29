//
// Created by pecuyu on 2021/3/27.
//

#ifndef SORTALGORITHM_HEAPSORT_H
#define SORTALGORITHM_HEAPSORT_H

#include "SortAlgorithm.h"
#include "structrue/MaxHeap.h"


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

        template<typename T>
        static void heapSort2(T array[], int length, bool asc) {
            assert(array != nullptr);
            assert(length > 0);

            // 通过数组构造一个最大堆
            MaxHeap<T> maxHeap(array, length);
            // 依次取出最大堆的最大元素重新写回原数组
            for (int i = 0; i < length; ++i) {
                T max = maxHeap.extractMax();
                array[asc ? (length - 1 - i) : i] = max;
            }
        }

        /**
         * 原地堆排序
         * @tparam T
         * @param array
         * @param length
         * @param asc
         */
        template<typename T>
        static void heapSort3(T array[], int length, bool asc) {
            // 将数组堆化 heapify
            for (int i = (length - 1) / 2; i >= 0; --i) {
                MaxHeap<T>::shiftDown(array, i, length);
            }

            // 排序
            for (int i = 0; i < length; ++i) {
                swap(array[0], array[length - 1 - i]);
                MaxHeap<T>::shiftDown(array, 0, length - 1 - i);
            }

            // 处理逆序
            if (!asc) {
                for (int i = 0; i < length / 2; ++i) {
                    swap(array[i], array[length - 1 - i]);
                }
            }
        }
    };

}
#endif //SORTALGORITHM_HEAPSORT_H
