/*
LeetCode 994. 腐烂的橘子 (Rotting Oranges)

题目概述 (Problem Summary)
-------------------------
在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
- 值 0 代表空单元格
- 值 1 代表新鲜橘子
- 值 2 代表腐烂的橘子

每分钟，腐烂的橘子周围 4 个方向上相邻的新鲜橘子都会腐烂。

返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

关键约束 (Key Constraints)
-------------------------
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 10
- grid[i][j] 仅为 0、1 或 2

示例 (Example)
-------------
输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4

输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行，第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。

输入：grid = [[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 多源 BFS 问题：从多个腐烂橘子同时开始扩散
- 求最短时间：BFS 天然按层遍历，每层代表一分钟
- 连通性检查：判断是否所有新鲜橘子都能被腐烂

关键观察：
1. 这是一个典型的多源 BFS 问题
2. 所有腐烂的橘子同时开始扩散，而不是依次扩散
3. 需要记录新鲜橘子的数量，最后检查是否全部腐烂
4. BFS 的层数就是经过的分钟数

为什么使用 BFS 而不是 DFS？
- BFS 按层遍历，每层代表一个时间单位
- DFS 无法保证同时扩散的效果
- BFS 能够自然地计算最短时间

算法核心：
1. 将所有初始腐烂的橘子加入队列（多源起点）
2. 统计新鲜橘子的数量
3. BFS 按层遍历，每层代表一分钟
4. 每次腐烂一个新鲜橘子，计数器减 1
5. 最后检查是否还有新鲜橘子

特殊情况：
- 一开始就没有新鲜橘子：返回 0
- 存在无法到达的新鲜橘子：返回 -1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
方法一：多源 BFS (Approach 1: Multi-Source BFS)

核心思想
--------
将所有腐烂的橘子作为起点，同时进行 BFS，按层遍历计算时间。

算法流程：
1. 初始化：
   a. 遍历网格，将所有腐烂的橘子 (2) 加入队列
   b. 统计新鲜橘子 (1) 的数量
   c. 如果没有新鲜橘子，直接返回 0
2. BFS 按层遍历：
   a. 记录当前层的大小（当前分钟内腐烂的橘子数量）
   b. 处理当前层的所有橘子：
      - 检查四个方向的相邻橘子
      - 如果是新鲜橘子，标记为腐烂，加入队列，新鲜橘子数量 -1
   c. 如果本轮有橘子腐烂，分钟数 +1
3. 检查结果：
   - 如果还有新鲜橘子，返回 -1
   - 否则返回分钟数

为什么要按层遍历？
- 同一层的橘子是在同一分钟内腐烂的
- 需要记录层数（分钟数），而不是总的步数
- 使用 size 变量记录当前层的大小，确保按层处理

为什么需要 rotten 标志？
- 区分"队列为空"和"本轮没有橘子腐烂"
- 只有在本轮有橘子腐烂时，才增加分钟数
- 避免最后一轮多计数一分钟

复杂度分析
---------
时间复杂度：O(m * n)
- 每个格子最多被访问一次
- m 是行数，n 是列数

空间复杂度：O(m * n)
- 队列最多存储所有格子
- 最坏情况是所有格子都是橘子

其中：
m = grid.length（行数）
n = grid[0].length（列数）
*/
class Solution {
public:
    // 四个方向：下、上、右、左
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    int orangesRotting(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();

        queue<pair<int, int>> q;  // 存储腐烂橘子的位置

        int fresh = 0;   // 新鲜橘子的数量
        int minute = 0;  // 经过的分钟数

        // 初始化：统计新鲜橘子数量，将腐烂橘子加入队列
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});  // 腐烂橘子加入队列
                }
                if (grid[i][j] == 1) {
                    fresh++;  // 统计新鲜橘子
                }
            }
        }

        // 特殊情况：一开始就没有新鲜橘子
        if (fresh == 0) {
            return 0;
        }

        // BFS 按层遍历
        while (!q.empty()) {
            int size = q.size();  // 当前层的大小（当前分钟内腐烂的橘子数量）
            bool rotten = false;  // 标记本轮是否有橘子腐烂

            // 处理当前层的所有橘子
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();

                // 检查四个方向的相邻橘子
                for (auto& d : dirs) {
                    int nx = x + d[0];
                    int ny = y + d[1];

                    // 边界检查和新鲜橘子检查
                    if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;  // 标记为腐烂
                        q.push({nx, ny});  // 加入队列
                        fresh--;           // 新鲜橘子数量 -1
                        rotten = true;     // 标记本轮有橘子腐烂
                    }
                }
            }

            // 如果本轮有橘子腐烂，分钟数 +1
            if (rotten) {
                minute++;
            }
        }

        // 如果还有新鲜橘子，说明无法全部腐烂
        if (fresh > 0) {
            return -1;
        }

        return minute;
    }
};

