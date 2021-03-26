//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_MERGESORT_H
#define SORTALGORITHM_MERGESORT_H

#include "SortAlgorithm.h"

namespace SortAlgorithm{

    class MergeSort{

    private:
        /**
         * 合并已经是有序的 [left,middle) 和 [middle,right) 两个子数组
         * @param array
         * @param left 左端,包含
         * @param middle
         * @param right 右端, 不包含
         * @param compare
         */
        template<typename T>
        static void mergeInner(T array[], int left, int middle, int right, Compare<T> compare = SortAlgorithm::less){
            if (left >= right) {
                return;
            }

            T zoom[right - left];
            for (int i = left; i < right; ++i) { // 将数组元素复制到临时的zoom
                zoom[i - left] = array[i];
            }

            // 遍历zoom数组, 比较[left,middle) 和 [middle,right) 两个子数组元素
            // compare后(比如大的),写回原来的array,直到写完, array即是有序的
            int a = left, b = middle; // 两个子数组的起始index
            for (int i = left; i < right; ++i) {
                if (a >= middle) { // 此时a段子数组已经完全复制回去
                    array[i] = zoom[b - left];
                    b++;
                } else if (b >= right) { // 此时b段子数组已经完全复制回去
                    array[i] = zoom[a - left];
                    a++;
                } else if (compare(zoom[a - left], zoom[b - left])) { // 假定比较为true,先存储a段子数组元素
                    array[i] = zoom[a - left];
                    a++;
                } else {
                    array[i] = zoom[b - left];
                    b++;
                }
            }
        }


        /**
         * 对 [left, right) 的数组进行排序
         * @param array
         * @param left 左端,包含
         * @param right 右端, 不包含
         * @param compare
         */
        template <typename T>
        static void mergeSortInner(T array[],int left, int right,Compare<T> compare = SortAlgorithm::less){
            if (right - left <= 1) { // 只有一个元素,视作已经有序,直接返回
                return;
            }

            int middle = left + (right - left) / 2;
            mergeSortInner(array, left, middle, compare); // 对左半部分进行排序
            mergeSortInner(array, middle, right, compare); // 对右半部分进行排序
            // 当左半部分末尾元素和右半部分起始元素比较为false, 说明此时整体不是有序,需要进行合并排序,
            // 否则说明已经时有序的了,直接跳过
            if (!compare(array[middle - 1], array[middle])) {
                mergeInner(array, left, middle, right, compare); // 将左右两个部分进行合并
            }
        }


    public:

        /**
         * 归并排序
         * @param array
         * @param length
         * @param compare
         */
        template<typename T>
        static void mergeSort(T array[], int length, Compare<T> compare = SortAlgorithm::less){
            // 调用内部的merge 函数
            mergeSortInner(array, 0, length, compare);
        }


        /**
         * 使用for 循环来实现merge排序
         * 自底向上,每隔2size 进行merge, 每次merge的size规模扩大2倍, 1, 2, 4, ...
         * @tparam T
         * @param array
         * @param length
         * @param compare
         */
        template<typename T>
        static void mergeSortWithForLoop(T array[], int length, Compare<T> compare = SortAlgorithm::less) {
            assert(array != nullptr);
            assert(length > 0);

            for (int size = 1; size < length; size *= 2) { // 每次归并的size规模, 1, 2, 4, ...
                for (int pos = 0; pos + size < length; pos += 2 * size) { // 从位置0, 每2size 进行merge
                    int middle = pos + size;
                    int right = std::min(pos + 2 * size, length);
                    mergeInner(array, pos, middle, right, compare); // merge 2size的数组
                }
            }
        }

    };

}
#endif //SORTALGORITHM_MERGESORT_H
