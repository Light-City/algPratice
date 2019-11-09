//
// Created by light on 19-9-2.
//

#ifndef ALG_SEQUENCEST_H
#define ALG_SEQUENCEST_H

#include <iostream>
#include <cassert>
#include "../interface.h"

using namespace std;

// 顺序查找表实现
template<typename Key, typename Value>

class SequenceST {
private:
    struct Node {
        Key key;
        Value value;
        Node *next;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
    };

    Node *head; // 表头
    int count;  // 顺序查找表中的节点数
public:
    // 构造函数
    SequenceST() {
        head = NULL;
        count = 0;
    }

    // 析构函数
    ~SequenceST() {
        while (head) {
            Node *node = head;
            head = head->next;
            delete node;
            count--;
        }
        assert(head == NULL && count == 0);
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Key key, Value value) {
        Node *node = head;
        while (node) {
            if (key == node->key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        Node *newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
        count++;
    }

    void set(Key key, Value value) {
        Node *node = head;
        while (node) {
            if (key == node->key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
    }

    bool contain(Key key) {
        Node *node = head;
        while (node) {
            if (key == node->key)
                return true;
            node = node->next;
        }
        return false;
    }

    Value *search(Key key) {
        Node *node = head;
        while (node) {
            if (key == node->key)
                return &node->value;
            node = node->next;
        }
        return NULL;
    }

    Value *remove(Key key) {
        if (head == NULL) return nullptr;

        // 第一个节点就满足删除节点条件，保留后继节点并删除当前节点
        if (key == head->key) {
            Node *delNode = head;
            head = head->next;
            count--;
            return &delNode->value;
        }

        Node *node = head;
        while (node->next && node->next->key != key) {
            node = node->next;
        }
        if (node->next) {
            Node *delNode = node->next;
            node->next = delNode->next;
            count--;
            return &delNode->value;
        }
    }
};






#endif //ALG_SEQUENCEST_H