/*
方法二：BFS + 时间戳 (Approach 2: BFS with Timestamp)

核心思想
--------
在队列中存储橘子的位置和腐烂时间，不需要按层遍历。

算法流程：
1. 队列存储 {x, y, time}，time 表示该橘子腐烂的时间
2. 初始腐烂的橘子时间为 0
3. BFS 过程中，新腐烂的橘子时间为当前时间 +1
4. 记录最大时间即为答案

优点：
- 不需要按层遍历，代码稍微简洁
- 时间戳更直观

缺点：
- 需要额外存储时间信息
- 空间开销稍大

复杂度分析
---------
时间复杂度：O(m * n)
空间复杂度：O(m * n)
*/
class Solution_Timestamp {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        queue<tuple<int, int, int>> q;  // {x, y, time}
        int fresh = 0;
        int maxTime = 0;

        // 初始化
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j, 0});  // 初始腐烂橘子，时间为 0
                }
                if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0) {
            return 0;
        }

        // BFS
        while (!q.empty()) {
            auto [x, y, time] = q.front();
            q.pop();

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    q.push({nx, ny, time + 1});  // 新腐烂橘子，时间 +1
                    fresh--;
                    maxTime = max(maxTime, time + 1);  // 更新最大时间
                }
            }
        }

        return fresh > 0 ? -1 : maxTime;
    }
};

/*
方法三：原地标记 + 多轮遍历 (Approach 3: In-Place Marking with Multiple Passes)

核心思想
--------
不使用队列，每轮遍历整个网格，标记新腐烂的橘子。

算法流程：
1. 每轮遍历网格，找到所有新鲜橘子
2. 检查每个新鲜橘子的四个方向是否有腐烂橘子
3. 如果有，标记为新腐烂（使用特殊值，如 3）
4. 遍历结束后，将所有新腐烂的橘子改为 2
5. 重复上述过程，直到没有新橘子腐烂

优点：
- 不需要额外的队列空间
- 代码逻辑简单

缺点：
- 时间效率低，需要多轮遍历
- 不推荐使用，仅作为对比

复杂度分析
---------
时间复杂度：O(m * n * k)
- k 是最大分钟数，最坏情况 O(m * n)
- 总时间复杂度 O((m * n)^2)

空间复杂度：O(1)
- 只使用常数额外空间
*/
class Solution_MultiPass {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        int minute = 0;
        bool hasRotten = true;

        // 持续遍历，直到没有新橘子腐烂
        while (hasRotten) {
            hasRotten = false;

            // 遍历网格，标记新腐烂的橘子
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (grid[i][j] == 1) {
                        // 检查四个方向是否有腐烂橘子
                        for (auto& d : dirs) {
                            int ni = i + d[0];
                            int nj = j + d[1];

                            if (ni >= 0 && ni < row && nj >= 0 && nj < col && grid[ni][nj] == 2) {
                                grid[i][j] = 3;  // 标记为新腐烂（临时值）
                                hasRotten = true;
                                break;
                            }
                        }
                    }
                }
            }

            // 将所有新腐烂的橘子改为 2
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (grid[i][j] == 3) {
                        grid[i][j] = 2;
                    }
                }
            }

            if (hasRotten) {
                minute++;
            }
        }

        // 检查是否还有新鲜橘子
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }

        return minute;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：grid = [[2,1,1],[1,1,0],[0,1,1]]

初始状态：
2 1 1
1 1 0
0 1 1

fresh = 6, minute = 0
队列：[(0,0)]

第 1 分钟：
- 处理 (0,0)：
  - 检查 (1,0)：grid[1][0] = 1，标记为 2，加入队列，fresh = 5
  - 检查 (0,1)：grid[0][1] = 1，标记为 2，加入队列，fresh = 4
- minute = 1

状态：
2 2 1
2 1 0
0 1 1

队列：[(1,0), (0,1)]

第 2 分钟：
- 处理 (1,0)：
  - 检查 (1,1)：grid[1][1] = 1，标记为 2，加入队列，fresh = 3
  - 检查 (2,0)：grid[2][0] = 0，跳过
- 处理 (0,1)：
  - 检查 (0,2)：grid[0][2] = 1，标记为 2，加入队列，fresh = 2
  - 检查 (1,1)：已经是 2，跳过
- minute = 2

状态：
2 2 2
2 2 0
0 1 1

队列：[(1,1), (0,2)]

