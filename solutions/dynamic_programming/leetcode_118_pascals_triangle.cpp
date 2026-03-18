/*
LeetCode 118. 杨辉三角 (Pascal's Triangle)

题目概述 (Problem Summary)
-------------------------
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在杨辉三角中：
- 每一行的第一个和最后一个元素都是 1
- 其余位置的元素等于上一行左上角和右上角两个元素之和

关键约束 (Key Constraints)
-------------------------
- 1 <= numRows <= 30

示例 (Example)
-------------
输入：numRows = 5
输出：[[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 逐行构造一个二维结构
- 当前行只依赖上一行，因此是非常典型的递推 / DP 建表题

关键观察：
1. 第 i 行一共有 i + 1 个数字
2. 每行两端固定是 1
3. 中间位置满足：
   triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j]

根据这些观察，可以得到两种典型解法：
1. 直接二维递推
2. 原地滚动构造单行（进阶）
*/

#include <iostream>
#include <vector>

using namespace std;

/*
方法一：二维递推 (Approach 1: 2D DP / Simulation)

核心思想
--------
按行构造答案。每一行先全部初始化为 1，再补齐中间位置。

算法流程：
1. 创建长度为 numRows 的二维数组
2. 第 i 行先开辟 i + 1 个位置，并全部填成 1
3. 对于中间位置 j（1 <= j < i）：
   triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j]
4. 返回整个 triangle

复杂度分析
---------
时间复杂度：O(numRows^2)
- 总共会填充约 1 + 2 + ... + numRows 个位置

空间复杂度：O(numRows^2)
- 结果数组本身的空间
*/
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle(numRows);

        for (int i = 0; i < numRows; ++i) {
            triangle[i].resize(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }

        return triangle;
    }
};

/*
方法二：单行滚动构造 (Approach 2: Rolling Row Construction)

核心思想
--------
只维护当前行，从右往左更新，避免覆盖掉上一轮仍然需要使用的数据。

算法流程：
1. 使用 row 维护当前行
2. 每轮先在末尾补一个 1
3. 从右往左更新中间位置：
   row[j] = row[j] + row[j - 1]
4. 把当前 row 加入答案

复杂度分析
---------
时间复杂度：O(numRows^2)
空间复杂度：O(numRows)

优点：
- 如果题目只要求逐行输出，这种写法更节省空间

缺点：
- 不如二维写法直观
*/
class Solution_Rolling {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        vector<int> row;

        for (int i = 0; i < numRows; ++i) {
            row.push_back(1);
            for (int j = i - 1; j >= 1; --j) {
                row[j] += row[j - 1];
            }
            result.push_back(row);
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
numRows = 5

第 0 行：[1]
第 1 行：[1,1]
第 2 行：[1,2,1]
第 3 行：[1,3,3,1]
第 4 行：[1,4,6,4,1]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维递推
- 时间复杂度：O(numRows^2)
- 空间复杂度：O(numRows^2)
- 优点：最好理解，最适合面试表达
- 缺点：额外保留了全部中间状态

方法二：单行滚动构造
- 时间复杂度：O(numRows^2)
- 空间复杂度：O(numRows)
- 优点：空间更省
- 缺点：更新顺序更容易写错
*/

/*
特殊情况 (Edge Cases)
--------------------
1. numRows = 1：直接返回 [[1]]
2. 行数较少时，中间位置循环不会进入
*/

static void printTriangle(const vector<vector<int>>& triangle) {
    cout << "[" << endl;
    for (const auto& row : triangle) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << row[i];
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    vector<vector<int>> result1 = solution.generate(1);
    cout << "测试用例 1 - numRows = 1" << endl;
    printTriangle(result1);

    vector<vector<int>> result2 = solution.generate(5);
    cout << "测试用例 2 - numRows = 5" << endl;
    printTriangle(result2);

    return 0;
}
