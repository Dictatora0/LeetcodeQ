/*
LeetCode 240. 搜索二维矩阵 II (Search a 2D Matrix II)

题目概述 (Problem Summary)
-------------------------
编写一个高效的算法来搜索 m × n 矩阵 matrix 中的一个目标值 target。

该矩阵具有以下特性：
- 每行的元素从左到右升序排列
- 每列的元素从上到下升序排列

关键约束 (Key Constraints)
-------------------------
- m == matrix.length
- n == matrix[i].length
- 1 <= n, m <= 300
- -10⁹ <= matrix[i][j] <= 10⁹
- 每行的所有元素从左到右升序排列
- 每列的所有元素从上到下升序排列
- -10⁹ <= target <= 10⁹

示例 (Example)
-------------
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true

解释：
矩阵：
 1   4   7  11  15
 2   5   8  12  19
 3   6   9  16  22
10  13  14  17  24
18  21  23  26  30

目标值 5 存在于矩阵中

输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在一个行列都有序的矩阵中高效搜索目标值

关键观察：
1. 矩阵的特殊性质：行递增、列递增
2. 如果从左上角开始，无法确定向右还是向下移动
3. 如果从右上角开始：
   - 当前值 > target：向左移动（排除当前列）
   - 当前值 < target：向下移动（排除当前行）
   - 当前值 = target：找到目标
4. 同样，从左下角开始也可以
5. 每次比较都能排除一行或一列，类似二分查找的思想

根据这些观察，可以得到几种典型解法：
1. 从右上角开始搜索 - O(m + n) 时间，最优解
2. 从左下角开始搜索 - O(m + n) 时间，同样高效
3. 对每一行进行二分查找 - O(m log n) 时间
4. 暴力搜索 - O(m * n) 时间
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 - 从右上角开始搜索 (Approach 1: My Original Solution - Search from Top-Right)

核心思想
--------
利用矩阵的有序特性，从右上角元素开始搜索，每次比较都能排除一行或一列。

算法流程：
1. 从右上角开始（row = 0, col = n - 1）
2. 比较当前元素与目标值：
   - 如果相等：找到目标，返回 true
   - 如果当前值 > target：向左移动（col--），排除当前列
   - 如果当前值 < target：向下移动（row++），排除当前行
3. 如果越界还没找到，返回 false

为什么从右上角开始？
- 右上角元素是该行最大值，该列最小值
- 如果 matrix[row][col] > target：
  - 说明整列都大于 target（因为列递增）
  - 可以安全地排除这一列，向左移动
- 如果 matrix[row][col] < target：
  - 说明整行都小于 target（因为行递增）
  - 可以安全地排除这一行，向下移动

为什么不能从左上角开始？
- 左上角是该行最小值，该列最小值
- 如果 matrix[row][col] < target，无法确定是向右还是向下
- 因为右边和下边的值都可能等于 target

复杂度分析
---------
时间复杂度：O(m + n)
- 最坏情况下，从右上角走到左下角
- 最多移动 m + n - 1 步

空间复杂度：O(1)
- 只使用常数个变量

其中：
m = 矩阵的行数
n = 矩阵的列数
*/
//利用矩阵的有序特性，从右上角元素开始搜索，每次比较都能排除一行或一列。
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int m = matrix.size();
        int n = matrix[0].size();

        // 从右上角开始
        int row = 0, col = n - 1;

        while (row < m && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                // 当前值太大，向左移动（排除当前列）
                col--;
            } else {
                // 当前值太小，向下移动（排除当前行）
                row++;
            }
        }

        return false;
    }
};

/*
方法二：从左下角开始搜索 (Approach 2: Search from Bottom-Left)

核心思想
--------
与方法一类似，但从左下角开始搜索。

算法流程：
1. 从左下角开始（row = m - 1, col = 0）
2. 比较当前元素与目标值：
   - 如果相等：找到目标，返回 true
   - 如果当前值 > target：向上移动（row--），排除当前行
   - 如果当前值 < target：向右移动（col++），排除当前列
3. 如果越界还没找到，返回 false

为什么从左下角开始也可以？
- 左下角元素是该行最小值，该列最大值
- 如果 matrix[row][col] > target：向上移动
- 如果 matrix[row][col] < target：向右移动
- 同样每次都能排除一行或一列

复杂度分析
---------
时间复杂度：O(m + n)
空间复杂度：O(1)
*/
class Solution_BottomLeft {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int m = matrix.size();
        int n = matrix[0].size();

