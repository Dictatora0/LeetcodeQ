/*
LeetCode 48. 旋转图像 (Rotate Image)

题目概述 (Problem Summary)
-------------------------
给定一个 n × n 的二维矩阵 matrix 表示一个图像，请你将图像顺时针旋转 90 度。

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

关键约束 (Key Constraints)
-------------------------
- n == matrix.length == matrix[i].length
- 1 <= n <= 20
- -1000 <= matrix[i][j] <= 1000

示例 (Example)
-------------
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]

解释：
原始矩阵：
1 2 3
4 5 6
7 8 9

旋转 90 度后：
7 4 1
8 5 2
9 6 3

输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将矩阵顺时针旋转 90 度，且要求原地操作

关键观察：
1. 旋转 90 度的规律：matrix[i][j] → matrix[j][n-1-i]
   - 第 i 行第 j 列的元素，旋转后会到第 j 行第 (n-1-i) 列
2. 可以先用辅助数组保存旋转后的结果，再复制回原矩阵
3. 更优的方法：先转置矩阵，再翻转每一行
   - 转置：matrix[i][j] ↔ matrix[j][i]
   - 翻转：reverse(matrix[i])
4. 还可以通过找规律直接原地旋转（四个位置一组循环替换）

根据这些观察，可以得到几种典型解法：
1. 辅助数组法 - 空间 O(n²)，简单直观
2. 转置+翻转法 - 空间 O(1)，两步操作
3. 原地旋转法 - 空间 O(1)，一次遍历
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 - 辅助数组法 (Approach 1: My Original Solution - Using Auxiliary Array)

核心思想
--------
使用辅助数组保存旋转后的矩阵，然后将结果复制回原矩阵。

算法流程：
1. 创建辅助数组 mem，预分配 n*n 的空间
2. 按照旋转规律填充辅助数组：
   - 从每一列的最下方元素开始（即旋转后形成的行的第一个元素）
   - 从下往上遍历该列，得到旋转后数组的一行
3. 将辅助数组的内容复制回原矩阵

为什么这样做是正确的？
- 旋转 90 度后，原矩阵的第 j 列（从下往上）变成新矩阵的第 j 行（从左往右）
- 即：matrix[n-1][j], matrix[n-2][j], ..., matrix[0][j] → 新矩阵第 j 行

复杂度分析
---------
时间复杂度：O(n²)
- 需要遍历所有 n² 个元素两次（一次填充，一次复制）

空间复杂度：O(n²)
- 需要额外的辅助数组存储 n² 个元素

其中：
n = 矩阵的边长
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        if(matrix.empty()||matrix[0].empty()){
            return;
        }

        int n = matrix.size();

        vector<int> mem; //保存旋转后数组的正确形式
        mem.reserve(n * n);

        //从每一列的最下方元素（即旋转后形成的行的第一个元素）开始
        for (int i = 0; i < n; i++){
            for (int j = n-1; j >= 0; j--){//上移指针，得到旋转后数组的一行并记录
                mem.push_back(matrix[j][i]);
            }
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrix[i][j] = mem[i * n + j];//根据坐标规律修改原数组
            }
        }
        }
};

/*
方法二：转置+翻转法 (Approach 2: Transpose and Reverse)

核心思想
--------
将旋转 90 度分解为两个简单操作：
1. 先沿主对角线转置矩阵
2. 再翻转每一行

算法流程：
1. 转置矩阵：交换 matrix[i][j] 和 matrix[j][i]（只需遍历上三角）
2. 翻转每一行：reverse(matrix[i])

为什么这样做是正确的？
- 转置：matrix[i][j] → matrix[j][i]
- 翻转：matrix[j][i] → matrix[j][n-1-i]
- 组合：matrix[i][j] → matrix[j][n-1-i]（正好是旋转 90 度的规律）

复杂度分析
---------
时间复杂度：O(n²)
- 转置需要 O(n²/2)
- 翻转需要 O(n²/2)
- 总计 O(n²)

空间复杂度：O(1)
- 只使用常数个临时变量
- 满足原地操作的要求
*/
class Solution_TransposeReverse {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return;

