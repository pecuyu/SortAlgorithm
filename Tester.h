//
// Created by pecuyu on 2021/3/24.
//

#ifndef SORTALGORITHM_TESTER_H
#define SORTALGORITHM_TESTER_H

#include "SortTestUtils.h"
#include "Algorithms.h"
#include "MaxHeap.h"


class Tester{

public:

    static void testBubbleSort(int length){
        int* arr = SortTestUtils::generateRandomArray(length, 0, 100);
        SortTestUtils::calculateSort("bubbleSort", arr, length,
                                     SortAlgorithm::BubbleSort::bubbleSort, SortAlgorithm::more);

        delete[] arr;
    }

    static void testSelectionSort(int length){
        int* arr = SortTestUtils::generateRandomArray(length, 0, length);
        int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 10);

        SortTestUtils::calculateSort("selectionSort", arr, length, SortAlgorithm::SelectionSort::selectionSort);
        SortTestUtils::calculateSort("selectionSort", nearlyOrderedArray, length, SortAlgorithm::SelectionSort::selectionSort);

        delete[] arr;
        delete[] nearlyOrderedArray;
    }

    static void testInsertionSort(int length){
        int* arr = SortTestUtils::generateRandomArray(length, 0, length);
        int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 100);
        int *nearlyOrderedArrayCopy = SortTestUtils::copyIntArray(nearlyOrderedArray, length);

        SortTestUtils::calculateSort("insertionSort", nearlyOrderedArray, length,
                                     SortAlgorithm::InsertionSort::insertionSort, SortAlgorithm::more);
        SortTestUtils::calculateSort("insertionSortOptimize", nearlyOrderedArrayCopy,
                                     length, SortAlgorithm::InsertionSort::insertionSortOptimize, SortAlgorithm::less);

        delete[] arr;
        delete[] nearlyOrderedArray;
        delete[] nearlyOrderedArrayCopy;
    }

    static void testMergeSort(int length){
        int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 100);
        int *nearlyOrderedArrayCopy = SortTestUtils::copyIntArray(nearlyOrderedArray, length);

        SortTestUtils::calculateSort("mergeSort", nearlyOrderedArray,
                                     length, SortAlgorithm::MergeSort::mergeSort);
        SortTestUtils::calculateSort("mergeSortWithForLoop", nearlyOrderedArrayCopy, length,
                                     SortAlgorithm::MergeSort::mergeSortWithForLoop);

        delete[] nearlyOrderedArray;
        delete[] nearlyOrderedArrayCopy;
    }


    static void testQuickSort(int length){
        // 对大量重复元素的数组排序
        int* arr = SortTestUtils::generateRandomArray(length, 0, 100); // 产生大量重复元素
        int *arrCopy = SortTestUtils::copyIntArray(arr, length);
        int *arrCopy2 = SortTestUtils::copyIntArray(arr, length);

        SortTestUtils::calculateSort("quickSort", arr, length, SortAlgorithm::QuickSort::quickSort);
        SortTestUtils::calculateSort("quickSort2", arrCopy, length, SortAlgorithm::QuickSort::quickSort2);
        SortTestUtils::calculateSort("quickSort3Ways", arrCopy2, length, SortAlgorithm::QuickSort::quickSort3Ways);

        delete[] arr;
        delete[] arrCopy;
        delete[] arrCopy2;

        std::cout<<std::endl;

        // 对近乎有序的数组进行排序
        int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 10);
        int *nearlyOrderedArrayCopy = SortTestUtils::copyIntArray(nearlyOrderedArray, length);
        int *nearlyOrderedArrayCopy2 = SortTestUtils::copyIntArray(nearlyOrderedArray, length);
        SortTestUtils::calculateSort("quickSort", nearlyOrderedArray, length, SortAlgorithm::QuickSort::quickSort);
        SortTestUtils::calculateSort("quickSort2", nearlyOrderedArrayCopy, length, SortAlgorithm::QuickSort::quickSort2);
        SortTestUtils::calculateSort("quickSort3Ways", nearlyOrderedArrayCopy2, length, SortAlgorithm::QuickSort::quickSort3Ways);

        delete[] nearlyOrderedArray;
        delete[] nearlyOrderedArrayCopy;
        delete[] nearlyOrderedArrayCopy2;
    }

    static void testMaxHeap(){
        SortAlgorithm::MaxHeap<int> maxHeap(10);
        maxHeap.insert(6);
        maxHeap.insert(3);
        maxHeap.insert(8);
        maxHeap.insert(9);
        maxHeap.insert(7);
        maxHeap.insert(16);
        maxHeap.insert(32);
        maxHeap.insert(85);
        maxHeap.insert(19);
        maxHeap.insert(199);
        maxHeap.insert(119);
        maxHeap.insert(27);

        maxHeap.print();

        while (maxHeap.size() > 0) {
            int max = maxHeap.extractMax();
            cout << max << " ";
        }
        cout << endl;
    }

    static void testHeapSort(int length){
        // 生产随机数组
        int* array = SortTestUtils::generateRandomArray(length, 0, 9999999);
        int *arrayCopy = SortTestUtils::copyIntArray(array, length);
        int *arrayCopy2 = SortTestUtils::copyIntArray(array, length);
        SortTestUtils::calculateSort("heapSort", array, length, SortAlgorithm::HeapSort::heapSort,false);
        SortTestUtils::calculateSort("heapSort2", array, length, SortAlgorithm::HeapSort::heapSort2,false);
        SortTestUtils::calculateSort("quickSort3Ways", arrayCopy, length, SortAlgorithm::QuickSort::quickSort3Ways);

        //SortTestUtils::printArray(array, length);
        delete[] array;
        delete[] arrayCopy;
        delete[] arrayCopy2;
    }

};

#endif //SORTALGORITHM_TESTER_H
