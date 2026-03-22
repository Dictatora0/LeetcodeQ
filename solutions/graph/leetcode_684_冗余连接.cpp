/*
LeetCode 684. 冗余连接 (Redundant Connection)

题目概述 (Problem Summary)
-------------------------
树可以看成是一个连通且无环的无向图。

给定往一棵 n 个节点（节点值 1～n）的树中添加一条边后的图。添加的边的两个顶点
包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。

图的信息记录于长度为 n 的二维数组 edges，edges[i] = [ai, bi] 表示图中在 ai 和 bi
之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，
则返回数组 edges 中最后出现的那条边。

关键约束 (Key Constraints)
-------------------------
- n == edges.length
- 3 <= n <= 1000
- edges[i].length == 2
- 1 <= ai < bi <= n
- ai != bi
- 图中没有重复的边
- 给定的图是连通的

示例 (Example)
-------------
输入：edges = [[1,2],[1,3],[2,3]]
输出：[2,3]
解释：删除 [2,3] 后，图变成树

输入：edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
输出：[1,4]
解释：删除 [1,4] 后，图变成树

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在无向图中检测环，找到导致环的那条边
- 树的定义：n 个节点，n-1 条边，无环，连通

关键观察：
1. 树有 n 个节点，n-1 条边
2. 题目给了 n 条边，多了一条
3. 多的这条边导致了环的出现
4. 需要找到最后出现的那条导致环的边

为什么使用 Union Find？
- Union Find 天然支持环检测
- 当合并两个节点时，如果它们已经在同一个集合，说明形成了环
- 这条边就是冗余的边

Union Find 检测环的原理：
- 初始时，每个节点是独立的集合
- 遍历边，尝试合并两个节点
- 如果两个节点已经连通（在同一个集合），说明这条边会形成环
- 返回这条边

为什么 Union Find 比 DFS 更好？
- DFS 需要每次都重新遍历图来检测环，时间复杂度 O(n^2)
- Union Find 可以在线检测，每次操作 O(α(n)) ≈ O(1)，总时间 O(n)

根据这些观察，可以得到 Union Find 解法。
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*
方法一：Union Find with Cycle Detection
(Approach 1: Union Find with Cycle Detection)

核心思想
--------
使用并查集动态维护连通性，当发现两个节点已经连通时，说明这条边会形成环。

Union Find 数据结构：
1. parent[i]：节点 i 的父节点
2. rank[i]：以节点 i 为根的树的高度

关键操作：
1. find(x)：查找 x 的根节点，使用路径压缩优化
2. unite(x, y)：合并 x 和 y 所属的集合
   - 如果 x 和 y 已经在同一个集合，返回 false（检测到环）
   - 否则合并两个集合，返回 true

算法流程：
1. 初始化并查集：每个节点是独立的集合
2. 遍历所有边：
   - 尝试合并边的两个端点
   - 如果合并失败（已经连通），说明这条边导致环
   - 返回这条边
3. 如果所有边都能成功合并，返回最后一条边（题目保证有解）

为什么这个算法正确？
- 树的性质：n 个节点，n-1 条边，无环
- 第 n 条边必然导致环（因为前 n-1 条边已经连通所有节点）
- Union Find 能够检测到第一条导致环的边
- 题目要求返回最后出现的边，所以遍历到最后

复杂度分析
---------
时间复杂度：O(n * α(n))，其中 α(n) 是 Ackermann 函数的反函数，接近 O(1)
  - 遍历 n 条边：O(n)
  - 每次 union/find：O(α(n)) ≈ O(1)
空间复杂度：O(n)，存储 parent 和 rank 数组
*/
class UnionFind {
public:
    vector<int> parent;  // parent[i] 表示节点 i 的父节点
    vector<int> rank;    // rank[i] 表示以节点 i 为根的树的高度

