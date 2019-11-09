//
// Created by light on 19-10-29.
//

#ifndef ALG_INTERFACE_H
#define ALG_INTERFACE_H

template<typename T>
class CommonStack {
public:
    virtual int getSize() = 0;

    virtual bool isEmpty() = 0;

    virtual void push(T e) = 0;

    virtual void pop() = 0;

    virtual T peek() = 0;
};


template<typename T>
class BaseQueue {
public:

    virtual bool isEmpty() = 0;

    virtual int getSize() = 0;

    virtual void enqueue(T e) = 0;

    virtual T dequeue() = 0;

    virtual T getFront() = 0;
};

template<typename Key, typename Value>
class Map {
    virtual void insert(Key key, Value value) = 0;

    virtual Value *remove(Key key) = 0;

    virtual bool contain(Key key) = 0;

    virtual Value *search(Key key) = 0;

    virtual void set(Key key, Value value) = 0;

    virtual int size() = 0;

    virtual bool isEmpty() = 0;
};

template<typename Key>
class Set {
    virtual void insert(Key key) = 0;

    virtual void remove(Key key) = 0;

    virtual bool contain(Key key) = 0;

    virtual int size() = 0;

    virtual bool isEmpty() = 0;

};


#endif //ALG_INTERFACE_H
