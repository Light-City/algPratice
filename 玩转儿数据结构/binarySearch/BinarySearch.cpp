//
// Created by light on 19-9-2.
//

#include <iostream>
#include <assert.h>
#include <tgmath.h>

using namespace std;

/**
 * 非递归查找
 * 二分查找法
 * 在有序数组arr中,查找target
 * 如果查找到target 返回相应的索引index
 * 如果没有查找到target,返回-1
 * @tparam T
 */
template<typename T>
int binarySearch(T arr[], int n, T target) {

    // 在arr[l...r]之中查找target
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) return mid;
        // 在arr[l...mid-1]查找target
        else if (target < arr[mid]) r = mid - 1;
        // 在arr[mid+1...r]查找target
        else if (target > arr[mid]) l = mid + 1;
    }
    return -1;
}
template<typename T>
int __binarySearch(T arr[], int l, int r, T target) {
    if(l>r) return -1;

    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;
    else if (target < arr[mid]) __binarySearch(arr, l, mid - 1, target);
    else if (target > arr[mid]) __binarySearch(arr, mid+1, r, target);
}
/**
 * 递归查找
 * @tparam T
 * @param arr
 * @param l
 * @param r
 * @param target
 * @return
 */
template<typename T>
int binarySearch1(T arr[], int n,T target) {
    return __binarySearch(arr,0,n-1,target);
}

int main() {

    int n = 1000000;
    int* a = new int[n];
    for( int i = 0 ; i < n ; i ++ )
        a[i] = i;

    // 测试非递归二分查找法
    clock_t startTime = clock();

    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for( int i = 0 ; i < 2*n ; i ++ ){
        int v = binarySearch(a, n, i);
        if( i < n )
            assert( v == i );
        else
            assert( v == -1 );
    }
    clock_t endTime = clock();
    cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;


    // 测试递归的二分查找法
    startTime = clock();

    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for( int i = 0 ; i < 2*n ; i ++ ){
        int v = binarySearch1(a, n, i);
        if( i < n )
            assert( v == i );
        else
            assert( v == -1 );
    }
    endTime = clock();
    cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;

    delete[] a;

    return 0;
}