        int n = matrix.size();

        // 步骤 1：转置矩阵（沿主对角线翻转）
        // 只需遍历上三角部分，避免重复交换
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 步骤 2：翻转每一行
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

/*
方法三：原地旋转法（四个位置一组） (Approach 3: In-place Rotation)

核心思想
--------
将矩阵分为若干层，从外层到内层逐层旋转。
对于每一层，将四个对应位置的元素进行循环替换。

算法流程：
1. 确定需要旋转的层数：n/2 层
2. 对于每一层：
   - 确定该层的边界
   - 遍历该层的每个位置（不包括最后一个，因为会形成循环）
   - 同时旋转四个对应位置的元素

旋转规律（四个位置一组）：
- 位置 1: (i, j)
- 位置 2: (j, n-1-i)
- 位置 3: (n-1-i, n-1-j)
- 位置 4: (n-1-j, i)

复杂度分析
---------
时间复杂度：O(n²)
- 每个元素访问一次

空间复杂度：O(1)
- 只使用常数个临时变量
*/
class Solution_InPlace {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return;

        int n = matrix.size();

        // 需要旋转的层数
        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;

            // 遍历当前层的每个位置
            for (int i = first; i < last; i++) {
                int offset = i - first;

                // 保存上边的元素
                int top = matrix[first][i];

                // 左边 → 上边
                matrix[first][i] = matrix[last - offset][first];

                // 下边 → 左边
                matrix[last - offset][first] = matrix[last][last - offset];

                // 右边 → 下边
                matrix[last][last - offset] = matrix[i][last];

                // 上边 → 右边
                matrix[i][last] = top;
            }
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：matrix = [[1,2,3],[4,5,6],[7,8,9]]

方法一（辅助数组）的执行过程：
1. 创建辅助数组 mem
2. 按列从下往上遍历：
   - 第 0 列：7, 4, 1 → mem = [7,4,1]
   - 第 1 列：8, 5, 2 → mem = [7,4,1,8,5,2]
   - 第 2 列：9, 6, 3 → mem = [7,4,1,8,5,2,9,6,3]
3. 复制回原矩阵：
   - matrix[0] = [7,4,1]
   - matrix[1] = [8,5,2]
   - matrix[2] = [9,6,3]

方法二（转置+翻转）的执行过程：
1. 转置矩阵：
   1 2 3      1 4 7
   4 5 6  →   2 5 8
   7 8 9      3 6 9

2. 翻转每一行：
   1 4 7      7 4 1
   2 5 8  →   8 5 2
   3 6 9      9 6 3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：辅助数组法
- 时间复杂度：O(n²)
- 空间复杂度：O(n²)
- 优点：思路简单直观，易于理解
- 缺点：不满足原地操作要求，空间开销大

方法二：转置+翻转法
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：满足原地操作要求，代码简洁
- 缺点：需要两次遍历

方法三：原地旋转法
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：满足原地操作要求，只需一次遍历
- 缺点：代码较复杂，不易理解

推荐使用方法二（转置+翻转），代码简洁且满足要求。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 1×1 矩阵：无需旋转
2. 2×2 矩阵：最小的需要旋转的情况
3. 奇数阶矩阵：中心元素不需要移动
4. 偶数阶矩阵：所有元素都需要移动
*/

int main() {
    Solution solution;

    // 测试用例 1：3×3 矩阵
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "测试用例 1 - 原矩阵：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    solution.rotate(matrix1);
    cout << "旋转后：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "期望：[[7,4,1],[8,5,2],[9,6,3]]" << endl << endl;

    // 测试用例 2：4×4 矩阵
    vector<vector<int>> matrix2 = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    cout << "测试用例 2 - 原矩阵：" << endl;
    for (auto& row : matrix2) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    solution.rotate(matrix2);
    cout << "旋转后：" << endl;
    for (auto& row : matrix2) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "期望：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]" << endl;

    return 0;
}
