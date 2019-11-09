//
// Created by light on 19-9-2.
//

#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>

using namespace std;



// 二分查找法, 在有序数组arr中, 查找target
// 如果找到target, 返回第一个target相应的索引index
// 如果没有找到target, 返回比target小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
// 如果这个target比整个数组的最小元素值还要小, 则不存在这个target的floor值, 返回-1
/**
 * 当存在大量重复的元素时，floor找的是第一个。
 * 当不存在指定的元素时，floor是比其小最大的一个。
 * @tparam T
 * @param arr
 * @param n
 * @param target
 * @return
 */
template<typename T>
int floor(T arr[], int n, T target){

    assert( n >= 0 );

    // 寻找比target小的最大索引
    int l = -1, r = n-1;
    while( l < r ){
        // 使用向上取整避免死循环
        int mid = l + (r-l+1)/2;
        if( arr[mid] >= target )
            r = mid - 1;
        else
            l = mid;
    }

    assert( l == r );

    // 如果该索引+1就是target本身, 该索引+1即为返回值
    if( l + 1 < n && arr[l+1] == target )
        return l + 1;

    // 否则, 该索引即为返回值
    return l;
}




// 二分查找法, 在有序数组arr中, 查找target
// 如果找到target, 返回最后一个target相应的索引index
// 如果没有找到target, 返回比target大的最小值相应的索引, 如果这个最小值有多个, 返回最小的索引
// 如果这个target比整个数组的最大元素值还要大, 则不存在这个target的ceil值, 返回整个数组元素个数n
/**
 * 当存在大量重复的元素时，ceil找的是第一个。
 * 当不存在指定的元素时，ceil是比其大最小的一个。
 * @tparam T
 * @param arr
 * @param n
 * @param target
 * @return
 */
template<typename T>
int ceil(T arr[], int n, T target){

    assert( n >= 0 );

    // 寻找比target大的最小索引值
    int l = 0, r = n;
    while( l < r ){
        // 使用普通的向下取整即可避免死循环
        int mid = l + (r-l)/2;
        if( arr[mid] <= target )
            l = mid + 1;
        else // arr[mid] > target
            r = mid;
    }

    assert( l == r );

    // 如果该索引-1就是target本身, 该索引+1即为返回值
    if( r - 1 >= 0 && arr[r-1] == target )
        return r-1;

    // 否则, 该索引即为返回值
    return r;
}

class Solution {
public:
    int ceil(vector<int>& nums, int n,int target) {
        if (nums.size() == 0) return -1;
        int left = 0, right = n-1;

        while (left <= right) {
            int mid =left+ (right-left) / 2;
            if (nums[mid] == target) {
                left = mid + 1; // 注意
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid-1;
            }
        }

        if(right<0) return 0;	// 或者写if(left==0) return -1; 如果right<0，那么此时nums中所有元素均大于target
        return nums[right] == target ? right : right+1;
    }
};

// 测试我们用二分查找法实现的floor和ceil两个函数
// 请仔细观察在我们的测试用例中，有若干的重复元素，对于这些重复元素，floor和ceil计算结果的区别：）
int main(){

    int a[] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    int n = sizeof(a)/sizeof(int);
    cout<<n<<endl;
    int floorIndex = ceil(a, n, 0);
    cout<<floorIndex<<endl;
    for( int i = 0 ; i <= 10 ; i ++ ){
        int ceilIndex = ceil(a, sizeof(a)/sizeof(int), i);
        cout<<"the ceil index of "<<i<<" is "<<ceilIndex<<".";
        if( ceilIndex >= 0 && ceilIndex < n )
            cout<<"The value is "<<a[ceilIndex]<<".";
        cout<<endl;

    }

    vector<int> nums= {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    for( int i = 0 ; i <= 10 ; i ++ ){
        int ceilIndex =Solution().ceil(nums,n,i);
        cout<<"the ceil index of "<<i<<" is "<<ceilIndex<<".";
        if( ceilIndex >= 0 && ceilIndex < n )
            cout<<"The value is "<<nums[ceilIndex]<<".";
        cout<<endl;
    }
    return 0;
}