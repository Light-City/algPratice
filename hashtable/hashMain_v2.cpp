//
// Created by light on 19-10-20.
//

#include "hash_v2.h"
#include <vector>
#include <set>


int main() {

    vector<string> words{"java", "c++", "c", "c++", "c#", "python", "ruby", "python",
                         "c", "c", "c++", "java", "c++", "rust", "python"};
    HashTable<string, int> ht;
    for (string word : words) {
        if (ht.contains(word)) {
            ht.set(word, ht.get(word) + 1);
        } else {
            ht.add(word, 1);
        }
    }
    cout<<ht;
    cout<<"size="<<ht.getSize()<<",maxCapacity="<<ht.maxCapacity()<<",minCapacity="<<ht.minCapacity()<<endl;
    string w="c++";
    ht.remove(w);
    if (ht.contains(w))
        cout << "" << w << ": " << ht.get(w) << endl;
    else
        cout << "No word " << w << " in words" << endl;
    cout<<ht;
    ht.remove("c#");
    ht.remove("java");
    ht.remove("c");
    cout<<"size="<<ht.getSize()<<",maxCapacity="<<ht.maxCapacity()<<",minCapacity="<<ht.minCapacity()<<endl;
    cout<<ht;
    return 0;
}