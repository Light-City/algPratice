//
// Created by light on 19-10-25.
//


#include "trie.h"

int main() {
    Trie *trie=new Trie();
    trie->_add("deer");
    trie->_add("door");
    trie->_add("dog");
    trie->_add("panda");
    trie->_add("pan");
    trie->_add("pan");
    cout<<trie->getSize()<<endl;    // 5
    cout<<trie->getVal("pan")<<endl;    // 2

    cout<<trie->contain("pan")<<endl;   // 1
    cout<<trie->_contain("door")<<endl; // 1

    cout<<trie->isPrefix("pan")<<endl;  // 1
    cout<<trie->_isPrefix("pan")<<endl; // 1

    cout<<trie->isPrefix("pag")<<endl;  // 0
    cout<<trie->_isPrefix("pag")<<endl; // 0

    trie->remove("deer");
    cout<<trie->_contain("deer")<<endl; // 0
    cout<<trie->_contain("dog")<<endl;  // 1
    cout<<trie->_contain("door")<<endl; // 1
    cout<<trie->getSize()<<endl;        // 4

    trie->remove("door");
    cout<<trie->_contain("door")<<endl; // 0
    cout<<trie->_contain("dog")<<endl;  // 1
    cout<<trie->getSize()<<endl;        // 3


    trie->remove("pan");
    cout<<trie->_contain("pan")<<endl;  // 0
    cout<<trie->_contain("panda")<<endl;// 1
    cout<<trie->getSize()<<endl;        // 2

    trie->remove("panda");
    cout<<trie->_contain("panda")<<endl;// 0
    cout<<trie->_contain("pan")<<endl;  // 0
    cout<<trie->getSize()<<endl;        // 1
    delete trie;
    return 0;
}

