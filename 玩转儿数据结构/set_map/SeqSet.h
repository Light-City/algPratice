//
// Created by light on 19-11-9.
//

#ifndef ALG_SEQSET_H
#define ALG_SEQSET_H

template<typename Key>
class SeqSet : Set<Key> {
private:
    SequenceST<Key, Key> *sst;
public:
    SeqSet() {
        sst = new SequenceST<Key, Key>();
    }

    ~SeqSet() {
        if (sst)
            delete sst;
    }

    void insert(Key key) override {
        sst->insert(key, key);
    }

    void remove(Key key) override {
        sst->remove(key);
    }

    bool contain(Key key) override {
        return sst->contain(key);
    }


    int size() override {
        return sst->size();
    }

    bool isEmpty() override {
        return sst->isEmpty();
    }
};

#endif //ALG_SEQSET_H
