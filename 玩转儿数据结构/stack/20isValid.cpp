//
// Created by light on 19-8-28.
//
#include <iostream>
#include <stack>
#include <map>

/**
 * 通过栈顶元素获取最近的那个元素
 */

using namespace std;

class Solution {
public:
    /**
     * 时间复杂度:O(n)
     * 空间复杂度:O(n)
     * @param s
     * @return
     */
    bool isValid(string s) {
        stack<char> sta;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                sta.push(s[i]);
            else if (s[i] == ')') {
                bool iscirok = judge(sta, s[i], '(');
                if (iscirok == false) return false;
            } else if (s[i] == '}') {
                bool ishuaok = judge(sta, s[i], '{');
                if (ishuaok == false) return false;
            } else if (s[i] == ']') {
                bool isfangok = judge(sta, s[i], '[');
                if (isfangok == false) return false;
            }
        }
        return sta.empty() ? true : false;
    }

    bool judge(stack<char> &sta, const char src, const char kuohao) {
        if (sta.empty())
            return false;
        char topchar = sta.top();
        sta.pop();
        if (topchar == kuohao)
            return true;
        return false;
    }
    // 上述简化版
    bool isValid2(string s) {
        stack<char> sta;
        char match;
        for(int i=0;i<s.length();i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                sta.push(s[i]);
            else {
                if(sta.empty()) return false;
                char topchar=sta.top();
                sta.pop();
                if(s[i]==')') {
                    match='(';
                } else if(s[i]=='}') {
                    match='{';
                } else if(s[i]==']') {
                    match = '[';
                }
                if(match!=topchar) return false;
            }
        }
        return sta.empty();
    }

    bool isValid1(string s) {
        map<char, char> m;
        m['}']='{';
        m[']']='[';
        m[')']='(';
        stack<char> st;
        st.push('0');
        for (int i = 0; i < s.length(); i++) {
            if (m.find(s[i])!=m.end() && m[s[i]] == st.top()) {
                st.pop();
                continue;
            }
            if (m.find(s[i])!=m.end() && m[s[i]] != st.top()&&st.top()!='0') {
                return false;
            }

            st.push(s[i]);
        }
        return st.size()==1;
    }


};


int main() {
    string s = "{}";
    cout << Solution().isValid2(s) << endl;
}