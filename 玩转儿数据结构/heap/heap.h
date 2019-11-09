//
// Created by light on 19-10-29.
//

#ifndef ALG_HEAP_H
#define ALG_HEAP_H

#include <vector>
#include <cassert>

using namespace std;
// 二叉堆是一棵完全二叉树


template<typename T>
class MaxHeap {
private:
    vector<T> data;

public:
    MaxHeap() {

    }

    MaxHeap(int capacity) {
        data = vector<T>(capacity);
    }

    // heapify : 将任意数组整理成堆的形状 时间复杂度O(n)
    // 直接把数组看成任意完全二叉树,从最后一个非叶节点开始sift down
    MaxHeap(const vector<T> &array) {
        data = array;
        T lastParent = parent(array.size() - 1);
        while (lastParent >= 0) {
            siftDown(lastParent);
            lastParent--;
        }
    }

    // 返回堆中的元素个数
    int size() {
        return data.size();
    }

    // 返回堆是否为空
    bool isEmpty() {
        return data.empty();
    }

    // 返回完全二叉树的数组表示中,一个索引所表示的元素的父亲节点的索引
    int parent(int index) {
        assert(index > 0);      // 根节点没有父亲
        return (index - 1) / 2;
    }

    // 返回完全二叉树的数组表示中,一个索引所表示的元素的左孩子节点的索引
    int leftChild(int index) {
        return 2 * index + 1;
    }

    // 返回完全二叉树的数组表示中,一个索引所表示的元素的右孩子节点的索引
    int rightChild(int index) {
        return 2 * index + 2;
    }

    // 向堆中添加元素 O(log(n))
    void add(T value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    // sift up 上浮
    void siftUp(int k) {
        while (k > 0 && data[parent(k)] < data[k]) {
            swap(k, parent(k));
            k = parent(k);
        }
    }

    void swap(int i, int j) {
        assert(i >= 0 && i < size() && j >= 0 && j < size());
        T t = data[i];
        data[i] = data[j];
        data[j] = t;
    }

    // 看堆中的最大元素
    T findMax() {
        assert(size() > 0);
        return data[0];
    }

    // 取出堆中最大元素 O(log(n))
    T extractMax() {
        T ret = findMax();

        swap(0, data.size() - 1);
        data.pop_back();
        siftDown(0);

        return ret;
    }

    void siftDown(int k) {
        while (leftChild(k) < data.size()) {
            int j = leftChild(k);
            if (j + 1 < data.size() && data[j + 1] > data[j]) j = rightChild(k); //j++
            // data[j]是此时leftChild 和 rightChild中的最大值
            if (data[k] > data[j]) break;
            swap(k, j);
            k = j;
        }
    }

    // replace : 取出最大元素后,放入一个新元素
    // 实现：可以先extractMax,再add,两次O(log(n))的操作
    // 实现: 可以直接将堆顶元素替换以后Sift Down,一次O(log(n))的操作
    // 取出堆中的最大元素,并且替换成元素value
    T replace(T value) {
        T ret = findMax();
        data[0] = value;
        siftDown(0);
        return ret;
    }


};


#endif //ALG_HEAP_H
