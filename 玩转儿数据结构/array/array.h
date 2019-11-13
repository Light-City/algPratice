//
// Created by light on 19-10-31.
//

#ifndef ALG_ARRAY_H
#define ALG_ARRAY_H


#include <cassert>
#include <iostream>

using namespace std;


// 动态数组
template<class T>
class Array {
private:
    T *data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        T *newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        data = newData;
        capacity = newCapacity;
    }

    void init(int capacity) {
        this->data = new T[capacity];
        this->size = 0;
        this->capacity = capacity;
    }

public:

    Array(int capacity) {
        init(capacity);
    }

    Array() {
//        this->Array(5); error!!!
//        new(this)Array(5);
        init(5);
    }

    ~Array() {
        delete[]data;
        size=0;
        capacity=0;
        cout << "deconstruct\n";
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    // add  O(n)
    void add(int index, T e) {
        assert(index >= 0 && index <= size);
        if (size == capacity) {
            resize(2 * capacity);  // 均摊复杂度O(1)
        }
        for (int i = size - 1; i >= index; i--) {
            data[i + 1] = data[i];
        }
        data[index] = e;
        size++;
    }

    // addfirst O(n)
    void addFirst(T e) {
        add(0, e);
    }

    // addlast O(1)
    void addLast(T e) {
        add(size, e);
    }

    // get O(1)
    T get(int index) {
        assert(index >= 0 && index < size);
        return data[index];
    }

    // set O(1)
    void set(int index, T e) {
        assert(index >= 0 && index < size);
        data[index] = e;
    }

    // contains O(n)
    bool contains(T e) {
        for (int i = 0; i < size; i++)
            if (data[i] == e) return true;
        return false;
    }

    // O(n)
    int find(T e) {
        for (int i = 0; i < size; ++i) {
            if (data[i] == e) {
                return i;
            }
        }
        return -1;
    }

    // O(n)
    T remove(int index) {
        assert(index >= 0 && index < size);
        T ret = data[index];
        for (int i = index + 1; i < size; ++i) {
            data[i - 1] = data[i];
        }
        size--;
        if (size == capacity / 4 && capacity / 2 != 0) resize(capacity / 2);     // 防止复杂度震荡 lazy
        return ret;
    }

    // O(n)
    T removeFirst() {
        return remove(0);
    }

    // O(1)
    T removeLast() {
        return remove(size - 1);
    }

    // O(n)
    void removeElement(T e) {
        int index = find(e);
        if (index != -1) {
            remove(index);
        }
    }

    // O(1)
    T getFirst() {
        return get(0);
    }

    // O(1)
    T getLast() {
        return get(size - 1);
    }


    // 打印输出
    friend ostream &operator<<(ostream &out, Array &array) {
        out << "Array: size = " << array.getSize() << ", capacity = " << array.getCapacity() << endl;
        out << "[";
        for (int i = 0; i < array.size; i++) {
            out << array.data[i];
            if (i != array.size - 1)
                out << ", ";
        }
        out << "]" << endl;
        return out;
    }
};


#endif //ALG_ARRAY_H
