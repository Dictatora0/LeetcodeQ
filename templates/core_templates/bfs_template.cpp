
/*
算法名称：广度优先搜索 BFS

算法核心思想
-----------
BFS 按层次逐层扩展，从起点开始先访问距离为 1 的节点，
再访问距离为 2 的节点，适合求最短路径（无权图）。

思路要点
-------
- 用队列保证“先进先出”的层序访问
- visited 要在入队时标记，避免重复入队
- 需要最少步数时，用分层 BFS
- 多源 BFS 可以同时从多个起点扩散

什么时候使用
-----------
适用场景：
- 无权图最短路径
- 树的层序遍历
- 状态图最少步数（迷宫、转移）
- 多源扩散问题

常见算法变体
-----------
1) 普通 BFS（单源）
2) 分层 BFS（记录层数）
3) 多源 BFS
4) 0-1 BFS（边权为 0/1）

复杂度分析
---------
时间复杂度：O(V + E)
空间复杂度：O(V)

ASCII 示例
---------
图：0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
BFS 访问顺序：0, 1, 2, 3

典型题目扩展
-----------
- 102 Binary Tree Level Order Traversal
- 279 Perfect Squares
- 752 Open the Lock
- 994 Rotting Oranges
- 127 Word Ladder

可直接使用的代码模板
------------------
见下方 BFS_Template

常见错误
--------
- 未及时标记 visited 导致重复入队
- 忘记分层导致步数统计错误
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

class BFS_Template {
public:
    void bfs(int start, const vector<vector<int>>& graph) {
        vector<int> visited(graph.size(), 0);
        queue<int> q;
        q.push(start);
        visited[start] = 1;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (int v : graph[u]) {
                if (!visited[v]) {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    // 分层 BFS：返回到达目标的最少步数，目标不存在返回 -1
    int bfsShortest(int start, int target, const vector<vector<int>>& graph) {
        vector<int> visited(graph.size(), 0);
        queue<int> q;
        q.push(start);
        visited[start] = 1;
        int step = 0;

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                int u = q.front(); q.pop();
                if (u == target) return step;
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            step++;
        }
        return -1;
    }

    // 多源 BFS：返回所有点到最近源点的最短距离
    vector<int> multiSourceBfs(const vector<vector<int>>& graph, const vector<int>& sources) {
        int n = graph.size();
        vector<int> dist(n, -1);
        queue<int> q;
        for (int s : sources) {
            dist[s] = 0;
            q.push(s);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

    // 0-1 BFS：边权为 0/1 的最短路径
    vector<int> zeroOneBfs(int start, const vector<vector<pair<int,int>>>& graph) {
        int n = graph.size();
        const int INF = 1e9;
        vector<int> dist(n, INF);
        deque<int> dq;
        dist[start] = 0;
        dq.push_front(start);

        while (!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            for (auto [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
        return dist;
    }
};

int main() {
    vector<vector<int>> graph = {
        {1, 2}, // 0
        {3},    // 1
        {3},    // 2
        {}      // 3
    };

    BFS_Template solver;
    cout << "BFS 访问顺序: ";
    solver.bfs(0, graph);
    cout << endl;

    cout << "0 -> 3 最少步数: " << solver.bfsShortest(0, 3, graph) << endl;
    return 0;
}
