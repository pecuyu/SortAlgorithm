//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_INSERTIONSORT_H
#define SORTALGORITHM_INSERTIONSORT_H

#include "SortAlgorithm.h"

namespace SortAlgorithm{

    class InsertionSort{

    public:
        /**
         * 插入排序
         * @param array
         * @param length
         * @param compare
         */
        template<typename T>
        static void insertionSort(T array[], int length, bool (*compare)(T &one, T &another) = SortAlgorithm::less){
            assert(array != nullptr);
            assert(length > 0);

            // 第0个元素默认算排序完成 从index 1 开始loop
            for (int i = 1; i < length; ++i) {
                // 从index为i的元素向前比较, 一旦compare不满足,则中断循环,否则交换元素
                for (int j = i; j > 0 && compare(array[j], array[j - 1]); --j) {
                    swap(array[j], array[j - 1]);
                }
            }
        }

        /**
         * 插入排序
         * 使用赋值替代swap
         * @param array
         * @param length
         * @param compare
         */
        template<typename T>
        static void insertionSortOptimize(T array[], int length, bool (*compare)(T &one, T &another) = SortAlgorithm::less){
            assert(array != nullptr);
            assert(length > 0);

            // 第0个元素默认算排序完成 从index 1 开始loop
            for (int i = 1; i < length; ++i) {
                // 从index为i-1的元素向前和pendingToInsert比较, 一旦compare不满足,则中断循环, 否则元素后移一位
                T pendingToInsert = array[i];// 寻找 array[i] 合适的插入位置
                int j = i; // 保存元素要插入的位置
                for (; j > 0 && compare(pendingToInsert, array[j - 1]); --j) {
                    array[j] = array[j - 1]; // 元素往后移动一位
                }

                if (j != i) {
                    array[j] = pendingToInsert;
                }
            }
        }

        // 对array[left...right)范围的数组进行插入排序
        // compare : less 升序, more 降序
        template<typename T>
        static void insertionSortWithRange(T array[], int left, int right,
                                    bool (*compare)(T &one, T &another) = SortAlgorithm::less) {
            assert(array != nullptr);
            assert(left <= right);

            for (int i = left + 1; i < right; i++) {
                T e = array[i];
                int j = i;
                for (; j > left && compare(e, array[j - 1]); j--) {
                    array[j] = array[j - 1];
                }
                array[j] = e;
            }
        }

    };

}

#endif //SORTALGORITHM_INSERTIONSORT_H