    // 构造函数：初始化并查集
    UnionFind(int n) {
        parent.resize(n + 1);  // 节点编号从 1 开始，所以需要 n+1
        rank.resize(n + 1, 1);

        // 初始化：每个节点的父节点是自己
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    // 查找操作：找到 x 所属集合的根节点
    // 使用路径压缩优化
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    // 合并操作：合并 x 和 y 所属的两个集合
    // 返回值：true 表示合并成功，false 表示已经在同一个集合（检测到环）
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // 如果 x 和 y 已经在同一个集合，说明这条边会形成环
        // 返回 false 表示检测到环
        if (rootX == rootY) {
            return false;
        }

        // 按秩合并：将矮树连到高树上
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true;  // 合并成功
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n);

        // 遍历所有边
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            // 尝试合并 u 和 v
            // 如果合并失败（返回 false），说明 u 和 v 已经连通
            // 这条边就是导致环的冗余边
            if (!uf.unite(u, v)) {
                return edge;  // 返回导致环的边
            }
        }

        // 题目保证有解，不会执行到这里
        return {};
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：edges = [[1,2],[1,3],[2,3]]

初始状态：
节点：    1   2   3
parent: [1,  2,  3]  // 每个节点是独立集合
rank:   [1,  1,  1]

可视化：
  1   2   3
  ↓   ↓   ↓
  1   2   3

第 1 步：处理边 [1,2]
- find(1) = 1, find(2) = 2
- 不在同一个集合，合并成功
- parent[2] = 1

可视化：
    1       3
   / \      ↓
  1   2     3

第 2 步：处理边 [1,3]
- find(1) = 1, find(3) = 3
- 不在同一个集合，合并成功
- parent[3] = 1

可视化：
      1
    / | \
   1  2  3

第 3 步：处理边 [2,3]
- find(2) = find(parent[2]) = find(1) = 1
- find(3) = find(parent[3]) = find(1) = 1
- 已经在同一个集合！检测到环
- 返回 [2,3]

关键观察：
- 节点 2 和节点 3 已经通过节点 1 连通
- 边 [2,3] 会形成环：1-2-3-1
- 这就是冗余的边

详细的环检测过程：
输入：edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]

初始：
  1   2   3   4   5
  ↓   ↓   ↓   ↓   ↓
  1   2   3   4   5

处理 [1,2]：合并 1 和 2
    1   3   4   5
   / \  ↓   ↓   ↓
  1   2 3   4   5

处理 [2,3]：合并 2 和 3（实际是合并 1 和 3）
      1       4   5
    / | \     ↓   ↓
   1  2  3    4   5

处理 [3,4]：合并 3 和 4（实际是合并 1 和 4）
        1           5
      / | \ \       ↓
     1  2  3  4     5

处理 [1,4]：
- find(1) = 1
- find(4) = 1（路径压缩后）
- 已经在同一个集合！检测到环
- 返回 [1,4]

可视化环：
  1 --- 2
  |     |
  |     3
  |     |
  +-----4

边 [1,4] 形成了环：1-2-3-4-1
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 最小情况（3 个节点）：正确检测环
2. 环在最后一条边：返回最后一条边
3. 环在中间：返回第一条导致环的边
4. 复杂图：正确检测第一个环
*/

/*
Union Find 环检测总结 (Union Find Cycle Detection)
------------------------------------------------
1. 为什么 Union Find 能检测环？
   - 如果两个节点已经连通，再添加边会形成环
   - unite() 返回 false 表示检测到环

2. 环检测的时间复杂度？
   - 每次 unite() 操作：O(α(n)) ≈ O(1)
   - 总时间复杂度：O(n * α(n)) ≈ O(n)

3. Union Find vs DFS 环检测：
   - Union Find：在线检测，O(n)
   - DFS：需要遍历整个图，O(n^2)
   - Union Find 更高效

4. 为什么返回最后出现的边？
   - 题目要求返回最后出现的边
   - 遍历边的顺序就是出现顺序
   - 第一个导致环的边就是答案

5. Union Find 的应用场景：
   - 动态连通性问题
   - 环检测
   - 最小生成树（Kruskal 算法）
   - 网络连接问题
*/

