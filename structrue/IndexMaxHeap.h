//
// Created by pecuyu on 2021/3/29.
//

#ifndef SORTALGORITHM_INDEXMAXHEAP_H
#define SORTALGORITHM_INDEXMAXHEAP_H

#include "../SortAlgorithm.h"

using SortAlgorithm::swap;

namespace Structures {
    /**
     *  索引最大堆, 父节点的元素始终保持 >= 子元素
     *  存储的元素从index=1开始 , 因此假若父节点的索引为pos, 则:
     *      左节点的index 为 2*pos
     *      有节点的index 为 2*pos + 1
     *
     *  indexs中的元素值表示 最大堆中nodes中元素的索引
     *  比较的时候使用原数组的元素 , 交换的时候使用的是indexs中的索引
     *
     *  对于 reverse 与 indexs 数组有如下规律
     *      reverse[i] = j
     *      indexs[j] =  i
     *
     *  根据以上可知:
     *      reverse[indexs[j]] = j    // indexs[j]替换i
     *      indexs[reverse[i]] = i    // reverse[i]替换j
     *
     * @tparam Node
     */
    template<typename Node>
    class IndexMaxHeap {
    private:
        Node* nodes; // 元素集, index从1开始到_size, 第0位不用
        int _size; // 实际元素个数
        int _capacity; // 实际最大容量(nodes长度) >=_size+1 , 每次容量不足递增2倍
        int* indexs;  // 索引堆, index的值表示在 nodes 数组的位置
        int* reverse; // 追踪indexs,记录的是indexs数组的索引. 第i位的值reverse[i]表示: 在indexs中值为i的索引
        int availableSize() const { return _capacity > 1 ? _capacity - 1 : 0; }

    public:
        IndexMaxHeap(int capacity) {
            this->_capacity = capacity + 1; // 元素index从1开始,多分配一位
            this->_size = 0;
            this->nodes = new Node[this->_capacity];
            this->indexs = new int[this->_capacity];
            this->reverse = new int[this->_capacity];
            for (int i = 0; i < this->_capacity; ++i) { // 初始化所有的值为0, 表示在indexs中没有对应的indexs,也就是元素不存在
                reverse[i] = 0;
            }
        }

        IndexMaxHeap(Node array[], int length) { // 通过array构造一个最大堆
            this->_capacity = length + 1;
            nodes = new Node[this->_capacity];
            indexs = new int[this->_capacity];
            reverse = new int[this->_capacity];
            for (int i = 0; i < length; ++i) {
                nodes[i + 1] = array[i];
                indexs[i + 1] = i + 1;
            }
            for (int i = 0; i < this->_capacity; ++i) { // 初始化所有的值为0, 表示在indexs中没有对应的indexs,也就是元素不存在
                reverse[i] = 0;
            }

            _size = length;

            // 对所有不满足最大堆要求的元素进行shiftDown操作,
            // 调整二叉树以满足最大堆要求
            for (int i = _size / 2; i > 0; --i) {
                shiftDownNoSwap(i);
            }
        }

        ~IndexMaxHeap(){
            delete[] nodes;
            delete[] indexs;
            delete[] reverse;
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
                if (parentPos < 1 || nodes[indexs[parentPos]] >= nodes[indexs[pos]]) {
                    break;
                }

                swap(indexs[pos],indexs[parentPos]);
                reverse[indexs[pos]] = pos;
                reverse[indexs[parentPos]] = parentPos;
                pos = parentPos;
            }
        }

        // pos处开始,从底到顶调整最大堆
        // 减少swap, 提升效率
        void shiftUpNoSwap(int pos) {
            if (pos <= 1) {
                return;
            }

            int prevNodePos = indexs[pos];
            Node target = nodes[prevNodePos];
            int parentPos;
            while (true) {
                parentPos = pos / 2;
                // 若父节点大于当前,则位置已满足
                if (parentPos < 1 || nodes[indexs[parentPos]] >= target) {
                    break;
                }

                indexs[pos] = indexs[parentPos]; // 移动父节点到当前
                reverse[indexs[pos]] = pos;
                pos = parentPos;
            }

            indexs[pos] = prevNodePos;
            reverse[prevNodePos] = pos;
        }


        // pos处开始,从顶到底调整最大堆
        void shiftDown(int pos) {
            // 左右节点索引
            int left = pos * 2;
            int right = left + 1;
            int newPos = pos; // 新要调整的位置,默认为pos

            while (left <= _size) { // 至少有一个子节点
                // 判断左右节点节点是否有大于当前pos处
                if (nodes[indexs[left]] > nodes[indexs[newPos]]) { // 如果newPos处小于左节点
                    newPos = left; // 更新位置为 left
                }

                if (right <= _size && nodes[indexs[right]] > nodes[indexs[newPos]]) { //  如果newPos处小于右节点
                    newPos = right; // 更新位置为 right
                }

                if (newPos == pos) { // pos没变,说明此时已满足
                    break;
                }

                swap(indexs[newPos], indexs[pos]);
                reverse[indexs[newPos]] = newPos;
                reverse[indexs[pos]] = pos;
                pos = newPos;
                left = pos * 2;
                right = left + 1;
            }
        }

