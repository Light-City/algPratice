//
// Created by light on 19-11-8.
//

#include <iostream>
#include <vector>

using namespace std;

int mySum(const vector<int> &vec, int index) {

    // 求解最基本问题
    if (vec.size() == index) return 0;

    // 把原问题转化成更小的问题
    int ret = 0;
    ret += vec[index] + mySum(vec, index + 1);
//    或者return vec[index] + mySum(vec, index + 1);
    return ret;
}



int main() {
    vector<int> vec{1, 2, 3, 4, 5};
    cout << mySum(vec, 0) << endl;
    return 0;
}