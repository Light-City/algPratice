//
// Created by light on 19-10-29.
//

#ifndef ALG_PRIORITYQUEUE_H
#define ALG_PRIORITYQUEUE_H

#include "../interface.h"
#include "heap.h"

template<typename T>
class PriorityQueue : BaseQueue<T> {
private:
    MaxHeap<T> maxHeap;
public:
    int getSize() override {
        return maxHeap.size();
    }

    void enqueue(T value) override {
        maxHeap.add(value);
    }

    T getFront() override {
        return maxHeap.findMax();
    }

    T dequeue() override {
        return maxHeap.extractMax();
    }

    bool isEmpty() override {
        return maxHeap.isEmpty();
    }


};

#endif //ALG_PRIORITYQUEUE_H
