/*
题目 / 示例名称：最短路入门 - Dijkstra 基础版
核心知识点：Dijkstra、优先队列、带正权图最短路、邻接表
适用场景：图有边权，且边权都是非负数，要求起点到终点的最短距离
关键思路：
1. BFS 适合“每条边代价都一样”的无权图最短路。
2. 如果边权不同，但都非负，就不能继续用普通 BFS，要改用 Dijkstra。
3. 设 `dist[v]` 表示起点到点 v 的当前最短已知距离。
4. 用小根堆每次取出当前距离最小的点，尝试用它去松弛相邻边：
   `dist[to] = min(dist[to], dist[u] + w)`
5. 因为边权非负，所以第一个被“正式取出”的最短距离是可靠的。
时间复杂度：O((n + m) log n)
空间复杂度：O(n + m)
常见错误：
1. 带权图还继续用 BFS。
2. 图里有负权边，却还用 Dijkstra。
3. 从优先队列弹出旧状态后不跳过，导致重复处理很多无效状态。
示例输入：
5 6 1 5
1 2 2
1 3 5
2 3 1
2 4 2
3 5 5
4 5 2
示例输出：
6
手动推演：
从 1 到 5 的一条最短路是：
1 -> 2 -> 4 -> 5
总代价是 2 + 2 + 2 = 6。
对比说明：
- 无权最短路：BFS
- 正权最短路：Dijkstra
- 有负权边：不能直接用 Dijkstra
*/

#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int to;
    long long weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, start, target;
    if (!(cin >> n >> m >> start >> target)) {
        return 0;
    }

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // 这里按无向图处理，所以要双向建边。
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    const long long INF = numeric_limits<long long>::max() / 4;
    // dist[v] 表示起点到 v 的当前最短已知距离。
    vector<long long> dist(n + 1, INF);

    // 小根堆里存 pair<当前距离, 节点编号>。
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    dist[start] = 0;
    // 起点先以距离 0 进入小根堆。
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        // 如果这是一个过期状态，就直接跳过。
        if (current_dist != dist[u]) {
            continue;
        }

        if (u == target) {
            // 当前弹出的就是到 target 的最短距离，可以直接返回。
            cout << dist[u] << '\n';
            return 0;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            long long new_dist = dist[u] + edge.weight;

            // 如果经过 u 能得到更短路径，就更新并重新入堆。
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                // 堆里允许存在旧状态，后面用 current_dist != dist[u] 去过滤。
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dist[target] << '\n';
    }

    return 0;
}
