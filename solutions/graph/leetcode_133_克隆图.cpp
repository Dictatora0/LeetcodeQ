/*
LeetCode 133. 克隆图 (Clone Graph)

题目概述 (Problem Summary)
-------------------------
给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。

图中的每个节点都包含它的值 val（int）和其邻居的列表（list[Node]）。

class Node {
    public int val;
    public List<Node> neighbors;
}

测试用例格式：
简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），
第二个节点值为 2（val = 2），以此类推。该图在测试用例中使用邻接列表表示。

邻接列表是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。

给定节点将始终是图中的第一个节点（值为 1）。你必须将给定节点的拷贝作为对克隆图的引用返回。

关键约束 (Key Constraints)
-------------------------
- 节点数不超过 100
- 每个节点值 Node.val 都是唯一的，1 <= Node.val <= 100
- 无向图是一个简单图，这意味着图中没有重复的边，也没有自环
- 由于图是无向的，如果节点 p 是节点 q 的邻居，那么节点 q 也必须是节点 p 的邻居
- 图是连通图，你可以从给定节点访问到所有节点

示例 (Example)
-------------
输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
输出：[[2,4],[1,3],[2,4],[1,3]]
解释：
图中有 4 个节点。
节点 1 的值是 1，它有两个邻居：节点 2 和节点 4 。
节点 2 的值是 2，它有两个邻居：节点 1 和节点 3 。
节点 3 的值是 3，它有两个邻居：节点 2 和节点 4 。
节点 4 的值是 4，它有两个邻居：节点 1 和节点 3 。

输入：adjList = [[]]
输出：[[]]
解释：输入包含一个空列表。该图仅包含一个值为 1 的节点，它没有任何邻居。

输入：adjList = []
输出：[]
解释：这个图是空的，它不含任何节点。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 深拷贝一个图结构
- 不能简单地复制引用，必须创建新的节点对象
- 需要保持原图的连接关系

关键观察：
1. 这是一个图的遍历问题（DFS 或 BFS）
2. 需要一个哈希表记录 原节点 → 新节点 的映射
3. 哈希表的作用：
   - 避免重复创建节点
   - 避免无限循环（图中有环）
   - 快速找到已创建的新节点

为什么需要哈希表？
问题 1：如果不用哈希表，会发生什么？
- 遍历到同一个节点时，会重复创建
- 例如：节点 1 → 节点 2 → 节点 1（环）
  第一次创建节点 1，第二次又创建节点 1，导致无限循环

问题 2：为什么不能直接复制？
- 直接复制会共享引用，不是深拷贝
- 例如：newNode.neighbors = oldNode.neighbors
  这样新旧节点的 neighbors 指向同一个列表

深拷贝 vs 浅拷贝：
- 浅拷贝：只复制对象本身，内部引用仍指向原对象
- 深拷贝：递归复制所有对象，创建完全独立的副本
- 这道题要求深拷贝

算法流程（DFS）：
1. 如果节点为空，返回 nullptr
2. 如果节点已经被克隆过（在哈希表中），直接返回克隆节点
3. 创建新节点，加入哈希表
4. 递归克隆所有邻居节点
5. 将克隆的邻居加入新节点的邻居列表
6. 返回新节点

为什么这个算法正确？
- 哈希表保证每个节点只被克隆一次
- DFS 保证遍历所有节点
- 递归保证所有邻居关系都被正确复制

根据这些观察，可以得到 DFS 和 BFS 两种解法。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/*
方法一：DFS + 哈希表 (Approach 1: DFS with HashMap)

核心思想
--------
使用 DFS 遍历图，用哈希表记录原节点到新节点的映射，避免重复创建和无限循环。

数据结构：
1. 哈希表：oldNode → newNode 的映射
2. 递归栈：DFS 遍历

算法流程：
1. 边界条件：如果节点为空，返回 nullptr
2. 检查哈希表：如果节点已克隆，直接返回克隆节点
3. 创建新节点：new Node(node->val)
4. 加入哈希表：记录映射关系
5. 递归克隆邻居：
   - 遍历原节点的所有邻居
   - 递归调用 cloneGraph 克隆每个邻居
   - 将克隆的邻居加入新节点的邻居列表
6. 返回新节点

为什么必须先加入哈希表再递归？
- 如果先递归再加入，会导致无限循环
- 例如：节点 1 → 节点 2 → 节点 1
  克隆节点 1 时，递归克隆节点 2
  克隆节点 2 时，递归克隆节点 1
  但节点 1 还没加入哈希表，又会重新克隆，无限循环

正确顺序：
1. 创建新节点
2. 加入哈希表（标记已克隆）
3. 递归克隆邻居（此时再遇到该节点，直接返回）

复杂度分析
---------
时间复杂度：O(N + E)，其中 N 是节点数，E 是边数
  - 每个节点访问一次：O(N)
  - 每条边访问一次：O(E)
空间复杂度：O(N)
  - 哈希表：O(N)
  - 递归栈：O(N)（最坏情况，链状图）
*/
class Solution {
private:
    // 哈希表：原节点 → 克隆节点的映射
    unordered_map<Node*, Node*> visited;

public:
    Node* cloneGraph(Node* node) {
        // 边界条件：空节点
        if (node == nullptr) {
            return nullptr;
        }

        // 如果节点已经被克隆过，直接返回克隆节点
        // 这样可以避免重复创建和无限循环
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }

