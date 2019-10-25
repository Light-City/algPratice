//
// Created by light on 19-10-25.
//

#ifndef ALG_TRIE_H
#define ALG_TRIE_H

#include <iostream>
#include <map>
using namespace std;


// 最大问题：空间
class Trie {
private:
    struct Node {        // Node节点并不需要存储当前字符是谁
        int value = 0;        // 当前节点的词频
        bool isWord = false;
        map<char, Node *> next;
    };
    Node *root;
    int size;
public:
    Trie() {
        root = new Node();
        size = 0;
    }

    // 获取 Trie中存储的单词数量
    int getSize() {
        return size;
    }

    // 获取单词的词频
    int getVal(string word) {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (cur->next.count(c) == 0) return 0;
            cur = cur->next.at(c);
        }
        return cur->value;
    }

    // 非递归
    // 添加新的单词word
    void add(string word) {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (cur->next.count(c) == 0)
                cur->next.insert(make_pair(c, new Node()));
            cur = cur->next.at(c);
        }
        if (cur->isWord == false) {   // 添加的是个新单词
            cur->isWord = true;
            cur->value = 1;
            size++;
        } else {        // 之前单词存在
            cur->value++;
        }
    }

    // 递归添加
    void _add(string word) {
        add(word, 0, root);
    }


    // 非递归 是否包含word
    bool contain(string word) {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            // not found
            if (cur->next.count(c) == 0) return false;
            cur = cur->next.at(c);
        }
        return cur->isWord;     // 比如trie树中有pandas 这个单词，但要查pan这个单词，此时应该返回cur->isWord，而不是true。
    }

    // 递归 是否包含word
    bool _contain(string word) {
        return contain(word, 0, root);
    }

    // 查询是否在Trie中有单词以prefix为前缀
    bool isPrefix(string prefix) {
        Node *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            char c = prefix[i];
            // not found
            if (cur->next.count(c) == 0) return false;
            cur = cur->next.at(c);
        }
        return true;
    }

    // 非递归查询是否在Trie中有单词以prefix为前缀
    bool _isPrefix(string prefix) {
        return isPrefix(prefix, 0, root);
    }

    void remove(string word) {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (cur->next.count(c) == 0) return;
            cur = cur->next.at(c);
        }
        // 到达删除被删除单词的最后一个字符
        if (cur->next.size() == 0) {       // 后面无节点,则自底向上删除
            __del(word, 0, root);
        } else {        // 后面有节点，直接标记当前节点不是单词即可
            cur->isWord = false;
        }
        size--;
        //恢复flag,否则只能删除1次，不能够连续删除！
        islast= false;
        isstop=false;
    }

    bool islast = false;   // 是否自底向上
    bool isstop = false;   // 是否停止向上删除
private:
    void __del(string word, int index, Node *node) {
        char c = word[index];
        if (word.size() - 1 == index) {
            islast = true;
            free(node->next.at(c));
            node->next.erase(c);
            return;
        }
        if (!isstop && islast) {
            if (node->next.size() >= 2 || node->isWord == true)
                isstop = true;
            free(node->next.at(c));
            node->next.erase(c);
        }
        __del(word, index + 1, node->next.at(c));
    }


    // 添加word
    void add(string word, int index, Node *node) {
        Node *cur = node;
        if (index == word.size()) {
            if (cur->isWord == false) {   // 添加的是个新单词
                cur->value = 1;
                cur->isWord = true;
                size++;
            } else {
                cur->value++;
            }
            return;
        }
        char c = word[index];
        if (cur->next.count(c) == 0)
            cur->next.insert(make_pair(c, new Node()));
        add(word, index + 1, node->next.at(c));
        return;
    }

    // 是否包含word
    bool contain(string word, int index, Node *node) {
        Node *cur = node;
        if (index == word.size())
            return cur->isWord;
        char c = word[index];
        if (cur->next.count(c) == 0)
            return false;
        return contain(word, index + 1, node->next.at(c));
    }

    // 是否包含前缀
    bool isPrefix(string word, int index, Node *node) {
        Node *cur = node;
        if (index == word.size())
            return true;
        char c = word[index];
        if (cur->next.count(c) == 0)
            return false;
        return isPrefix(word, index + 1, node->next.at(c));
    }
};


#endif //ALG_TRIE_H