/*
方法二：DFS 环检测 (Approach 2: DFS Cycle Detection for Comparison)

核心思想
--------
对于每条边，尝试删除它，然后用 DFS 检查是否还连通。
如果删除后仍然连通，说明这条边是冗余的。

算法流程：
1. 从后往前遍历边（因为要返回最后出现的边）
2. 对于每条边，临时删除它
3. 用 DFS 检查图是否还连通
4. 如果还连通，说明这条边是冗余的，返回它

为什么从后往前遍历？
- 题目要求返回最后出现的边
- 从后往前遍历，第一个满足条件的就是答案

复杂度分析
---------
时间复杂度：O(n^2)，对于每条边都要 DFS 一次
空间复杂度：O(n)，DFS 递归栈和图的存储

注：这个方法比 Union Find 慢，但更容易理解
*/
class Solution_DFS {
public:
    bool dfs(vector<vector<int>>& graph, int node, int target, vector<bool>& visited) {
        if (node == target) return true;
        visited[node] = true;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                if (dfs(graph, neighbor, target, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isConnected(vector<vector<int>>& edges, int skipIndex, int n) {
        vector<vector<int>> graph(n + 1);

        // 构建图，跳过指定的边
        for (int i = 0; i < edges.size(); i++) {
            if (i == skipIndex) continue;
            int u = edges[i][0], v = edges[i][1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // 检查是否连通
        vector<bool> visited(n + 1, false);
        return dfs(graph, 1, n, visited);
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        // 从后往前遍历，找到第一个可以删除的边
        for (int i = n - 1; i >= 0; i--) {
            if (isConnected(edges, i, n)) {
                return edges[i];
            }
        }

        return {};
    }
};

int main() {
    Solution solution;

    // 测试用例 1：简单环
    // 图：1-2-3，边 [2,3] 形成环
    vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result1 = solution.findRedundantConnection(edges1);
    cout << "测试用例 1 - 输出: [" << result1[0] << "," << result1[1] << "] (期望: [2,3])" << endl;

    // 测试用例 2：复杂环
    // 图：1-2-3-4，边 [1,4] 形成环
    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    vector<int> result2 = solution.findRedundantConnection(edges2);
    cout << "测试用例 2 - 输出: [" << result2[0] << "," << result2[1] << "] (期望: [1,4])" << endl;

    // 测试用例 3：最小情况
    // 3 个节点，3 条边
    vector<vector<int>> edges3 = {{1, 2}, {2, 3}, {1, 3}};
    vector<int> result3 = solution.findRedundantConnection(edges3);
    cout << "测试用例 3 - 输出: [" << result3[0] << "," << result3[1] << "] (期望: [1,3])" << endl;

    // 测试用例 4：环在最后
    vector<vector<int>> edges4 = {{1, 2}, {1, 3}, {1, 4}, {2, 4}};
    vector<int> result4 = solution.findRedundantConnection(edges4);
    cout << "测试用例 4 - 输出: [" << result4[0] << "," << result4[1] << "] (期望: [2,4])" << endl;

    // 测试用例 5：DFS 方法（较慢，仅用于对比）
    Solution_DFS solution_dfs;
    vector<vector<int>> edges5 = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result5 = solution_dfs.findRedundantConnection(edges5);
    cout << "测试用例 5 (DFS) - 输出: [" << result5[0] << "," << result5[1] << "] (期望: [2,3])" << endl;

    return 0;
}

/*
补充：常见变体与面试追问
----------------------
常见变体：
1. LeetCode 685 冗余连接 II（有向图）
2. LeetCode 1319 连通网络的操作次数
3. LeetCode 547 省份数量

面试追问：
Q1: 为什么并查集能判环？
A1: 若一条边两端已连通，再加这条边就形成环。

Q2: 本题为什么顺序扫描就能得到答案？
A2: 题设是树 + 一条额外边，首次触发“已连通”的那条即冗余边。

Q3: 路径压缩和按秩合并分别优化什么？
A3: 路径压缩降低 find 链长；按秩合并避免树退化。
*/
