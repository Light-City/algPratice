//
// Created by light on 19-11-8.
//
#include "../interface.h"

#ifndef ALG_LINKEDLISTQUEUE_H
#define ALG_LINKEDLISTQUEUE_H


// 基于链表的队列
// 队尾插入 队首删除
template<typename T>
class LinkedListQueue : public BaseQueue<T> {
private:
    class Node {
    public:
        T e;
        Node *next;

        Node(T e, Node *next) : e(e), next(next) {}

        Node(T e) : e(e), next(NULL) {}

        friend ostream &operator<<(ostream &out, Node &node) {
            out << "node value is " << node.e << endl;
            return out;
        }
    };

    Node *head;
    Node *tail;
    int size;
public:
    LinkedListQueue() : head(NULL), tail(NULL), size(0) {

    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void enqueue(T e) {
        if (NULL == tail) {
            tail = new Node(e);
            head = tail;
        } else {
            tail->next = new Node(e);
            tail = tail->next;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty())
            throw "Cannot dequeue from an empty queue.";
        Node *retNode = head;
        head = head->next;
        retNode->next = NULL;
        if (head == NULL)
            tail == head;
        size--;
        return retNode->e;
    }

    T getFront() {
        if (isEmpty())
            throw "Cannot dequeue from an empty queue.";
        return head->e;
    }

    friend ostream &operator<<(ostream &out, LinkedListQueue &linkedListQueue) {
        out << "Queue:front ";
        Node *cur = linkedListQueue.head;
        while (cur != NULL) {
            out << cur->e << "->";
            cur = cur->next;
        }
        out << "NULL tail" << endl;
        return out;
    }
};

#endif //ALG_LINKEDLISTQUEUE_H