        // 创建新节点（只复制值，邻居列表稍后填充）
        Node* cloneNode = new Node(node->val);

        // 关键：先将映射加入哈希表，再递归克隆邻居
        // 这样可以避免环导致的无限循环
        visited[node] = cloneNode;

        // 递归克隆所有邻居节点
        for (Node* neighbor : node->neighbors) {
            // 递归调用 cloneGraph 克隆邻居
            // 如果邻居已经被克隆过，会直接从哈希表返回
            cloneNode->neighbors.push_back(cloneGraph(neighbor));
        }

        // 返回克隆节点
        return cloneNode;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：adjList = [[2,4],[1,3],[2,4],[1,3]]

可视化原图：
    1 --- 2
    |     |
    |     |
    4 --- 3

DFS 克隆过程：

初始状态：
visited = {}

第 1 步：cloneGraph(节点1)
- 节点1 不在 visited 中
- 创建新节点1'：Node(1)
- visited = {节点1 → 节点1'}
- 递归克隆邻居：[节点2, 节点4]

第 2 步：cloneGraph(节点2)（从节点1的邻居）
- 节点2 不在 visited 中
- 创建新节点2'：Node(2)
- visited = {节点1 → 节点1', 节点2 → 节点2'}
- 递归克隆邻居：[节点1, 节点3]

第 3 步：cloneGraph(节点1)（从节点2的邻居）
- 节点1 在 visited 中！
- 直接返回 visited[节点1] = 节点1'
- 避免了无限循环

第 4 步：cloneGraph(节点3)（从节点2的邻居）
- 节点3 不在 visited 中
- 创建新节点3'：Node(3)
- visited = {节点1 → 节点1', 节点2 → 节点2', 节点3 → 节点3'}
- 递归克隆邻居：[节点2, 节点4]

第 5 步：cloneGraph(节点2)（从节点3的邻居）
- 节点2 在 visited 中！
- 直接返回 visited[节点2] = 节点2'

第 6 步：cloneGraph(节点4)（从节点3的邻居）
- 节点4 不在 visited 中
- 创建新节点4'：Node(4)
- visited = {节点1 → 节点1', 节点2 → 节点2', 节点3 → 节点3', 节点4 → 节点4'}
- 递归克隆邻居：[节点1, 节点3]

第 7 步：cloneGraph(节点1)（从节点4的邻居）
- 节点1 在 visited 中！
- 直接返回 visited[节点1] = 节点1'

第 8 步：cloneGraph(节点3)（从节点4的邻居）
- 节点3 在 visited 中！
- 直接返回 visited[节点3] = 节点3'

第 9 步：回到第 1 步，继续克隆节点1的第二个邻居
- cloneGraph(节点4)
- 节点4 在 visited 中！
- 直接返回 visited[节点4] = 节点4'

最终克隆图：
    1' --- 2'
    |      |
    |      |
    4' --- 3'

关键观察：
1. 哈希表防止重复创建节点
2. 哈希表防止无限循环（环）
3. 每个节点只被创建一次
4. 所有邻居关系都被正确复制

DFS 调用栈示例：
cloneGraph(1)
  ├─ cloneGraph(2)
  │   ├─ cloneGraph(1) → 返回 visited[1]
  │   └─ cloneGraph(3)
  │       ├─ cloneGraph(2) → 返回 visited[2]
  │       └─ cloneGraph(4)
  │           ├─ cloneGraph(1) → 返回 visited[1]
  │           └─ cloneGraph(3) → 返回 visited[3]
  └─ cloneGraph(4) → 返回 visited[4]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空图（nullptr）：返回 nullptr
2. 单节点无邻居：正确克隆
3. 两节点互相连接：正确处理环
4. 复杂图：正确克隆所有节点和边
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：DFS + 哈希表
- 时间复杂度：O(N + E)
- 空间复杂度：O(N)
- 优点：代码简洁，递归思路清晰
- 缺点：递归深度可能很大（链状图）

方法二：BFS + 哈希表
- 时间复杂度：O(N + E)
- 空间复杂度：O(N)
- 优点：迭代实现，避免栈溢出
- 缺点：代码稍复杂

DFS vs BFS：
- DFS：递归实现，代码简洁
- BFS：迭代实现，更安全（避免栈溢出）
- 对于这道题，两者时间和空间复杂度相同
- 推荐 DFS，因为代码更简洁

为什么必须用哈希表？
1. 避免重复创建节点
2. 避免无限循环（图中有环）
3. 快速查找已创建的节点
4. 没有哈希表，算法无法正确工作
*/

/*
方法二：BFS + 哈希表 (Approach 2: BFS with HashMap)

核心思想
--------
使用 BFS 遍历图，用哈希表记录原节点到新节点的映射。

算法流程：
1. 边界条件：如果节点为空，返回 nullptr
2. 创建队列，将起始节点加入队列
3. 创建起始节点的克隆，加入哈希表
4. BFS 遍历：
   - 取出队首节点
   - 遍历其所有邻居
   - 如果邻居未被克隆，创建克隆并加入队列
   - 将克隆的邻居加入当前节点的邻居列表
5. 返回起始节点的克隆

BFS vs DFS：
- BFS 使用队列，DFS 使用递归栈
- BFS 按层遍历，DFS 按深度遍历
- 对于克隆图，两者效果相同

复杂度分析
---------
时间复杂度：O(N + E)
空间复杂度：O(N)
*/
class Solution_BFS {
public:
    Node* cloneGraph(Node* node) {
        // 边界条件：空节点
        if (node == nullptr) {
            return nullptr;
        }

        // 哈希表：原节点 → 克隆节点的映射
        unordered_map<Node*, Node*> visited;

        // BFS 队列
        queue<Node*> q;
        q.push(node);

        // 创建起始节点的克隆
        visited[node] = new Node(node->val);

        // BFS 遍历
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            // 遍历当前节点的所有邻居
            for (Node* neighbor : curr->neighbors) {
                // 如果邻居未被克隆，创建克隆并加入队列
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }

                // 将克隆的邻居加入当前克隆节点的邻居列表
                visited[curr]->neighbors.push_back(visited[neighbor]);
            }
        }

        // 返回起始节点的克隆
        return visited[node];
    }
};

/*
BFS 示例推演
-----------
输入：adjList = [[2,4],[1,3],[2,4],[1,3]]

可视化原图：
    1 --- 2
    |     |
    |     |
    4 --- 3

BFS 克隆过程：

初始状态：
队列：[节点1]
visited = {节点1 → 节点1'}

第 1 步：处理节点1
- 取出节点1
- 邻居：[节点2, 节点4]
- 节点2 未克隆：创建节点2'，加入队列
- 节点4 未克隆：创建节点4'，加入队列
- 节点1'.neighbors = [节点2', 节点4']
- 队列：[节点2, 节点4]
- visited = {节点1 → 节点1', 节点2 → 节点2', 节点4 → 节点4'}

第 2 步：处理节点2
- 取出节点2
- 邻居：[节点1, 节点3]
- 节点1 已克隆：直接使用节点1'
- 节点3 未克隆：创建节点3'，加入队列
- 节点2'.neighbors = [节点1', 节点3']
- 队列：[节点4, 节点3]
- visited = {节点1 → 节点1', 节点2 → 节点2', 节点4 → 节点4', 节点3 → 节点3'}

第 3 步：处理节点4
- 取出节点4
- 邻居：[节点1, 节点3]
- 节点1 已克隆：直接使用节点1'
- 节点3 已克隆：直接使用节点3'
- 节点4'.neighbors = [节点1', 节点3']
- 队列：[节点3]

第 4 步：处理节点3
- 取出节点3
- 邻居：[节点2, 节点4]
- 节点2 已克隆：直接使用节点2'
- 节点4 已克隆：直接使用节点4'
- 节点3'.neighbors = [节点2', 节点4']
- 队列：[]

BFS 完成，返回节点1'

关键观察：
1. BFS 按层遍历：第 1 层(节点1) → 第 2 层(节点2,节点4) → 第 3 层(节点3)
2. 每个节点只被处理一次
3. 哈希表防止重复创建
*/

// 辅助函数：打印图（用于测试）
void printGraph(Node* node, unordered_map<Node*, bool>& visited) {
    if (node == nullptr || visited[node]) {
        return;
    }

    visited[node] = true;
    cout << "节点 " << node->val << " 的邻居: ";
    for (Node* neighbor : node->neighbors) {
        cout << neighbor->val << " ";
    }
    cout << endl;

    for (Node* neighbor : node->neighbors) {
        printGraph(neighbor, visited);
    }
}

// 辅助函数：构建测试图
Node* buildGraph(vector<vector<int>>& adjList) {
    if (adjList.empty()) {
        return nullptr;
    }

    int n = adjList.size();
    vector<Node*> nodes(n + 1);

    // 创建所有节点
    for (int i = 1; i <= n; i++) {
        nodes[i] = new Node(i);
    }

    // 建立邻居关系
    for (int i = 0; i < n; i++) {
        for (int neighbor : adjList[i]) {
            nodes[i + 1]->neighbors.push_back(nodes[neighbor]);
        }
    }

    return nodes[1];
}

int main() {
    Solution solution;

    // 测试用例 1：标准四节点图
    cout << "测试用例 1：四节点图" << endl;
    vector<vector<int>> adjList1 = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};
    Node* graph1 = buildGraph(adjList1);
    Node* cloned1 = solution.cloneGraph(graph1);

