/*
 * ============================================================================
 * DFS 深度优先搜索 - 面试必备完整模板
 * Depth-First Search - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * DFS 是一种遍历或搜索树/图的算法，沿着一条路径一直走到底，
 * 然后回溯到上一个节点，继续探索其他路径。
 *
 * 【通俗解释】
 * 想象你在迷宫中探险：
 * - 选择一条路一直走到死胡同
 * - 回退到上一个岔路口
 * - 选择另一条路继续探索
 * - 重复直到找到出口或探索完所有路径
 *
 * 【为什么有效】
 * 1. 系统性：保证不遗漏任何路径
 * 2. 空间效率：只需要记录当前路径
 * 3. 递归实现：代码简洁优雅
 *
 * 【与其他算法对比】
 * - vs BFS：DFS 用栈（递归），BFS 用队列
 * - vs 回溯：回溯是 DFS 的特殊应用
 * - vs 动态规划：DFS 可能重复计算，DP 记忆化避免重复
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别 DFS 题目】
 *
 * ✅ 关键词识别：
 * 1. "所有路径" - DFS 遍历
 * 2. "连通性" - DFS 判断连通
 * 3. "岛屿" - 二维 DFS
 * 4. "树的遍历" - 递归 DFS
 * 5. "图的遍历" - DFS + visited
 *
 * ✅ 题目特征：
 * - 树或图的遍历
 * - 需要探索所有可能性
 * - 路径相关问题
 * - 连通性问题
 *
 * ❌ 不适合 DFS：
 * - 最短路径（用 BFS）
 * - 需要层序遍历
 * - 图太大会栈溢出
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：二叉树 DFS（最基础）
// 时间复杂度：O(n)
// 空间复杂度：O(h) h 为树高
// ============================================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreeDFS {
public:
    // 前序遍历：根 -> 左 -> 右
    void preorder(TreeNode* root) {
        if (!root) return;

        visit(root);           // 访问根节点
        preorder(root->left);  // 递归左子树
        preorder(root->right); // 递归右子树
    }

    // 中序遍历：左 -> 根 -> 右
    void inorder(TreeNode* root) {
        if (!root) return;

        inorder(root->left);
        visit(root);
        inorder(root->right);
    }

    // 后序遍历：左 -> 右 -> 根
    void postorder(TreeNode* root) {
        if (!root) return;

        postorder(root->left);
        postorder(root->right);
        visit(root);
    }

private:
    void visit(TreeNode* node) {
        cout << node->val << " ";
    }
};

// ============================================================================
// 模板 2：图 DFS（需要 visited）
// 时间复杂度：O(V + E)
// 空间复杂度：O(V)
// ============================================================================

class GraphDFS {
public:
    void dfs(vector<vector<int>>& graph, int start) {
        unordered_set<int> visited;
        dfsHelper(graph, start, visited);
    }

private:
    void dfsHelper(vector<vector<int>>& graph, int node, unordered_set<int>& visited) {
        // 1. 标记已访问
        visited.insert(node);

        // 2. 处理当前节点
        cout << node << " ";

        // 3. 递归访问邻居
        for (int neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(graph, neighbor, visited);
            }
        }
    }
};

// ============================================================================
// 模板 3：二维网格 DFS（岛屿问题）
// 时间复杂度：O(m * n)
// 空间复杂度：O(m * n)
// ============================================================================

class GridDFS {
public:
    // 四个方向：上、右、下、左
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    void dfs(vector<vector<int>>& grid, int x, int y) {
        int m = grid.size(), n = grid[0].size();

        // 1. 边界检查
        if (x < 0 || x >= m || y < 0 || y >= n) return;

        // 2. 检查是否已访问或不可访问
        if (grid[x][y] == 0) return;

        // 3. 标记已访问
        grid[x][y] = 0;

        // 4. 递归四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            dfs(grid, nx, ny);
        }
    }
};

// ============================================================================
// 模板 4：路径 DFS（记录路径）
// 时间复杂度：O(n!)
// 空间复杂度：O(n)
// ============================================================================

class PathDFS {
public:
    vector<vector<int>> allPaths;

    void dfs(vector<vector<int>>& graph, int node, int target, vector<int>& path) {
        // 1. 将当前节点加入路径
        path.push_back(node);

        // 2. 到达目标，记录路径
        if (node == target) {
            allPaths.push_back(path);
        } else {
            // 3. 继续探索
            for (int neighbor : graph[node]) {
                dfs(graph, neighbor, target, path);
            }
        }

        // 4. 回溯：移除当前节点
        path.pop_back();
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：岛屿数量
// LeetCode 200: Number of Islands
// ============================================================================

class Solution_NumIslands {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int m = grid.size(), n = grid[0].size();
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }

        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int x, int y) {
        int m = grid.size(), n = grid[0].size();

        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0') {
            return;
        }

        grid[x][y] = '0';  // 标记已访问

        // 四个方向
        dfs(grid, x-1, y);
        dfs(grid, x+1, y);
        dfs(grid, x, y-1);
        dfs(grid, x, y+1);
    }
};

// ============================================================================
// 变体 2：二叉树的最大深度
// LeetCode 104: Maximum Depth of Binary Tree
// ============================================================================

class Solution_MaxDepth {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        return max(leftDepth, rightDepth) + 1;
    }
};

// ============================================================================
// 变体 3：路径总和
// LeetCode 112: Path Sum
// ============================================================================

class Solution_HasPathSum {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;

        // 叶子节点
        if (!root->left && !root->right) {
            return root->val == targetSum;
        }

        // 递归左右子树
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
};

// ============================================================================
// 变体 4：二叉树的所有路径
// LeetCode 257: Binary Tree Paths
// ============================================================================

class Solution_BinaryTreePaths {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (!root) return result;

        string path = to_string(root->val);
        dfs(root, path, result);
        return result;
    }

private:
    void dfs(TreeNode* node, string path, vector<string>& result) {
        // 叶子节点
        if (!node->left && !node->right) {
            result.push_back(path);
            return;
        }

        if (node->left) {
            dfs(node->left, path + "->" + to_string(node->left->val), result);
        }

        if (node->right) {
            dfs(node->right, path + "->" + to_string(node->right->val), result);
        }
    }
};

// ============================================================================
// 变体 5：克隆图
// LeetCode 133: Clone Graph
// ============================================================================

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int _val) : val(_val) {}
};

class Solution_CloneGraph {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> visited;
        return dfs(node, visited);
    }

private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& visited) {
        if (visited.count(node)) {
            return visited[node];
        }

        // 创建新节点
        Node* clone = new Node(node->val);
        visited[node] = clone;

        // 递归克隆邻居
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfs(neighbor, visited));
        }

        return clone;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【如何向面试官解释思路】
 *
 * 1. 识别问题类型
 *    "这是一个图/树的遍历问题，我用 DFS 来解决..."
 *
 * 2. 说明递归三要素
 *    - 终止条件：什么时候停止递归
 *    - 递归逻辑：每一步做什么
 *    - 回溯操作：需要恢复状态吗
 *
 * 3. 分析复杂度
 *    "时间复杂度 O(n)，每个节点访问一次；空间复杂度 O(h)，递归栈深度"
 *
 * 【常见追问】
 *
 * Q1: "DFS 和 BFS 的区别？"
 * A1: "DFS 用栈（递归），深度优先；BFS 用队列，广度优先。
 *      DFS 适合路径问题，BFS 适合最短路径"
 *
 * Q2: "如何避免重复访问？"
 * A2: "用 visited 集合记录已访问节点，或者原地修改标记"
 *
 * Q3: "递归会栈溢出吗？"
 * A3: "如果树很深可能会，可以改用迭代 + 显式栈"
 */