        // 从左下角开始
        int row = m - 1, col = 0;

        while (row >= 0 && col < n) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                // 当前值太大，向上移动（排除当前行）
                row--;
            } else {
                // 当前值太小，向右移动（排除当前列）
                col++;
            }
        }

        return false;
    }
};

/*
方法三：对每一行进行二分查找 (Approach 3: Binary Search on Each Row)

核心思想
--------
对矩阵的每一行进行二分查找。

算法流程：
1. 遍历每一行
2. 对当前行进行二分查找
3. 如果找到目标值，返回 true
4. 遍历完所有行都没找到，返回 false

复杂度分析
---------
时间复杂度：O(m log n)
- 对 m 行分别进行二分查找
- 每次二分查找的时间复杂度为 O(log n)

空间复杂度：O(1)

与方法一的对比：
- 方法一：O(m + n)，更优
- 方法三：O(m log n)，当 n 很大时可能更慢
*/
class Solution_BinarySearch {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int m = matrix.size();

        for (int i = 0; i < m; i++) {
            if (binarySearch(matrix[i], target)) {
                return true;
            }
        }

        return false;
    }

private:
    bool binarySearch(vector<int>& row, int target) {
        int left = 0, right = row.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (row[mid] == target) {
                return true;
            } else if (row[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5

方法一（从右上角开始）的执行过程：

矩阵：
 1   4   7  11  15
 2   5   8  12  19
 3   6   9  16  22
10  13  14  17  24
18  21  23  26  30

1. 初始位置：row = 0, col = 4，matrix[0][4] = 15
   - 15 > 5，向左移动，col = 3

2. 当前位置：row = 0, col = 3，matrix[0][3] = 11
   - 11 > 5，向左移动，col = 2

3. 当前位置：row = 0, col = 2，matrix[0][2] = 7
   - 7 > 5，向左移动，col = 1

4. 当前位置：row = 0, col = 1，matrix[0][1] = 4
   - 4 < 5，向下移动，row = 1

5. 当前位置：row = 1, col = 1，matrix[1][1] = 5
   - 5 == 5，找到目标，返回 true

搜索路径：15 → 11 → 7 → 4 → 5
总共比较了 5 次
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：从右上角开始搜索
- 时间复杂度：O(m + n)
- 空间复杂度：O(1)
- 优点：最优时间复杂度，代码简洁
- 缺点：需要理解为什么从右上角开始

方法二：从左下角开始搜索
- 时间复杂度：O(m + n)
- 空间复杂度：O(1)
- 优点：与方法一等价，可以根据个人喜好选择
- 缺点：同方法一

方法三：对每一行二分查找
- 时间复杂度：O(m log n)
- 空间复杂度：O(1)
- 优点：思路直观，利用了行有序的特性
- 缺点：没有充分利用列有序的特性，时间复杂度较高

推荐使用方法一或方法二，时间复杂度最优。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空矩阵：返回 false
2. 1×1 矩阵：直接比较唯一元素
3. 目标值小于左上角：直接返回 false
4. 目标值大于右下角：直接返回 false
5. 目标值在边界上：正确处理边界情况
*/

int main() {
    Solution solution;

    // 测试用例 1：目标值存在
    vector<vector<int>> matrix1 = {
        {1,4,7,11,15},
        {2,5,8,12,19},
        {3,6,9,16,22},
        {10,13,14,17,24},
        {18,21,23,26,30}
    };
    int target1 = 5;
    cout << "测试用例 1 - 矩阵：" << endl;
    for (auto& row : matrix1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "搜索目标：" << target1 << endl;
    cout << "结果：" << (solution.searchMatrix(matrix1, target1) ? "true" : "false") << endl;
    cout << "期望：true" << endl << endl;

    // 测试用例 2：目标值不存在
    int target2 = 20;
    cout << "测试用例 2 - 搜索目标：" << target2 << endl;
    cout << "结果：" << (solution.searchMatrix(matrix1, target2) ? "true" : "false") << endl;
    cout << "期望：false" << endl << endl;

    // 测试用例 3：边界情况
    vector<vector<int>> matrix3 = {{1,4},{2,5}};
    int target3 = 2;
    cout << "测试用例 3 - 矩阵：" << endl;
    for (auto& row : matrix3) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "搜索目标：" << target3 << endl;
    cout << "结果：" << (solution.searchMatrix(matrix3, target3) ? "true" : "false") << endl;
    cout << "期望：true" << endl;

    return 0;
}
