/*
LeetCode 509. 斐波那契数 (Fibonacci Number)

题目概述 (Problem Summary)
-------------------------
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

给定 n，计算 F(n)。

斐波那契数列定义：
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1

关键约束 (Key Constraints)
-------------------------
- 0 <= n <= 30

示例 (Example)
-------------
输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1

输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2

输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 计算斐波那契数列的第 n 项

关键观察：
1. 这是动态规划的经典入门题
2. 状态定义：dp[i] 表示第 i 个斐波那契数
3. 状态转移：dp[i] = dp[i-1] + dp[i-2]
4. 初始状态：dp[0] = 0, dp[1] = 1
5. 可以优化空间，只保存前两个数

根据这些观察，可以得到几种典型解法：
1. 递归（暴力）- 时间复杂度 O(2^n)，会超时
2. 递归 + 记忆化 - 时间复杂度 O(n)
3. 动态规划（数组）- 时间 O(n)，空间 O(n)
4. 动态规划（空间优化）- 时间 O(n)，空间 O(1)
5. 矩阵快速幂 - 时间 O(log n)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：递归（暴力）(Approach 1: Naive Recursion)

核心思想
--------
直接按照定义递归计算。

算法流程：
1. 如果 n <= 1，返回 n
2. 否则返回 fib(n-1) + fib(n-2)

问题：
- 存在大量重复计算
- 例如计算 fib(5) 时，fib(3) 会被计算多次

复杂度分析
---------
时间复杂度：O(2^n)
- 递归树的节点数呈指数增长

空间复杂度：O(n)
- 递归调用栈的深度

这种方法会超时，不推荐使用。
*/
class Solution_Recursive {
public:
    int fib(int n) {
        // 递归终止条件
        if (n <= 1) return n;

        // 递归计算
        return fib(n - 1) + fib(n - 2);
    }
};

/*
方法二：递归 + 记忆化 (Approach 2: Recursion with Memoization)

核心思想
--------
使用数组记录已经计算过的结果，避免重复计算。

算法流程：
1. 创建记忆数组 memo，初始化为 -1
2. 如果 memo[n] 已经计算过，直接返回
3. 否则递归计算并存储结果

复杂度分析
---------
时间复杂度：O(n)
- 每个数只计算一次

空间复杂度：O(n)
- 记忆数组 + 递归栈
*/
class Solution_Memo {
public:
    int fib(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }

private:
    int helper(int n, vector<int>& memo) {
        // 递归终止条件
        if (n <= 1) return n;

        // 如果已经计算过，直接返回
        if (memo[n] != -1) return memo[n];

        // 递归计算并存储结果
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
        return memo[n];
    }
};

/*
方法三：动态规划（数组）(Approach 3: Dynamic Programming with Array)

核心思想
--------
使用数组自底向上计算斐波那契数。

算法流程：
1. 创建 dp 数组，dp[i] 表示第 i 个斐波那契数
2. 初始化：dp[0] = 0, dp[1] = 1
3. 从 i = 2 开始，依次计算 dp[i] = dp[i-1] + dp[i-2]
4. 返回 dp[n]

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(n)
- dp 数组
*/
class Solution_DP {
public:
    int fib(int n) {
        // 边界情况
        if (n <= 1) return n;

        // 创建 dp 数组
        vector<int> dp(n + 1);

        // 初始化
        dp[0] = 0;
        dp[1] = 1;

        // 状态转移
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

/*
方法四：动态规划（空间优化）(Approach 4: DP with Space Optimization)

核心思想
--------
观察到计算 dp[i] 只需要 dp[i-1] 和 dp[i-2]，不需要保存整个数组。
使用两个变量滚动更新即可。

算法流程：
1. 初始化 prev = 0, curr = 1
2. 从 i = 2 开始，计算 next = prev + curr
3. 更新：prev = curr, curr = next
4. 返回 curr

这是最优解法！

复杂度分析
---------
时间复杂度：O(n)
- 遍历 n 次

空间复杂度：O(1)
- 只使用常数个变量
*/
class Solution {
public:
    int fib(int n) {
        // 边界情况
        if (n <= 1) return n;

        // 初始化前两个斐波那契数
        int prev = 0;  // F(0)
        int curr = 1;  // F(1)

        // 从 F(2) 开始计算
        for (int i = 2; i <= n; i++) {
            int next = prev + curr;  // F(i) = F(i-1) + F(i-2)
            prev = curr;             // 更新 F(i-2)
            curr = next;             // 更新 F(i-1)
        }

        return curr;
    }
};

/*
方法五：矩阵快速幂 (Approach 5: Matrix Exponentiation)

核心思想
--------
利用矩阵乘法的性质，将斐波那契数列转化为矩阵幂运算。

[F(n+1)]   [1 1]^n   [1]
[F(n)  ] = [1 0]   * [0]

使用快速幂可以在 O(log n) 时间内计算。

复杂度分析
---------
时间复杂度：O(log n)
- 快速幂的时间复杂度

空间复杂度：O(1)
- 只使用常数个矩阵

这是最快的方法，但对于 n <= 30 的情况，方法四已经足够。
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
计算 F(5)

方法四（空间优化 DP）的执行过程：
1. 初始化：prev = 0, curr = 1
2. i = 2: next = 0 + 1 = 1, prev = 1, curr = 1
3. i = 3: next = 1 + 1 = 2, prev = 1, curr = 2
4. i = 4: next = 1 + 2 = 3, prev = 2, curr = 3
5. i = 5: next = 2 + 3 = 5, prev = 3, curr = 5
6. 返回 curr = 5

斐波那契数列：0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归（暴力）
- 时间复杂度：O(2^n)
- 空间复杂度：O(n)
- 优点：代码简单
- 缺点：效率极低，会超时

方法二：递归 + 记忆化
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：避免重复计算
- 缺点：需要额外空间

方法三：动态规划（数组）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：自底向上，逻辑清晰
- 缺点：空间未优化

方法四：动态规划（空间优化）⭐ 推荐
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：时间和空间都很优秀
- 缺点：无

方法五：矩阵快速幂
- 时间复杂度：O(log n)
- 空间复杂度：O(1)
- 优点：最快
- 缺点：实现复杂，对于小规模问题不必要

推荐使用方法四，代码简洁且效率高。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. n = 0：返回 0
2. n = 1：返回 1
3. n = 2：返回 1
4. n 很大：使用空间优化的 DP 或矩阵快速幂
*/

int main() {
    Solution solution;

    // 测试用例
    vector<int> testCases = {0, 1, 2, 3, 4, 5, 10, 20, 30};

    cout << "斐波那契数列测试：" << endl;
    for (int n : testCases) {
        cout << "F(" << n << ") = " << solution.fib(n) << endl;
    }

    // 验证前几项
    cout << "\n前 10 项斐波那契数列：" << endl;
    for (int i = 0; i < 10; i++) {
        cout << solution.fib(i) << " ";
    }
    cout << endl;
    cout << "期望：0 1 1 2 3 5 8 13 21 34" << endl;

    return 0;
}
