/*
LeetCode 1143. 最长公共子序列 (Longest Common Subsequence)

题目概述 (Problem Summary)
-------------------------
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
如果不存在公共子序列，返回 0。

子序列：由原字符串删除某些字符（或不删除）而不改变剩余字符相对位置形成的新字符串。

关键约束 (Key Constraints)
-------------------------
- 1 <= text1.length, text2.length <= 1000
- text1 和 text2 仅由小写英文字符组成

示例 (Example)
-------------
输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace"，长度为 3

输入：text1 = "abc", text2 = "abc"
输出：3

输入：text1 = "abc", text2 = "def"
输出：0

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 经典的二维动态规划问题：比较两个序列的相似度

关键观察：
1. dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的最长公共子序列长度
2. 如果 text1[i-1] == text2[j-1]，则 dp[i][j] = dp[i-1][j-1] + 1
3. 否则 dp[i][j] = max(dp[i-1][j], dp[i][j-1])
4. 初始化：dp[0][j] = 0, dp[i][0] = 0

根据这些观察，可以得到两种典型解法：
1. 二维 DP（标准解法）
2. 一维 DP（空间优化）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - 2D DP)

核心思想
--------
使用二维 DP 数组记录两个字符串的最长公共子序列长度。

状态定义：
dp[i][j] = text1 前 i 个字符和 text2 前 j 个字符的最长公共子序列长度

状态转移方程：
if (text1[i-1] == text2[j-1]):
    dp[i][j] = dp[i-1][j-1] + 1
else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])

算法流程：
1. 创建 (m+1) x (n+1) 的 DP 数组，初始化为 0
2. 遍历 text1 的每个字符 i (1 到 m)
3. 遍历 text2 的每个字符 j (1 到 n)
4. 根据字符是否相等更新 dp[i][j]
5. 返回 dp[m][n]

复杂度分析
---------
时间复杂度：O(m * n)
空间复杂度：O(m * n)
*/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }
};

/*
方法二：空间优化解法 (Approach 2: Space Optimized Solution - 1D DP)

核心思想
--------
观察到 dp[i][j] 只依赖于 dp[i-1][j-1]、dp[i-1][j] 和 dp[i][j-1]，
可以使用一维数组 + 一个变量来优化空间。

算法流程：
1. 使用一维数组 dp，长度为 n+1
2. 使用变量 prev 保存 dp[i-1][j-1]
3. 从左到右更新 dp 数组

复杂度分析
---------
时间复杂度：O(m * n)
空间复杂度：O(min(m, n))
*/
class Solution_Optimized {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();

        // 优化：让较短的字符串作为列
        if (m < n) {
            swap(text1, text2);
            swap(m, n);
        }

        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            int prev = 0;  // 保存 dp[i-1][j-1]
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }

        return dp[n];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
text1 = "abcde", text2 = "ace"

DP 表格：
    ""  a  c  e
""   0  0  0  0
a    0  1  1  1
b    0  1  1  1
c    0  1  2  2
d    0  1  2  2
e    0  1  2  3

推演过程：
i=1, j=1: text1[0]='a' == text2[0]='a', dp[1][1] = dp[0][0] + 1 = 1
i=1, j=2: text1[0]='a' != text2[1]='c', dp[1][2] = max(dp[0][2], dp[1][1]) = 1
i=1, j=3: text1[0]='a' != text2[2]='e', dp[1][3] = max(dp[0][3], dp[1][2]) = 1
i=2, j=1: text1[1]='b' != text2[0]='a', dp[2][1] = max(dp[1][1], dp[2][0]) = 1
i=2, j=2: text1[1]='b' != text2[1]='c', dp[2][2] = max(dp[1][2], dp[2][1]) = 1
i=2, j=3: text1[1]='b' != text2[2]='e', dp[2][3] = max(dp[1][3], dp[2][2]) = 1
i=3, j=1: text1[2]='c' != text2[0]='a', dp[3][1] = max(dp[2][1], dp[3][0]) = 1
i=3, j=2: text1[2]='c' == text2[1]='c', dp[3][2] = dp[2][1] + 1 = 2
i=3, j=3: text1[2]='c' != text2[2]='e', dp[3][3] = max(dp[2][3], dp[3][2]) = 2
i=4, j=1: text1[3]='d' != text2[0]='a', dp[4][1] = max(dp[3][1], dp[4][0]) = 1
i=4, j=2: text1[3]='d' != text2[1]='c', dp[4][2] = max(dp[3][2], dp[4][1]) = 2
i=4, j=3: text1[3]='d' != text2[2]='e', dp[4][3] = max(dp[3][3], dp[4][2]) = 2
i=5, j=1: text1[4]='e' != text2[0]='a', dp[5][1] = max(dp[4][1], dp[5][0]) = 1
i=5, j=2: text1[4]='e' != text2[1]='c', dp[5][2] = max(dp[4][2], dp[5][1]) = 2
i=5, j=3: text1[4]='e' == text2[2]='e', dp[5][3] = dp[4][2] + 1 = 3

结果：3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)
- 优点：直观易懂，可以回溯路径
- 缺点：空间占用大

方法二：一维 DP
- 时间复杂度：O(m * n)
- 空间复杂度：O(min(m, n))
- 优点：空间优化
- 缺点：无法回溯路径
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 两个字符串完全相同：返回字符串长度
2. 两个字符串没有公共字符：返回 0
3. 一个字符串为空：返回 0
4. 一个字符串是另一个的子序列：返回较短字符串的长度
*/

/*
相关问题 (Related Problems)
--------------------------
1. LeetCode 72. 编辑距离 (Edit Distance)
2. LeetCode 583. 两个字符串的删除操作 (Delete Operation for Two Strings)
3. LeetCode 712. 两个字符串的最小ASCII删除和 (Minimum ASCII Delete Sum)
4. LeetCode 1035. 不相交的线 (Uncrossed Lines)
*/

int main() {
    Solution solution;

    // 测试用例 1
    string text1_1 = "abcde", text2_1 = "ace";
    cout << "测试用例 1 - 输出: " << solution.longestCommonSubsequence(text1_1, text2_1)
         << " (期望: 3)" << endl;

    // 测试用例 2：完全相同
    string text1_2 = "abc", text2_2 = "abc";
    cout << "测试用例 2 - 输出: " << solution.longestCommonSubsequence(text1_2, text2_2)
         << " (期望: 3)" << endl;

    // 测试用例 3：没有公共字符
    string text1_3 = "abc", text2_3 = "def";
    cout << "测试用例 3 - 输出: " << solution.longestCommonSubsequence(text1_3, text2_3)
         << " (期望: 0)" << endl;

    // 测试用例 4
    string text1_4 = "ezupkr", text2_4 = "ubmrapg";
    cout << "测试用例 4 - 输出: " << solution.longestCommonSubsequence(text1_4, text2_4)
         << " (期望: 2)" << endl;

    return 0;
}
