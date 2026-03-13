/*
LeetCode 3. 无重复字符的最长子串 (Longest Substring Without Repeating Characters)

题目概述 (Problem Summary)
-------------------------
给定一个字符串 s，找出不含重复字符的最长子串的长度。

关键约束 (Key Constraints)
-------------------------
- 0 <= s.length <= 5 * 10^4
- 字符可能包含字母、数字、符号和空格

示例 (Example)
-------------
输入：s = "abcabcbb"
输出：3
解释：最长不重复子串为 "abc"，长度为 3

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在字符串中找一个最长连续区间，保证区间内字符都不重复

关键观察：
1. 区间内不能有重复字符，符合滑动窗口的条件
2. 当右端加入新字符导致重复时，需要移动左端缩小窗口
3. 若能记录字符上一次出现的位置，可直接跳过无效区间

根据这些观察，可以得到两种典型解法：
1. 滑动窗口 + 哈希集合：逐步收缩直到无重复
2. 滑动窗口 + 上次位置数组：直接跳过重复字符
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用滑动窗口维护当前无重复的子串区间。
右指针向右扩展，若遇到重复字符，则左指针不断右移并移除字符，
直到窗口内没有重复字符。

算法流程：
1. 初始化左指针 left = 0，右指针 right 从 0 遍历
2. 若 s[right] 已在集合中，持续移动 left 并删除 s[left]
3. 将 s[right] 加入集合，更新最大长度

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(min(n, 字符集大小))
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window; // 记录当前窗口中的字符
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            // 如果当前字符重复，移动左指针缩小窗口
            while (window.count(s[right])) {
                window.erase(s[left]);
                ++left;
            }

            // 将当前字符加入窗口
            window.insert(s[right]);

            // 更新最大长度
            int curLen = right - left + 1;
            if (curLen > maxLen) maxLen = curLen;
        }

        return maxLen;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Last Index)

优化思路
--------
记录每个字符上一次出现的位置。
当发现重复字符时，左指针直接跳到重复字符的下一个位置，
避免逐步移动。

为什么更快：
- 左指针单调递增
- 每个字符只处理一次

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(字符集大小)
*/
class Solution_Optimized {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1); // 记录字符上次出现位置
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            unsigned char c = static_cast<unsigned char>(s[right]);
            if (last[c] >= left) {
                left = last[c] + 1; // 直接跳过重复字符
            }
            last[c] = right;
            int curLen = right - left + 1;
            if (curLen > maxLen) maxLen = curLen;
        }

        return maxLen;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
字符串：s = "abba"

初始：left=0, window=""
right=0 -> 'a'，窗口="a"，max=1
right=1 -> 'b'，窗口="ab"，max=2
right=2 -> 'b' 重复，left 跳到上次 'b' 的下一位
窗口="b"，max=2
right=3 -> 'a'，窗口="ba"，max=2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：集合滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(min(n, 字符集大小))
- 优点：实现直观
- 缺点：遇到重复时需要逐步缩小

方法二：记录上次位置
- 时间复杂度：O(n)
- 空间复杂度：O(字符集大小)
- 优点：左指针可直接跳跃
- 缺点：需要维护额外数组
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：结果为 0
2. 全部相同字符：结果为 1
3. 全部不重复：结果为字符串长度
4. 含空格与符号：同样适用
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    string s1 = "abcabcbb";
    cout << "测试用例 1 - 输出: " << solution.lengthOfLongestSubstring(s1)
         << " (期望: 3)" << endl;

    // 测试用例 2
    string s2 = "bbbbb";
    cout << "测试用例 2 - 输出: " << solution.lengthOfLongestSubstring(s2)
         << " (期望: 1)" << endl;

    // 测试用例 3
    string s3 = "pwwkew";
    cout << "测试用例 3 - 输出: " << solution.lengthOfLongestSubstring(s3)
         << " (期望: 3)" << endl;

    return 0;
}
