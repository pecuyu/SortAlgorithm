//
// Created by pecuyu on 2021/3/26.
//

#ifndef SORTALGORITHM_MAXHEAP_H
#define SORTALGORITHM_MAXHEAP_H

#include <iostream>
#include "SortAlgorithm.h"

namespace SortAlgorithm{
    /**
     *  最大堆, 父节点的元素始终保持 >= 子元素
     *  存储的元素从index=1开始 , 因此假若父节点的索引为pos, 则:
     *      左节点的index 为 2*pos
     *      有节点的index 为 2*pos + 1
     *
     * @tparam Node
     */
    template<typename Node>
    class MaxHeap {
    private:
        Node* nodes; // 元素集, index从1开始
        int _size; // 实际元素个数
        int capacity; // 实际最大容量 >=_size

    public:
        MaxHeap(int capacity) {
            this->capacity = capacity + 1; // 元素index从1开始,多分配一位
            this->_size = 0;
            this->nodes = new Node[this->capacity];
        }

        int size() {
            return this->_size;
        }

        bool empty() {
            return _size == 0;
        }

        // pos处开始,从底到顶调整最大堆
        void shiftUp(int pos) {
            while (true) {
                int parentPos = pos / 2;
                // 若父节点大于当前,则位置已满足
                if (parentPos < 1 || nodes[parentPos] >= nodes[pos]) {
                    break;
                }

                swap(nodes[pos],nodes[parentPos]);
                pos = parentPos;
            }
        }

        // pos处开始,从顶到底调整最大堆
        void shiftDown(int pos) {
            while (true) {
                if (pos >= _size) {
                    break;
                }

                // 左右节点索引
                int left = pos * 2;
                int right = left + 1;
                int newPos = pos; // 新要调整的位置,默认为pos
                // 判断左右节点节点是否有大于当前pos处
                if (left <= _size && nodes[left] > nodes[newPos]) { // 如果newPos处小于左节点
                    newPos = left; // 更新位置为 left
                }

                if (right <= _size && nodes[right] > nodes[newPos]) { //  如果newPos处小于右节点
                    newPos = right; // 更新位置为 right
                }

                if (newPos == pos) { // pos没变,说明此时已满足
                    break;
                }

                swap(nodes[newPos], nodes[pos]);
                pos = newPos;
            }
        }

        /**
         * 确保容量满足要求
         */
        void ensureCapacity() {
            if (_size < capacity) {
                std::cout << __func__ << " : no need extend!" << std::endl;
                return;
            }
            std::cout << __func__ << " : extend capacity!" << std::endl;

            // extend capacity
            int newCapacity = capacity * 2;
            Node *newNodes = new Node[newCapacity];
            for (int i = 1; i <= _size; ++i) {
                newNodes[i] = nodes[i];
            }

            delete[] nodes;
            capacity = newCapacity;
            nodes = newNodes;
        }

        /**
         *  插入元素
         * @param node
         * @return
         */
        bool insert(Node node) {
            // 添加到最后位置
            int index = ++_size;
            if (index > capacity) {
                ensureCapacity();
            }
            nodes[index] = node;
            // 从底到顶调整节点位置
            shiftUp(_size);

            return true;
        }

        /**
         * 取出最大值
         */
        Node extractMax() {
            if (empty()) {
                return nodes[0];
            }

            // 取出最大值
            Node max = nodes[1];
            if (_size > 1) {
                // 将最后一位,放到第一位
                nodes[1] = nodes[_size];
            }
            --_size; // 元素个数递减

            shiftDown(1); // 重新调整最大堆

            return max;
        }

        void print() {
            cout << "size=" << size() << " ,capacity=" << capacity << endl;

            for (int i = 1; i <= _size; ++i) {
                std::cout << nodes[i] << " ";
            }
            std::cout << std::endl;
        }
    };


}


#endif //SORTALGORITHM_MAXHEAP_H

