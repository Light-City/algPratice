//
// Created by light on 19-10-25.
//
#include <iostream>
#include <string>
#include <map>

using namespace std;

class WordDictionary {
private:
    struct Node {        // Node节点并不需要存储当前字符是谁
        bool isWord = false;
        map<char, Node *> next;
    };
    Node *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new Node();
    }

    ~WordDictionary() {
        destroy(root);
    }

    void destroy(Node *node) {
        if (node) {
            for (auto each:node->next)
                delete each.second;
            delete node;
        }
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (cur->next.count(c) == 0)
                cur->next.insert(make_pair(c, new Node()));
            cur = cur->next.at(c);
        }
        cur->isWord = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return match(root, word, 0);
    }

private:
    bool match(Node *node, string word, int index) {
        if (index == word.size())
            return node->isWord;
        char c = word[index];
        if (c != '.') {
            if (node->next.count(c) == 0) return false;
            return match(node->next.at(c), word, index + 1);
        } else {
            for (auto x:node->next)
                if (match(node->next.at(x.first), word, index + 1))
                    return true;
            return false;
        }
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */