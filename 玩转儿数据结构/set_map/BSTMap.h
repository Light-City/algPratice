//
// Created by light on 19-11-8.
//

#ifndef ALG_BSTMAP_H
#define ALG_BSTMAP_H

// 有序集合
template<typename Key, typename Value>
class BSTMap : public Map<Key, Value> {
private:
    BST<Key, Value> bst;
public:
    BSTMap() {

    }

    virtual int size() {
        return bst.size();
    }

    virtual bool isEmpty() {
        return bst.isEmpty();
    }

    virtual bool contain(Key key) {
        return bst.contain(key);
    }

    virtual Value *search(Key key) {
        return bst.search(key);
    }

    virtual void set(Key key, Value value) {
        bst.set(key, value);
    }

    virtual void insert(Key key, Value value) {
        bst.insert(key, value);
    }

    virtual Value *remove(Key key) {
        return bst.remove(key);
    }

};

#endif //ALG_BSTMAP_H
