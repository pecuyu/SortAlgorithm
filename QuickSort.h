//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_QUICKSORT_H
#define SORTALGORITHM_QUICKSORT_H

#include "SortAlgorithm.h"
#include "InsertionSort.h"

namespace SortAlgorithm {

    class QuickSort {

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
        static int partition(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
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

        // 进行分割,返回分割点pos
        // 对重复的元素v尽量均匀分散到左右2个子数组
        template<typename T>
        static int partition2(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(left <= right);
            assert(array != nullptr);

            if (right - left <= 1) { // 少于等于一个元素直接返回
                return 0;
            }

            // 取随机一位放在left位置作为参考值
            long p = random() % (right - left) + left;
            swap(array[p], array[left]);

            T v = array[left]; // 认定此处的值为中间值进行分割

            // 对于less: array[left..i] <= v,  array[j..right) >= v
            // 对于重复率很高的数组,平衡两边的v的数量
            int i = left + 1, j = right - 1;
            while (true) {
                while (i < right && compare(array[i], v)) i++;  // 对于less, 过滤小于v的
                while (j > left && !compare(array[j], v) && (array[j] != v)) j--; // 对于less, 过滤大于v, 此处不包含v

                if (i > j) break;
                // 交换元素, 然后移动index
                if (array[i] != array[j]) {
                    swap(array[i], array[j]);
                }
                i++;
                j--;
            }

            swap(array[left], array[j]);

            return j;
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
        static void quickSortInner2(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);
            if (right - left <= 1) { // 少于等于一个元素直接返回
                return;
            }

            // 小于16,使用插入排序进行优化
            if (right - left <= 16) {
                SortAlgorithm::InsertionSort::insertionSortWithRange(array, left, right, compare);
                return;
            }

            int pos = partition2(array, left, right, compare); // 分割,返回分割的position
            quickSortInner2(array, left, pos, compare);  // 对左部分进行快排
            quickSortInner2(array, pos + 1, right, compare); // 对右部分进行快排
        }

        // 对 array[left,right) 的数组进行3路快速排序
        // 将数组分为 >V , =V , <V 进行排序
        template<typename T>
        static void
        quickSort3WaysInner(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);

            if (right - left <= 1) {
                return;
            }

            // 取随机一位做分割点
            swap(array[left], array[random() % (right - left) + left]);
            T v = array[left];

            // partition
            int lt = left; // 对于less : array(left...lt] < v
            int pos = lt + 1; // array(lt+1...pos) = v
            int gt = right; // 对于less : array[gt,right) > v
            while (true) {
                if (pos >= gt) {
                    break;
                }

                if (array[pos] == v) { // 等于v直接后移一位
                    pos++;
                } else if (compare(array[pos], v)) {
                    ++lt;
                    if (lt != pos) { // 相同index,直接跳过
                        swap(array[lt], array[pos]); // 此处两个index都移动
                    }
                    ++pos;
                } else {
                    swap(array[--gt], array[pos]);  // 此处只需移动gt
                }
            }

            // 将第一个元素与lt交换, 交换后lt是第一个等于v的元素,gt-1 是最后一个等于v的元素
            // 即 array[lt,gt) = v
            swap(array[left], array[lt]);

            // 对不等于v的2部分 array[left,lt) 和 array[gt,right) 再进行排序
            quickSort3WaysInner(array, left, lt);
            quickSort3WaysInner(array, gt, right);
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

        template<typename T>
        static void quickSort2(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);
            assert(length > 0);

            srand(time(NULL));
            quickSortInner2(array, 0, length, compare);
        }

        // 三路快速排序
        template<typename T>
        static void quickSort3Ways(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less) {
            assert(array != nullptr);
            assert(length > 0);

            srand(time(NULL)); // 随机数种子
            quickSort3WaysInner(array, 0, length, compare);
        }

    };

}
#endif //SORTALGORITHM_QUICKSORT_H
