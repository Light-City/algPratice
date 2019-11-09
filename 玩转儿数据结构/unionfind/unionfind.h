//
// Created by light on 19-10-26.
//

#ifndef ALG_UNIONFIND_H
#define ALG_UNIONFIND_H
/**
 * 网络中节点间的连接状态  网络是个抽象的概念
 * 数学中的集合类实现
 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class UF {
public:
    virtual int getSize() {};

    virtual bool isConnected(int p, int q) {};

    virtual void unionElements(int p, int q) {};
};

/**
 * 第一种UnionFind
 */
class UnionFind1 : public UF {
private:
    vector<int> id;
public:
    UnionFind1(int size) {
        id = vector<int>(size);
        // 每个id属于不同的集合
        for (int i = 0; i < id.size(); i++)
            id[i] = i;
    }

    int getSize() {
        return id.size();
    }

private:
    // 查找元素p对应的集合编号 quickfind find O(1)
    int find(int p) {
        assert(p >= 0 && p < id.size());
        return id[p];
    }

public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // quick find union O(n) 合并元素p和元素q所属的集合
    virtual void unionElements(int p, int q) {
        int pId = find(p);
        int qId = find(q);

        if (pId == qId) return;
        // 将pId的所有pId更换为qId 最终p与q所属集合的所有元素都与q所属集合一致
        for (int i = 0; i < id.size(); i++)
            if (id[i] == pId) id[i] = qId;
    }
};

/**
 * 第二种UnionFind
 * 查询与合并的时间复杂度都为O(h) h远远小于n h为树的高度
 */
class UnionFind2 : public UF {
private:
    vector<int> parent;
public:
    UnionFind2(int size) {
        parent = vector<int>(size);
        for (int i = 0; i < parent.size(); i++)
            parent[i] = i;
    }

    int getSize() {
        return parent.size();
    }

private:
    // 递归
    // 查找元素p的根节点 quickfind find O(h)  h<n
    int find(int p) {
        assert(p >= 0 && p < parent.size());
        if (parent[p] == p)
            return p;
        return find(parent[p]);
    }

    // 非递归
    int _find(int p) {
        assert(p >= 0 && p < parent.size());
        while (parent[p] != p)
            p = parent[p];
        return p;
    }

public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // union O(h) h肯定小于n 故union要快 合并元素p的根节点与元素q的根节点
    virtual void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) return;
        parent[pRoot] = qRoot;
    }

};

/**
 * 第三种 基于树的大小(只是当前父亲节点+孩子节点总数)优化
 */
class UnionFind3 : public UF {
private:
    vector<int> parent;
    vector<int> sz; // sz[i]表示以i为根的集合中元素个数
public:
    UnionFind3(int size) {
        parent = vector<int>(size);
        sz = vector<int>(size);
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
            sz[i] = 1;
        }

    }

    int getSize() {
        return parent.size();
    }

private:
    // 递归
    // 查找元素p的根节点 quickfind find O(h)  h<n
    int find(int p) {
        assert(p >= 0 && p < parent.size());
        if (parent[p] == p)
            return p;
        return find(parent[p]);
    }

    // 非递归
    int _find(int p) {
        assert(p >= 0 && p < parent.size());
        while (parent[p] != p)
            p = parent[p];
        return p;
    }