    cout << "原图:" << endl;
    unordered_map<Node*, bool> visited1;
    printGraph(graph1, visited1);

    cout << "克隆图:" << endl;
    unordered_map<Node*, bool> visited2;
    printGraph(cloned1, visited2);
    cout << endl;

    // 测试用例 2：单节点无邻居
    cout << "测试用例 2：单节点无邻居" << endl;
    vector<vector<int>> adjList2 = {{}};
    Node* graph2 = buildGraph(adjList2);
    Node* cloned2 = solution.cloneGraph(graph2);
    cout << "原图节点值: " << graph2->val << ", 邻居数: " << graph2->neighbors.size() << endl;
    cout << "克隆图节点值: " << cloned2->val << ", 邻居数: " << cloned2->neighbors.size() << endl;
    cout << "是否是不同对象: " << (graph2 != cloned2 ? "是" : "否") << endl;
    cout << endl;

    // 测试用例 3：空图
    cout << "测试用例 3：空图" << endl;
    Node* graph3 = nullptr;
    Node* cloned3 = solution.cloneGraph(graph3);
    cout << "克隆结果: " << (cloned3 == nullptr ? "nullptr" : "非空") << endl;
    cout << endl;

    // 测试用例 4：两节点互相连接
    cout << "测试用例 4：两节点互相连接" << endl;
    vector<vector<int>> adjList4 = {{2}, {1}};
    Node* graph4 = buildGraph(adjList4);
    Node* cloned4 = solution.cloneGraph(graph4);