/*
 * ============================================================================
 * 第六部分：易错点
 * ============================================================================
 */

/*
 * 【常见错误 1：忘记边界检查】
 * ❌ dfs(grid, x+1, y);  // 没检查边界
 * ✅ if (x+1 < m) dfs(grid, x+1, y);
 *
 * 【常见错误 2：忘记标记已访问】
 * ❌ 没有 visited，导致无限递归
 * ✅ visited.insert(node);
 *
 * 【常见错误 3：回溯时忘记恢复状态】
 * ❌ path.push_back(node);  // 忘记 pop_back
 * ✅ path.push_back(node); dfs(...); path.pop_back();
 */

/*
 * ============================================================================
 * 第七部分：复杂度分析
 * ============================================================================
 */

/*
 * 【时间复杂度】
 * - 树：O(n)，n 为节点数
 * - 图：O(V + E)，V 为顶点数，E 为边数
 * - 二维网格：O(m * n)
 *
 * 【空间复杂度】
 * - 递归栈：O(h)，h 为深度
 * - visited：O(n)
 */

/*
 * ============================================================================
 * 第八部分：真题实战
 * ============================================================================
 */

/*
 * ⭐ 简单
 * 1. LC 104: 二叉树的最大深度
 * 2. LC 112: 路径总和
 * 3. LC 257: 二叉树的所有路径
 * 4. LC 100: 相同的树
 *
 * ⭐⭐ 中等（高频）
 * 5. LC 200: 岛屿数量 ⭐⭐⭐⭐⭐
 * 6. LC 133: 克隆图 ⭐⭐⭐⭐
 * 7. LC 695: 岛屿的最大面积 ⭐⭐⭐⭐
 * 8. LC 130: 被围绕的区域
 * 9. LC 417: 太平洋大西洋水流问题
 * 10. LC 207: 课程表（拓扑排序）
 *
 * ⭐⭐⭐ 困难
 * 11. LC 124: 二叉树中的最大路径和
 * 12. LC 297: 二叉树的序列化与反序列化
 */

/*
 * ============================================================================
 * 第九部分：完整示例
 * ============================================================================
 */

void testNumIslands() {
    Solution_NumIslands sol;
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "岛屿数量: " << sol.numIslands(grid) << endl;
}

/*
 * ============================================================================
 * 第十部分：速查表
 * ============================================================================
 */

/*
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │                      DFS 算法速查表                                      │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * 【核心框架】
 * void dfs(node) {
 *     if (终止条件) return;
 *     标记已访问;
 *     for (每个邻居) {
 *         if (未访问) dfs(邻居);
 *     }
 *     回溯（如需要）;
 * }
 *
 * 【识别关键词】
 * ✓ 所有路径 → DFS
 * ✓ 连通性 → DFS
 * ✓ 岛屿 → 二维 DFS
 *
 * 【时间复杂度】O(V + E)
 * 【空间复杂度】O(h) 递归栈
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 200, LC 104
 * ⭐⭐⭐⭐ LC 133, LC 695
 */

int main() {
    testNumIslands();
    cout << "DFS 算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o dfs dfs_template.cpp && ./dfs
 */
