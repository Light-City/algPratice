//
// Created by light on 19-10-20.
//
#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

/**
 * 哈希表 底层构建采用map,也就是红黑树,该key是具有可比较的,而哈希表是不可比较的,所以传入不可比较的key,会报错.
 * 哈希表 牺牲了顺序性
 * 后面实现：前期采用链表作为底层,当冲突达到一定程度的时候,采用红黑树.其中能够转为红黑树的条件是传递的key可比较.
 * @tparam Key
 * @tparam Value
 */
template<typename Key, typename Value>
class HashTable {
private:
    const static int upperTol = 3;
    const static int lowerTol = 1;
    int capacityIndex = 0;
    map<Key, Value> **hashtable;
    int M;
    int size;
    // 素数数组
    const vector<int> capacity = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
                                  196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
                                  50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

public:
    /**
     * 默认构造
     * @param M
     */
    HashTable()  {
        M = capacity[capacityIndex], size = 0;
        // 这里的括号是为了初始化为0,这就可以不用写下面的代码,当然在后面add之类的操作,就不需要动态分配内存.
        // this->hashtable = new map<Key, Value> *[M]();
        this->hashtable = new map<Key, Value> *[M];
        for (int i = 0; i < M; i++) {
            this->hashtable[i] = new map<Key, Value>;
        }
    }


    /**
     * 析构函数,释放内存
     */
    ~HashTable() {
        free(M);
    }


public:
    /**
     * 获取哈希表元素个数
     * @return
     */
    int getSize() {
        return size;
    }

    /**
     * 添加新元素
     * @param key
     * @param value
     */
    void add(Key key, Value value) {
        // 拉链法出来的map如果为空,就动态分配一个map,然后进行插入
        // 如果key不存在就看内存是否存在,不存在,就分配,存在就插入
        if (hashtable[hashFunc(key)] == NULL || hashtable[hashFunc(key)]->count(key) == 0) {
            if (hashtable[hashFunc(key)] == NULL)
                hashtable[hashFunc(key)] = new map<Key, Value>;
            hashtable[hashFunc(key)]->insert(make_pair(key, value));
            size++;
            if (size >= maxCapacity() && capacityIndex + 1 < capacity.size()) {
                capacityIndex++;
                resize(capacity[M]);
            }
        } else {
            // 否则,修改value.
            hashtable[hashFunc(key)]->erase(key);
            hashtable[hashFunc(key)]->insert(make_pair(key, value));
        }
    }

    /**
     * 移除Key
     * @param key
     * @return 0 success -1 fail
     */
    Value remove(Key key) {
        Value ret = -1;
        // 是否包含key,若包含key,则直接删除
        if (contains(key)) {
            hashtable[hashFunc(key)]->erase(key);
            size--;
//            if (size == 0) delete hashtable[hashFunc(key)];       // 可以添加这行来动态减少内存
            ret = 0;
            if (size < minCapacity() && capacityIndex - 1 >= 0) {
                capacityIndex--;
                resize(capacityIndex);
            }
        }
        return ret;
    }

    /**
     * 重设value
     * @param key
     * @param value
     */
    void set(Key key, Value value) {
        // key不存在
        if (!contains(key))
            throw "key not exists!";
        // 修改value
        hashtable[hashFunc(key)]->erase(key);
        hashtable[hashFunc(key)]->insert(make_pair(key, value));
    }

    /**
     * 是否包含key
     * @param key
     * @return
     */
    bool contains(Key key) {
        return hashtable[hashFunc(key)] == NULL || this->hashtable[hashFunc(key)]->count(key) == 0 ? false : true;
    }

    /**
     * 获取key对应的value
     * @param key
     * @return
     */
    Value get(Key key) {
        if (contains(key))
            return hashtable[hashFunc(key)]->at(key);
        return 0;
    }

    /**
     * 最大容量
     * @return
     */
    Value maxCapacity() {
        return M * upperTol;
    }

    /**
     * 最小容量
     * @return
     */
    Value minCapacity() {
        return M * lowerTol;
    }

private:
    /**
     * 哈希函数
     * @param key
     * @return
     */
    int hashFunc(Key key) {
        std::hash<Key> h;
        return (h(key) & 0x7fffffff) % M;
    }

    template<typename K, typename V>
    // 重载<<操作符
    friend ostream &operator<<(ostream &out, HashTable<K, V> &hashTable);

    /**
     * 打印hash表中所有数据
     */
    void print() {
        string res = "{";
        for (int i = 0; i < this->M; i++)
            if (this->hashtable[i])
                for (auto m:*(this->hashtable[i]))
                    res += m.first + ":" + to_string(m.second) + ",";
        res.replace(res.size() - 1, string::npos, "}");
        cout << res << endl;
    }

    /**
     * 动态调整内存,保证时间复杂度O(1)查找
     * 把扩容后的操作,平摊到前面每次操作,时间复杂度O(2),那就是O(1)了
     * @param newM
     */
    void resize(int newM) {
        cout << "resize " << newM << endl;
        map<Key, Value> **newHashTable = new map<Key, Value> *[newM];
        for (int i = 0; i < newM; i++) {
            newHashTable[i] = new map<Key, Value>;
        }
        int oldM = M;
        this->M = newM;
        for (int i = 0; i < oldM; i++) {
            map<Key, Value> m = *(hashtable[i]);
            for (auto p:m)
                newHashTable[hashFunc(p.first)]->insert(make_pair(p.first, p.second));
        }

        free(oldM);
        this->hashtable = newHashTable;
    }

private:
    /**
     * 释放内存
     * @param M
     */
    void free(int M) {
        for (int i = 0; i < M; i++) {
            if (hashtable[i])
                delete hashtable[i];
        }
        delete[]hashtable;
    }
};

template<typename K, typename V>
ostream &operator<<(ostream &out, HashTable<K, V> &hashTable) {
    hashTable.print();
    return out;
}

/**
 *  哈希函数的设计原则：
 *      1.一致性：如果a==b,则hashFunc(a)=o=hashFunc(b)
 *      2.高效性：计算高效简便
 *      3.均匀性：哈希值均匀分布
 */
// (hashcode(k1) & 0x7fffffff)%M
// f为7个一个f有4个1那么就是28个1,,7有3个1,,总共31个1
// 而最高位第32位表示正负，故上述取&后，变为正数。
