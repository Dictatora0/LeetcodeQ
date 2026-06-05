/*
题目 / 示例名称：多源 BFS - 网格扩散最少时间
核心知识点：多源 BFS、队列、按层扩展、最短扩散时间
适用场景：题目里有多个起点同时向外扩散，要求最少多少轮、多少分钟、多少步覆盖全部目标
关键思路：
1. 普通 BFS 是“一个起点”入队。
2. 多源 BFS 是“所有起点一起”先入队。
3. 之后仍然按 BFS 的层次顺序扩展，因此第一次到达某个格子的时间就是最短扩散时间。
4. 本题中：
   - `2` 表示扩散源
   - `1` 表示还未被覆盖的目标格
   - `0` 表示空格，不参与扩散
时间复杂度：O(n * m)
空间复杂度：O(n * m)
常见错误：
1. 只把一个起点入队，漏掉其他同时开始扩散的源点。
2. 在出队时才标记访问，导致同一格重复入队。
3. 没有统计剩余目标格数量，最后无法判断是否全部覆盖。
示例输入：
3 3
2 1 1
1 1 0
0 1 1
示例输出：
4
手动推演：
第 0 分钟：只有左上角的 2
第 1 分钟：扩散到第一行第二列、第二行第一列
第 2 分钟：继续扩散
最终第 4 分钟覆盖完所有 1，所以答案是 4。
对比说明：
- 单源最短路：一个起点入队。
- 多源最短路 / 扩散：所有起点一起入队。
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

const int MS_BFS_DX[4] = {-1, 1, 0, 0};
const int MS_BFS_DY[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<int>> grid(n, vector<int>(m, 0));
    queue<tuple<int, int, int>> q;
    // remaining_targets 表示还有多少个值为 1 的目标格没有被覆盖。
    int remaining_targets = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                // 所有扩散源同时作为 BFS 的第 0 层起点入队。
                q.push({i, j, 0});
            } else if (grid[i][j] == 1) {
                ++remaining_targets;
            }
        }
    }

    int answer = 0;

    while (!q.empty()) {
        auto [x, y, minute] = q.front();
        q.pop();
        // answer 记录最后一个被成功扩散到的时间层数。
        answer = max(answer, minute);

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + MS_BFS_DX[dir];
            int ny = y + MS_BFS_DY[dir];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            // 只有值为 1 的目标格才需要被扩散覆盖。
            if (grid[nx][ny] != 1) {
                continue;
            }

            // 一旦入队，就立刻改成 2，表示它已经被覆盖，避免重复入队。
            grid[nx][ny] = 2;
            --remaining_targets;
            q.push({nx, ny, minute + 1});
        }
    }

    // 如果还有 1 没被覆盖，说明有目标格永远到不了。
    if (remaining_targets > 0) {
        cout << -1 << '\n';
    } else {
        cout << answer << '\n';
    }

    return 0;
}
