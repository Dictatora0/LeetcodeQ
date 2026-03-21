/*
LeetCode 547. 省份数量 (Number of Provinces)

题目概述 (Problem Summary)
-------------------------
有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，
且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。

省份是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给定一个 n x n 的矩阵 isConnected，其中 isConnected[i][j] = 1 表示第 i 个城市和
第 j 个城市直接相连，否则为 0。

返回矩阵中省份的数量。

关键约束 (Key Constraints)
-------------------------
- 1 <= n <= 200
- n == isConnected.length
- n == isConnected[i].length
- isConnected[i][j] 为 1 或 0
- isConnected[i][i] == 1
- isConnected[i][j] == isConnected[j][i]

示例 (Example)
-------------
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
输出：2
解释：城市 0 和城市 1 相连，城市 2 独立，共 2 个省份

输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
输出：3
解释：三个城市都独立，共 3 个省份

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在无向图中找连通分量的数量
- 每个省份是一个连通分量

关键观察：
1. 这是一个图的连通性问题
2. 可以用 DFS/BFS 解决，但 Union Find 更适合
3. Union Find（并查集）是专门处理动态连通性问题的数据结构

什么是 Union Find（并查集）？
- 一种树形数据结构，用于处理不相交集合的合并和查询
- 支持两种操作：
  1. find(x)：查找 x 所属的集合（返回代表元素）
  2. union(x, y)：合并 x 和 y 所属的两个集合

Union Find 的核心思想：
- 每个集合用一棵树表示
- 树的根节点是集合的代表元素
- parent[x] 表示 x 的父节点
- 如果 parent[x] == x，则 x 是根节点

为什么 Union Find 适合这道题？
1. 需要动态维护连通性（合并城市）
2. 需要查询连通分量数量
3. Union Find 的时间复杂度接近 O(1)

根据这些观察，可以得到 Union Find 解法。
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*
方法一：Union Find（并查集）with Path Compression
(Approach 1: Union Find with Path Compression)

核心思想
--------
使用并查集维护城市的连通性，统计最终的集合数量。

Union Find 数据结构：
1. parent[i]：节点 i 的父节点
2. rank[i]：以节点 i 为根的树的高度（用于优化）

关键操作：
1. find(x)：查找 x 的根节点（集合代表元素）
   - 路径压缩优化：将路径上所有节点直接连到根节点
2. union(x, y)：合并 x 和 y 所属的集合
   - 按秩合并优化：将矮树连到高树上

算法流程：
1. 初始化：每个城市是独立的集合
2. 遍历矩阵：如果两个城市相连，合并它们
3. 统计：计算有多少个独立的集合（根节点数量）

为什么需要路径压缩？
- 没有路径压缩：find 操作可能是 O(n)
- 有路径压缩：find 操作接近 O(1)
- 例如：链状树 1->2->3->4，查找 4 需要 3 步
  路径压缩后：1->2, 1->3, 1->4，再次查找只需 1 步

为什么需要按秩合并？
- 没有按秩合并：树可能退化成链
- 有按秩合并：树的高度保持在 O(log n)
- 例如：合并两棵树时，将矮树连到高树上，避免树变高

复杂度分析
---------
时间复杂度：O(n^2 * α(n))，其中 α(n) 是 Ackermann 函数的反函数，接近 O(1)
  - 遍历矩阵：O(n^2)
  - 每次 union/find：O(α(n)) ≈ O(1)
空间复杂度：O(n)，存储 parent 和 rank 数组
*/
class UnionFind {
public:
    vector<int> parent;  // parent[i] 表示节点 i 的父节点
    vector<int> rank;    // rank[i] 表示以节点 i 为根的树的高度
    int count;           // 集合数量

    // 构造函数：初始化并查集
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);  // 初始高度为 1
        count = n;          // 初始有 n 个独立集合

        // 初始化：每个节点的父节点是自己（独立集合）
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // 查找操作：找到 x 所属集合的根节点
    // 使用路径压缩优化：将路径上所有节点直接连到根节点
    int find(int x) {
        // 如果 x 不是根节点，递归查找根节点
        if (parent[x] != x) {
            // 路径压缩：将 x 直接连到根节点
            // 这样下次查找 x 时，只需一步就能找到根节点
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并操作：合并 x 和 y 所属的两个集合
    // 使用按秩合并优化：将矮树连到高树上
    void unite(int x, int y) {
        int rootX = find(x);  // 找到 x 的根节点
        int rootY = find(y);  // 找到 y 的根节点

        // 如果已经在同一个集合，不需要合并
        if (rootX == rootY) {
            return;
        }

        // 按秩合并：将矮树连到高树上
        // 这样可以保持树的高度尽可能小
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;  // 将 rootX 连到 rootY 下
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;  // 将 rootY 连到 rootX 下
        } else {
            // 高度相同，随意选一个作为根
            parent[rootY] = rootX;
            rank[rootX]++;  // 高度增加 1
        }

        count--;  // 集合数量减 1
    }

    // 获取集合数量
    int getCount() {
        return count;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);

        // 遍历矩阵，合并相连的城市
        // 只需遍历上三角矩阵（因为矩阵是对称的）
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    uf.unite(i, j);  // 合并城市 i 和城市 j
                }
            }
        }

        return uf.getCount();  // 返回集合数量（省份数量）
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]

