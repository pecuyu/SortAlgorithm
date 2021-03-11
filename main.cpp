#include <iostream>
#include "SortAlgorithm.h"
#include "SortTestUtils.h"

int main() {

    int length = 1000;
    int* arr = SortTestUtils::generateRandomArray(length, 0, 99999);

    //SortAlgorithm::selectionSort(arr, length);
   // SortTestUtils::calculateSort("selectionSort", arr, length, SortAlgorithm::selectionSort);
    SortTestUtils::calculateSort("bubbleSort", arr, length, SortAlgorithm::bubbleSort,SortAlgorithm::more);
    SortTestUtils::printArray(arr, length);

    delete[] arr;

    return 0;
}
