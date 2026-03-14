#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//BFS 网格模板

class Solution {
public:
    int bfs(vector<vector<int>>& grid, int sx, int sy) {

        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int,int>> q;

        q.push({sx, sy});
        grid[sx][sy] = 0;

        vector<vector<int>> dirs = {
            {1,0},{-1,0},{0,1},{0,-1}
        };

        while (!q.empty()) {

            auto [x, y] = q.front();
            q.pop();

            for (auto& d : dirs) {

                int nx = x + d[0];
                int ny = y + d[1];

                if (nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {

                    grid[nx][ny] = 0;
                    q.push({nx, ny});

                }
            }
        }

        return 0;
    }
};

//网格题万能骨架
class Solution {
public:

    int m, n;

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    void dfs(vector<vector<int>>& grid, int x, int y) {

        if (x<0 || x>=m || y<0 || y>=n) return;
        if (grid[x][y] == 0) return;

        grid[x][y] = 0;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            dfs(grid, nx, ny);
        }
    }

    int solve(vector<vector<int>>& grid) {

        m = grid.size();
        n = grid[0].size();

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    ans++;
                    dfs(grid, i, j);
                }

            }
        }

        return ans;
    }
};

class Solution {
public:
    int row, col;
    vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    void dfs(vector<vector<char>> &grid,int x,int y){
        if(x < 0 || x>=row || y< 0 ||y>=col){
            return;
        }

        if(grid[x][y] == '0'){
            return;
        }

        grid[x][y] = '0';

        for(auto d:dirs){
            dfs(grid, x + d[0], y + d[1]);
        }
    }

    int numIslands(vector<vector<char>> &grid)
    {
        // 行数
        row = grid.size();
        // 列数
        col = grid[0].size();

        int ans = 0;

        for (int i = 0; i < row;i++){
            for (int j = 0; j < col;j++){
                if(grid[i][j]=='1'){
                    ans += 1;
                    dfs(grid, i, j);
                }
            }
        }

        return ans;
    }
};



int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
