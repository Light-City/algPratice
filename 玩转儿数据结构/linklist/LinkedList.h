//
// Created by light on 19-11-8.
//

#include <iostream>

#include "../interface.h"

using namespace std;
#ifndef ALG_LINKEDLIST_H
#define ALG_LINKEDLIST_H

template<typename T>
class LinkedList {
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

    Node *dummyHead;
    int size;
public:
    LinkedList() {
        T dummyVal;
        dummyHead = new Node(dummyVal);
        size = 0;
    }

    ~LinkedList() {
        Node *cur = dummyHead;
        while (cur) {
            delete cur;
            size--;
            cur = cur->next;
        }
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    // O(n)
    void add(int index, T e) {
        if (index < 0 || index > size)
            throw "add failed. Illegal index.";

        Node *prev = dummyHead;
        for (int i = 0; i < index; i++) {
            prev = prev->next;
        }
//            Node *node = new Node(e);
//            node->next = prev->next;
//            prev->next = node;
        prev->next = new Node(e, prev->next);
        size++;
    }

    // O(1)
    void addFirst(T e) {
        add(0, e);
    }

    // O(n)
    void addLast(T e) {
        add(size, e);
    }

    // O(n)
    T get(int index) {
        if (index < 0 || index >= size)
            throw "get failed.Illegal index. ";
        Node *cur = dummyHead->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->e;
    }

    T getFirst() {
        return get(0);
    }

    T getLast() {
        return get(size - 1);
    }

    // O(n)
    bool contains(T e) {
        Node *cur = dummyHead->next;
        while (cur) {
            if (cur->e == e)
                return true;
            cur = cur->next;
        }
        return false;
    }

    // O(n)
    T remove(int index) {
        if (index < 0 || index >= size)
            throw "Remove failed.Illegal index. ";
        Node *prev = dummyHead;
        for (int i = 0; i < index; i++) {
            prev = prev->next;
        }
        Node *retNode = prev->next;
        prev->next = retNode->next;
        retNode->next = NULL;
        size--;
        return retNode->e;
    }

    // O(1)
    T removeFirst() {
        return remove(0);
    }

    // O(n)
    T removeLast() {
        return remove(size - 1);
    }

    void removeElement(T e) {
        Node *prev = dummyHead;
        while (prev->next)
            if (prev->next->e == e) {
                size--;
                prev->next = prev->next->next;
            } else
                prev = prev->next;
        return;
    }

    friend ostream &operator<<(ostream &out, LinkedList &linkedList) {
        Node *cur = linkedList.dummyHead->next;
        while (cur) {
            out << cur->e << "->";
            cur = cur->next;
        }
        out << "NULL" << endl;
        return out;
    }
};

#endif //ALG_LINKEDLIST_H
