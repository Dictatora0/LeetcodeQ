/*
LeetCode 207. 课程表 (Course Schedule)

题目概述 (Problem Summary)
-------------------------
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1。

在选修某些课程之前需要一些先修课程。先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi]，
表示如果要学习课程 ai 则必须先学习课程 bi。

例如，先修课程对 [0, 1] 表示：想要学习课程 0，你需要先完成课程 1。

请你判断是否可能完成所有课程的学习？如果可以，返回 true；否则，返回 false。

关键约束 (Key Constraints)
-------------------------
- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= 5000
- prerequisites[i].length == 2
- 0 <= ai, bi < numCourses
- prerequisites[i] 中的所有课程对互不相同

示例 (Example)
-------------
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。这是可能的。

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，需要先完成课程 0；并且学习课程 0 之前，还应先完成课程 1。这是不可能的。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断有向图中是否存在环
- 如果存在环，说明存在循环依赖，无法完成所有课程
- 如果不存在环，说明可以找到一个拓扑排序，能够完成所有课程

关键观察：
1. 这是一个典型的拓扑排序问题
2. 课程之间的依赖关系构成一个有向图
3. prerequisites[i] = [a, b] 表示 b -> a 的有向边（b 是 a 的前置课程）
4. 如果图中存在环，则无法完成所有课程
5. 如果图中不存在环（DAG - 有向无环图），则可以完成所有课程

什么是拓扑排序？
- 对有向无环图的所有顶点进行线性排序
- 使得对于任何有向边 u -> v，u 都排在 v 的前面
- 拓扑排序的应用：任务调度、编译顺序、课程安排等

拓扑排序的两种实现方法：
1. Kahn 算法（BFS）：基于入度
2. DFS：基于深度优先搜索和颜色标记
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
方法一：Kahn 算法（BFS + 入度）(Approach 1: Kahn's Algorithm - BFS with In-degree)

核心思想
--------
使用 BFS 和入度的概念来实现拓扑排序。

算法流程：
1. 构建图的邻接表表示和入度数组
   - graph[i] 存储课程 i 的所有后续课程
   - inDegree[i] 存储课程 i 的入度（有多少门前置课程）
2. 将所有入度为 0 的课程加入队列（这些课程没有前置要求，可以直接学习）
3. BFS 过程：
   a. 从队列中取出一门课程
   b. 学习这门课程（计数器 +1）
   c. 将这门课程的所有后续课程的入度 -1
   d. 如果某门后续课程的入度变为 0，将其加入队列
4. 如果最终学习的课程数等于总课程数，说明可以完成所有课程

为什么这个算法有效？
- 入度为 0 的课程没有前置要求，可以直接学习
- 学习一门课程后，它的后续课程的前置要求减少
- 如果存在环，环中的所有课程的入度永远不会变为 0
- 因此，如果存在环，最终学习的课程数会少于总课程数

复杂度分析
---------
时间复杂度：O(V + E)
- V 是课程数量（顶点数）
- E 是先修课程关系数量（边数）
- 构建图：O(E)
- BFS 遍历：每个顶点和每条边最多访问一次，O(V + E)

空间复杂度：O(V + E)
- 邻接表：O(E)
- 入度数组：O(V)
- 队列：O(V)

其中：
V = numCourses
E = prerequisites.length
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 构建图的邻接表
        vector<vector<int>> graph(numCourses);
        // 入度数组
        vector<int> inDegree(numCourses, 0);

        // 构建图和入度数组
        // prerequisites[i] = [a, b] 表示 b -> a（学习 a 之前需要先学习 b）
        for (auto& p : prerequisites) {
            int a = p[0];  // 后续课程
            int b = p[1];  // 前置课程
            graph[b].push_back(a);  // b -> a
            inDegree[a]++;  // a 的入度 +1
        }

        // 将所有入度为 0 的课程加入队列
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // BFS 拓扑排序
        int count = 0;  // 已学习的课程数量
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            count++;  // 学习当前课程

            // 遍历当前课程的所有后续课程
            for (int next : graph[cur]) {
                inDegree[next]--;  // 后续课程的入度 -1
                // 如果后续课程的入度变为 0，加入队列
                if (inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // 如果学习的课程数等于总课程数，说明可以完成所有课程
        return count == numCourses;
    }
};

/*
方法二：DFS + 颜色标记 (Approach 2: DFS with Color Marking)

核心思想
--------
使用 DFS 检测图中是否存在环。使用三种颜色标记节点的访问状态。

颜色标记：
- 0（白色）：未访问
- 1（灰色）：正在访问（在当前 DFS 路径中）
- 2（黑色）：已完成访问

算法流程：
1. 构建图的邻接表
2. 对每个未访问的节点进行 DFS
3. DFS 过程：
   a. 将当前节点标记为灰色（正在访问）
   b. 遍历所有邻居节点：
      - 如果邻居是灰色，说明存在环，返回 false
      - 如果邻居是白色，递归访问
   c. 将当前节点标记为黑色（已完成访问）

为什么这个算法有效？
- 灰色节点表示当前 DFS 路径上的节点
- 如果在 DFS 过程中遇到灰色节点，说明形成了环
- 黑色节点表示已经完成访问，不会再访问

复杂度分析
---------
时间复杂度：O(V + E)
- 每个顶点和每条边最多访问一次

空间复杂度：O(V + E)
- 邻接表：O(E)
- 颜色数组：O(V)
- 递归调用栈：O(V)
*/
class Solution_DFS {
public:
    vector<vector<int>> graph;
    vector<int> color;  // 0: 未访问, 1: 正在访问, 2: 已完成

