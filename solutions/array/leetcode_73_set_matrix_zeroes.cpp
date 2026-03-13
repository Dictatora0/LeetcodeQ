/*
LeetCode 73. 矩阵置零 (Set Matrix Zeroes)

题目概述 (Problem Summary)
-------------------------
给定一个 m × n 的矩阵 matrix，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。
请使用原地算法。

关键约束 (Key Constraints)
-------------------------
- m == matrix.length
- n == matrix[0].length
- 1 <= m, n <= 200
- -2³¹ <= matrix[i][j] <= 2³¹ - 1

进阶要求：
- 一个直观的解决方案是使用 O(m + n) 的额外空间，但这并不是一个好的解决方案
- 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案
- 你能想出一个仅使用常量空间的解决方案吗？

示例 (Example)
-------------
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]

解释：
原始矩阵：
1 1 1
1 0 1
1 1 1

第 1 行第 1 列的元素为 0，所以第 1 行和第 1 列都要置零：
1 0 1
0 0 0
1 0 1

输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 标记需要置零的行和列，然后统一置零
- 关键是如何在常量空间内完成标记

关键观察：
1. 最直观的方法：使用两个数组分别记录需要置零的行和列
2. 空间优化：可以使用矩阵的第一行和第一列作为标记数组
3. 需要特殊处理第一行和第一列本身是否需要置零
4. 处理顺序很重要：先标记，再置零，最后处理第一行和第一列

根据这些观察，可以得到几种典型解法：
1. 额外数组法 - O(m + n) 空间，简单直观
2. 使用第一行第一列作为标记 - O(1) 空间，最优解
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 - 使用第一行第一列作为标记 (Approach 1: My Original Solution - Using First Row and Column)

核心思想
--------
使用矩阵的第一行和第一列作为标记数组，记录哪些行和列需要置零。
由于第一行和第一列本身可能也需要置零，所以需要额外的两个变量来记录。

算法流程：
1. 使用两个布尔变量记录第一行和第一列是否需要置零
   - isFirstRowZero：第一行是否有 0
   - isFirstColZero：第一列是否有 0

2. 遍历矩阵（从第二行第二列开始），如果 matrix[i][j] == 0：
   - 将 matrix[i][0] 标记为 0（表示第 i 行需要置零）
   - 将 matrix[0][j] 标记为 0（表示第 j 列需要置零）

3. 根据第一行和第一列的标记，置零对应的行和列
   - 从第二行开始，如果 matrix[i][0] == 0，将第 i 行置零
   - 从第二列开始，如果 matrix[0][j] == 0，将第 j 列置零

4. 最后根据两个布尔变量，处理第一行和第一列

为什么要先检查第一行和第一列？
- 因为我们要用第一行和第一列作为标记数组
- 如果不先记录它们的状态，后续的标记操作会覆盖原始信息

为什么要从后往前处理？
- 避免标记信息被过早清除
- 先处理内部元素，最后处理第一行和第一列

复杂度分析
---------
时间复杂度：O(m * n)
- 需要遍历矩阵三次：
  1. 检查第一行和第一列
  2. 标记需要置零的行和列
  3. 根据标记置零

空间复杂度：O(1)
- 只使用了两个布尔变量
- 满足常量空间的要求

其中：
m = 矩阵的行数
n = 矩阵的列数
*/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();

        if(row == 0){
            return ;
        }

        int col = matrix[0].size();

        bool isFirstRowZero = false;
        bool isFirstColZero = false;

        for(int i = 0; i < col; i++){
            //检查第一行中是否有0
            if(matrix[0][i] == 0){
                isFirstRowZero = true;
            }
        }

        for(int i = 0; i < row; i++){
            //检查第一列中是否有0
            if(matrix[i][0] == 0){
                isFirstColZero = true;
            }
        }

        for(int i = 1; i < row; i++){
            for(int j = 1; j < col; j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;   //所在行的第一个元素标记为0
                    matrix[0][j] = 0;   //所在列的第一个元素标记为0
                }
            }
        }

        for(int i = 1; i < row; i++){
            //从第二行开始检查当前行的第一个元素
            if(matrix[i][0] == 0){
                for (int j = 1; j < col; j++){
                    //将被标记的行置0
                    matrix[i][j] = 0;
                }
        }
    }

        for(int j = 1; j < col; j++){
            ////从第二列开始检查当前列的第一个元素
            if(matrix[0][j] == 0){
                for (int i = 1; i < row; i++){
                    //将被标记的列置0
                    matrix[i][j] = 0;
                }
        }
    }

        if(isFirstRowZero){
            for (int i = 0; i < col;i++){
                matrix[0][i] = 0;
            }
        }
        if(isFirstColZero){
            for (int i = 0; i < row;i++){
                matrix[i][0] = 0;
            }
        }
        }
};

