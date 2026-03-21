/*
LeetCode 74. 搜索二维矩阵 (Search a 2D Matrix)

题目概述 (Problem Summary)
-------------------------
给定一个 m x n 的整数矩阵 matrix，该矩阵具有以下特性：
- 每行中的整数从左到右按非递减顺序排列
- 每行的第一个整数大于前一行的最后一个整数

给定一个整数 target，如果 target 在矩阵中，返回 true；否则返回 false。

要求：时间复杂度为 O(log(m * n))

关键约束 (Key Constraints)
-------------------------
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 100
- -10^4 <= matrix[i][j], target <= 10^4

示例 (Example)
-------------
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true

输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在一个有序的二维矩阵中查找目标值

关键观察：
1. 矩阵的每一行都是有序的
2. 每一行的第一个元素大于上一行的最后一个元素
3. 这意味着整个矩阵可以看作一个有序的一维数组
4. 可以使用二分查找，时间复杂度 O(log(m*n))

核心技巧：二维坐标与一维索引的转换
- 一维索引 mid 对应的二维坐标：
  - 行号：mid / n（整除）
  - 列号：mid % n（取余）
- 例如：3x4 的矩阵，mid=5 对应 matrix[5/4][5%4] = matrix[1][1]

为什么这个转换有效？
- 将二维矩阵按行展开成一维数组：
  [0,1,2,3, 4,5,6,7, 8,9,10,11]
  对应矩阵：
  [0,1,2,3]
  [4,5,6,7]
  [8,9,10,11]
- 索引 5 在第 1 行（5/4=1），第 1 列（5%4=1）

根据这些观察，可以得到二分查找解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - Binary Search on 2D Matrix)

核心思想
--------
将二维矩阵看作一维有序数组，使用标准二分查找。

算法流程：
1. 初始化 left=0, right=m*n-1
2. 计算 mid = left + (right - left) / 2
3. 将 mid 转换为二维坐标：
   - 行号：mid / n
   - 列号：mid % n
4. 比较 matrix[mid/n][mid%n] 与 target：
   - 相等：返回 true
   - 大于：right = mid - 1
   - 小于：left = mid + 1
5. 循环结束后返回 false

为什么这个算法正确？
- 矩阵的有序性保证了二分查找的单调性
- 坐标转换保证了正确访问矩阵元素
- 标准二分查找保证了 O(log(m*n)) 的时间复杂度

复杂度分析
---------
时间复杂度：O(log(m*n))，二分查找
空间复杂度：O(1)，只使用常数额外空间
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int left = 0;
        int right = m * n - 1;  // 一维数组的最后一个索引

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // 关键：将一维索引 mid 转换为二维坐标
            // mid / n 得到行号，mid % n 得到列号
            int midValue = matrix[mid / n][mid % n];

            if (midValue == target) {
                return true;
            } else if (midValue > target) {
                right = mid - 1;  // 目标在左半部分
            } else {
                left = mid + 1;   // 目标在右半部分
            }
        }

        return false;
    }
};

/*
方法二：优化解法 (Approach 2: Two-Step Binary Search)

优化思路
--------
先用二分查找定位目标所在的行，再在该行中二分查找。

算法流程：
1. 第一次二分：在第一列中查找 target 所在的行
2. 第二次二分：在确定的行中查找 target

复杂度分析
---------
时间复杂度：O(log m + log n)
空间复杂度：O(1)

注：O(log m + log n) 与 O(log(m*n)) 等价，但实现稍复杂
*/
class Solution_TwoStep {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 第一步：找到目标可能所在的行
        int row = 0;
        int top = 0, bottom = m - 1;
        while (top <= bottom) {
            int mid = top + (bottom - top) / 2;
            if (matrix[mid][0] <= target) {
                row = mid;
                top = mid + 1;
            } else {
                bottom = mid - 1;
            }
        }

        // 第二步：在该行中二分查找
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[row][mid] == target) {
                return true;
            } else if (matrix[row][mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return false;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3

一维视角：[1,3,5,7,10,11,16,20,23,30,34,60]
m=3, n=4, 总共 12 个元素

第 1 轮：
- left=0, right=11
- mid=5, matrix[5/4][5%4] = matrix[1][1] = 11
- 11 > 3，right=4

第 2 轮：
- left=0, right=4
- mid=2, matrix[2/4][2%4] = matrix[0][2] = 5
- 5 > 3，right=1

第 3 轮：
- left=0, right=1
- mid=0, matrix[0/4][0%4] = matrix[0][0] = 1
- 1 < 3，left=1

第 4 轮：
- left=1, right=1
- mid=1, matrix[1/4][1%4] = matrix[0][1] = 3
- 3 == 3，返回 true
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单行矩阵：退化为一维二分查找
2. 单列矩阵：同样适用
3. target 小于最小值或大于最大值：正常返回 false
4. 1x1 矩阵：直接比较
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：一维二分查找
- 时间复杂度：O(log(m*n))
- 空间复杂度：O(1)
- 优点：代码简洁，思路直观
- 缺点：需要理解坐标转换

方法二：两步二分查找
- 时间复杂度：O(log m + log n)
- 空间复杂度：O(1)
- 优点：更符合直觉
- 缺点：代码稍长

推荐方法一，因为代码更简洁。
*/

int main() {
    Solution solution;

    // 测试用例 1：目标存在
    vector<vector<int>> matrix1 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target1 = 3;
    bool result1 = solution.searchMatrix(matrix1, target1);
    cout << "测试用例 1 - 输出: " << (result1 ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例 2：目标不存在
    vector<vector<int>> matrix2 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target2 = 13;
    bool result2 = solution.searchMatrix(matrix2, target2);
    cout << "测试用例 2 - 输出: " << (result2 ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例 3：单行矩阵
    vector<vector<int>> matrix3 = {{1, 3, 5, 7}};
    int target3 = 5;
    bool result3 = solution.searchMatrix(matrix3, target3);
    cout << "测试用例 3 - 输出: " << (result3 ? "true" : "false") << " (期望: true)" << endl;

    return 0;
}
