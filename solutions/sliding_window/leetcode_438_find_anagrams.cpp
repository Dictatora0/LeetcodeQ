/*
LeetCode 438. 找到字符串中所有字母异位词 (Find All Anagrams in a String)

题目概述 (Problem Summary)
-------------------------
给定字符串 s 和字符串 p，找出 s 中所有 p 的字母异位词的起始索引。
字母异位词要求字符种类和次数都相同。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length, p.length <= 3 * 10^4
- s 和 p 只包含小写英文字母

示例 (Example)
-------------
输入：s = "cbaebabacd", p = "abc"
输出：[0, 6]
解释：
从索引 0 的子串 "cba" 与 "abc" 互为异位词
从索引 6 的子串 "bac" 与 "abc" 互为异位词

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在 s 中找所有长度为 p.length 的窗口，使其字符频次与 p 相同

关键观察：
1. 由于 p 的长度固定，窗口大小固定为 m
2. 只需比较窗口频次与 p 的频次是否一致
3. 频次差异可用计数数组维护

根据这些观察，可以得到两种典型解法：
1. 滑动窗口 + 计数数组对比
2. 滑动窗口 + 差异计数（更高效）
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用两个大小为 26 的计数数组：
一个记录 p 的频次，一个记录当前窗口的频次。
当窗口大小达到 p.length 时，比较两个数组是否相同。

算法流程：
1. 统计 p 的频次
2. 滑动窗口遍历 s，维护窗口频次
3. 当窗口大小为 m 时，比较频次数组，若相同则记录索引

复杂度分析
---------
时间复杂度：O(n * 26) ≈ O(n)
空间复杂度：O(26)
*/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(p.size());
        if (n < m) return result;

        vector<int> need(26, 0);
        vector<int> window(26, 0);
        for (char c : p) {
            need[c - 'a']++;
        }

        for (int i = 0; i < n; ++i) {
            window[s[i] - 'a']++;

            if (i >= m) {
                window[s[i - m] - 'a']--;
            }

            if (i >= m - 1) {
                if (window == need) {
                    result.push_back(i - m + 1);
                }
            }
        }

        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Diff Count)

优化思路
--------
用一个差分数组 diff 表示窗口频次与 p 的频次差值，
再维护一个 mismatch 计数，表示有多少字符的差值不为 0。
当 mismatch == 0 时说明窗口与 p 的频次完全一致。

为什么更快：
- 每次滑动只更新两个字符的差值
- O(1) 判断是否匹配

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(26)
*/
class Solution_Optimized {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(p.size());
        if (n < m) return result;

        vector<int> diff(26, 0);
        int mismatch = 0;

        // 初始化 diff 为窗口(前 m 个字符) - p
        for (int i = 0; i < m; ++i) {
            diff[s[i] - 'a']++;
            diff[p[i] - 'a']--;
        }

        for (int i = 0; i < 26; ++i) {
            if (diff[i] != 0) mismatch++;
        }

        if (mismatch == 0) result.push_back(0);

        for (int i = m; i < n; ++i) {
            int in = s[i] - 'a';
            int out = s[i - m] - 'a';

            // 移入字符
            if (diff[in] == 0) mismatch++;
            diff[in]++;
            if (diff[in] == 0) mismatch--;

            // 移出字符
            if (diff[out] == 0) mismatch++;
            diff[out]--;
            if (diff[out] == 0) mismatch--;

            if (mismatch == 0) {
                result.push_back(i - m + 1);
            }
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "cbaebabacd", p = "abc", m = 3

窗口 "cba" -> 频次匹配 -> 记录索引 0
窗口 "bae" -> 不匹配
...
窗口 "bac" -> 匹配 -> 记录索引 6
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：窗口频次数组比较
- 时间复杂度：O(n)
- 空间复杂度：O(26)
- 优点：实现简单
- 缺点：每次需要比较整个数组

方法二：差分 + mismatch
- 时间复杂度：O(n)
- 空间复杂度：O(26)
- 优点：O(1) 判断匹配
- 缺点：实现稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. s 比 p 短：返回空
2. 完全相同：结果为 [0]
3. 没有任何匹配：返回空
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    string s1 = "cbaebabacd";
    string p1 = "abc";
    vector<int> result1 = solution.findAnagrams(s1, p1);
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << " (期望: [0, 6])" << endl;

    // 测试用例 2
    string s2 = "abab";
    string p2 = "ab";
    vector<int> result2 = solution.findAnagrams(s2, p2);
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << " (期望: [0, 1, 2])" << endl;

    return 0;
}
