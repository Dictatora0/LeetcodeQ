/*
 * ============================================================================
 * BFS 广度优先搜索 - 面试必备完整模板
 * Breadth-First Search - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * BFS 是一种层序遍历算法，先访问离起点近的节点，再访问远的节点。
 * 使用队列实现，保证按距离从近到远访问。
 *
 * 【通俗解释】
 * 想象你在水中扔一块石头：
 * - 水波一圈圈向外扩散
 * - 先到达近的地方，后到达远的地方
 * - BFS 就像这样一层层扩展
 *
 * 【为什么有效】
 * 1. 最短路径：第一次到达目标就是最短路径
 * 2. 层序遍历：按层处理，逻辑清晰
 * 3. 完整性：保证访问所有可达节点
 *
 * 【与其他算法对比】
 * - vs DFS：BFS 用队列，DFS 用栈；BFS 找最短路径，DFS 找所有路径
 * - vs Dijkstra：BFS 适用于无权图，Dijkstra 适用于带权图
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别 BFS 题目】
 *
 * ✅ 关键词识别：
 * 1. "最短路径" - 90% 是 BFS
 * 2. "最少步数" - BFS
 * 3. "层序遍历" - BFS
 * 4. "最小距离" - BFS
 * 5. "一层层扩散" - BFS
 *
 * ✅ 题目特征：
 * - 无权图的最短路径
 * - 树的层序遍历
 * - 图的连通性（也可用 DFS）
 * - 状态空间搜索
 *
 * ❌ 不适合 BFS：
 * - 需要所有路径（用 DFS）
 * - 带权图最短路径（用 Dijkstra）
 * - 深度优先的问题
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：基础 BFS（图遍历）
// 时间复杂度：O(V + E)
// 空间复杂度：O(V)
// ============================================================================

class BasicBFS {
public:
    void bfs(vector<vector<int>>& graph, int start) {
        queue<int> q;
        unordered_set<int> visited;

        // 1. 起点入队
        q.push(start);
        visited.insert(start);

        // 2. 队列不空就继续
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // 3. 处理当前节点
            cout << node << " ";

            // 4. 邻居入队
            for (int neighbor : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
    }
};

// ============================================================================
// 模板 2：层序 BFS（记录层数）
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// ============================================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class LevelOrderBFS {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();  // 当前层的节点数
            vector<int> level;

            // 处理当前层的所有节点
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            result.push_back(level);
        }

        return result;
    }
};

// ============================================================================
// 模板 3：最短路径 BFS
// 时间复杂度：O(V + E)
// 空间复杂度：O(V)
// ============================================================================

class ShortestPathBFS {
public:
    int shortestPath(vector<vector<int>>& graph, int start, int end) {
        queue<int> q;
        unordered_set<int> visited;
        int steps = 0;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();

                if (node == end) return steps;

                for (int neighbor : graph[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                }
            }

            steps++;
        }

        return -1;  // 无法到达
    }
};

// ============================================================================
// 模板 4：二维网格 BFS
// 时间复杂度：O(m * n)
// 空间复杂度：O(m * n)
// ============================================================================

class GridBFS {
public:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int bfs(vector<vector<int>>& grid, int startX, int startY,
            int targetValue, int obstacleValue = -1) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        q.push({startX, startY});
        visited[startX][startY] = true;
        int steps = 0;

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();

                // 处理当前位置
                if (grid[x][y] == targetValue) return steps;

                // 四个方向
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        !visited[nx][ny] && grid[nx][ny] != obstacleValue) {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }

            steps++;
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：二叉树的层序遍历
// LeetCode 102: Binary Tree Level Order Traversal
// ============================================================================

class Solution_LevelOrder {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            vector<int> level;

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            result.push_back(level);
        }

        return result;
    }
};

// ============================================================================
// 变体 2：腐烂的橘子
// LeetCode 994: Rotting Oranges
// ============================================================================

class Solution_OrangesRotting {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;

        // 统计新鲜橘子，腐烂橘子入队
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0) return 0;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        int minutes = 0;

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }

            if (!q.empty()) minutes++;
        }

        return fresh == 0 ? minutes : -1;
    }
};

// ============================================================================
// 变体 3：单词接龙
// LeetCode 127: Word Ladder
// ============================================================================

class Solution_LadderLength {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;

        queue<string> q;
        q.push(beginWord);
        int steps = 1;

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();

                if (word == endWord) return steps;

                // 尝试改变每个字符
                for (int j = 0; j < word.size(); j++) {
                    char original = word[j];

                    for (char c = 'a'; c <= 'z'; c++) {
                        word[j] = c;

                        if (wordSet.count(word)) {
                            q.push(word);
                            wordSet.erase(word);
                        }
                    }

                    word[j] = original;
                }
            }

            steps++;
        }

        return 0;
    }
};

// ============================================================================
// 变体 4：01 矩阵
// LeetCode 542: 01 Matrix
// ============================================================================

class Solution_UpdateMatrix {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        // 所有 0 入队
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }

        return dist;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【30 秒讲清 BFS】
 * 1. 先定义场景：
 *    "这题要求最少步数/最短路径，且每条边代价相同，优先用 BFS。"
 * 2. 再讲核心机制：
 *    "BFS 用队列按层扩展，离起点更近的状态会先被处理。"
 * 3. 最后给正确性：
 *    "第一次到达目标节点时，步数一定最小。"
 *
 * 【面试官高频追问】
 * Q1: 为什么不是 DFS？
 * A1: DFS 会先走深，不能保证第一次到达就是最短。
 *
 * Q2: 为什么是 O(V+E)？
 * A2: 每个点最多入队一次，每条边最多检查一次。
 *
 * Q3: visited 什么时候标记？
 * A3: 入队时就标记，避免同一层重复入队。
 */

