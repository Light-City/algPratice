//
// Created by light on 19-10-30.
//



// 使用自己的Priority_Queue
#include <vector>
#include <iostream>
#include <unordered_map>
#include "PriorityQueue.h"
// C++ 默认的优先队列采用vector作为底层容器,且默认为大顶堆,传递进去的是less,比较的时候是根据第二个参数判别
using namespace std;

class Freq {
public:
    int e, freq;

    Freq(int key, int frequence) : e(key), freq(frequence) {}


    // 比较大小都是相对的,由我们来定,我们底层是一个大顶堆,而实际上我们需要一个小顶堆,那么我们可以重载元素(例如这里放进队列的是个Freq)操作符,将>里面操作变为<,<操作符变为>内容,就完成了类似小顶堆的功能。
    bool operator<(const Freq &another) {
        if (this->freq < another.freq) {
            return false;
        } else {
            return true;
        }
    }

    bool operator>(const Freq &another) {
        if (this->freq > another.freq) {
            return false;
        } else {
            return true;
        }
    }
};

class Solution {
public:

    // 使用自己的Priority_Queue

    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        for (auto num:nums) map[num]++;

        PriorityQueue<Freq> *pq = new PriorityQueue<Freq>;
        for (auto m:map) {
            Freq f(m.first, m.second);
            if (pq->getSize() < k) pq->enqueue(f);
            else if (m.second > pq->getFront().freq) {
                pq->dequeue();
                pq->enqueue(f);
            }
        }
        vector<int> res;
        while (!pq->isEmpty()) {
            res.push_back(pq->getFront().e);
            pq->dequeue();
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
    int i = 1;
    return 0;
}
