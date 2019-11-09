//
// Created by light on 19-10-28.
//

#ifndef ALG_SEGMENT_H
#define ALG_SEGMENT_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
class Merge {
public:
    virtual T merge(T a, T b) = 0;
};

template<typename T, typename Merge>
class SegmentTree {
private:
    vector<T> data;
    vector<T> tree;
public:
    SegmentTree(const vector<T> &arr) {
        data = arr;
        tree = vector<T>(4 * arr.size(), 0);
        if (data.size() > 0)
            buildSegmentTree(0, 0, data.size() - 1);
    }

    T get(int index) {
        if (index < 0 || index >= data.size())
            throw "index is illegal";
        return data[index];
    }

    Merge m;

    // 线段树 查询操作  log(n)
    T query(int queryL, int queryR) {
        assert(queryL >= 0 && queryR < data.size() && queryL <= queryR);
        return query(0, 0, data.size() - 1, queryL, queryR);
    }

    // 将index位置的值,更新为value log(n)
    void set(int index, T value) {
        if (index < 0 || index >= data.size())
            throw "index is illegal";
        data[index] = value;
        set(0, 0, data.size() - 1, index, value);
    }

private:
    // 返回完全二叉树的数组表示中，,一个索引表示的元素的左孩子节点的索引
    int leftChild(int index) {
        return 2 * index + 1;
    }

    // 返回完全二叉树的数组表示中，,一个索引表示的元素的右孩子节点的索引
    int rightChild(int index) {
        return 2 * index + 2;
    }

    // 在treeIndex的位置创建表示区间[l,..r]的线段树
    void buildSegmentTree(int treeIndex, int l, int r) {
        if (l == r) {
            tree[treeIndex] = data[l];
            return;
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        // [l,mid]
        buildSegmentTree(leftTreeIndex, l, mid);
        // [mid+1,r]
        buildSegmentTree(rightTreeIndex, mid + 1, r);

        tree[treeIndex] = m.merge(tree[leftTreeIndex], tree[rightTreeIndex]);   // 具体merge 比如求和
    }

    void set(int treeIndex, int l, int r, int index, int value) {
        if (l == r) {
            tree[treeIndex] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        if (index >= mid + 1) set(rightTreeIndex, mid + 1, r, index, value);
        else set(leftTreeIndex, l, mid, index, value);
        tree[treeIndex] = m.merge(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    template<typename E, typename M>
    friend ostream &operator<<(ostream &cout, SegmentTree<E, M> &segmentTree);

private:
    // 在以treeId为根的线段树中[l...r]的范围里,搜索区间[queryL...queryR]的值
    T query(int treeIndex, int l, int r, int queryL, int queryR) {
        // 递归终止条件
        if (l == queryL && r == queryR)
            return tree[treeIndex];

        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);

        if (queryL >= mid + 1)
            return query(rightTreeIndex, mid + 1, r, queryL, queryR);
        else if (queryR <= mid)
            return query(leftTreeIndex, l, mid, queryL, queryR);
        T leftRes = query(leftTreeIndex, l, mid, queryL, mid);
        T rightRes = query(rightTreeIndex, mid + 1, r, mid + 1, queryR);
        // 如果取两边区间最大值,就掉max,做什么操作,就传什么操作的merge即可。
        return m.merge(leftRes, rightRes);
    }
};

template<typename E, typename M>
ostream &operator<<(ostream &out, SegmentTree<E, M> &segmentTree) {
    string res = "[";
    for (int i = 0; i < segmentTree.tree.size(); i++) {
        res += to_string(segmentTree.tree[i]);
        if (i != segmentTree.tree.size() - 1)
            res += ", ";
    }
    res += "]";
    out << res << endl;

    return out;
}

#endif //ALG_SEGMENT_H
