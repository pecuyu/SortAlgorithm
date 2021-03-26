//
// Created by pecuyu on 2021/3/26.
//

#ifndef SORTALGORITHM_MAXHEAP_H
#define SORTALGORITHM_MAXHEAP_H

#include <iostream>
#include "SortAlgorithm.h"

namespace SortAlgorithm{

    template<typename Node>
    class MaxHeap {
    private:
        Node* nodes;
        int _size;
        int capacity;

    public:
        MaxHeap(int capacity){
            this->capacity = capacity + 1; // 元素index从1开始,多分配一位
            this->_size = 0;
            this->nodes = new Node[this->capacity];
        }

        int size(){
            return this->_size;
        }

        bool empty(){
            return _size == 0;
        }

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

        void ensureCapacity() {
            if (_size < capacity) {
                std::cout << __func__ << " : no need extend!" << std::endl;
                return;
            }
            std::cout << __func__ << " : extend capacity!" << std::endl;

            // extend capacity
            int newCapacity = capacity * 2;
            Node *newNodes = new Node[newCapacity];
            for (int i = 1; i < _size; ++i) {
                newNodes[i] = nodes[i];
            }

            delete[] nodes;
            capacity = newCapacity;
            nodes = newNodes;
        }

        bool insert(Node node){
            // 添加到最后位置
            int index = ++_size;
            if (index > capacity) {
                ensureCapacity();
            }
            nodes[index] = node;
            // 从底到顶跳转节点位置
            shiftUp(_size);
        }

        void print(){
            cout << "size=" << size() << " ,capacity=" << capacity << endl;

            for (int i = 1; i <= _size; ++i) {
                std::cout << nodes[i] << " " ;
            }
            std::cout << std::endl;
        }
    };


}


#endif //SORTALGORITHM_MAXHEAP_H

