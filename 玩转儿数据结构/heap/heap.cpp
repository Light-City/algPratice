//
// Created by light on 19-10-29.
//

#include <cstdlib>
#include <climits>
#include <iostream>
#include "heap.h"
#include "PriorityQueue.h"

double testHeap(const vector<int> &testData, bool isHeapify) {
    time_t startTime = clock();
    MaxHeap<int> *maxHeap;
    if (isHeapify)
        maxHeap = new MaxHeap<int>(testData);
    else {
        maxHeap = new MaxHeap<int>();
        for (auto num:testData)
            maxHeap->add(num);
    }

    vector<int> res(testData.size());

    for (int i = 0; i < testData.size(); i++) {
        res[i] = maxHeap->extractMax();
    }

    for (int i = 1; i < testData.size(); i++) {
        if (res[i - 1] < res[i]) throw "Error";
    }
    cout << "Test MaxHeap completed." << endl;
    delete maxHeap;

    time_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

int main() {
    int n = 10000;

    vector<int> testData(n);

    for (int i = 0; i < n; i++) {
        int r = rand() % (INT_MAX + 1);
        testData.push_back(r);
    }
    // O(nlog(n))
    double time1 = testHeap(testData, false);
    cout << "without heapify " << time1 << " s" << endl;
    // O(n)
    double time2 = testHeap(testData, true);
    cout << "with heapify " << time2 << " s" << endl;
    PriorityQueue<int> priorityQueue;


    return 0;
}