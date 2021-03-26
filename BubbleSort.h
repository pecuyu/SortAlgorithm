//
// Created by pecuyu on 2021/3/22.
//

#ifndef SORTALGORITHM_BUBBLESORT_H
#define SORTALGORITHM_BUBBLESORT_H

#include "SortAlgorithm.h"

namespace SortAlgorithm{

    class BubbleSort{

    public:
        /**
         * 冒泡排序
         * @param array
         * @param length
         * @param compare 比较函数
         */
        template<typename T>
        static void bubbleSort(T array[], int length,
                        Compare<T> compare = SortAlgorithm::less) {
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

    };

}


#endif //SORTALGORITHM_BUBBLESORT_H
