//
// Created by pecuyu on 2021/3/10.
//

#ifndef SORTALGORITHM_SORTALGORITHM_H
#define SORTALGORITHM_SORTALGORITHM_H

#include <cstdio>
#include "cassert"
#include "algorithm"
#include "ctime"

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
     * Compare 函数指针模板
     */
    template<typename T>
    using Compare = bool (*)(T &, T &);

}

#endif //SORTALGORITHM_SORTALGORITHM_H
