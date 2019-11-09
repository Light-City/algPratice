//
// Created by light on 19-11-7.
//
#include "../bst/BST.h"
#include "../interface.h"

#ifndef ALG_BSTSET_H
#define ALG_BSTSET_H

// 有序集合
template<typename Key>
class BSTSet : public Set<Key> {
private:
    BST<Key, Key> bst;
public:
    // O(h) h=log(n)  最差O(n) 其他一样 这样的话就得用AVL
    virtual void insert(Key key) override {
        bst.insert(key, key);
    }
    // O(h)
    virtual void remove(Key key) override {
        bst.remove(key);
    }

    // O(h)
    virtual bool contain(Key key) override {
        bst.contain(key);
    }

    virtual int size() override {
        bst.size();
    }

    virtual bool isEmpty() override {
        bst.isEmpty();
    }
};


#endif //ALG_BSTSET_H
