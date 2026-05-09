/*
 * LeetCode 19. Remove Nth From End
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // TODO: 在此实现
    }

};

int main() {
    // TODO: 添加测试用例
    return 0;
}
