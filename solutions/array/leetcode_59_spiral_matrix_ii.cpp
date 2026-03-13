/*
LeetCode 59. 螺旋矩阵 II (Spiral Matrix II)

题目概述 (Problem Summary)
-------------------------
给定一个正整数 n，生成一个 n x n 的矩阵，
按顺时针螺旋顺序填入 1 到 n^2。

关键约束 (Key Constraints)
-------------------------
- 1 <= n <= 20

示例 (Example)
-------------
输入：n = 3
输出：
[
 [1,2,3],
 [8,9,4],
 [7,6,5]
]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 按固定的螺旋顺序逐层填充矩阵

关键观察：
1. 可以用四个边界 (top, bottom, left, right) 控制一层的填充
2. 每次填充一圈后收缩边界
3. 直到所有数字填完

根据这些观察，可以得到两种典型解法：
1. 边界收缩法
2. 方向数组 + 访问控制
*/

#include <iostream>
#include <vector>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用四个边界收缩：
按右、下、左、上四个方向填充一圈，然后收缩边界继续。

算法流程：
1. 初始化 top=0, bottom=n-1, left=0, right=n-1
2. 依次填充上边、右边、下边、左边
3. 每完成一圈，边界向内收缩

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(1)（不计输出矩阵）
*/
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int cur = 1, maxVal = n * n;

        while (cur <= maxVal) {
            for (int j = left; j <= right && cur <= maxVal; ++j) {
                matrix[top][j] = cur++;
            }
            top++;

            for (int i = top; i <= bottom && cur <= maxVal; ++i) {
                matrix[i][right] = cur++;
            }
            right--;

            for (int j = right; j >= left && cur <= maxVal; --j) {
                matrix[bottom][j] = cur++;
            }
            bottom--;

            for (int i = bottom; i >= top && cur <= maxVal; --i) {
                matrix[i][left] = cur++;
            }
            left++;
        }

        return matrix;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Direction Simulation)

优化思路
--------
使用方向数组（右、下、左、上）进行模拟，
当下一步越界或已访问时，转向。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n^2)（需要 visited）
*/
class Solution_Optimized {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        int dir = 0;
        int r = 0, c = 0;

        for (int val = 1; val <= n * n; ++val) {
            matrix[r][c] = val;
            visited[r][c] = true;

            int nr = r + dirs[dir][0];
            int nc = c + dirs[dir][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc]) {
                dir = (dir + 1) % 4;
                nr = r + dirs[dir][0];
                nc = c + dirs[dir][1];
            }
            r = nr;
            c = nc;
        }

        return matrix;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
n = 3
填充顺序：
1 2 3
8 9 4
7 6 5
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：边界收缩
- 时间复杂度：O(n^2)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：边界处理较多

方法二：方向模拟
- 时间复杂度：O(n^2)
- 空间复杂度：O(n^2)
- 优点：实现直观
- 缺点：需要 visited
*/

/*
特殊情况 (Edge Cases)
--------------------
1. n=1：输出 [[1]]
2. n=2：标准 2x2 螺旋
*/

static void printMatrix(const vector<vector<int>>& matrix) {
    cout << "[\n";
    for (const auto& row : matrix) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            cout << row[i];
            if (i + 1 < row.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1
    int n1 = 3;
    cout << "测试用例 1 - 输出:\n";
    printMatrix(solution.generateMatrix(n1));
    cout << "期望：3x3 螺旋矩阵" << endl;

    // 测试用例 2
    int n2 = 1;
    cout << "测试用例 2 - 输出:\n";
    printMatrix(solution.generateMatrix(n2));
    cout << "期望：[[1]]" << endl;

    return 0;
}
