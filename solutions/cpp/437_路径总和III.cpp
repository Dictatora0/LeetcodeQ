#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    unordered_map<long,long> prefix;
    int result = 0;

    void dfs(TreeNode * node,int curSum,int target){
        if(!node){
            return;
        }
        curSum += node->val;
        if(prefix.count(curSum - target)){
            result += prefix[curSum - target];
        }

        prefix[curSum]++;
        dfs(node->left, curSum, target);
        dfs(node->right, curSum, target);

        prefix[curSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1;

        dfs(root, 0, targetSum);

        return result;
    }
};


int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}