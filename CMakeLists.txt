cmake_minimum_required(VERSION 3.17)
project(SortAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(SortAlgorithm main.cpp SortAlgorithm.h SortTestUtils.h BubbleSort.h SelectionSort.h InsertionSort.h MergeSort.h QuickSort.h Tester.h MaxHeap.h HeapSort.h Algorithms.h)