//
// Created by light on 19-11-9.
//

#ifndef ALG_SEQMAP_H
#define ALG_SEQMAP_H

template<typename Key, typename Value>
class SeqMap : Map<Key, Value> {
private:
    SequenceST<Key, Value> *sst;
public:
    SeqMap() {
        sst = new SequenceST<Key, Value>();
    }

    ~SeqMap() {
        if (sst) {
            delete sst;
        }
    }

    void insert(Key key, Value value) override {
        sst->insert(key, value);
    }

    Value *remove(Key key) override {
        return sst->remove(key);
    }

    bool contain(Key key) override {
        return sst->contain(key);
    }

    Value *search(Key key) override {
        return sst->search(key);
    }

    void set(Key key, Value value) override {
        sst->set(key, value);
    }

    int size() override {
        return sst->size();
    }

    bool isEmpty() override {
        return sst->isEmpty();
    }
};

#endif //ALG_SEQMAP_H
