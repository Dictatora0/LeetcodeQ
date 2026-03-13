/*
LeetCode 54. 螺旋矩阵 (Spiral Matrix)

题目概述 (Problem Summary)
-------------------------
给定一个 m × n 的矩阵 matrix，请按照顺时针螺旋顺序，返回矩阵中的所有元素。

关键约束 (Key Constraints)
-------------------------
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 10
- -100 <= matrix[i][j] <= 100

示例 (Example)
-------------
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

解释：
1 → 2 → 3
        ↓
4 → 5   6
↑       ↓
7 ← 8 ← 9

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]

解释：
1 → 2 → 3 → 4
            ↓
5 → 6 → 7   8
↑           ↓
9 ← 10← 11← 12

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 按照螺旋顺序（外圈到内圈）遍历矩阵的所有元素

关键观察：
1. 螺旋遍历可以看作是一层一层地遍历
2. 每一层的遍历顺序：右 → 下 → 左 → 上
3. 需要维护四个边界：上边界、下边界、左边界、右边界
4. 每遍历完一条边，对应的边界就要收缩
5. 需要注意边界条件，避免重复遍历

根据这些观察，可以得到几种典型解法：
1. 模拟法（边界收缩）- 最直观，O(m*n) 时间
2. 方向数组法 - 使用方向向量控制移动
3. 递归法 - 递归处理每一层
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 - 边界收缩法 (Approach 1: My Original Solution - Boundary Shrinking)

核心思想
--------
维护四个边界（上、下、左、右），按照螺旋顺序遍历，每遍历完一条边就收缩对应的边界。

算法流程：
1. 初始化四个边界：
   - top = 0（上边界）
   - bottom = row - 1（下边界）
   - left = 0（左边界）
   - right = col - 1（右边界）
2. 循环条件：top <= bottom && left <= right
3. 每次循环按顺序遍历四条边：
   a. 从左到右遍历上边界，然后 top++
   b. 从上到下遍历右边界，然后 right--
   c. 从右到左遍历下边界（需检查 top <= bottom），然后 bottom--
   d. 从下到上遍历左边界（需检查 left <= right），然后 left++

为什么需要额外的边界检查？
- 在遍历下边界和左边界时，可能上下边界或左右边界已经相遇
- 如果不检查，会导致重复遍历某些元素

复杂度分析
---------
时间复杂度：O(m * n)
- 每个元素访问一次

空间复杂度：O(1)
- 不考虑输出数组，只使用常数个变量
- 如果考虑输出数组，空间复杂度为 O(m * n)

其中：
m = 矩阵的行数
n = 矩阵的列数
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {

        if (matrix.empty() || matrix[0].empty()) return {};

        int row = matrix.size();
        int col = matrix[0].size();

        vector<int> ans;
        ans.reserve(row * col);// 提前分配空间，提高效率

        int left = 0,right = col-1;
        int top = 0,bottom = row-1;

        while (top <= bottom && left <= right) {
                // 从左到右遍历上边界
                for (int j = left; j <= right; ++j) {
                    ans.push_back(matrix[top][j]);
                }
                ++top; // 上边界下移

                // 从上到下遍历右边界
                for (int i = top; i <= bottom; ++i) {
                    ans.push_back(matrix[i][right]);
                }
                --right; // 右边界左移

                // 从右到左遍历下边界（需检查是否还有行）
                if (top <= bottom) {
                    for (int j = right; j >= left; --j) {
                        ans.push_back(matrix[bottom][j]);
                    }
                    --bottom; // 下边界上移
                }

                // 从下到上遍历左边界（需检查是否还有列）
                if (left <= right) {
                    for (int i = bottom; i >= top; --i) {
                        ans.push_back(matrix[i][left]);
                    }
                    ++left; // 左边界右移
                }
            }
            return ans;
        }
    };

/*
方法二：方向数组法 (Approach 2: Direction Array)

核心思想
--------
使用方向数组控制移动方向，遇到边界或已访问的元素时改变方向。

算法流程：
1. 定义方向数组：右(0,1)、下(1,0)、左(0,-1)、上(-1,0)
2. 使用 visited 数组标记已访问的元素
3. 从 (0,0) 开始，按当前方向移动
4. 如果下一个位置越界或已访问，则顺时针转向
5. 继续移动直到访问完所有元素

复杂度分析
---------
时间复杂度：O(m * n)
- 每个元素访问一次

空间复杂度：O(m * n)
- 需要 visited 数组标记已访问元素
*/
class Solution_Direction {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> result;
        result.reserve(m * n);

        // 方向数组：右、下、左、上
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int dir = 0; // 当前方向索引

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int x = 0, y = 0;

        for (int i = 0; i < m * n; i++) {
            result.push_back(matrix[x][y]);
            visited[x][y] = true;

            // 计算下一个位置
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 如果下一个位置越界或已访问，则转向
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny]) {
                dir = (dir + 1) % 4; // 顺时针转向
                nx = x + dx[dir];
                ny = y + dy[dir];
            }

            x = nx;
            y = ny;
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：matrix = [[1,2,3],[4,5,6],[7,8,9]]

方法一（边界收缩）的执行过程：

初始状态：
top = 0, bottom = 2, left = 0, right = 2

第一轮循环：
1. 从左到右遍历上边界（top=0）：1, 2, 3
   top++ → top = 1
   ans = [1,2,3]

2. 从上到下遍历右边界（right=2）：6, 9
   right-- → right = 1
   ans = [1,2,3,6,9]

3. 从右到左遍历下边界（bottom=2）：8, 7
   bottom-- → bottom = 1
   ans = [1,2,3,6,9,8,7]

4. 从下到上遍历左边界（left=0）：4
   left++ → left = 1
   ans = [1,2,3,6,9,8,7,4]

第二轮循环：
1. 从左到右遍历上边界（top=1）：5
   top++ → top = 2
   ans = [1,2,3,6,9,8,7,4,5]

2. top > bottom，循环结束

最终结果：[1,2,3,6,9,8,7,4,5]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：边界收缩法
- 时间复杂度：O(m * n)
- 空间复杂度：O(1)（不考虑输出数组）
- 优点：空间效率高，逻辑清晰
- 缺点：需要仔细处理边界条件

方法二：方向数组法
- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)
- 优点：代码结构统一，易于理解
- 缺点：需要额外的 visited 数组

推荐使用方法一（边界收缩法），空间效率更高。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单行矩阵：[[1,2,3]] → [1,2,3]
2. 单列矩阵：[[1],[2],[3]] → [1,2,3]
3. 1×1 矩阵：[[1]] → [1]
4. 2×2 矩阵：最小的需要完整螺旋的情况
5. 矩形矩阵：行数和列数不相等
*/

int main() {
    Solution solution;

    // 测试用例 1：3×3 矩阵
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "测试用例 1 - 输入矩阵：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    vector<int> result1 = solution.spiralOrder(matrix1);
    cout << "螺旋顺序：[";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[1,2,3,6,9,8,7,4,5]" << endl << endl;

    // 测试用例 2：3×4 矩阵
    vector<vector<int>> matrix2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    cout << "测试用例 2 - 输入矩阵：" << endl;
    for (auto& row : matrix2) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    vector<int> result2 = solution.spiralOrder(matrix2);
    cout << "螺旋顺序：[";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[1,2,3,4,8,12,11,10,9,5,6,7]" << endl;

    return 0;
}