public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // union O(h) h肯定小于n 故union要快 合并元素p的根节点与元素q的根节点
    virtual void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) return;
        // 根据两个元素所在树的元素个数不同判断合并方向
        // 将元素少的集合合并到元素多的集合上
        if (sz[pRoot] < sz[qRoot]) {
            parent[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        } else {
            parent[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
    }
};

/**
 * 基于rank(树的深度)的优化
 */
class UnionFind4 : public UF {
private:
    vector<int> parent;
    vector<int> rank; // rank[i]表示根节点为i的树的高度
public:
    UnionFind4(int size) {
        parent = vector<int>(size);
        rank = vector<int>(size);
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
            rank[i] = 1;
        }

    }

    int getSize() {
        return parent.size();
    }

private:
    // 递归
    // 查找元素p的根节点 quickfind find O(h)  h<n
    int find(int p) {
        assert(p >= 0 && p < parent.size());
        if (parent[p] == p)
            return p;
        return find(parent[p]);
    }

    // 非递归
    int _find(int p) {
        assert(p >= 0 && p < parent.size());
        while (parent[p] != p)
            p = parent[p];
        return p;
    }

public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // union O(h) h肯定小于n 故union要快 合并元素p的根节点与元素q的根节点
    virtual void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) return;
        // 根据两个元素所在树的rank不同判断合并方向
        // 将rank低的集合合并到rank高的集合上
        if (rank[pRoot] < rank[qRoot])
            parent[pRoot] = qRoot;
        else if (rank[qRoot] < rank[pRoot])
            parent[qRoot] = pRoot;
        else {  // rank[pRoot] == rank[qRoot]
            parent[qRoot] = pRoot;
            rank[pRoot] += 1;
        }
    }
};

/**
 * 第五种 路径压缩
 */
class UnionFind5 : public UF {
private:
    vector<int> parent;
    vector<int> rank; // rank[i]表示根节点为i的树的高度 此时不同于第四种方法 并不实际反应高度值
public:
    UnionFind5(int size) {
        parent = vector<int>(size);
        rank = vector<int>(size);
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
            rank[i] = 1;
        }

    }

    int getSize() {
        return parent.size();
    }

private:
    // 递归
    // 查找元素p的根节点 quickfind find O(h)  h<n
    int find(int p) {
        assert(p >= 0 && p < parent.size());
        if (parent[p] == p)
            return p;
        parent[p] = parent[parent[p]];        // add this line    不需要维护rank
        return find(parent[p]);
    }

    // 非递归
    int _find(int p) {
        assert(p >= 0 && p < parent.size());
        while (parent[p] != p) {
            parent[p] = parent[parent[p]];        // add this line    不需要维护rank
            p = parent[p];
        }
        return p;
    }

public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // union O(h) h肯定小于n 故union要快 合并元素p的根节点与元素q的根节点
    virtual void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) return;
        // 根据两个元素所在树的rank不同判断合并方向
        // 将rank低的集合合并到rank高的集合上
        if (rank[pRoot] < rank[qRoot])
            parent[pRoot] = qRoot;
        else if (rank[qRoot] < rank[pRoot])
            parent[qRoot] = pRoot;
        else {  // rank[pRoot] == rank[qRoot]
            parent[qRoot] = pRoot;
            rank[pRoot] += 1;
        }
    }
};

/**
 * 第六种 路径压缩
 */
class UnionFind6 : public UF {
private:
    vector<int> parent;
    vector<int> rank; // rank[i]表示根节点为i的树的高度 此时不同于第四种方法 并不实际反应高度值
public:
    UnionFind6(int size) {
        parent = vector<int>(size);
        rank = vector<int>(size);
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
            rank[i] = 1;
        }

    }

    int getSize() {
        return parent.size();
    }

private:
    // 递归
    // 查找元素p的根节点 quickfind find O(h)  h<n
    int find(int p) {
        assert(p >= 0 && p < parent.size());
        if (parent[p] != p)
            parent[p] = find(parent[p]);        // 直接指向根节点
        return parent[p];
    }


public:
    virtual bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // union O(h) h肯定小于n 故union要快 合并元素p的根节点与元素q的根节点
    virtual void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) return;
        // 根据两个元素所在树的rank不同判断合并方向
        // 将rank低的集合合并到rank高的集合上
        if (rank[pRoot] < rank[qRoot])
            parent[pRoot] = qRoot;
        else if (rank[qRoot] < rank[pRoot])
            parent[qRoot] = pRoot;
        else {  // rank[pRoot] == rank[qRoot]
            parent[qRoot] = pRoot;
            rank[pRoot] += 1;
        }
    }
};


#endif //ALG_UNIONFIND_H