初始状态：
城市：    0   1   2
parent: [0,  1,  2]  // 每个城市是独立集合
rank:   [1,  1,  1]
count:  3

可视化：
  0   1   2
  ↓   ↓   ↓
  0   1   2  (每个节点指向自己)

第 1 步：处理 isConnected[0][1] = 1
- 合并城市 0 和城市 1
- find(0) = 0, find(1) = 1
- rank[0] == rank[1]，将 1 连到 0 下
- parent[1] = 0, rank[0] = 2, count = 2

可视化：
    0       2
    ↓       ↓
  0 1       2

第 2 步：处理 isConnected[0][2] = 0
- 不相连，跳过

第 3 步：处理 isConnected[1][2] = 0
- 不相连，跳过

最终状态：
parent: [0, 0, 2]
rank:   [2, 1, 1]
count:  2

可视化：
    0       2
   / \      ↓
  0   1     2

省份 1：{0, 1}
省份 2：{2}
答案：2

详细的 Union 操作示例：
假设有 5 个城市，连接关系：0-1, 1-2, 3-4

初始：
  0   1   2   3   4
  ↓   ↓   ↓   ↓   ↓
  0   1   2   3   4

union(0, 1)：
    0   2   3   4
   / \  ↓   ↓   ↓
  0   1 2   3   4

union(1, 2)：
- find(1) = 0（路径压缩后）
- find(2) = 2
- 合并 0 和 2
      0       3   4
    / | \     ↓   ↓
   0  1  2    3   4

union(3, 4)：
      0       3
    / | \    / \
   0  1  2  3   4

最终：2 个省份

路径压缩示例：
假设有链状树：1 -> 2 -> 3 -> 4 -> 5

查找 find(1) 前：
  5
  ↑
  4
  ↑
  3
  ↑
  2
  ↑
  1

查找 find(1) 后（路径压缩）：
      5
    / | \ \
   1  2  3 4

所有节点直接连到根节点，下次查找只需 O(1)
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 所有城市独立：返回 n
2. 所有城市相连：返回 1
3. 单个城市：返回 1
4. 两个省份：正确合并和计数
*/

/*
Union Find 关键点总结 (Union Find Key Takeaways)
----------------------------------------------
1. 什么是 find() 操作？
   - 查找节点所属集合的根节点（代表元素）
   - 路径压缩：将路径上所有节点直接连到根节点
   - 优化后时间复杂度：O(α(n)) ≈ O(1)

2. 什么是 union() 操作？
   - 合并两个节点所属的集合
   - 按秩合并：将矮树连到高树上
   - 优化后时间复杂度：O(α(n)) ≈ O(1)

3. 为什么需要路径压缩？
   - 避免树退化成链，保持查找效率
   - 将 O(n) 的查找优化到 O(1)

4. 为什么需要按秩合并？
   - 保持树的高度尽可能小
   - 避免树变得过高，影响查找效率

5. Union Find vs DFS：
   - Union Find：适合动态连通性问题，支持在线查询
   - DFS：适合静态图遍历，需要重新遍历才能查询
   - 对于这道题，Union Find 更优雅

6. 时间复杂度：
   - 单次操作：O(α(n))，其中 α(n) 是 Ackermann 函数的反函数
   - α(n) 增长极慢：α(10^80) ≈ 4，实际应用中可视为 O(1)
*/

/*
方法二：DFS 深度优先搜索 (Approach 2: DFS for Comparison)

核心思想
--------
使用 DFS 遍历每个连通分量，统计连通分量数量。

算法流程：
1. 使用 visited 数组标记已访问的城市
2. 遍历所有城市，遇到未访问的城市启动 DFS
3. DFS 遍历整个连通分量并标记
4. 统计 DFS 调用次数

复杂度分析
---------
时间复杂度：O(n^2)，遍历矩阵
空间复杂度：O(n)，visited 数组和递归栈
*/
class Solution_DFS {
public:
    void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int i) {
        visited[i] = true;
        for (int j = 0; j < isConnected.size(); j++) {
            if (isConnected[i][j] == 1 && !visited[j]) {
                dfs(isConnected, visited, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(isConnected, visited, i);
                count++;
            }
        }

        return count;
    }
};

int main() {
    Solution solution;

    // 测试用例 1：两个省份
    // 城市 0 和 1 相连，城市 2 独立
    vector<vector<int>> isConnected1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int result1 = solution.findCircleNum(isConnected1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 2)" << endl;

    // 测试用例 2：三个独立省份
    vector<vector<int>> isConnected2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    int result2 = solution.findCircleNum(isConnected2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 3)" << endl;

    // 测试用例 3：一个大省份
    vector<vector<int>> isConnected3 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    int result3 = solution.findCircleNum(isConnected3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: 1)" << endl;

    // 测试用例 4：复杂连接
    // 城市 0-1-2 相连，城市 3-4 相连
    vector<vector<int>> isConnected4 = {
        {1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}
    };
    int result4 = solution.findCircleNum(isConnected4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 2)" << endl;

    // 测试用例 5：DFS 方法
    Solution_DFS solution_dfs;
    vector<vector<int>> isConnected5 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int result5 = solution_dfs.findCircleNum(isConnected5);
    cout << "测试用例 5 (DFS) - 输出: " << result5 << " (期望: 2)" << endl;

    return 0;
}
