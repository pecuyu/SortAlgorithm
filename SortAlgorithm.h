//
// Created by pecuyu on 2021/3/10.
//

#ifndef SORTALGORITHM_SORTALGORITHM_H
#define SORTALGORITHM_SORTALGORITHM_H

#include <cstdio>
#include "cassert"
#include "algorithm"

namespace SortAlgorithm {

    template<typename T>
    void swap(T &one, T &another) {
        T temp = one;
        one = another;
        another = temp;
    }

    template<typename T>
    bool less(T &one, T &another) {
        return one < another;
    }

    template<typename T>
    bool more(T &one, T &another) {
        return one > another;
    }

    /**
     * 选择排序
     * @param array
     * @param length
     * @param compare 比较函数
     */
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

    /**
     * 冒泡排序
     * @param array
     * @param length
     * @param compare 比较函数
     */
    template<typename T>
    void bubbleSort(T array[], int length,
                    bool (*compare)(T &one, T &another) = SortAlgorithm::less) {
        assert(array != nullptr);
        assert(length > 0);

        bool sorted;
        for (int i = 0; i < length; ++i) { // 遍历数组
            sorted = true;
            for (int j = 0; j < length - i - 1; ++j) {
                // 0...length-i ,每次遍历后,array[length-i-1] 为当前序列最值
                // 比较 array[j] 和 array[(j+1)]
                if (compare(array[j], array[j + 1])) {
                    swap(array[j], array[j + 1]);
                    sorted = false; // 有交换,说明可能没有排序完成
                }
            }

            if (sorted) { // 遍历序列没有改变,说明排序完成
                break;
            }
        }
    }

}

#endif //SORTALGORITHM_SORTALGORITHM_H
