//
// Created by light on 19-10-20.
//

#include "hash.h"
#include <vector>


int main() {

    vector<string> words{"java", "c++", "c", "c++", "c#", "python", "ruby", "python",
                         "c", "c", "c++", "java", "c++", "rust", "python"};
    HashTable<string, int> ht(1);
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

    map<string,int> m{{"a",1},{"b",2}};
    for(auto i:m) cout<<i.first<<" "<<i.second<<" ";
    cout<<endl;
    m.insert({{"a",2}});
    for(auto i:m) cout<<i.first<<" "<<i.second<<" ";
    cout<<endl;
    m["a"]=2;
    for(auto i:m) cout<<i.first<<" "<<i.second<<" ";
    cout<<endl;
    return 0;
}