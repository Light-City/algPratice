//
// Created by light on 19-10-18.
//



#include <algorithm>
#include "../rbtree/rb_tree.h"
#include "../hash/hash.h"
#include "../avl/AVL.h"
#include "../file/FileOps.h"
#include "../set_map/BSTSet.h"
#include "../set_map/BSTMap.h"
#include "../set_map/LinkedListSet.h"
#include "../set_map/LinkedListMap.h"
#include "../set_map/SeqMap.h"
#include "../set_map/SeqSet.h"
#include "../queue/ArrayQueue.h"
#include "../queue/loopQueue.h"
#include "../queue/LinkedListQueue.h"
#include "../stack/ArrayStack.h"
#include "../stack/LinkedListStack.h"
#include "../linklist/LinkedList.h"

using namespace std;

template<typename T>
double testMap(T *map, string filename) {
    clock_t startTime = clock();
    srand(66);
    vector<string> words;
    if (FileOps::readFile(filename, words)) {
        std::cout << "Total words: " << words.size() << std::endl;
        for (string word : words) {
            if (map->contain(word)) {
                map->set(word, *(map->search(word)) + 1);
            } else {
                map->insert(word, 1);
            }
        }
        if (map->contain("labour"))
            cout << "'labour' : " << *(map->search("labour")) << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        map->remove("labour");      // remove返回值为树根
        if (map->contain("labour"))
            cout << "'labour' : " << *(map->search("labour")) << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
    }
    clock_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

template<typename T>
double testSet(T *set, string filename) {
    clock_t startTime = clock();
    srand(66);
    vector<string> words;
    if (FileOps::readFile(filename, words)) {
        std::cout << "Total words: " << words.size() << std::endl;
        for (string word : words) {
            set->insert(word);
        }
        std::cout << "Total different words: " << set->size() << std::endl;
    }
    clock_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

template<typename T>
double testQueue(BaseQueue<T> *q, int opCount) {
    clock_t startTime = clock();
    for (int i = 0; i < opCount; i++) {
        q->enqueue(i);
    }
    for (int i = 0; i < opCount; i++) {
        q->dequeue();
    }
    clock_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

template<typename T>
double testStack(CommonStack<T> *stack, int opCount) {
    clock_t startTime = clock();
    for (int i = 0; i < opCount; i++) {
        stack->push(i);
    }
    for (int i = 0; i < opCount; i++) {
        stack->pop();
    }
    clock_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

/**
 * 对于完全随机的数据,普通的二分搜索树很好用!
 * 缺点：极端情况退化成链表(或高度不平衡)
 * 对于查询较多的使用情况,AVL树很好用
 * 红黑树牺牲了平衡性(2longn的高度)
 * 统计性能更优(综合增删改查所有的操作)
 * @return
 */
int main() {

    // 我们使用文本量更小的共产主义宣言进行试验:)
    string filename = "/home/light/CLionProjects/alg/算法基础/file/communist.txt";
    vector<string> words;

    if (FileOps::readFile(filename, words)) {

        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

        // 测试1, 我们按照文本原有顺序插入进二分搜索树
        time_t startTime = clock();
        BST<string, int> *bst = new BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = (*bst).search(*iter);
            if (res == NULL)
                (*bst).insert(*iter, 1);
            else
                (*res)++;
        }
        vector<pair<string, int>> res1 = bst->_postOrder();
        cout << endl;
        vector<pair<string, int>> res2 = bst->postOrder();
        if (res1 != res2) cout << "not ok" << endl;
        else
            cout << "ok" << endl;

        // 我们查看labour一词的词频
        if (bst->contain("labour"))
            cout << "'labour' : " << *(*bst).search("labour") << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        time_t endTime = clock();

        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

        delete bst;


        // 测试2, 我们按照文本原有顺序插入顺序查找表
        startTime = clock();
        SequenceST<string, int> *sst = new SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = (*sst).search(*iter);
            if (res == NULL)
                (*sst).insert(*iter, 1);
            else
                (*res)++;
        }

        if (sst->contain("labour"))
            cout << "'labour' : " << *(*sst).search("labour") << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        int *value = sst->remove("labour");
        cout << *value << endl;
        // 我们查看labour一词的词频
        if (sst->contain("labour"))
            cout << "'labour' : " << *(*sst).search("labour") << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        endTime = clock();

        cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

        delete sst;


        // 测试3, 我们将原文本排序后插入二分搜索树, 查看其效率
        startTime = clock();
        BST<string, int> *bst2 = new BST<string, int>();

        sort(words.begin(), words.end());
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = (*bst2).search(*iter);
            if (res == NULL)
                (*bst2).insert(*iter, 1);
            else
                (*res)++;
        }

        // 我们查看labour一词的词频
        cout << "'labour' : " << *(*bst2).search("labour") << endl;
        endTime = clock();

        cout << "BST2 , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

        delete bst2;



        // 测试1, 我们按照文本原有顺序插入进二分搜索树
        startTime = clock();
        RBTree<string, int> *rbTree = new RBTree<string, int>();

        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = (*rbTree).search(*iter);
            if (res == NULL)
                (*rbTree).insert(*iter, 1);
            else
                (*res)++;
        }

        // 我们查看labour一词的词频
        if (rbTree->contain("labour"))
            cout << "'labour' : " << *(rbTree->search("labour")) << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
//
//        rbTree->insert(100, "v100");
//        rbTree->insert(50, "v50");
//        rbTree->insert(150, "v150");
//        rbTree->insert(20, "v20");
//        rbTree->insert(85, "v85");
//        rbTree->insert(10, "v10");
//        rbTree->insert(15, "a15");
//        rbTree->insert(75, "v75");
//        rbTree->insert(95, "v95");
//        rbTree->insert(65, "v65");
//        rbTree->insert(76, "v76");
//        rbTree->insert(60, "v60");
//        rbTree->insert(66, "v66");
//        rbTree->insert(61, "v61");

//        rbTree->levelOrder();
        endTime = clock();

        cout << "RBTree, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

        delete rbTree;


        startTime = clock();
        HashTable<string, int> *ht = new HashTable<string, int>(words.size());
        for (string word : words) {
            if (ht->contains(word)) {
                ht->set(word, ht->get(word) + 1);
            } else {
                ht->add(word, 1);
            }
        }
        if (ht->contains("labour"))
            cout << "'labour' : " << ht->get("labour") << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
//        int ret = ht->remove("labour");
//        cout << ret << endl;
//        cout << ht->getSize() << endl;
//        if (ht->contains("labour"))
//            cout << "'labour' : " << ht->get("labour") << endl;
//        else
//            cout << "No word 'labour' in " + filename << endl;
        endTime = clock();

        cout << "HashTable, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        delete ht;

        cout << endl;
        startTime = clock();
        AVL<string, int> *avlTree = new AVL<string, int>();


        for (string word : words) {
            if (avlTree->contain(word)) {
                avlTree->set(word, *(avlTree->search(word)) + 1);
            } else {
                avlTree->insert(word, 1);
            }
        }
        if (avlTree->contain("labour"))
            cout << "'labour' : " << *(avlTree->search("labour")) << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        avlTree->remove("labour");
        if (avlTree->contain("labour"))
            cout << "'labour' : " << *(avlTree->search("labour")) << endl;
        else
            cout << "No word 'labour' in " + filename << endl;
        std::cout << avlTree->isBST() << endl;
        std::cout << avlTree->isBalanced() << endl;
        endTime = clock();
        cout << "avlTree, time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        delete avlTree;
        cout << endl;


        LinkedListMap<string, int> *linkedListMap = new LinkedListMap<string, int>();
        float linkMapTime = testMap(linkedListMap, filename);
        std::cout << "linkMap time : " << linkMapTime << " s " << std::endl;
        delete linkedListMap;

        cout << endl;

        BSTMap<string, int> *bstMap = new BSTMap<string, int>();
        float bstMapTime = testMap(bstMap, filename);
        std::cout << "bstMap time : " << bstMapTime << " s " << std::endl;
        delete bstMap;

        cout << endl;


        SeqMap<string, int> *seqMap = new SeqMap<string, int>();
        float seqMapTime = testMap(seqMap, filename);
        std::cout << "seqMap time : " << seqMapTime << " s " << std::endl;
        delete seqMap;

        cout << endl;

        AVLMap<string, int> *avlMap = new AVLMap<string, int>();
        float avlMapTime = testMap(avlMap, filename);
        std::cout << "AVLMap time : " << avlMapTime << " s " << std::endl;
        delete avlMap;

        cout << endl;


        BSTSet<string> *bstSet = new BSTSet<string>();
        double time1 = testSet(bstSet, filename);
        std::cout << "BstSet time : " << time1 << " s " << std::endl;
        delete bstSet;

        cout << endl;

        LinkedListSet<string> *linkedListSet = new LinkedListSet<string>();
        double time2 = testSet(linkedListSet, filename);
        std::cout << "LinkedListSet time : " << time2 << " s " << std::endl;
        delete linkedListSet;

        cout << endl;

        SeqSet<string> *seqSet = new SeqSet<string>();
        double time3 = testSet(seqSet, filename);
        std::cout << "SeqSet time : " << time3 << " s " << std::endl;
        delete seqSet;

        cout << endl;

        AVLSet<string> *avlSet = new AVLSet<string>();
        double time4 = testSet(avlSet, filename);
        std::cout << "AVLSet time : " << time4 << " s " << std::endl;

        delete avlSet;


        cout << endl;

        BaseQueue<int> *queue = new ArrayQueue<int>();
        BaseQueue<int> *lq = new loopQueue<int>();
        BaseQueue<int> *linkq = new LinkedListQueue<int>();
        int opCount = 100000;
        cout << "queue time " << endl;
        cout << testQueue(queue, opCount) << endl;
        cout << "loopQueue time " << endl;
        cout << testQueue(lq, opCount) << endl;
        cout << "LinkedListQueue time " << endl;
        cout << testQueue(linkq, opCount) << endl;
        delete queue;
        delete lq;
        delete linkq;

        cout << endl;

        CommonStack<int> *stack = new ArrayStack<int>();
        LinkedListStack<int> *linkedListStack = new LinkedListStack<int>();
        cout << "array stack time " << endl;
        cout << testStack(stack, opCount) << endl;
        cout << "linkedList stack time " << endl;
        cout << testStack(linkedListStack, opCount) << endl;
        delete stack;
        delete linkedListStack;
    }
    vector<int> a = {1, 23};
    vector<int> b = {2, 23};
    return 0;
}