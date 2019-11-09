//
// Created by light on 19-10-30.
//

// 使用STL的priorityqueue
#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "PriorityQueue.h"
// C++ 默认的优先队列采用vector作为底层容器,且默认为大顶堆,传递进去的是less,比较的时候是根据第二个参数判别
using namespace std;

class Freq {
public:
    int e, freq;

    Freq(int key, int frequence) : e(key), freq(frequence) {}
    bool operator<(const Freq &f) const{        // 必须加const
        return this->freq > f.freq;
    }

};

// less < 重载
//inline bool operator<(const Freq &f1, const Freq &f2) {
//    return f1.freq > f2.freq;
//}
//
// greater > 重载
inline bool operator>(const Freq &f1, const Freq &f2) {
    return f1.freq > f2.freq;
}

struct cmp {
    bool operator()(Freq a, Freq b) {
        return a.freq > b.freq;
    }
};
// c++ 11语法
template <typename T> using minHeap=priority_queue<T, vector<T>, cmp>;
class Solution {
public:

    // 使用STL的priority_queue
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        for (auto num:nums) map[num]++;

        // greater 为a>b 实际上是看b 那就是每次放入队列中是教小的元素

//        priority_queue<Freq, vector<Freq>> *pq = new priority_queue<Freq, vector<Freq>>;
//        priority_queue<Freq, vector<Freq>, greater<Freq>> *pq = new priority_queue<Freq, vector<Freq>, greater<Freq>>;
        minHeap<Freq> *pq=new minHeap<Freq>;
        for (auto m:map) {
            Freq f(m.first, m.second);
            if (pq->size() < k) pq->push(f);
            else if (m.second > pq->top().freq) {
                pq->pop();
                pq->push(f);
            }
        }
        vector<int> res;
        while (!pq->empty()) {
            res.push_back(pq->top().e);
            pq->pop();
        }
        delete pq;
        return res;
    }
};


int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    vector<int> res = Solution().topKFrequent(nums, k);
    for (auto i:res) cout << i << endl;


    priority_queue<int> pq(nums.begin(),nums.end());

    while(!pq.empty()) {
        cout<<pq.top()<<endl;
        pq.pop();
    }
    return 0;
}