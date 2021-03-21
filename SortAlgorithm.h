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

    /**
     * 插入排序
     * @param array
     * @param length
     * @param compare
     */
    template<typename T>
    void insertionSort(T array[], int length, bool (*compare)(T &one, T &another) = SortAlgorithm::less){
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
    void insertionSortOptimize(T array[], int length, bool (*compare)(T &one, T &another) = SortAlgorithm::less){
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

    /**
     * 合并已经是有序的 [left,middle) 和 [middle,right) 两个子数组
     * @param array
     * @param left 左端,包含
     * @param middle
     * @param right 右端, 不包含
     * @param compare
     */
    template<typename T>
    void mergeInner(T array[], int left, int middle, int right, bool (*compare)(T &, T &) = SortAlgorithm::less){
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
    void mergeSortInner(T array[],int left, int right,bool (*compare)(T &, T &) = SortAlgorithm::less){
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


    /**
     * 归并排序
     * @param array
     * @param length
     * @param compare
     */
    template<typename T>
    void mergeSort(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less){
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
    void mergeSortWithForLoop(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less) {
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
    int partition(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less){
        assert(left <= right);
        assert(array != nullptr);

        if (right - left <= 1) { // 少于等于一个元素直接返回
            return 0;
        }

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
    void quickSortInner(T array[], int left, int right, bool (*compare)(T &, T &) = SortAlgorithm::less) {
        assert(array != nullptr);
        if (right - left <= 1) { // 少于等于一个元素直接返回
            return;
        }

        int pos = partition(array, left, right, compare); // 分割,返回分割的position
        quickSortInner(array, left, pos, compare);  // 对左部分进行快排
        quickSortInner(array, pos + 1, right, compare); // 对右部分进行快排
    }

    // 快速排序
    template<typename T>
    void quickSort(T array[], int length, bool (*compare)(T &, T &) = SortAlgorithm::less) {
        assert(array != nullptr);
        assert(length > 0);

        quickSortInner(array, 0, length, compare);
    }

}

#endif //SORTALGORITHM_SORTALGORITHM_H
