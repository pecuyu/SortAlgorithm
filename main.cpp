#include <iostream>
#include "SortAlgorithm.h"
#include "SortTestUtils.h"

int main() {

    int length = 10000;
    //int* arr = SortTestUtils::generateRandomArray(length, 0, 3);
    //int *arrCopy = SortTestUtils::copyIntArray(arr, length);
    int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 100);
    int *nearlyOrderedArrayCopy = SortTestUtils::copyIntArray(nearlyOrderedArray, length);
    //SortAlgorithm::selectionSort(arr, length);
    SortTestUtils::calculateSort("selectionSort", nearlyOrderedArray, length, SortAlgorithm::selectionSort);
    //SortTestUtils::printArray(nearlyOrderedArray, length);

    //SortTestUtils::calculateSort("bubbleSort", arr, length, SortAlgorithm::bubbleSort, SortAlgorithm::more);
    //SortTestUtils::calculateSort("insertionSort", arr, length, SortAlgorithm::insertionSort, SortAlgorithm::more);
    SortTestUtils::calculateSort("insertionSortOptimize", nearlyOrderedArrayCopy, length, SortAlgorithm::insertionSortOptimize, SortAlgorithm::less);

    //SortTestUtils::printArray(arr, length);

    //delete[] arr;
    //delete[] arrCopy;
    delete[]nearlyOrderedArray;
    delete[] nearlyOrderedArrayCopy;

    return 0;
}
