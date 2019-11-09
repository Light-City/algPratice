priority_queue 优先队列默认构建的是大顶堆

为何priority_queue采用的less作为大顶堆？

(1) push方法先调用vector的push方法,然后调用push_heap,最后调用__push_heap,最后这个函数中使用比较器,从最后一个非叶子节点开始向上查找,直到找到比插入的元素大于等于的位置,就把这个元素放在那个位置上。
很明显,这个是构建大顶堆的sift up过程。
(2) pop方法调用pop_heap,再调用__pop_heap,然后取第一个元素将其放到后面,然后调用__adjust_heap恢复堆不变,最后调用一下vector的pop_back,刚才放到最后的那个元素给弹出去，也就是最大的元素。

对比pop与push是另个完全相反的过程。
- 对于pop是先取第一个元素放到最后再pop_back出去,此时弹出的是最大元素。
- 对于push是先把元素给push_back进去,然后开始维护堆,把大的元素给sift up。

因此底层采用的less为大顶堆。

小顶堆构建四种方法(准确的三种,最后一种不算)

（1）直接重载less的小于操作符


```cpp
class Freq {
public:
    int e, freq;

    Freq(int key, int frequence) : e(key), freq(frequence) {}

};
// 全局重载  注意参数必须为const xxx&
inline bool operator<(const Freq &f1, const Freq &f2) {
    return f1.freq > f2.freq;
}
```

调用处为：

```cpp
priority_queue<Freq, vector<Freq>> *pq = new priority_queue<Freq, vector<Freq>>;
// 等价于
priority_queue<Freq, vector<Freq>,less<Freq>> *pq = new priority_queue<Freq, vector<Freq>,less<Freq>>;
```

（2）重载greater的大于操作符

```cpp
// 全局重载  注意参数必须为const xxx&
inline bool operator>(const Freq &f1, const Freq &f2) {
    return f1.freq > f2.freq;
}
priority_queue<Freq, vector<Freq>,greater<Freq>> *pq = new priority_queue<Freq, vector<Freq>,greater<Freq>>;
```



（3）仿函数

```cpp
struct cmp {
    bool operator()(Freq a, Freq b) {
        return a.freq > b.freq;
    }
};
```
调用：
```cpp
priority_queue<Freq, vector<Freq>, cmp> *pq = new priority_queue<Freq, vector<Freq>, cmp>;
```


（4）利用using构建全局的大顶堆或小顶堆

```cpp
template <typename T> using minHeap=priority_queue<T, vector<T>, cmp>;
int main() {
    minHeap<Freq> *pq=new minHeap<Freq>;
    // do something
    return 0;
}
```

