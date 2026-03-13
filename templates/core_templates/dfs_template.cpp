
/*
算法名称：深度优先搜索 DFS

算法核心思想
-----------
DFS 沿着一条路径不断向深处探索，
直到无法继续再回溯到分叉点，继续探索其他路径。
它非常适合“需要遍历所有可能路径/结构”的问题。

思路要点
-------
- 明确递归函数的含义（输入、输出、状态）
- 先写终止条件，再写“选择—递归—撤销”
- 树问题默认无环，图问题必须 visited 防重复
- 深度过大可改为显式栈（迭代 DFS）

什么时候使用
-----------
适用场景：
- 树遍历（前序/中序/后序）
- 图遍历、连通性、岛屿数量
- 路径搜索、回溯枚举（排列、组合、子集）
- 需要“走到底再返回”的问题

常见算法变体
-----------
1) 树 DFS（递归）
2) 图 DFS（visited 防重复）
3) 回溯 DFS（带路径与剪枝）
4) 返回值 DFS（后序统计）
5) 记忆化 DFS（自顶向下 DP）
6) 迭代 DFS（显式栈）

复杂度分析
---------
时间复杂度：O(V + E) 或 O(搜索空间)
空间复杂度：O(递归深度)

ASCII 示例
---------
示例树：
    1
   / \
  2   3
 / \
4   5

DFS 访问顺序（前序）：1 -> 2 -> 4 -> 5 -> 3

典型题目扩展
-----------
- 94 Binary Tree Inorder Traversal
- 104 Maximum Depth of Binary Tree
- 200 Number of Islands
- 236 Lowest Common Ancestor
- 46 Permutations
- 78 Subsets

可直接使用的代码模板
------------------
见下方 DFS_Template

常见错误
--------
- 忘记 visited 导致重复遍历或死循环
- 递归终止条件错误导致栈溢出
- 回溯未恢复状态（path/used）
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class DFS_Template {
public:
    // 树 DFS：前序遍历
    void dfsTree(TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        dfsTree(node->left);
        dfsTree(node->right);
    }

    // 图 DFS：邻接表 + visited
    void dfsGraph(int u, const vector<vector<int>>& graph, vector<int>& visited) {
        visited[u] = 1;
        cout << u << " ";
        for (int v : graph[u]) {
            if (!visited[v]) dfsGraph(v, graph, visited);
        }
    }

    // 迭代 DFS：显式栈
    void dfsGraphIter(int start, const vector<vector<int>>& graph) {
        vector<int> visited(graph.size(), 0);
        stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (visited[u]) continue;
            visited[u] = 1;
            cout << u << " ";
            for (int v : graph[u]) {
                if (!visited[v]) st.push(v);
            }
        }
    }

    // 返回值 DFS：计算树高
    int height(TreeNode* node) {
        if (!node) return 0;
        int lh = height(node->left);
        int rh = height(node->right);
        return max(lh, rh) + 1;
    }

    // 记忆化 DFS：斐波那契
    int fibMemo(int n) {
        vector<int> memo(n + 1, -1);
        return dfsFib(n, memo);
    }

    // 回溯示例：生成所有子集
    void subsets(const vector<int>& nums, vector<vector<int>>& res) {
        vector<int> path;
        dfsSubsets(0, nums, path, res);
    }

private:
    int dfsFib(int n, vector<int>& memo) {
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n];
        memo[n] = dfsFib(n - 1, memo) + dfsFib(n - 2, memo);
        return memo[n];
    }

    void dfsSubsets(int idx, const vector<int>& nums, vector<int>& path, vector<vector<int>>& res) {
        res.push_back(path);
        for (int i = idx; i < (int)nums.size(); ++i) {
            path.push_back(nums[i]);
            dfsSubsets(i + 1, nums, path, res);
            path.pop_back();
        }
    }
};

int main() {
    // 树示例
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    DFS_Template solver;
    cout << "树 DFS 前序: ";
    solver.dfsTree(root);
    cout << "\n树高: " << solver.height(root) << endl;

    // 图示例
    vector<vector<int>> graph = {
        {1, 2}, // 0
        {3},    // 1
        {3},    // 2
        {}      // 3
    };
    vector<int> visited(graph.size(), 0);
    cout << "图 DFS(递归): ";
    solver.dfsGraph(0, graph, visited);
    cout << "\n图 DFS(迭代): ";
    solver.dfsGraphIter(0, graph);
    cout << endl;

    return 0;
}
