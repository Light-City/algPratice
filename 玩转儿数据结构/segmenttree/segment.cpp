//
// Created by light on 19-10-28.
//

#include "segment.h"

template<typename T>
class intMerge : public Merge<T> {
public:
    virtual T merge(T a, T b) {
        return a + b;
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    SegmentTree<int, intMerge<int>> segmentTree(nums);
    cout << segmentTree.query(0, 5) << endl;
    cout << segmentTree << endl;
}