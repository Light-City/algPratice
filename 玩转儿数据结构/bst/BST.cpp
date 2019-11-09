//
// Created by light on 19-9-2.
//
#include "BST.h"

// 测试二分搜索树中的predecessor和successor两个函数
int main(){

    // 生成 0 到 N-1 一共 N 个数字的数组
    int N = 1000;
    int* nums = new int[N];
    for( int i = 0 ; i < N ; i ++)
        nums[i] = i;

    // 将数组中的数组乱序
    shuffle(nums, N);

    // 将这个N个数插入到二叉树中
    BST<int,int> bst;
    for(int i = 0 ; i < N ; i ++ )
        bst.insert(i, i);

    // 测试前驱算法, 除了数字0没有前驱, 每个数字x的前驱应该为x-1
    for(int i = 0 ; i < N ; i ++){
        if( i == 0 ){
            assert(bst.predecessor(i) == NULL);
            cout << "The predesessor of 0 is NULL" << endl;
        }
        else{
            assert(bst.predecessor(i)->key == i-1);
            cout << "The predesessor of " << i << " is " << i-1 << endl;
        }
    }

    cout<<endl;

    // 测试后继算法, 除了数字没有N-1后继, 每个数字x的后继应该为x+1
    for(int i = 0 ; i < N ; i ++){
        if( i == N-1 ){
            assert(bst.successor(i) == NULL);
            cout << "The successor of " << i << " is NULL" << endl;
        }
        else{
            assert(bst.successor(i)->key == i+1);
            cout << "The successor of " << i << " is " << i+1 << endl;
        }
    }

    return 0;
}