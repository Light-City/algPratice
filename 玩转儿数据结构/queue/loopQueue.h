//
// Created by light on 19-11-9.
//

#ifndef ALG_LOOPQUEUE_H
#define ALG_LOOPQUEUE_H

// 基于动态数组的循环队列
template<typename T>
class loopQueue : public BaseQueue<T> {
private:
    T *data;
    int front, tail;
    int size;
    int capacity;
    int total;
public:
    loopQueue(int capacity) {
        this->data = new T[capacity + 1];  // 浪费了一个空间 (tail+1)%capacity=front 队满
        this->size = size;
        this->capacity = capacity;
        this->front = this->tail = 0;
        this->total = capacity + 1;
    }

    loopQueue() {
        this->capacity = 10;
        this->data = new T[capacity + 1];  // 浪费了一个空间 (tail+1)%capacity=front 队满
        this->size = 0;
        this->front = this->tail = 0;
        this->total = capacity + 1;
    }

    T getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return front == tail;
    }

    int getSize() {
        return size;
    }

    void enqueue(T e) {
        if ((tail + 1) % total == front) {
            resize(getCapacity() * 2);
        }
        data[tail] = e;
        tail = (tail + 1) % total;
        size++;
    }

    void resize(int newCapacity) {
        T *newData = new T[newCapacity + 1];
        for (int i = 0; i < size; i++)
            newData[i] = data[(i + front) % total];
        capacity = newCapacity;
        total = capacity + 1;
        data = newData;
        front = 0;
        tail = size;
    }

    T dequeue() {
        if (isEmpty())
            throw "Cannot dequeue from an empty queue.";
        T ret = data[front];
        data[front] = NULL;
        front = (front + 1) % total;
        size--;
        if (size == getCapacity() / 4 && getCapacity() / 2 != 0)
            resize(getCapacity() / 2);
        return ret;
    }

    T getFront() {
        if (isEmpty())
            throw "Queue is Empty.";
        return data[front];
    }

    friend ostream &operator<<(ostream &out, loopQueue &lq) {
        out << "loopQueue: size = " << lq.getSize() << ", capacity = " << lq.getCapacity() << endl;
        out << "front [";
        for (int i = lq.front; i != lq.tail; i = (i + 1) % lq.total) {
            out << lq.data[i];
            if ((i + 1) % lq.total != lq.tail)
                out << ", ";
        }
        out << "] tail" << endl;
        return out;
    }
};

#endif //ALG_LOOPQUEUE_H
