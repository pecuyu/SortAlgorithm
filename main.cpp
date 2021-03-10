#include <iostream>
#include "SortAlgorithm.h"
#include "SortTestUtils.h"

int main() {

    std::cout << "Hello, World!" << std::endl;

    int length = 100000;
    int* arr = SortTestUtils::generateRandomArray(length, 0, 99999);

    //SortAlgorithm::selectionSort(arr, length);
    SortTestUtils::calculateSort("selectionSort", arr, length, SortAlgorithm::selectionSort);

    SortTestUtils::printArray(arr, length);

    delete[] arr;

    return 0;
}
