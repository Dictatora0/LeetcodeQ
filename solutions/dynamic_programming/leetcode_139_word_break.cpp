/*
LeetCode 139. 单词拆分 (Word Break)

题目概述 (Problem Summary)
-------------------------
给定一个字符串 s 和一个字符串字典 wordDict，判断 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
注意：字典中的单词可以重复使用。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length <= 300
- 1 <= wordDict.length <= 1000
- 1 <= wordDict[i].length <= 20
- s 和 wordDict[i] 仅由小写英文字母组成
- wordDict 中的所有字符串互不相同

示例 (Example)
-------------
输入：s = "leetcode", wordDict = ["leet","code"]
输出：true
解释：返回 true 因为 "leetcode" 可以被拆分成 "leet code"

输入：s = "applepenapple", wordDict = ["apple","pen"]
输出：true
解释：返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"
注意你可以重复使用字典中的单词

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断字符串是否可以由字典中的单词组合而成

关键观察：
1. dp[i] 表示字符串 s 的前 i 个字符能否被拆分
2. 对于位置 i，需要检查所有 j < i 的位置
3. 如果 dp[j] 为 true 且 s[j...i-1] 在字典中，则 dp[i] = true
4. 使用哈希集合存储字典，提高查找效率

根据这些观察，可以得到两种典型解法：
1. 动态规划
2. 动态规划 + 优化（从后向前遍历）
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/*
方法一：动态规划 (Approach 1: Dynamic Programming)

核心思想
--------
使用 dp[i] 表示字符串 s 的前 i 个字符能否被拆分。

状态定义：
dp[i] = 字符串 s[0...i-1] 能否被字典中的单词拼接而成

状态转移方程：
dp[i] = true，如果存在 j (0 <= j < i) 使得：
  - dp[j] == true
  - s[j...i-1] 在字典中

初始状态：
dp[0] = true（空字符串可以被拆分）

算法流程：
1. 将 wordDict 转换为哈希集合，O(1) 查找
2. 创建 dp 数组，dp[0] = true
3. 双重循环：外层遍历 i (1 到 n)，内层遍历 j (0 到 i-1)
4. 如果 dp[j] 为 true 且 s[j...i-1] 在字典中，设置 dp[i] = true
5. 返回 dp[n]

复杂度分析
---------
时间复杂度：O(n² × m) - n 是字符串长度，m 是平均单词长度（substr 操作）
空间复杂度：O(n + k) - n 是 dp 数组，k 是字典大小
*/
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        // dp[i] 表示前 i 个字符组成的子串 s[0...i-1] 是否可以被字典中的单词拼出来
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;  // 找到一种拆分方式即可
                }
            }
        }

        return dp[n];
    }
};

/*
方法二：优化的动态规划 (Approach 2: Optimized DP)

优化思路
--------
1. 记录字典中最长单词的长度，限制内层循环范围
2. 从后向前遍历 j，减少不必要的检查

复杂度分析
---------
时间复杂度：O(n × maxLen × m) - maxLen 是字典中最长单词长度
空间复杂度：O(n + k)
*/
class Solution_Optimized {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        // 找到字典中最长单词的长度
        int maxLen = 0;
        for (const string& word : wordDict) {
            maxLen = max(maxLen, (int)word.size());
        }

        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            // 只需要检查最近 maxLen 个位置
            for (int j = max(0, i - maxLen); j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "leetcode", wordDict = ["leet", "code"]

初始化：
dict = {"leet", "code"}
dp = [true, false, false, false, false, false, false, false, false]
索引:  0     1      2      3      4      5      6      7      8

i=1, s[0...0]="l":
  j=0: dp[0]=true, "l" 不在字典中
  dp[1]=false

i=2, s[0...1]="le":
  j=0: dp[0]=true, "le" 不在字典中
  j=1: dp[1]=false
  dp[2]=false

i=3, s[0...2]="lee":
  j=0: dp[0]=true, "lee" 不在字典中
  j=1: dp[1]=false
  j=2: dp[2]=false
  dp[3]=false

i=4, s[0...3]="leet":
  j=0: dp[0]=true, "leet" 在字典中 ✓
  dp[4]=true

i=5, s[0...4]="leetc":
  j=0: dp[0]=true, "leetc" 不在字典中
  j=1: dp[1]=false
  j=2: dp[2]=false
  j=3: dp[3]=false
  j=4: dp[4]=true, "c" 不在字典中
  dp[5]=false

i=6, s[0...5]="leetco":
  j=4: dp[4]=true, "co" 不在字典中
  dp[6]=false

i=7, s[0...6]="leetcod":
  j=4: dp[4]=true, "cod" 不在字典中
  dp[7]=false

i=8, s[0...7]="leetcode":
  j=4: dp[4]=true, "code" 在字典中 ✓
  dp[8]=true

最终 dp = [true, false, false, false, true, false, false, false, true]
答案：dp[8] = true
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：基础动态规划
- 时间复杂度：O(n² × m)
- 空间复杂度：O(n + k)
- 优点：实现简单直观
- 缺点：可能检查很多不必要的位置

方法二：优化的动态规划
- 时间复杂度：O(n × maxLen × m)
- 空间复杂度：O(n + k)
- 优点：减少不必要的检查
- 缺点：需要预处理最长单词长度
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：返回 true（dp[0] = true）
2. 字典为空：只有空字符串返回 true
3. 字符串无法拆分：返回 false
4. 单词可以重复使用：正常处理
*/

int main() {
    Solution solution;
    Solution_Optimized solution_opt;

    // 测试用例 1
    string s1 = "leetcode";
    vector<string> wordDict1 = {"leet", "code"};
    cout << "测试用例 1 - 方法一输出: " << (solution.wordBreak(s1, wordDict1) ? "true" : "false")
         << " (期望: true)" << endl;
    cout << "测试用例 1 - 方法二输出: " << (solution_opt.wordBreak(s1, wordDict1) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 2
    string s2 = "applepenapple";
    vector<string> wordDict2 = {"apple", "pen"};
    cout << "测试用例 2 - 方法一输出: " << (solution.wordBreak(s2, wordDict2) ? "true" : "false")
         << " (期望: true)" << endl;
    cout << "测试用例 2 - 方法二输出: " << (solution_opt.wordBreak(s2, wordDict2) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 3
    string s3 = "catsandog";
    vector<string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << "测试用例 3 - 方法一输出: " << (solution.wordBreak(s3, wordDict3) ? "true" : "false")
         << " (期望: false)" << endl;
    cout << "测试用例 3 - 方法二输出: " << (solution_opt.wordBreak(s3, wordDict3) ? "true" : "false")
         << " (期望: false)" << endl;

    return 0;
}
