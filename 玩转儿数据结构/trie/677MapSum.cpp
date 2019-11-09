//
// Created by light on 19-10-25.
//
#include <iostream>
#include <map>

using namespace std;

class MapSum {
private:
    struct Node {        // Node节点并不需要存储当前字符是谁
        int value = 0;      // key所对应的value
        map<char, Node *> next;
    };
    Node *root;
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new Node();
    }

    void insert(string key, int val) {
        Node *cur = root;
        for (int i = 0; i < key.size(); i++) {
            char c = key[i];
            if (cur->next.count(c) == 0)
                cur->next.insert(make_pair(c, new Node()));
            cur = cur->next.at(c);
        }
        cur->value = val;
    }
    /**
     * 先查找到prefix最后一个char的位置，再从这个char开始递归求和。
     * @param prefix
     * @return
     */
    int sum(string prefix) {
        Node *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            char c = prefix[i];
            if (cur->next.count(c) == 0) return 0;
            cur = cur->next.at(c);
        }
        return _sum(cur);
    }

private:
    int _sum(Node *node) {
        int res = node->value;
        for (auto x:node->next)
            res += _sum(x.second);
        return res;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */