//
// Created by light on 19-11-8.
//

#ifndef ALG_LINKEDLISTSTACK_H
#define ALG_LINKEDLISTSTACK_H

#endif //ALG_LINKEDLISTSTACK_H

// 无序集合
template<typename T>
class LinkedListStack : public CommonStack<T> {
private:
    LinkedList<T> *linkedList;
public:

    LinkedListStack() {
        linkedList = new LinkedList<T>();
    }
    ~LinkedListStack() {
        delete linkedList;
    }
    int getSize() {
        return linkedList->getSize();
    }

    bool isEmpty() {
        return linkedList->isEmpty();
    }


    void push(T e) {
        linkedList->addFirst(e);
    }

    void pop() {
        linkedList->removeFirst();
    }

    T peek() {
        return linkedList->getFirst();
    }

    friend ostream &operator<<(ostream &out, LinkedListStack &linkedListStack) {
        out << *(linkedListStack.linkedList);
        return out;
    }
};