        // pos处开始,从顶到底调整最大堆
        // 减少swap, 提升效率
        void shiftDownNoSwap(int pos) {
            if (pos >= _size) {
                return;
            }

            int prevNodePos = indexs[pos];
            Node target = nodes[prevNodePos];
            int left = pos * 2;  // 左右节点索引
            int right = left + 1;
            int newPos; // 新要调整的位置

            while (left <= _size) { // 至少需要一个子节点才继续
                newPos = left; // 新要调整的位置,默认为left
                // 判断左右节点节点是否有大于当前target处, 记录newPos
                if (right <= _size && nodes[indexs[right]] > nodes[indexs[left]]) {
                    newPos = right;
                }

                if (target >= nodes[indexs[newPos]]) { // >=所有子节点
                    break;
                }

                indexs[pos] = indexs[newPos]; // 将子节点移动到父节点位置, 移动索引
                reverse[indexs[pos]] = pos;
                pos = newPos;
                left = pos * 2;  // 左右节点索引
                right = left + 1;
            }

            indexs[pos] = prevNodePos;
            reverse[prevNodePos] = pos;
        }

        /**
         * pos处开始,从顶到底调整最大堆
         * @tparam T
         * @param array
         * @param pos 从当前位置开始调节最大堆
         * @param length array长度(调整堆的长度)
         */
        static void shiftDown(Node array[], int pos, int length) {
            assert(array != nullptr);
            assert(length > pos >= 0);

            Node target = array[pos];
            int left = pos * 2 + 1;
            int right = left + 1;
            int newPos;

            while (left < length) { // 至少有一个左元素才继续
                newPos = left;
                // 如果存在左右节点,让两者比较得出最大值
                if (right < length && array[right] > array[left]) {
                    newPos = right;
                }

                // 让当前的target和左右节点最大值进行比较
                if (target >= array[newPos]) {
                    break; // 比两者都大,跳出循环
                }

                array[pos] = array[newPos]; // 元素上移一位
                pos = newPos;
                left = pos * 2 + 1;
                right = left + 1;
            }

            array[pos] = target;
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
            int *newIndexs = new int[newCapacity];
            int *newReverse = new int[newCapacity];
            for (int i = 1; i <= _size; ++i) {
                newNodes[i] = nodes[i];
                newIndexs[i] = indexs[i];
                newReverse[i] = reverse[i];
            }

            _capacity = newCapacity;
            delete[] nodes;
            nodes = newNodes;
            delete[] indexs;
            indexs = newIndexs;
            delete[] reverse;
            reverse = newReverse;
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
            indexs[index] = index;
            reverse[index] = index;
            // 从底到顶调整节点位置
            shiftUpNoSwap(_size);

            return true;
        }

        /**
         * 插入指定位置, 若大于_size, 则尾部追加,否则替换指定pos的值
         * @param pos 映射到内部的索引, pos加1
         * @param newNode
         */
        void insert(int pos, Node newNode) {
            pos++; // 外界的index从0开始, 内部维护的index从1开始,因此需要加1
            if (pos > _size){ // 在末尾追加
                insert(newNode);
            } else { // 替换指定pos的值
                nodes[pos] = newNode;
                // 找到indexs中记录值为pos的index
                int index = reverse[pos]; //
                shiftUpNoSwap(index);
                shiftDownNoSwap(index);

                /*for (int i = 1; i <= _size; ++i) {
                    if (indexs[i] == pos) {
                        shiftUpNoSwap(i);
                        shiftDownNoSwap(i);
                        break;
                    }
                }*/
                
            }
        }

        /**
         * 取出最大值
         */
        Node extractMax() {
            if (empty()) {
                return nodes[indexs[0]];
            }

            // 取出最大值
            Node max = nodes[indexs[1]];
            if (_size > 1) {
                // 将最后一位,放到第一位
                indexs[1] = indexs[_size];
                reverse[indexs[1]] = 1;
                reverse[indexs[_size]] = 0; // 此元素不存在,index归0
            }
            --_size; // 元素个数递减

            shiftDownNoSwap(1); // 重新调整最大堆

            return max;
        }

        void printHeap() {
            cout << "size=" << size() << " ,capacity=" << _capacity << endl;

            for (int i = 1; i <= _size; ++i) {
                std::cout << nodes[indexs[i]] << "\t";
            }
            std::cout << std::endl;
        }

        void printNodes(){
            for (int i = 1; i <= _size; ++i) {
                std::cout << nodes[i] << "\t";
            }
            std::cout << std::endl;
        }

        void printIndexs(){
            for (int i = 1; i <= _size; ++i) {
                std::cout << indexs[i] << "\t";
            }
            std::cout << std::endl;
        }

        void printReverse(){
            for (int i = 1; i <= _size; ++i) {
                std::cout << reverse[i] << "\t";
            }
            std::cout << std::endl;
        }

    };


}



#endif //SORTALGORITHM_INDEXMAXHEAP_H
