
/*
链表工具
包含：构建、打印、释放
*/

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* buildList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    for (int x : nums) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    ListNode* head = buildList({1,2,3});
    printList(head);
    freeList(head);
    return 0;
}
