//
// Created by light on 19-11-7.
//

#ifndef ALG_ARRAYSTACK_H
#define ALG_ARRAYSTACK_H

#include "../array/array.h"
#include "../interface.h"
#include "../stack/ArrayStack.h"


// 基于动态数组的Stack
template<typename T>
class ArrayStack : public CommonStack<T> {
private:
    Array<T> *array;
public:
    ArrayStack(int capacity) {
        array = new Array<T>(capacity);
    }

    ArrayStack() {
        array = new Array<T>();
    }

    ~ArrayStack() {
        delete[]array;
    }

    int getSize() {
        return array->getSize();
    }

    bool isEmpty() {
        return array->isEmpty();
    }

    int getCapacity() {
        return array->getCapacity();
    }

    // 入栈策略：尾部添加 O(1)
    void push(T e) {
        array->addLast(e);
    }

    // 出栈策略：尾部出  O(1)
    void pop() {
        array->removeLast();
    }

    // O(1)
    T peek() {
        return array->getLast();
    }

    friend ostream &operator<<(ostream &out, ArrayStack &stack) {
        out << *(stack.array);
        return out;
    }
};


#endif //ALG_ARRAYSTACK_H
