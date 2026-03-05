#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr){
            return nullptr;
        }
        
        // 哈希表：原节点 -> 新节点
        unordered_map<Node *, Node *> nodeMap;

        // 第一遍：创建所有新节点，建立映射关系
        Node *current = head;
        while (current)
        {
            nodeMap[current] = new Node(current->val);
            current = current->next;
        }

        // 第二遍：设置新节点的 next 和 random 指针
        current = head;
        while(current){
            Node *newNode = nodeMap[current];
            newNode->next = nodeMap[current->next]; // next 指向对应的新节点
            newNode->random = nodeMap[current->random];  // random 指向对应的新节点

            current = current->next;
        }

        return nodeMap[head];
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}