/*
方法二：额外数组法 (Approach 2: Using Extra Arrays)

核心思想
--------
使用两个额外的数组分别记录需要置零的行和列。

算法流程：
1. 创建两个布尔数组：
   - rows[m]：记录哪些行需要置零
   - cols[n]：记录哪些列需要置零

2. 遍历矩阵，如果 matrix[i][j] == 0：
   - 标记 rows[i] = true
   - 标记 cols[j] = true

3. 再次遍历矩阵，如果 rows[i] 或 cols[j] 为 true：
   - 将 matrix[i][j] 置为 0

复杂度分析
---------
时间复杂度：O(m * n)
- 需要遍历矩阵两次

空间复杂度：O(m + n)
- 需要两个额外的数组
*/
class Solution_ExtraSpace {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();

        vector<bool> rows(m, false);
        vector<bool> cols(n, false);

        // 标记需要置零的行和列
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }
            }
        }

        // 根据标记置零
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rows[i] || cols[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

/*
方法三：优化的第一行第一列标记法 (Approach 3: Optimized First Row/Column Marking)

核心思想
--------
与方法一类似，但使用更简洁的实现方式。
只用一个变量记录第一列是否需要置零，第一行的状态可以通过 matrix[0][0] 判断。

算法流程：
1. 用 matrix[0][0] 表示第一行是否需要置零
2. 用 firstColZero 表示第一列是否需要置零
3. 其余逻辑与方法一相同

复杂度分析
---------
时间复杂度：O(m * n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();

        bool firstColZero = false;

        // 检查第一列是否需要置零
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
            }
        }

        // 使用第一行和第一列作为标记
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 根据标记置零（从后往前，避免覆盖标记）
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 1; j--) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 处理第一列
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：matrix = [[1,1,1],[1,0,1],[1,1,1]]

方法一的执行过程：

1. 检查第一行和第一列：
   - 第一行：[1,1,1]，无 0，isFirstRowZero = false
   - 第一列：[1,1,1]，无 0，isFirstColZero = false

2. 标记需要置零的行和列（从 [1][1] 开始）：
   - matrix[1][1] = 0
   - 标记：matrix[1][0] = 0（第 1 行需要置零）
   - 标记：matrix[0][1] = 0（第 1 列需要置零）

   矩阵变为：
   1 0 1
   0 0 1
   1 1 1

3. 根据标记置零：
   - matrix[1][0] = 0，将第 1 行置零：[0,0,0]
   - matrix[0][1] = 0，将第 1 列置零：[0,0,0]

   矩阵变为：
   1 0 1
   0 0 0
   1 0 1

4. 处理第一行和第一列：
   - isFirstRowZero = false，第一行不变
   - isFirstColZero = false，第一列不变

最终结果：
1 0 1
0 0 0
1 0 1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：使用第一行第一列作为标记
- 时间复杂度：O(m * n)
- 空间复杂度：O(1)
- 优点：满足常量空间要求，最优解
- 缺点：逻辑较复杂，需要仔细处理边界

方法二：额外数组法
- 时间复杂度：O(m * n)
- 空间复杂度：O(m + n)
- 优点：逻辑简单，易于理解
- 缺点：需要额外空间

方法三：优化的标记法
- 时间复杂度：O(m * n)
- 空间复杂度：O(1)
- 优点：代码更简洁
- 缺点：需要从后往前遍历

推荐使用方法一或方法三，满足常量空间要求。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 第一行有 0：需要将整个第一行置零
2. 第一列有 0：需要将整个第一列置零
3. 只有一行或一列：简化为一维问题
4. 全是 0：整个矩阵置零
5. 没有 0：矩阵不变
*/

int main() {
    Solution solution;

    // 测试用例 1：中间有 0
    vector<vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}};
    cout << "测试用例 1 - 原矩阵：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    solution.setZeroes(matrix1);
    cout << "置零后：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "期望：[[1,0,1],[0,0,0],[1,0,1]]" << endl << endl;

    // 测试用例 2：多个 0
    vector<vector<int>> matrix2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    cout << "测试用例 2 - 原矩阵：" << endl;
    for (auto& row : matrix2) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    solution.setZeroes(matrix2);
    cout << "置零后：" << endl;
    for (auto& row : matrix2) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "期望：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]" << endl;

    return 0;
}
