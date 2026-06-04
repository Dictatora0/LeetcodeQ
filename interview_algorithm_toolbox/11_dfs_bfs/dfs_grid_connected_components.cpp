/*
题目 / 示例名称：DFS 统计网格连通块
核心知识点：DFS、网格遍历、连通块
适用场景：题目问“岛屿数量”“连通块个数”“有多少片区域”
关键思路：扫到一个未访问的 '1' 时，就用 DFS 把整块区域都标记掉，答案加一
时间复杂度：O(n * m)
空间复杂度：O(n * m)，主要是 visited
常见错误：
1. 忘记判边界。
2. 没有 visited，导致重复搜索甚至死循环。
3. 题目允许八方向连通，却只写了四方向。
示例输入：
4 5
11000
11010
00100
00011
示例输出：
4
手动推演：
第一片是左上角 2x2，第二片是中间单个 1，第三片是右上角单个 1，第四片是右下角两个 1。
对比说明：
- DFS 和 BFS 都能做。
- 只要求计数时，DFS 写法通常更短。
*/

#include <iostream>
#include <vector>

using namespace std;

const int DFS_DX[4] = {-1, 1, 0, 0};
const int DFS_DY[4] = {0, 0, -1, 1};

void dfs(int x, int y,
         const vector<string>& grid,
         vector<vector<int>>& visited) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    visited[x][y] = 1;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + DFS_DX[dir];
        int ny = y + DFS_DY[dir];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            continue;
        }
        if (visited[nx][ny] || grid[nx][ny] != '1') {
            continue;
        }

        dfs(nx, ny, grid, visited);
    }
}

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

    vector<vector<int>> visited(n, vector<int>(m, 0));
    int components = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                ++components;
                dfs(i, j, grid, visited);
            }
        }
    }

    cout << components << '\n';
    return 0;
}
