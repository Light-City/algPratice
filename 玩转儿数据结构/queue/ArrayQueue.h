//
// Created by light on 19-11-7.
//

#ifndef ALG_ARRAYQUEUE_H
#define ALG_ARRAYQUEUE_H


#include "../array/array.h"
#include <cstring>

// 基于动态数组的单向队列
template<typename T>
class ArrayQueue : public BaseQueue<T> {
private:
    Array<T> *array;
public:
    ArrayQueue(int capacity) {
        array = new Array<T>(capacity);
    }

    ArrayQueue() {
        array = new Array<T>();
    }

    int getSize() {
        return array->getSize();
    }

    bool isEmpty() {
        return array->isEmpty();
    }

    T getCapacity() {
        return array->getCapacity();
    }
    // 入队： 尾部 O(1)
    void enqueue(T e) {
        array->addLast(e);
    }
    // 出队：头部 O(n)
    T dequeue() {
        return array->removeFirst();
    }

    T getFront() {
        return array->getFirst();
    }

    friend ostream &operator<<(ostream &out, ArrayQueue &queue) {
        out << *(queue.array);
        return out;
    }
};


#endif //ALG_ARRAYQUEUE_H
