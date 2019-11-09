//
// Created by light on 19-10-26.
//

#include "unionfind.h"

double testUF(UF uf, int m) {
    int size = uf.getSize();
    time_t start = clock();
    // [0,size)范围随机数
    for (int i = 0; i < m; i++) {
        int a = rand() % size;
        int b = rand() % size;
        uf.unionElements(a, b);
    }
    for (int i = 0; i < m; i++) {
        int a = rand() % size;
        int b = rand() % size;
        uf.isConnected(a, b);
    }
    time_t end = clock();

    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {

    UnionFind1 unionFind1(10);
    cout << unionFind1.getSize() << endl;
    cout << unionFind1.isConnected(1, 2) << endl;
    unionFind1.unionElements(1, 2);
    cout << unionFind1.isConnected(1, 2) << endl;

    UnionFind2 unionFind2(10);
    cout << unionFind2.getSize() << endl;
    unionFind2.unionElements(1, 2);
    unionFind2.unionElements(7, 2);
    cout << unionFind2.isConnected(1, 2) << endl;
    cout << unionFind2.isConnected(1, 7) << endl;
    cout << unionFind2.isConnected(2, 7) << endl;

    unionFind2.unionElements(3, 8);
    unionFind2.unionElements(4, 3);
    unionFind2.unionElements(9, 4);
    cout << unionFind2.isConnected(9, 8) << endl;
    int size = 10000000;
    int m = 10000000;
    UnionFind1 unionFind11(size);
    UnionFind1 unionFind22(size);
    UnionFind3 unionFind33(size);
    UnionFind4 unionFind44(size);
    UnionFind5 unionFind55(size);
    UnionFind6 unionFind66(size);
    cout << "UnionFind 1 result is " << testUF(unionFind11, m) << " s." << endl;
    cout << "UnionFind 2 result is " << testUF(unionFind22, m) << " s." << endl;
    cout << "UnionFind 3 result is " << testUF(unionFind33, m) << " s." << endl;
    cout << "UnionFind 4 result is " << testUF(unionFind44, m) << " s." << endl;
    cout << "UnionFind 5 result is " << testUF(unionFind55, m) << " s." << endl;
    cout << "UnionFind 6 result is " << testUF(unionFind66, m) << " s." << endl;
    return 0;
}



