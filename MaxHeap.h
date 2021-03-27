//
// Created by pecuyu on 2021/3/26.
//

#ifndef SORTALGORITHM_MAXHEAP_H
#define SORTALGORITHM_MAXHEAP_H

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
        Node* nodes; // 元素集, index从1开始到_size, 第0位不用
        int _size; // 实际元素个数
        int _capacity; // 实际最大容量(nodes长度) >=_size+1 , 每次容量不足递增2倍

        int availableSize() const { return _capacity > 1 ? _capacity - 1 : 0; }

    public:
        MaxHeap(int capacity) {
            this->_capacity = capacity + 1; // 元素index从1开始,多分配一位
            this->_size = 0;
            this->nodes = new Node[this->_capacity];
        }

        MaxHeap(Node array[], int length) { // 通过array构造一个最大堆
            this->_capacity = length + 1;
            nodes = new Node[this->_capacity];
            for (int i = 0; i < length; ++i) {
                nodes[i + 1] = array[i];
            }
            _size = length;

            // 对所有不满足最大堆要求的元素进行shiftDown操作,
            // 调整二叉树以满足最大堆要求
            for (int i = _size / 2; i > 0; --i) {
                shiftDownNoSwap(i);
            }
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

        // pos处开始,从底到顶调整最大堆
        // 减少swap, 提升效率
        void shiftUpNoSwap(int pos) {
            if (pos <= 1) {
                return;
            }

            int prevPos = pos;
            Node target = nodes[pos];
            int parentPos;
            while (true) {
                parentPos = pos / 2;
                // 若父节点大于当前,则位置已满足
                if (parentPos < 1 || nodes[parentPos] >= target) {
                    break;
                }

                nodes[pos] = nodes[parentPos]; // 移动父节点到当前
                pos = parentPos;
            }

            if (prevPos != pos) {
                nodes[pos] = target;
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

        // pos处开始,从顶到底调整最大堆
        // 减少swap, 提升效率
        void shiftDownNoSwap(int pos) {
            if (pos >= _size) {
                return;
            }

            int prevPos = pos;
            Node target = nodes[pos];
            int left;
            int right;
            int newPos; // 新要调整的位置,默认为pos
            bool hasBiggerChild = false;

            while (true) {
                if (pos >= _size) {
                    break;
                }

                // 左右节点索引
                left = pos * 2;
                right = left + 1;
                newPos = pos; // 新要调整的位置,默认为pos
                hasBiggerChild = false;
                // 判断左右节点节点是否有大于当前target处, 记录newPos
                /*if (right <= _size) { // 说明有2个child
                    bool leftBigger = nodes[left] > nodes[right];
                    if (leftBigger) {
                        if (nodes[left] > target) {
                            newPos = left;
                        }
                    } else if (nodes[right] > target) {
                        newPos = right;
                    }
                } else if (left <= _size) { // 有左节点
                    if (nodes[left] > target) {
                        newPos = left;
                    }
                } else { // 无子节点
                    break;
                }*/ // 上面注释掉的与下面两个比较功能类似

                if (left <= _size && nodes[left] > target) { // 如果newPos处小于左节点
                    hasBiggerChild = true;
                    newPos = left;
                }

                // 如果发现左节点大于target, 此时比较的时左右节点谁大. 否则判断右节点与target
                if (right <= _size && (hasBiggerChild ? // 此处说明left是否大于target
                            (nodes[right] > nodes[left]) :  // 若大于target,此时判断左右子节点谁大
                            (nodes[right] > target) /* 否则比较右节点和target的大小 */  )) {
                    //  如果newPos处小于右节点
                    newPos = right; // 更新位置为 right
                }

                if (newPos == pos) { // pos没变,说明此时已满足
                    break;
                }

                nodes[pos] = nodes[newPos]; // 将子节点移动到父节点位置
                pos = newPos;
            }

            if (prevPos != pos) {
                nodes[pos] = target;
            }
        }


        /**
         * 确保容量满足要求
         */
        void ensureCapacity() {
            if (_size < availableSize()) {
                std::cout << __func__ << " : no need extend!" << std::endl;
                return;
            }
            std::cout << __func__ << " : extend capacity!" << std::endl;

            // extend capacity
            int newCapacity = _capacity * 2;
            Node *newNodes = new Node[newCapacity];
            for (int i = 1; i <= _size; ++i) {
                newNodes[i] = nodes[i];
            }

            delete[] nodes;
            _capacity = newCapacity;
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
            if (index > availableSize()) {
                ensureCapacity();
            }
            nodes[index] = node;
            // 从底到顶调整节点位置
            shiftUpNoSwap(_size);

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

            shiftDownNoSwap(1); // 重新调整最大堆

            return max;
        }

        void print() {
            cout << "size=" << size() << " ,capacity=" << _capacity << endl;

            for (int i = 1; i <= _size; ++i) {
                std::cout << nodes[i] << " ";
            }
            std::cout << std::endl;
        }
    };


}


#endif //SORTALGORITHM_MAXHEAP_H