    // DFS 检测环
    // course: 当前课程
    // 返回 true 表示存在环
    bool hasCycle(int course) {
        // 如果当前课程正在访问中（灰色），说明存在环
        if (color[course] == 1) {
            return true;
        }

        // 如果当前课程已完成访问（黑色），直接返回
        if (color[course] == 2) {
            return false;
        }

        // 标记当前课程为正在访问（灰色）
        color[course] = 1;

        // 遍历所有后续课程
        for (int next : graph[course]) {
            if (hasCycle(next)) {
                return true;  // 发现环
            }
        }

        // 标记当前课程为已完成（黑色）
        color[course] = 2;

        return false;  // 没有发现环
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 构建图
        graph.resize(numCourses);
        color.resize(numCourses, 0);

        for (auto& p : prerequisites) {
            int a = p[0];
            int b = p[1];
            graph[b].push_back(a);  // b -> a
        }

        // 对每个未访问的课程进行 DFS
        for (int i = 0; i < numCourses; i++) {
            if (color[i] == 0) {
                if (hasCycle(i)) {
                    return false;  // 存在环，无法完成所有课程
                }
            }
        }

        return true;  // 不存在环，可以完成所有课程
    }
};

/*
方法三：拓扑排序（返回排序结果）(Approach 3: Topological Sort - Return Order)

核心思想
--------
在方法一的基础上，不仅判断是否可以完成所有课程，还返回一个可行的学习顺序。

这个方法对于 LeetCode 210（课程表 II）很有用。

算法流程：
与方法一相同，但在 BFS 过程中记录学习顺序。

复杂度分析
---------
与方法一相同。
*/
class Solution_WithOrder {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);

        for (auto& p : prerequisites) {
            int a = p[0];
            int b = p[1];
            graph[b].push_back(a);
            inDegree[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> order;  // 学习顺序
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            order.push_back(cur);  // 记录学习顺序

            for (int next : graph[cur]) {
                inDegree[next]--;
                if (inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // 如果学习的课程数不等于总课程数，返回空数组
        if (order.size() != numCourses) {
            return {};
        }

        return order;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]

图的结构：
0 -> 1 -> 3
0 -> 2 -> 3

使用 Kahn 算法的执行过程：

1. 构建图和入度数组：
   graph[0] = [1, 2]
   graph[1] = [3]
   graph[2] = [3]
   graph[3] = []
   inDegree = [0, 1, 1, 2]

2. 初始化队列：
   q = [0]（只有课程 0 的入度为 0）

3. BFS 过程：
   - 取出 0，count = 1
     - 访问 1：inDegree[1] = 0，加入队列
     - 访问 2：inDegree[2] = 0，加入队列
     q = [1, 2]

   - 取出 1，count = 2
     - 访问 3：inDegree[3] = 1
     q = [2]

   - 取出 2，count = 3
     - 访问 3：inDegree[3] = 0，加入队列
     q = [3]

   - 取出 3，count = 4
     q = []

4. count = 4 == numCourses，返回 true

学习顺序：0 -> 1 -> 2 -> 3 或 0 -> 2 -> 1 -> 3

---

示例 2：numCourses = 2, prerequisites = [[1,0],[0,1]]

图的结构：
0 <-> 1（存在环）

使用 Kahn 算法的执行过程：

1. 构建图和入度数组：
   graph[0] = [1]
   graph[1] = [0]
   inDegree = [1, 1]

2. 初始化队列：
   q = []（没有入度为 0 的课程）

3. BFS 过程：
   队列为空，直接结束

4. count = 0 != numCourses，返回 false
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：Kahn 算法（BFS + 入度）
- 时间复杂度：O(V + E)
- 空间复杂度：O(V + E)
- 优点：直观易懂，容易实现，可以直接得到拓扑排序
- 缺点：需要额外的入度数组和队列

方法二：DFS + 颜色标记
- 时间复杂度：O(V + E)
- 空间复杂度：O(V + E)
- 优点：代码简洁，不需要入度数组
- 缺点：需要理解颜色标记的含义，递归可能导致栈溢出

两种方法时间和空间复杂度相同，选择哪个取决于个人偏好。
Kahn 算法更直观，DFS 更简洁。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 没有先修课程：prerequisites = []，返回 true
2. 只有一门课程：numCourses = 1，返回 true
3. 存在自环：[0, 0]，返回 false
4. 存在多个环：需要正确检测
5. 多个连通分量：图不连通，但仍可能完成所有课程
*/

/*
拓扑排序应用场景 (Topological Sort Applications)
---------------------------------------------
1. 课程安排：本题
2. 任务调度：任务之间有依赖关系
3. 编译顺序：源文件之间的依赖关系
4. 项目管理：项目任务的先后顺序
5. 数据库表的创建顺序：外键依赖关系

拓扑排序的特点：
- 只适用于有向无环图（DAG）
- 拓扑排序不唯一
- 如果图中存在环，则不存在拓扑排序
*/

/*
Kahn 算法模板 (Kahn's Algorithm Template)
----------------------------------------
bool topologicalSort(int n, vector<vector<int>>& edges) {
    // 1. 构建图和入度数组
    vector<vector<int>> graph(n);
    vector<int> inDegree(n, 0);

    for (auto& edge : edges) {
        int from = edge[0];
        int to = edge[1];
        graph[from].push_back(to);
        inDegree[to]++;
    }

    // 2. 将所有入度为 0 的节点加入队列
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 3. BFS
    int count = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        count++;

        for (int next : graph[cur]) {
            inDegree[next]--;
            if (inDegree[next] == 0) {
                q.push(next);
            }
        }
    }

    // 4. 判断是否存在环
    return count == n;
}
*/

int main() {
    Solution solution;

    // 测试用例 1：可以完成
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    bool result1 = solution.canFinish(numCourses1, prerequisites1);
    cout << "测试用例 1 - 可以完成所有课程: " << (result1 ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例 2：存在环，无法完成
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    bool result2 = solution.canFinish(numCourses2, prerequisites2);
    cout << "测试用例 2 - 可以完成所有课程: " << (result2 ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例 3：复杂情况
    int numCourses3 = 4;
    vector<vector<int>> prerequisites3 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    bool result3 = solution.canFinish(numCourses3, prerequisites3);
    cout << "测试用例 3 - 可以完成所有课程: " << (result3 ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例 4：没有先修课程
    int numCourses4 = 3;
    vector<vector<int>> prerequisites4 = {};
    bool result4 = solution.canFinish(numCourses4, prerequisites4);
    cout << "测试用例 4 - 可以完成所有课程: " << (result4 ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例 5：使用方法三获取学习顺序
    Solution_WithOrder solution2;
    vector<int> order = solution2.findOrder(numCourses3, prerequisites3);
    cout << "测试用例 5 - 学习顺序: [";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i];
        if (i < order.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}
