//
// Created by light on 19-11-8.
//

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    ListNode(const vector<int> &array) {
        if (array.size() == 0)
            throw "array cannot be empty";
        this->val = array[0];
        ListNode *cur = this;
        for (int i=1;i<array.size();i++) {
            cur->next = new ListNode(array[i]);
            cur = cur->next;
        }
    }

    friend ostream &operator<<(ostream &out, ListNode &listNode) {
        out << "List:head ";
        ListNode *cur = &listNode;
        while (cur) {
            out << cur->val << "->";
            cur=cur->next;
        }
        out<<"NULL"<<endl;
        return out;
    }
};

class Solution {
public:
    ListNode *removeElements(ListNode *head, int val) {

        // 先处理删除头部
        while (head && head->val == val) head = head->next;

        ListNode *cur = head, *prev = head;
        while (cur) {
            if (cur->val == val) {
                prev->next = cur->next;
            } else {
                prev = cur;
            }
            cur = cur->next;
        }
        return head;
    }
    /**
   * 对上述简化
   * @param head
   * @param val
   * @return
   */
    ListNode *removeElements1(ListNode *head, int val) {
        ListNode *HEAD = new ListNode(-1), *pre = HEAD;
        HEAD->next = head;
        while (pre->next) {
            if (pre->next->val == val) {
                pre->next = pre->next->next;
            } else {
                pre = pre->next;
            }
        }
        pre = HEAD->next;
        delete HEAD;
        return pre;
    }
    /**
     * 递归
     * @param head
     * @param val
     * @return
     */
    ListNode *removeElements2(ListNode *head, int val) {
        if (head == NULL) return head;
        // 后面 n-1几个节点删除后的链表 head
        ListNode *back = removeElements2(head->next, val);
        // 考虑当前节点 如果当前节点是删除节点,就直接返回前面back的头
        if (head->val == val)
            return back;
        // 否则当前节点不需要被删除,那么就连接上,并返回当前节点即可。
        head->next = back;
        return head;
    }

    // 上述简化版
    ListNode *removeElements3(ListNode *head, int val) {
        if (head == NULL) return head;
        // 后面 n-1几个节点删除后的链表 head
        head->next = removeElements3(head->next, val);
        // 考虑当前节点 如果当前节点是删除节点,就直接返回前面back的头
        if (head->val == val)
            return head->next;
        // 否则当前节点不需要被删除,那么就连接上,并返回当前节点即可。
        return head;
    }
};


int main() {
    vector<int> array{1,3,5,6,8,6};
    ListNode *listNode = new ListNode(array);

    cout<<*listNode<<endl;

    Solution().removeElements(listNode,6);

    cout<<*listNode<<endl;
    delete listNode;

    return 0;
}