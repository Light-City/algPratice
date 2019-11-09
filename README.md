## 0.导语

本仓库学习自波波老师的慕课网课程《玩转儿数据结构》，由于官方为JAVA版本，但是本人用的C++，因此将自己的C++笔记放到下面。

课程链接：https://coding.imooc.com/class/207.html

后面将更新波波老师的其他课程学习笔记。

## 1.玩转数据结构 从入门到进阶C++版

- 动态数组

  - [动态数组实现](./玩转儿数据结构/array/array.h)
  - [动态数组测试](./玩转儿数据结构/array/array.cpp)

  学习要点：动态数组的增删改查、时间复杂度、防止复杂度震荡策略。

- 栈和队列

  - 栈

    - [栈的公共接口](./玩转儿数据结构/interface.h)
    - [基于底层为动态数组的栈实现](./玩转儿数据结构/stack/ArrayStack.h)
    - [基于底层为链表的栈实现](./玩转儿数据结构/stack/LinkedListStack.h)
    - [栈的测试](./玩转儿数据结构/test/Tamin.cpp)
    - [LeetCode20题](./玩转儿数据结构/stack/20isValid.cpp)

    学习要点：使用组合方案来完成栈的底层数据结构为数组，定义栈的入栈与出队策略。

  - 队列

    - [队列的公共接口](./玩转儿数据结构/interface.h)
    - [基于底层为动态数组的队列实现](./玩转儿数据结构/queue/ArrayQueue.h)
    - [基于底层为动态数组的循环队实现](./玩转儿数据结构/queue/loopQueue.h/)
    - [基于底层为链表的队列实现](./玩转儿数据结构/stack/LinkedListQueue.h)
    - [队列的测试](./玩转儿数据结构/test/Tamin.cpp)

    学习要点：多种底层实现的效率对比，接口的定义，定义队列的入队与出队策略。

- 链表

  - [链表的实现](./玩转儿数据结构/linklist/LinkedList.h)
  - [链表栈实现](./玩转儿数据结构/stack/LinkedListStack.h)
  - [链表队列实现](./玩转儿数据结构/stack/LinkedListQueue.h)
  - [链表、链表栈、链表队列实现](./玩转儿数据结构/linklist/LinkedList.cpp)
  - [LeetCode203题不带与带dummyHead两种实现](./玩转儿数据结构/linklist/203ListNode.cpp)
  - [LeetCode203题递归实现](./玩转儿数据结构/recursion/203ListNode.cpp)
  - [求和递归实现](./玩转儿数据结构/recursion/recursion.cpp)

  学习要点：链表内部节点结构定义、dummyHead使用、时间复杂度分析、链表栈与链表队列实现。z掌握递归的宏观与微观、如何对递归进行测试。

- 二分搜索树

  - [二分搜索树实现](./玩转儿数据结构/bst/BST.h)

  - [二分搜索树测试](./玩转儿数据结构/bst/BST.cpp)

    - 补充
      - [顺序查找表实现](./玩转儿数据结构/bst/SequenceST.h)
      - [二分查找法实现](./玩转儿数据结构/binarySearch/BinarySearch.cpp)
      - [基于floor与ceil的二分查找法实现](./玩转儿数据结构/binarySearch/floor_ceil_BinarySearch.cpp)

    

  学习要点：掌握二分搜索树的结构、四种遍历方式的递归与非递归，bst树中最大与最小节点，删除节点原则，拓展二分查找法与基于floo、ceil的实现，当bst树退化为链表的时候对应的顺序查找表实现，顺序查找表与二分搜索树的效率对比。

