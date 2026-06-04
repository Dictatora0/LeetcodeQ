/*
题目 / 示例名称：BFS 求网格最短路
核心知识点：BFS、最短路、队列、层次扩展
适用场景：无权网格里从起点到终点的最少步数
关键思路：BFS 按距离一层层扩展，第一次到达终点时得到的就是最短距离
时间复杂度：O(n * m)
空间复杂度：O(n * m)
常见错误：
1. 访问标记放在出队时做，导致同一格被重复入队。
2. 忘记墙壁不可走。
3. 用 DFS 求最短路，结果又慢又绕。
示例输入：
3 4
S..#
.#.#
..T.
示例输出：
4
手动推演：
一条最短路径是 (0,0)->(0,1)->(0,2)->(1,2)->(2,2)，共 4 步。
对比说明：
- 无权最短路：BFS 优先。
- 如果边权不同，就不能直接用普通 BFS 了。
*/

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int BFS_DX[4] = {-1, 1, 0, 0};
const int BFS_DY[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    pair<int, int> start = {-1, -1};
    pair<int, int> target = {-1, -1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') {
                start = {i, j};
            } else if (grid[i][j] == 'T') {
                target = {i, j};
            }
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        if (current == target) {
            cout << dist[current.first][current.second] << '\n';
            return 0;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = current.first + BFS_DX[dir];
            int ny = current.second + BFS_DY[dir];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (grid[nx][ny] == '#' || dist[nx][ny] != -1) {
                continue;
            }

            dist[nx][ny] = dist[current.first][current.second] + 1;
            q.push({nx, ny});
        }
    }

    cout << -1 << '\n';
    return 0;
}
