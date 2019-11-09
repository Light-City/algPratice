//
// Created by light on 19-11-8.
//

#ifndef ALG_LINKEDLISTSET_H
#define ALG_LINKEDLISTSET_H

#include "../linklist/LinkedList.h"

template<typename Key>
class LinkedListSet : public Set<Key> {
private:
    LinkedList<Key> *linkedList;
public:
    LinkedListSet() {
        linkedList = new LinkedList<Key>;
    }

    // O(n)
    virtual void insert(Key key) {
        if (!linkedList->contains(key)) linkedList->addFirst(key);
    }

    // O(n)
    virtual void remove(Key key) {
        linkedList->removeElement(key);
    }

    // O(n)
    virtual bool contain(Key key) {
        return linkedList->contains(key);
    }

    virtual int size() {
        return linkedList->getSize();
    }

    virtual bool isEmpty() {
        return linkedList->isEmpty();
    }
};

#endif //ALG_LINKEDLISTSET_H