- 集合与映射

  - 集合

    - [集合接口](./玩转儿数据结构/interface.h)
    - [基于底层为二分搜索树的集合](./玩转儿数据结构/set_map/BSTSet.h)
    - [基于底层为链表的集合](./玩转儿数据结构/set_map/LinkedListSet.h)
    - [LeetCode804问题](./玩转儿数据结构/set_map/804uniqueMorseRepresentations.cpp)
    - 拓展
      - [基于底层为顺序查找表的集合](./玩转儿数据结构/set_map/SeqSet.h)

    学习要点：集合接口定义、二分搜索树与链表集合的效率对比。

  - 映射

    - [映射接口](./玩转儿数据结构/interface.h)
    - [基于底层为二分搜索树的映射](./玩转儿数据结构/set_map/BSTMap.h)
    - [基于底层为链表的映射](./玩转儿数据结构/set_map/LinkedListSet.h)
    - [LeetCode804问题](./玩转儿数据结构/set_map/804uniqueMorseRepresentations.cpp)
    - 拓展
      - [基于底层为顺序查找表的映射](./玩转儿数据结构/set_map/LinkedListMap.h)

    学习要点：映射接口定义、二分搜索树与链表映射的效率对比。学会什么时候用映射，什么时候用集合。

- 优先队列和堆

  - [基于动态数组的大顶堆实现](./玩转儿数据结构/heap/heap.h)
  - [基于底层为大顶堆的优先队列实现](./玩转儿数据结构/heap/PriorityQueue.h)
  - [大顶堆与优先队列测试](./玩转儿数据结构/heap/heap.cpp)
  - [使用C++ STL的优先队列解LeetCode347题](./玩转儿数据结构/347topKFrequent.cpp)
  - [使用我们自己的优先队列解LeetCode347题](./玩转儿数据结构/347_local.cpp)

  学习要点：堆的sift up与sift down、heapify、堆与优先队列的关系、如何使用STL的大顶堆与小顶堆、如何使用自己的优先队列解题。

- 线段树

  - [基于动态数组的线段树实现](./玩转儿数据结构/segmenttree/segment.h)
  - [线段树测试](./玩转儿数据结构/segmenttree/segment.cpp)
  - [LeetCode303题](./玩转儿数据结构/segmenttree/303NumArray.cpp)
  - [LeetCode307题](./玩转儿数据结构/segmenttree/307NumArray.cpp)

  学习要点：掌握线段树的概念与应用，经典应用区间更新查询等，学会使用动态数组作为线段树的底层数据结构，掌握开辟多大空间存储。掌握其不是完全二叉树也不是满二叉树，但是平衡二叉树,依然可以用数组表示,看做满二叉树,后面不存在的节点在数组中用空来表示即可。

- 字典树

  - [字典树的实现](./玩转儿数据结构/trie/trie.h)
  - [LeetCode211题](./玩转儿数据结构/trie/211WordDictionary.cpp)
  - [LeetCode677题](./玩转儿数据结构/trie/677MapSum.cpp)

  学习要点：掌握字典树节点定义，学会使用自己的字典树解题。

- 并查集

  - [基于动态数组的并查集六种实现](./玩转儿数据结构/unionfind/unionfind.h)
  - [并查集测试](./玩转儿数据结构/unionfind/unionfind.cpp)

  学习要点：quickfind、基于树高度优化的并查集、基于树的大小(只是当前父亲节点+孩子节点总数)优化、基于rank(树的深度)的优化、路径压缩1、路径压缩2。

- 平衡树AVL

  - [AVL实现](./玩转儿数据结构/avl/AVL.h)
  - [AVL测试](./玩转儿数据结构/test/Tmain.cpp)

  学习要点：左旋转、右旋转、平衡因子维护等。

- 红黑树

  - [红黑树实现](./玩转儿数据结构/rbtree/rb_tree.h)
  - [红黑树测试](./玩转儿数据结构/rbtree/rbmain.cpp)

  学习要点：红黑树节点颜色标记、左旋转、右旋转、颜色翻转、插入节点颜色调整。

- 哈希表

  - [简单的哈希表](./玩转儿数据结构/hash/hash.h)
  - [简单的哈希表测试](./玩转儿数据结构/hash/hashMain.cpp)
  - [素数哈希函数的哈希表](./玩转儿数据结构/hash/hash_v2.h)
  - [素数哈希函数的哈希表测试](./玩转儿数据结构/hash/hashMain_v2.cpp)

  学习要点：哈希表动态扩容、哈希函数定义等。


## 2.其他

待更新。。。

## 关于作者

个人公众号：

![wechat](./img/wechat.jpg)

个人博客：http://light-city.club/

QQ：455954986