    cout << "原图:" << endl;
    unordered_map<Node*, bool> visited3;
    printGraph(graph4, visited3);

    cout << "克隆图:" << endl;
    unordered_map<Node*, bool> visited4;
    printGraph(cloned4, visited4);
    cout << endl;

    // 测试用例 5：BFS 方法
    cout << "测试用例 5：BFS 方法" << endl;
    Solution_BFS solution_bfs;
    vector<vector<int>> adjList5 = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};
    Node* graph5 = buildGraph(adjList5);
    Node* cloned5 = solution_bfs.cloneGraph(graph5);

    cout << "BFS 克隆图:" << endl;
    unordered_map<Node*, bool> visited5;
    printGraph(cloned5, visited5);

    return 0;
}


/*
补充：常见变体与面试追问
----------------------
常见变体：
1. LeetCode 138 复制带随机指针的链表
2. 克隆有向图 / 带权图（节点结构扩展）
3. 深拷贝对象图（工程场景）

面试追问：
Q1: 为什么一定要 old->new 的哈希映射？
A1: 防止重复克隆和死循环，同时复用已创建克隆节点。

Q2: DFS 和 BFS 克隆有什么区别？
A2: 本质一致，都是图遍历 + 映射；差异只在遍历顺序。

Q3: 什么时候创建克隆节点最合适？
A3: 第一次访问原节点时立即创建并入映射。
*/
