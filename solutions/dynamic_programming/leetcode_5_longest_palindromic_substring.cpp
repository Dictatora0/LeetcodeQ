/*
LeetCode 5. 最长回文子串 (Longest Palindromic Substring)

题目概述 (Problem Summary)
-------------------------
给定一个字符串 s，找到 s 中最长的回文子串。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length <= 1000
- s 仅由数字和英文字母组成

示例 (Example)
-------------
输入：s = "babad"
输出："bab"
解释："aba" 也是一个有效答案

输入：s = "cbbd"
输出："bb"

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找出字符串中最长的回文子串

关键观察：
1. 回文串的特点：正读和反读都一样
2. dp[i][j] 表示 s[i...j] 是否为回文串
3. 如果 s[i] == s[j] 且 s[i+1...j-1] 是回文串，则 s[i...j] 也是回文串
4. 单个字符和两个相同字符都是回文串

根据这些观察，可以得到三种典型解法：
1. 动态规划
2. 中心扩展
3. Manacher 算法（最优）
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
方法一：动态规划 (Approach 1: Dynamic Programming)

核心思想
--------
使用二维 dp 数组记录所有子串是否为回文串。

状态定义：
dp[i][j] = s[i...j] 是否为回文串

状态转移方程：
如果 s[i] == s[j]:
  - 如果 j - i <= 1：dp[i][j] = true（单字符或两个相同字符）
  - 否则：dp[i][j] = dp[i+1][j-1]
否则:
  dp[i][j] = false

初始状态：
dp[i][i] = true（单个字符是回文串）

算法流程：
1. 创建 n×n 的 dp 数组
2. 按子串长度从小到大遍历
3. 对于每个子串，根据状态转移方程更新 dp
4. 记录最长回文子串的起始位置和长度

复杂度分析
---------
时间复杂度：O(n²)
空间复杂度：O(n²)
*/
class Solution_DP {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0;
        int maxLen = 1;

        // 单个字符都是回文串
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        // 按子串长度遍历
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;

                if (s[i] == s[j]) {
                    if (len == 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }

                    if (dp[i][j] && len > maxLen) {
                        start = i;
                        maxLen = len;
                    }
                }
            }
        }

        return s.substr(start, maxLen);
    }
};

/*
方法二：中心扩展 (Approach 2: Expand Around Center)

核心思想
--------
遍历每个可能的回文中心，向两边扩展。

关键点：
- 回文中心可以是单个字符（奇数长度）
- 回文中心可以是两个字符之间（偶数长度）

算法流程：
1. 遍历每个位置作为中心
2. 对于每个中心，尝试奇数长度和偶数长度的扩展
3. 记录最长的回文子串

复杂度分析
---------
时间复杂度：O(n²) - 每个中心最多扩展 n 次
空间复杂度：O(1)
*/
class Solution_Expand {
public:
    int expand(string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            int len1 = expand(s, i, i);       // 奇数长度
            int len2 = expand(s, i, i + 1);   // 偶数长度
            int len = max(len1, len2);

            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }
};

