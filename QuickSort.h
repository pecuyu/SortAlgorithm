//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_QUICKSORT_H
#define SORTALGORITHM_QUICKSORT_H

#include "SortAlgorithm.h"

namespace SortAlgorithm{

    class QuickSort{

    private:
        /**
         * 返回快排的分割点
         * 符合compare比较的放左部分,否则放右部分
         * @tparam T
         * @param array
         * @param left
         * @param right
         * @param compare
         * @return
         */
        template<typename T>
        static int partition(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less){
            assert(left <= right);
            assert(array != nullptr);

            if (right - left <= 1) { // 少于等于一个元素直接返回
                return 0;
            }

            // 取随机一位放在left位置作为参考值
            long p = random() % (right - left) + left;
            swap(array[p], array[left]);

            T v = array[left]; // 认定此处的值为中间值进行分割
            // 假定k时分界线, 大于k的为大于v,小于k的都是小于v
            // 在此处使用compare进行对比, compare为true的在左边, 否则在右边
            int k = left;
            // 对于less实现, array[left..k] < v <= array[k+1..right)
            for (int i = left + 1; i < right; ++i) {
                if (compare(array[i], v)) {
                    // 将compare 为true时 , array[k+1] 与 v的元素交换, 并递增k
                    ++k;  // k+1
                    if (k != i) { // 同一位置,不需要交换
                        swap(array[k], array[i]);
                    }
                }
            }

            int finalK = k >= right ? right - 1 : k;
            if (left != finalK) {
                swap(array[left], array[finalK]); // 交换临界点到k的位置
            }

            return finalK;
        }

        /**
         * 内部,快速排序. 边界范围 [left,right)
         * @tparam T
         * @param array
         * @param left
         * @param right
         * @param compare
         */
        template<typename T>
        static void quickSortInner(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);
            if (right - left <= 1) { // 少于等于一个元素直接返回
                return;
            }

            int pos = partition(array, left, right, compare); // 分割,返回分割的position
            quickSortInner(array, left, pos, compare);  // 对左部分进行快排
            quickSortInner(array, pos + 1, right, compare); // 对右部分进行快排
        }

    public:
        // 快速排序
        template<typename T>
        static void quickSort(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);
            assert(length > 0);

            srand(time(NULL));
            quickSortInner(array, 0, length, compare);
        }

    };

}
#endif //SORTALGORITHM_QUICKSORT_H
