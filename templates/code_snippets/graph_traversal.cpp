
/*
图遍历代码片段
包含：邻接表、BFS、DFS
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs(int u, const vector<vector<int>>& g, vector<int>& vis) {
    vis[u] = 1;
    for (int v : g[u]) if (!vis[v]) dfs(v, g, vis);
}

void bfs(int s, const vector<vector<int>>& g) {
    vector<int> vis(g.size(), 0);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!vis[v]) { vis[v] = 1; q.push(v); }
    }
}

int main() {
    vector<vector<int>> g = {{1,2},{2},{3},{}};
    vector<int> vis(g.size(), 0);
    dfs(0, g, vis);
    bfs(0, g);
    cout << "graph traversal done" << endl;
    return 0;
}
