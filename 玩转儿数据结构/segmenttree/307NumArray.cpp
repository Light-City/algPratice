//
// Created by light on 19-10-28.
//
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;
/**
 * 使用线段树
 */
class NumArray {
private:
    vector<int> data;
    vector<int> tree;
public:
    NumArray(vector<int> &nums) {
        data = nums;
        tree = vector<int>(4 * data.size());
        if (data.size() > 0)
            buildSegmentTree(0, 0, data.size() - 1);
    }

    void update(int index, int value) {
        if (index < 0 || index >= data.size())
            throw "index is illegal";
        data[index] = value;
        set(0, 0, data.size() - 1, index, value);
    }

    void set(int treeIndex, int l, int r, int index, int value) {
        if (l == r) {
            tree[treeIndex] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = getLeftChild(treeIndex);
        int rightTreeIndex = getRightChild(treeIndex);
        if (index >= mid + 1) set(rightTreeIndex, mid + 1, r, index, value);
        else set(leftTreeIndex, l, mid, index, value);
        tree[treeIndex] = tree[leftTreeIndex] + tree[rightTreeIndex];
    }

    int sumRange(int i, int j) {
        assert(i >= 0 && j < data.size() && i <= j);
        return sumRange(0, 0, data.size() - 1, i, j);
    }

    void buildSegmentTree(int treeIndex, int l, int r) {
        if (l == r) {
            tree[treeIndex] = data[l];
            return;
        }

        int mid = l + (r - l) / 2;
        int leftTreeIndex = getLeftChild(treeIndex);
        int rightTreeIndex = getRightChild(treeIndex);
        buildSegmentTree(leftTreeIndex, l, mid);
        buildSegmentTree(rightTreeIndex, mid + 1, r);

        tree[treeIndex] = tree[leftTreeIndex] + tree[rightTreeIndex];
    }

    int sumRange(int treeIndex, int l, int r, int targetL, int targetR) {
        if (l == targetL && r == targetR) {
            return tree[treeIndex];
        }

        int mid = l + (r - l) / 2;
        int leftTreeIndex = getLeftChild(treeIndex);
        int rightTreeIndex = getRightChild(treeIndex);

        if (targetL >= mid + 1)
            return sumRange(rightTreeIndex, mid + 1, r, targetL, targetR);
        else if (targetR <= mid)
            return sumRange(leftTreeIndex, l, mid, targetL, targetR);
        return sumRange(leftTreeIndex, l, mid, targetL, mid) + sumRange(rightTreeIndex, mid + 1, r, mid + 1, targetR);
    }

    int getLeftChild(int index) {
        return 2 * index + 1;
    }

    int getRightChild(int index) {
        return 2 * index + 2;
    }
};

class NumArray1 {
private:
    vector<int> sum;    // sum[i]存储前i个元素和
    vector<int> data;

public:
    NumArray1(vector<int> &nums) {
        data = nums;
        sum = vector<int>(nums.size() + 1);
        sum[0] = 0;
        for (int i = 1; i <= nums.size(); i++)
            sum[i] = sum[i - 1] + nums[i - 1];
    }

    void update(int i, int val) {
        data[i] = val;
        for (int k = i + 1; k <= data.size(); k++)
            sum[k] = sum[k - 1] + data[k - 1];
    }

    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];     // [0...i...j...n-1]对应的求和sum为[1...i+1...j+1...n] 那就是sum[j+1]=sum[i]
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