/*
 * ============================================================================
 * 第六部分：易错点
 * ============================================================================
 */

/*
 * 【常见错误 1：visited 标记时机错误】
 * ❌ 出队后才标记，可能重复入队
 * ✅ 入队时立即标记
 *
 * 【常见错误 2：层数统计错位】
 * ❌ 每处理一个节点就 steps++
 * ✅ 每处理完一整层后 steps++
 *
 * 【常见错误 3：把 BFS 用在带权图】
 * ❌ 边权不等仍用 BFS 求最短路
 * ✅ 带权图用 Dijkstra / Bellman-Ford
 *
 * 【常见错误 4：网格题边界漏判】
 * ❌ 少写一个越界条件导致 RE
 * ✅ 统一写边界函数，四方向复用
 */

/*
 * ============================================================================
 * 第七部分：复杂度分析
 * ============================================================================
 */

/*
 * 【图 BFS】
 * 时间复杂度：O(V + E)
 * 空间复杂度：O(V)（队列 + visited）
 *
 * 【树层序遍历】
 * 时间复杂度：O(n)
 * 空间复杂度：O(w)，w 为最大层宽，最坏 O(n)
 *
 * 【网格 BFS】
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)
 */

/*
 * ============================================================================
 * 第八部分：真题实战
 * ============================================================================
 */

/*
 * ⭐ 简单
 * 1. LC 111: 二叉树的最小深度
 * 2. LC 104: 二叉树的最大深度（BFS/DFS 都可）
 *
 * ⭐⭐ 中等（高频）
 * 3. LC 102: 二叉树的层序遍历 ⭐⭐⭐⭐⭐
 * 4. LC 994: 腐烂的橘子 ⭐⭐⭐⭐⭐
 * 5. LC 542: 01 矩阵 ⭐⭐⭐⭐
 * 6. LC 752: 打开转盘锁 ⭐⭐⭐⭐
 *
 * ⭐⭐⭐ 困难
 * 7. LC 127: 单词接龙 ⭐⭐⭐⭐⭐
 * 8. LC 301: 删除无效的括号
 */

/*
 * ============================================================================
 * 第九部分：完整示例
 * ============================================================================
 */

void testShortestPathBFS() {
    // 无权图示例：0 -> 1,2; 1 -> 3; 2 -> 3; 3 -> 4
    vector<vector<int>> graph = {
        {1, 2},    // 0
        {3},       // 1
        {3},       // 2
        {4},       // 3
        {}         // 4
    };

    ShortestPathBFS solver;
    int steps = solver.shortestPath(graph, 0, 4);
    cout << "0 到 4 的最短步数: " << steps << endl;
}

/*
 * ============================================================================
 * 第十部分：速查表
 * ============================================================================
 */

/*
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │                      BFS 算法速查表                                      │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * 【核心框架】
 * queue<Node> q;
 * visited.insert(start);
 * q.push(start);
 *
 * int steps = 0;
 * while (!q.empty()) {
 *     int sz = q.size();
 *     while (sz--) {
 *         Node cur = q.front(); q.pop();
 *         if (cur == target) return steps;
 *         for (Node nxt : neighbors(cur)) {
 *             if (!visited.count(nxt)) {
 *                 visited.insert(nxt);
 *                 q.push(nxt);
 *             }
 *         }
 *     }
 *     steps++;
 * }
 *
 * 【题型关键词】
 * ✓ 最少步数
 * ✓ 无权最短路
 * ✓ 层序遍历
 * ✓ 多源扩散
 */

int main() {
    testShortestPathBFS();
    cout << "BFS 算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o bfs bfs_template.cpp && ./bfs
 */