/*
方法三：Manacher 算法 (Approach 3: Manacher's Algorithm)

优化思路
--------
Manacher 算法是专门用于解决最长回文子串问题的线性时间算法。

核心思想：
1. 预处理字符串，在每个字符之间插入特殊字符（如 #），统一奇偶长度
2. 使用数组 p[i] 记录以 i 为中心的回文半径
3. 利用已知的回文信息，避免重复计算

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Manacher {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";

        // 预处理字符串
        string t = "#";
        for (char c : s) {
            t += c;
            t += '#';
        }

        int n = t.size();
        vector<int> p(n, 0);  // p[i] 表示以 i 为中心的回文半径
        int center = 0;       // 当前回文中心
        int right = 0;        // 当前回文右边界

        int maxLen = 0;
        int maxCenter = 0;

        for (int i = 0; i < n; i++) {
            // 利用对称性
            if (i < right) {
                int mirror = 2 * center - i;
                p[i] = min(right - i, p[mirror]);
            }

            // 尝试扩展
            int left = i - (p[i] + 1);
            int r = i + (p[i] + 1);
            while (left >= 0 && r < n && t[left] == t[r]) {
                p[i]++;
                left--;
                r++;
            }

            // 更新中心和右边界
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }

            // 更新最长回文
            if (p[i] > maxLen) {
                maxLen = p[i];
                maxCenter = i;
            }
        }

        // 从预处理字符串中提取原始回文子串
        int start = (maxCenter - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "babad"

方法一：动态规划
初始化：dp[i][i] = true

len=2:
  i=0, j=1: s[0]='b', s[1]='a', 不相等
  i=1, j=2: s[1]='a', s[2]='b', 不相等
  i=2, j=3: s[2]='b', s[3]='a', 不相等
  i=3, j=4: s[3]='a', s[4]='d', 不相等

len=3:
  i=0, j=2: s[0]='b', s[2]='b', 相等，dp[0][2]=dp[1][1]=true ✓
    maxLen=3, start=0
  i=1, j=3: s[1]='a', s[3]='a', 相等，dp[1][3]=dp[2][2]=true ✓
    maxLen=3, start=1
  i=2, j=4: s[2]='b', s[4]='d', 不相等

len=4:
  i=0, j=3: s[0]='b', s[3]='a', 不相等
  i=1, j=4: s[1]='a', s[4]='d', 不相等

len=5:
  i=0, j=4: s[0]='b', s[4]='d', 不相等

答案："bab" 或 "aba"（取决于先找到哪个）

方法二：中心扩展
i=0, s[0]='b':
  奇数：expand(0,0) -> "b", len=1
  偶数：expand(0,1) -> s[0]!=s[1], len=0
  maxLen=1

i=1, s[1]='a':
  奇数：expand(1,1) -> "bab", len=3
  偶数：expand(1,2) -> s[1]!=s[2], len=0
  maxLen=3, start=0

i=2, s[2]='b':
  奇数：expand(2,2) -> "aba", len=3
  偶数：expand(2,3) -> s[2]!=s[3], len=0
  maxLen=3（不更新）

答案："bab"
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：动态规划
- 时间复杂度：O(n²)
- 空间复杂度：O(n²)
- 优点：思路清晰，可以记录所有回文子串
- 缺点：空间占用大

方法二：中心扩展
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：空间最优，实现简单
- 缺点：时间复杂度不是最优

方法三：Manacher 算法
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：时间复杂度最优
- 缺点：实现较复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单个字符：返回该字符
2. 所有字符相同：返回整个字符串
3. 没有回文子串（长度>1）：返回任意单个字符
4. 整个字符串是回文：返回整个字符串
*/

int main() {
    Solution_DP solution_dp;
    Solution_Expand solution_expand;
    Solution_Manacher solution_manacher;

    // 测试用例 1
    string s1 = "babad";
    cout << "测试用例 1 - DP输出: " << solution_dp.longestPalindrome(s1)
         << " (期望: bab 或 aba)" << endl;
    cout << "测试用例 1 - Expand输出: " << solution_expand.longestPalindrome(s1)
         << " (期望: bab 或 aba)" << endl;
    cout << "测试用例 1 - Manacher输出: " << solution_manacher.longestPalindrome(s1)
         << " (期望: bab 或 aba)" << endl;

    // 测试用例 2
    string s2 = "cbbd";
    cout << "测试用例 2 - DP输出: " << solution_dp.longestPalindrome(s2)
         << " (期望: bb)" << endl;
    cout << "测试用例 2 - Expand输出: " << solution_expand.longestPalindrome(s2)
         << " (期望: bb)" << endl;
    cout << "测试用例 2 - Manacher输出: " << solution_manacher.longestPalindrome(s2)
         << " (期望: bb)" << endl;

    // 测试用例 3
    string s3 = "a";
    cout << "测试用例 3 - DP输出: " << solution_dp.longestPalindrome(s3)
         << " (期望: a)" << endl;
    cout << "测试用例 3 - Expand输出: " << solution_expand.longestPalindrome(s3)
         << " (期望: a)" << endl;
    cout << "测试用例 3 - Manacher输出: " << solution_manacher.longestPalindrome(s3)
         << " (期望: a)" << endl;

    // 测试用例 4
    string s4 = "aaaa";
    cout << "测试用例 4 - DP输出: " << solution_dp.longestPalindrome(s4)
         << " (期望: aaaa)" << endl;
    cout << "测试用例 4 - Expand输出: " << solution_expand.longestPalindrome(s4)
         << " (期望: aaaa)" << endl;
    cout << "测试用例 4 - Manacher输出: " << solution_manacher.longestPalindrome(s4)
         << " (期望: aaaa)" << endl;

    return 0;
}

