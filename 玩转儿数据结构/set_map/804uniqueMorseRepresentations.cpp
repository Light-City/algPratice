//
// Created by light on 19-11-8.
//
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int uniqueMorseRepresentations(vector<string> &words) {

        vector<string> vec{".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                           "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
                           "--.."};

        set<string> s;

        for (auto str:words) {
            string tmp = "";
            for (auto i:str) tmp += vec[i - 'a'];
            s.insert(tmp);
        }
        return s.size();
    }
};