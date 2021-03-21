#include <iostream>
#include "SortAlgorithm.h"
#include "SortTestUtils.h"

int main() {

    int length = 1000000;
    int* arr = SortTestUtils::generateRandomArray(length, 0, 99999);
    int *arrCopy = SortTestUtils::copyIntArray(arr, length);
    //int *nearlyOrderedArray = SortTestUtils::generateNearlyOrderedArray(length, 1000);
    //int *nearlyOrderedArrayCopy = SortTestUtils::copyIntArray(nearlyOrderedArray, length);
    //SortAlgorithm::selectionSort(arr, length);
    //SortTestUtils::calculateSort("selectionSort", nearlyOrderedArray, length, SortAlgorithm::selectionSort);
    //SortTestUtils::printArray(nearlyOrderedArray, length);

    //SortTestUtils::calculateSort("bubbleSort", arr, length, SortAlgorithm::bubbleSort, SortAlgorithm::more);
    //SortTestUtils::calculateSort("insertionSort", arr, length, SortAlgorithm::insertionSort, SortAlgorithm::more);
   // SortTestUtils::calculateSort("insertionSortOptimize", nearlyOrderedArrayCopy, length, SortAlgorithm::insertionSortOptimize, SortAlgorithm::less);

    //SortTestUtils::calculateSort("mergeSort", nearlyOrderedArrayCopy, length, SortAlgorithm::mergeSort);

    SortTestUtils::calculateSort("mergeSortWithForLoop", arr, length,
                                 SortAlgorithm::mergeSortWithForLoop);

    SortTestUtils::calculateSort("quickSort", arrCopy, length, SortAlgorithm::quickSort);

    //SortTestUtils::printArray(nearlyOrderedArrayCopy, length);
    //delete[] arr;
    //delete[] arrCopy;
   // delete[]nearlyOrderedArray;
   // delete[] nearlyOrderedArrayCopy;

    return 0;
}
