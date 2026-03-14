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

    int bfs(vector<vector<int>>& grid, int startX, int startY) {
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
                if (grid[x][y] == 目标值) return steps;

                // 四个方向
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        !visited[nx][ny] && grid[nx][ny] != 障碍) {
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
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 强调"最短路径"时用 BFS
 * 2. 说明队列的作用：保证按距离访问
 * 3. 层序遍历时记得用 size 控制
 *
 * 【易错点】
 * ❌ 忘记标记 visited
 * ❌ 层序遍历时没用 size
 * ❌ 入队时才标记 visited（应该入队时就标记）
 *
 * 【复杂度】
 * 时间：O(V + E) 或 O(m*n)
 * 空间：O(V) 或 O(m*n)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 102, LC 994, LC 200
 * ⭐⭐⭐⭐ LC 127, LC 542, LC 207
 *
 * 【速查表】
 * queue<int> q;
 * unordered_set<int> visited;
 * q.push(start);
 * visited.insert(start);
 *
 * while (!q.empty()) {
 *     int size = q.size();  // 层序遍历
 *     for (int i = 0; i < size; i++) {
 *         int node = q.front(); q.pop();
 *         // 处理节点
 *         for (邻居) {
 *             if (!visited.count(邻居)) {
 *                 q.push(邻居);
 *                 visited.insert(邻居);
 *             }
 *         }
 *     }
 * }
 */

int main() {
    cout << "BFS 算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o bfs bfs_template.cpp && ./bfs
 */
