/*
LeetCode 72. 编辑距离 (Edit Distance)

题目概述 (Problem Summary)
-------------------------
给定两个字符串 word1 和 word2，计算将 word1 转换成 word2 所使用的最少操作数。
你可以对一个字符串进行如下三种操作：
1. 插入一个字符
2. 删除一个字符
3. 替换一个字符

关键约束 (Key Constraints)
-------------------------
- 0 <= word1.length, word2.length <= 500
- word1 和 word2 由小写英文字母组成

示例 (Example)
-------------
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 计算两个字符串之间的最小编辑距离（Levenshtein Distance）

关键观察：
1. 这是一个经典的二维动态规划问题
2. dp[i][j] 表示 word1 的前 i 个字符转换成 word2 的前 j 个字符所需的最少操作数
3. 如果 word1[i-1] == word2[j-1]，不需要操作，dp[i][j] = dp[i-1][j-1]
4. 否则，需要考虑三种操作：
   - 插入：dp[i][j-1] + 1
   - 删除：dp[i-1][j] + 1
   - 替换：dp[i-1][j-1] + 1

根据这些观察，可以得到两种典型解法：
1. 二维动态规划
2. 空间优化的一维动态规划
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/*
方法一：二维动态规划 (Approach 1: 2D Dynamic Programming)

核心思想
--------
使用二维 dp 数组记录子问题的解。

状态定义：
dp[i][j] = word1 的前 i 个字符转换成 word2 的前 j 个字符所需的最少操作数

状态转移方程：
如果 word1[i-1] == word2[j-1]:
    dp[i][j] = dp[i-1][j-1]
否则:
    dp[i][j] = min({
        dp[i][j-1] + 1,      // 插入操作
        dp[i-1][j] + 1,      // 删除操作
        dp[i-1][j-1] + 1     // 替换操作
    })

初始状态：
dp[0][j] = j  // word1 为空，需要插入 j 个字符
dp[i][0] = i  // word2 为空，需要删除 i 个字符

算法流程：
1. 创建 (m+1) × (n+1) 的 dp 数组
2. 初始化第一行和第一列
3. 双重循环填充 dp 数组
4. 返回 dp[m][n]

复杂度分析
---------
时间复杂度：O(m × n) - m 和 n 分别是两个字符串的长度
空间复杂度：O(m × n) - dp 数组
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 初始化边界条件
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        // 填充 dp 数组
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({
                        dp[i][j - 1] + 1,      // 插入
                        dp[i - 1][j] + 1,      // 删除
                        dp[i - 1][j - 1] + 1   // 替换
                    });
                }
            }
        }

        return dp[m][n];
    }
};

/*
方法二：空间优化的动态规划 (Approach 2: Space-Optimized DP)

优化思路
--------
观察状态转移方程，dp[i][j] 只依赖于：
- dp[i-1][j-1]（左上）
- dp[i-1][j]（上）
- dp[i][j-1]（左）

因此可以用一维数组滚动更新，只需保存上一行的信息。

复杂度分析
---------
时间复杂度：O(m × n)
空间复杂度：O(n) - 只用一维数组
*/
class Solution_Optimized {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<int> dp(n + 1);

        // 初始化第一行
        for (int j = 0; j <= n; j++) {
            dp[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            int prev = dp[0];  // 保存 dp[i-1][j-1]
            dp[0] = i;         // 更新第一列

            for (int j = 1; j <= n; j++) {
                int temp = dp[j];  // 保存当前值（即 dp[i-1][j]）

                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prev;
                } else {
                    dp[j] = min({
                        dp[j - 1] + 1,  // 插入（左）
                        dp[j] + 1,      // 删除（上）
                        prev + 1        // 替换（左上）
                    });
                }

                prev = temp;  // 更新 prev 为下一轮的左上值
            }
        }

        return dp[n];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
word1 = "horse", word2 = "ros"

构建 dp 数组：
    ""  r  o  s
""   0  1  2  3
h    1
o    2
r    3
s    4
e    5

填充过程：

dp[1][1]: h vs r, 不相等
  min(dp[0][1]+1=2, dp[1][0]+1=2, dp[0][0]+1=1) = 1

dp[1][2]: h vs o, 不相等
  min(dp[1][1]+1=2, dp[0][2]+1=3, dp[0][1]+1=2) = 2

dp[1][3]: h vs s, 不相等
  min(dp[1][2]+1=3, dp[0][3]+1=4, dp[0][2]+1=3) = 3

dp[2][1]: ho vs r, o != r
  min(dp[1][1]+1=2, dp[2][0]+1=3, dp[1][0]+1=2) = 2

dp[2][2]: ho vs ro, o == o
  dp[2][2] = dp[1][1] = 1

dp[2][3]: ho vs ros, o != s
  min(dp[2][2]+1=2, dp[1][3]+1=4, dp[1][2]+1=3) = 2

继续填充...

最终 dp 数组：
    ""  r  o  s
""   0  1  2  3
h    1  1  2  3
o    2  2  1  2
r    3  2  2  2
s    4  3  3  2
e    5  4  4  3

答案：dp[5][3] = 3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维动态规划
- 时间复杂度：O(m × n)
- 空间复杂度：O(m × n)
- 优点：直观易理解，可以回溯具体操作序列
- 缺点：空间占用较大

方法二：空间优化
- 时间复杂度：O(m × n)
- 空间复杂度：O(n)
- 优点：空间最优
- 缺点：不容易回溯操作序列
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 其中一个字符串为空：返回另一个字符串的长度
2. 两个字符串相同：返回 0
3. 两个字符串完全不同：最坏情况需要 max(m, n) 次操作
*/

int main() {
    Solution solution;
    Solution_Optimized solution_opt;

    // 测试用例 1
    string word1_1 = "horse", word2_1 = "ros";
    cout << "测试用例 1 - 方法一输出: " << solution.minDistance(word1_1, word2_1)
         << " (期望: 3)" << endl;
    cout << "测试用例 1 - 方法二输出: " << solution_opt.minDistance(word1_1, word2_1)
         << " (期望: 3)" << endl;

    // 测试用例 2
    string word1_2 = "intention", word2_2 = "execution";
    cout << "测试用例 2 - 方法一输出: " << solution.minDistance(word1_2, word2_2)
         << " (期望: 5)" << endl;
    cout << "测试用例 2 - 方法二输出: " << solution_opt.minDistance(word1_2, word2_2)
         << " (期望: 5)" << endl;

    // 测试用例 3
    string word1_3 = "", word2_3 = "abc";
    cout << "测试用例 3 - 方法一输出: " << solution.minDistance(word1_3, word2_3)
         << " (期望: 3)" << endl;
    cout << "测试用例 3 - 方法二输出: " << solution_opt.minDistance(word1_3, word2_3)
         << " (期望: 3)" << endl;

    return 0;
}