第 3 分钟：
- 处理 (1,1)：
  - 检查 (2,1)：grid[2][1] = 1，标记为 2，加入队列，fresh = 1
- 处理 (0,2)：
  - 所有方向都不是新鲜橘子
- minute = 3

状态：
2 2 2
2 2 0
0 2 1

队列：[(2,1)]

第 4 分钟：
- 处理 (2,1)：
  - 检查 (2,2)：grid[2][2] = 1，标记为 2，加入队列，fresh = 0
- minute = 4

最终状态：
2 2 2
2 2 0
0 2 2

fresh = 0，返回 minute = 4
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：多源 BFS（按层遍历）
- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)
- 优点：效率高，代码清晰，推荐使用
- 缺点：需要理解按层遍历的技巧

方法二：BFS + 时间戳
- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)
- 优点：时间戳更直观
- 缺点：空间开销稍大

方法三：原地标记 + 多轮遍历
- 时间复杂度：O((m * n)^2)
- 空间复杂度：O(1)
- 优点：空间效率高
- 缺点：时间效率低，不推荐

推荐使用方法一，效率高且代码清晰。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 一开始就没有新鲜橘子：返回 0
2. 没有腐烂橘子但有新鲜橘子：返回 -1
3. 存在孤立的新鲜橘子：返回 -1
4. 单个格子：根据格子内容返回相应结果
5. 全是空格子：返回 0
*/

/*
多源 BFS 模板总结 (Multi-Source BFS Template Summary)
---------------------------------------------------
多源 BFS 的通用框架：

int multiSourceBFS(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    int target = 0;  // 目标数量
    int time = 0;

    // 1. 初始化：将所有源点加入队列
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == SOURCE) {
                q.push({i, j});
            }
            if (grid[i][j] == TARGET) {
                target++;
            }
        }
    }

    // 2. BFS 按层遍历
    while (!q.empty()) {
        int size = q.size();  // 当前层大小
        bool changed = false;

        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            // 检查四个方向
            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (isValid(nx, ny) && grid[nx][ny] == TARGET) {
                    grid[nx][ny] = SOURCE;
                    q.push({nx, ny});
                    target--;
                    changed = true;
                }
            }
        }

        if (changed) {
            time++;
        }
    }

    // 3. 检查结果
    return target == 0 ? time : -1;
}

关键点：
1. 将所有源点同时加入队列
2. 按层遍历，每层代表一个时间单位
3. 使用 size 变量确保按层处理
4. 最后检查是否达到目标状态
*/

/*
BFS vs DFS 在网格问题中的选择 (BFS vs DFS in Grid Problems)
--------------------------------------------------------
使用 BFS 的场景：
1. 求最短路径/最短时间
2. 多源扩散问题
3. 层序遍历
4. 需要按距离处理

使用 DFS 的场景：
1. 连通性问题（岛屿数量）
2. 路径存在性
3. 回溯问题
4. 不关心距离

本题特点：
- 需要求最短时间 -> 使用 BFS
- 多个源点同时扩散 -> 多源 BFS
- 按层遍历，每层代表一分钟
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    vector<vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    int result1 = solution.orangesRotting(grid1);
    cout << "测试用例 1 - 所需分钟数: " << result1 << " (期望: 4)" << endl;

    // 测试用例 2：存在孤立橘子
    vector<vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    int result2 = solution.orangesRotting(grid2);
    cout << "测试用例 2 - 所需分钟数: " << result2 << " (期望: -1)" << endl;

    // 测试用例 3：没有新鲜橘子
    vector<vector<int>> grid3 = {
        {0, 2}
    };
    int result3 = solution.orangesRotting(grid3);
    cout << "测试用例 3 - 所需分钟数: " << result3 << " (期望: 0)" << endl;

    // 测试用例 4：全是新鲜橘子，没有腐烂橘子
    vector<vector<int>> grid4 = {
        {1, 1},
        {1, 1}
    };
    int result4 = solution.orangesRotting(grid4);
    cout << "测试用例 4 - 所需分钟数: " << result4 << " (期望: -1)" << endl;

    // 测试用例 5：单个腐烂橘子
    vector<vector<int>> grid5 = {
        {2}
    };
    int result5 = solution.orangesRotting(grid5);
    cout << "测试用例 5 - 所需分钟数: " << result5 << " (期望: 0)" << endl;

    // 测试用例 6：复杂情况
    vector<vector<int>> grid6 = {
        {2, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    int result6 = solution.orangesRotting(grid6);
    cout << "测试用例 6 - 所需分钟数: " << result6 << " (期望: 6)" << endl;

    return 0;
}
