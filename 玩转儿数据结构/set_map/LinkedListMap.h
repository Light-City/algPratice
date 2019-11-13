//
// Created by light on 19-11-8.
//

#ifndef ALG_LINKEDLISTMAP_H
#define ALG_LINKEDLISTMAP_H

template<typename Key, typename Value>
class LinkedListMap : public Map<Key, Value> {
private:
    class Node {
    public:
        Key key;
        Value value;
        Node *next;

        Node(Key key, Value value, Node *next) : key(key), value(value), next(next) {}

        Node() {
            Key key;
            Value value;
            new(this)Node(key, value, NULL);
        }

        friend ostream &operator<<(ostream &out, Node &node) {
            out << node.key << ":" << node.value << endl;
            return out;
        }
    };

    Node *dummyHead;
    int count;
public:
    LinkedListMap() {
        dummyHead = new Node();
    }

    ~LinkedListMap() {
        Node *cur = dummyHead;
        while (cur) {
            delete cur;
            cur = cur->next;
            count--;
        }
    }

    virtual int size() {
        return count;
    }

    virtual bool isEmpty() {
        return count == 0;
    }


    virtual Node *getNode(Key key) {
        Node *cur = dummyHead->next;
        while (cur) {
            if (cur->key == key)
                return cur;
            cur = cur->next;
        }
        return NULL;
    }

    virtual bool contain(Key key) {
        return getNode(key);
    }

    virtual Value *search(Key key) {
        Node *node = getNode(key);
        return (node == NULL) ? NULL : &node->value;
    }

    virtual void insert(Key key, Value value) {
        Node *node = getNode(key);
        if (node == NULL) {
            dummyHead->next = new Node(key, value, dummyHead->next);        // 头插法
            count++;
        } else {
            node->value = value;
        }
    }

    virtual void set(Key key, Value value) {
        Node *node = getNode(key);
        if (node == NULL)
            throw "Key not found ";
        node->value = value;
    }

    virtual Value *remove(Key key) {
        Node *prev = dummyHead;
        while (prev->next) {
            if (prev->next->key == key)
                break;
            prev = prev->next;
        }
        if (prev->next) {
            Node *delNode = prev->next;
            prev->next = delNode->next;
            delNode->next = NULL;
            count--;
            return &delNode->value;
        }
        return NULL;
    }
};

#endif //ALG_LINKEDLISTMAP_H
