/*
LeetCode 200. 岛屿数量 (Number of Islands)

题目概述 (Problem Summary)
-------------------------
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

关键约束 (Key Constraints)
-------------------------
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 300
- grid[i][j] 的值为 '0' 或 '1'

示例 (Example)
-------------
输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 统计二维网格中连通分量的个数
- 每个岛屿是一个连通分量，由相邻的 '1' 组成

关键观察：
1. 这是一个典型的图遍历问题，可以用 DFS 或 BFS 解决
2. 遍历网格，每次遇到 '1' 时，说明发现了一个新岛屿
3. 从这个 '1' 开始，用 DFS/BFS 将整个岛屿标记为已访问（改为 '0'）
4. 继续遍历，重复上述过程，直到遍历完整个网格

为什么要标记为 '0'？
- 避免重复计数同一个岛屿
- 相当于"淹没"已经访问过的陆地
- 也可以用额外的 visited 数组，但直接修改原数组更节省空间

网格遍历的四个方向：
- 上：(x-1, y)
- 下：(x+1, y)
- 左：(x, y-1)
- 右：(x, y+1)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
方法一：DFS（深度优先搜索）(Approach 1: Depth-First Search)

核心思想
--------
使用 DFS 遍历网格，每次发现一个 '1' 时，从该位置开始 DFS，将整个岛屿的所有 '1' 标记为 '0'。

算法流程：
1. 遍历整个网格的每个位置 (i, j)
2. 如果 grid[i][j] == '1'：
   a. 岛屿数量 +1
   b. 从 (i, j) 开始 DFS，将整个岛屿标记为 '0'
3. DFS 函数：
   a. 检查边界条件和当前位置是否为 '1'
   b. 将当前位置标记为 '0'
   c. 递归访问四个相邻位置

为什么使用 DFS？
- DFS 能够深入探索，一次性标记完整个岛屿
- 实现简洁，代码量少
- 适合处理连通性问题

复杂度分析
---------
时间复杂度：O(m * n)
- 每个格子最多被访问一次
- m 是行数，n 是列数

空间复杂度：O(m * n)
- 最坏情况下，整个网格都是陆地，递归深度为 m * n
- 平均情况下，递归深度取决于最大岛屿的大小

其中：
m = grid.length（行数）
n = grid[0].length（列数）
*/
class Solution {
public:
    int row, col;
    // 四个方向：下、上、右、左
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    // DFS 函数：从 (x, y) 开始，标记整个岛屿
    // grid: 二维网格
    // x, y: 当前位置坐标
    void dfs(vector<vector<char>>& grid, int x, int y) {
        // 边界检查：超出网格范围
        if (x < 0 || x >= row || y < 0 || y >= col) {
            return;
        }

        // 如果当前位置是水或已访问过的陆地，直接返回
        if (grid[x][y] == '0') {
            return;
        }

        // 标记当前位置为已访问（将陆地变为水）
        grid[x][y] = '0';

        // 递归访问四个相邻位置
        for (auto& d : dirs) {
            dfs(grid, x + d[0], y + d[1]);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        // 获取网格的行数和列数
        row = grid.size();
        col = grid[0].size();

        int ans = 0;  // 岛屿数量

        // 遍历整个网格
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // 发现一个新岛屿
                if (grid[i][j] == '1') {
                    ans++;  // 岛屿数量 +1
                    dfs(grid, i, j);  // 标记整个岛屿
                }
            }
        }

        return ans;
    }
};

/*
方法二：BFS（广度优先搜索）(Approach 2: Breadth-First Search)

核心思想
--------
使用 BFS 遍历网格，每次发现一个 '1' 时，从该位置开始 BFS，将整个岛屿的所有 '1' 标记为 '0'。

算法流程：
1. 遍历整个网格的每个位置 (i, j)
2. 如果 grid[i][j] == '1'：
   a. 岛屿数量 +1
   b. 从 (i, j) 开始 BFS，将整个岛屿标记为 '0'
3. BFS 函数：
   a. 将起点加入队列，标记为 '0'
   b. 当队列不为空时：
      - 取出队首元素
      - 检查四个相邻位置
      - 如果相邻位置是 '1'，标记为 '0' 并加入队列

BFS vs DFS：
- BFS 使用队列，按层遍历
- DFS 使用递归（或栈），深度优先
- 对于本题，两者效果相同，选择哪个取决于个人偏好

复杂度分析
---------
时间复杂度：O(m * n)
- 每个格子最多被访问一次

空间复杂度：O(min(m, n))
- 队列中最多存储 O(min(m, n)) 个元素
- 最坏情况是网格呈对角线形状的岛屿
*/
class Solution_BFS {
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        int ans = 0;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    ans++;
                    // BFS 标记整个岛屿
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = '0';  // 标记起点

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        // 检查四个相邻位置
                        for (auto& d : dirs) {
                            int nx = x + d[0];
                            int ny = y + d[1];

                            // 边界检查和陆地检查
                            if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == '1') {
                                grid[nx][ny] = '0';  // 标记为已访问
                                q.push({nx, ny});    // 加入队列
                            }
                        }
                    }
                }
            }
        }

        return ans;
    }
};

