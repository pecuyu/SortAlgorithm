//
// Created by pecuyu on 2021/3/10.
//

#ifndef SORTALGORITHM_SORTTESTUTILS_H
#define SORTALGORITHM_SORTTESTUTILS_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace SortTestUtils{

    // 生成数组长度为n , 元素范围是left到right的闭区间 [ left, right]
    int *generateRandomArray(int length, int left, int right)
    {
        assert(length > 0);
        assert(left <= right);

        srand(time(NULL));

        int *array = new int[length];
        assert(array != nullptr);

        for (int i = 0; i < length; ++i) {
            array[i] = random() % (right - left + 1) + left;
        }

        return array;
    }

    /**
     * 生成一个近乎有序的数组
     * @param length
     * @param swapTimes 任意交换数组元素的次数
     * @param asc 升序还是降序
     * @return
     */
    int *generateNearlyOrderedArray(int length, int swapTimes, bool asc = true) {
        if (swapTimes >= length) {
            swapTimes = length / 10;
        }

        int *array = new int[length];
        for (int i = 0; i < length; ++i) {
            array[i] = asc ? (i + 1) : (length - i);
        }

        srand(time(NULL));
        for (int i = 0; i < swapTimes; ++i) { // 交换任意两处元素
            int x = random() % length;
            int y = random() % length;
            SortAlgorithm::swap(array[x], array[y]);
        }

        return array;
    }

    int *copyIntArray(int array[], int length) {
        int *resArray = new int[length];
        copy(array, array + length, resArray);

        return resArray;
    }

    void printArray(int *array, int length) {
        for (int i = 0; i < length; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    // ASC 升序
    template<typename T>
    bool isAscSorted(const T array[], int length)
    {
        for (int i = 0; i < length-1; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        cout << "isAscSorted" << endl;
        return true;
    }

    // DESC 降序
    template<typename T>
    bool isDescSorted(const T array[], int length)
    {
        for (int i = 0; i < length-1; ++i) {
            if (array[i] < array[i + 1]) {
                return false;
            }
        }
        cout << "isDescSorted" << endl;
        return true;
    }

    template<typename T>
    bool isSorted(const T array[], int length)
    {
        return isAscSorted(array, length) || isDescSorted(array, length);
    }

    /**
     * 计算排序算法耗时
     * @param sortName
     * @param array
     * @param length
     * @param sort  使用的排序算法
     * @param compare 元素比较函数, 默认 {SortAlgorithm::less)
     */
    template<typename T>
    void calculateSort(const string& sortName, T array[],int length,
                       void (*sort)(T[], int length, bool(*compare)(T &one, T &another)),
                       bool(*compare)(T &one, T &another) = SortAlgorithm::less)
    {
        clock_t startTime = clock();
        sort(array, length,compare);
        clock_t endTime = clock();

        assert(isSorted(array,length)); // 判断排序是否成功

        cout << sortName << " wastes " << double (endTime - startTime) / CLOCKS_PER_SEC <<"s"<< endl;
    }

}


#endif //SORTALGORITHM_SORTTESTUTILS_H
