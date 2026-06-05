/*
题目 / 示例名称：拓扑排序入门 - Kahn 算法
核心知识点：拓扑排序、入度、队列、DAG
适用场景：题目给出若干“先做 A 再做 B”的依赖关系，要求输出一种合法顺序
关键思路：
1. 对于有向边 `u -> v`，表示 `u` 必须排在 `v` 前面。
2. 统计每个点的入度，入度表示“还有多少前置依赖没完成”。
3. 所有入度为 0 的点，都可以立刻入队。
4. 每次从队列取出一个点，加入拓扑序列，
   然后删除它发出的边，使后继点的入度减 1。
5. 如果某个后继点入度减到 0，就说明它的前置依赖都处理完了，可以入队。
6. 如果最后取出的点数小于 n，说明图里存在环，无法完成拓扑排序。
时间复杂度：O(n + m)
空间复杂度：O(n + m)
常见错误：
1. 把无向图也拿来做拓扑排序。
2. 忘记在入度减为 0 时入队。
3. 不检查是否处理完全部节点，导致有环时还误以为成功。
示例输入：
4 4
1 2
1 3
2 4
3 4
示例输出：
1 2 3 4
手动推演：
- 初始入度为 0 的点只有 1，所以先输出 1。
- 删除 1 的出边后，2 和 3 入度都变成 0，可以继续输出。
- 最后 4 的前置依赖全部完成，再输出 4。
对比说明：
- 普通 BFS 是“按距离层次扩展”。
- 拓扑排序里的队列不是按距离，而是按“当前是否已经没有前置依赖”来推进。
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        // 有一条 u -> v，说明 v 多了一个前置依赖。
        ++indegree[v];
    }

    queue<int> q;
    for (int node = 1; node <= n; ++node) {
        if (indegree[node] == 0) {
            // 入度为 0，表示没有前置依赖，可以作为当前可执行节点入队。
            q.push(node);
        }
    }

    // order 按照“依赖满足后出队”的顺序记录拓扑序列。
    vector<int> order;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        order.push_back(current);

        for (int next : graph[current]) {
            // current 已经被放进拓扑序，等价于删除 current -> next 这条边。
            --indegree[next];
            if (indegree[next] == 0) {
                // next 的所有前置依赖都处理完了，现在可以入队。
                q.push(next);
            }
        }
    }

    if (static_cast<int>(order.size()) != n) {
        // 还有点没被取出来，说明剩余部分形成了环。
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << order[i];
    }
    cout << '\n';
    return 0;
}