/*
方法三：并查集 (Approach 3: Union-Find)

核心思想
--------
使用并查集数据结构，将相邻的陆地合并到同一个集合中，最后统计集合的数量。

算法流程：
1. 初始化并查集，每个陆地格子是一个独立的集合
2. 遍历网格，对于每个陆地格子：
   - 检查右边和下边的相邻格子
   - 如果相邻格子也是陆地，合并两个集合
3. 统计最终的集合数量（即岛屿数量）

优点：
- 适合动态连通性问题
- 支持在线查询（边添加边查询）

缺点：
- 代码复杂度较高
- 对于本题，DFS/BFS 更简洁

复杂度分析
---------
时间复杂度：O(m * n * α(m * n))
- α 是阿克曼函数的反函数，增长极其缓慢，可以认为是常数

空间复杂度：O(m * n)
- 需要存储并查集的 parent 和 rank 数组
*/
class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count;  // 集合数量

    UnionFind(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        count = 0;

        parent.resize(m * n);
        rank.resize(m * n, 0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    parent[i * n + j] = i * n + j;
                    count++;
                }
            }
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // 按秩合并
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            count--;  // 合并后集合数量减 1
        }
    }

    int getCount() {
        return count;
    }
};

class Solution_UnionFind {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        UnionFind uf(grid);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    // 检查右边
                    if (j + 1 < n && grid[i][j + 1] == '1') {
                        uf.unite(i * n + j, i * n + j + 1);
                    }
                    // 检查下边
                    if (i + 1 < m && grid[i + 1][j] == '1') {
                        uf.unite(i * n + j, (i + 1) * n + j);
                    }
                }
            }
        }

        return uf.getCount();
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：grid = [
  ["1","1","0"],
  ["1","0","0"],
  ["0","0","1"]
]

使用 DFS 方法的执行过程：

初始状态：ans = 0

遍历 (0,0)：grid[0][0] = '1'
- ans = 1
- DFS 从 (0,0) 开始：
  - 标记 (0,0) = '0'
  - 访问 (0,1)：grid[0][1] = '1'
    - 标记 (0,1) = '0'
    - 访问 (1,1)：grid[1][1] = '0'，返回
    - 访问 (0,2)：grid[0][2] = '0'，返回
  - 访问 (1,0)：grid[1][0] = '1'
    - 标记 (1,0) = '0'
    - 访问四个方向，都是 '0' 或越界，返回

遍历 (0,1)：grid[0][1] = '0'（已被标记），跳过
遍历 (0,2)：grid[0][2] = '0'，跳过
遍历 (1,0)：grid[1][0] = '0'（已被标记），跳过
遍历 (1,1)：grid[1][1] = '0'，跳过
遍历 (1,2)：grid[1][2] = '0'，跳过
遍历 (2,0)：grid[2][0] = '0'，跳过
遍历 (2,1)：grid[2][1] = '0'，跳过
遍历 (2,2)：grid[2][2] = '1'
- ans = 2
- DFS 从 (2,2) 开始：
  - 标记 (2,2) = '0'
  - 访问四个方向，都是 '0' 或越界，返回

最终 ans = 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：DFS
- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)（递归栈）
- 优点：代码简洁，易于理解
- 缺点：递归深度可能很大，存在栈溢出风险

方法二：BFS
- 时间复杂度：O(m * n)
- 空间复杂度：O(min(m, n))
- 优点：空间效率更高，不会栈溢出
- 缺点：需要额外的队列

方法三：并查集
- 时间复杂度：O(m * n * α(m * n)) ≈ O(m * n)
- 空间复杂度：O(m * n)
- 优点：支持动态连通性查询
- 缺点：代码复杂，对于本题有些"杀鸡用牛刀"

推荐使用 DFS 或 BFS，代码简洁且效率高。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全是水：grid = [["0","0"],["0","0"]]，返回 0
2. 全是陆地：grid = [["1","1"],["1","1"]]，返回 1
3. 单个格子：grid = [["1"]]，返回 1
4. 多个独立岛屿：需要正确计数
5. 复杂形状的岛屿：L 型、环形等，DFS/BFS 都能正确处理
*/

/*
网格遍历模板总结 (Grid Traversal Template Summary)
-----------------------------------------------
DFS 模板：

void dfs(vector<vector<char>>& grid, int x, int y) {
    // 1. 边界检查
    if (x < 0 || x >= m || y < 0 || y >= n) return;

    // 2. 终止条件检查
    if (grid[x][y] == '0') return;

    // 3. 标记当前位置
    grid[x][y] = '0';

    // 4. 递归访问四个方向
    dfs(grid, x + 1, y);  // 下
    dfs(grid, x - 1, y);  // 上
    dfs(grid, x, y + 1);  // 右
    dfs(grid, x, y - 1);  // 左
}

BFS 模板：

void bfs(vector<vector<char>>& grid, int sx, int sy) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    grid[sx][sy] = '0';

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                grid[nx][ny] = '0';
                q.push({nx, ny});
            }
        }
    }
}

关键点：
1. 边界检查：防止数组越界
2. 标记已访问：避免重复访问
3. 四个方向遍历：上下左右
4. 终止条件：遇到水或边界
*/

int main() {
    Solution solution;

    // 测试用例 1：单个岛屿
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    int result1 = solution.numIslands(grid1);
    cout << "测试用例 1 - 岛屿数量: " << result1 << " (期望: 1)" << endl;

    // 测试用例 2：多个岛屿
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int result2 = solution.numIslands(grid2);
    cout << "测试用例 2 - 岛屿数量: " << result2 << " (期望: 3)" << endl;

    // 测试用例 3：全是水
    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'}
    };
    int result3 = solution.numIslands(grid3);
    cout << "测试用例 3 - 岛屿数量: " << result3 << " (期望: 0)" << endl;

    // 测试用例 4：全是陆地
    vector<vector<char>> grid4 = {
        {'1','1'},
        {'1','1'}
    };
    int result4 = solution.numIslands(grid4);
    cout << "测试用例 4 - 岛屿数量: " << result4 << " (期望: 1)" << endl;

    return 0;
}
