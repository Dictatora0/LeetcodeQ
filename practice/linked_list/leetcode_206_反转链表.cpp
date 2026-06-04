/*
 * LeetCode 206.反转链表
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *pre = nullptr;
        ListNode *cur = head;

        while (cur)
        {
            ListNode *nextNode = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nextNode;
        }
        return head;
    }
};

int main()
{
    // TODO: 添加测试用例
    return 0;
}
