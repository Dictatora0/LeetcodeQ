/*
LeetCode 76. 最小覆盖子串 (Minimum Window Substring)

题目概述 (Problem Summary)
-------------------------
给定字符串 s 和字符串 t，找出 s 中包含 t 所有字符的最小子串。
如果不存在，返回空字符串。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length, t.length <= 10^5
- s 和 t 由英文字母组成（大小写敏感）

示例 (Example)
-------------
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释："BANC" 包含 A、B、C 且长度最短

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在 s 中找到一个最短区间，使其包含 t 的全部字符及其次数

关键观察：
1. 区间内需满足“覆盖 t 的全部字符”这一约束，适合滑动窗口
2. 右指针扩大窗口，左指针收缩窗口以得到最短解
3. 需要统计字符出现次数，并判断当前窗口是否已“覆盖”

根据这些观察，可以得到两种典型解法：
1. 滑动窗口 + 哈希表统计频次
2. 滑动窗口 + 数组统计频次（更快）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用滑动窗口与哈希表记录当前窗口内字符出现次数，
当窗口覆盖了 t 中所有字符后，尝试收缩左边界获得最短窗口。

算法流程：
1. 统计 t 中每个字符需要的次数（need）
2. 右指针扩展窗口，统计窗口内字符次数（window）
3. 当窗口满足覆盖条件时，移动左指针缩小窗口
4. 记录最短长度与起始位置

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(k)

其中：
n = s 的长度
k = t 中不同字符数量
*/
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.size() < t.size()) return "";

        unordered_map<char, int> need;
        unordered_map<char, int> window;
        for (char c : t) {
            need[c]++;
        }

        int required = static_cast<int>(need.size()); // 需要满足的字符种类数
        int formed = 0;                               // 已满足的字符种类数
        int left = 0;
        int bestLen = INT_MAX;
        int bestL = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            char c = s[right];
            window[c]++;

            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }

            // 当窗口满足覆盖条件时，尝试收缩
            while (left <= right && formed == required) {
                int curLen = right - left + 1;
                if (curLen < bestLen) {
                    bestLen = curLen;
                    bestL = left;
                }

                char d = s[left];
                window[d]--;
                if (need.count(d) && window[d] < need[d]) {
                    formed--;
                }
                left++;
            }
        }

        return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Array Count)

优化思路
--------
用固定大小数组替代哈希表进行计数（适合字符集固定的情况），
降低常数开销，提高性能。

为什么更快：
- 数组访问是 O(1)，常数更低
- 避免哈希开销

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(字符集大小)
*/
class Solution_Optimized {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.size() < t.size()) return "";

        vector<int> need(256, 0);
        vector<int> window(256, 0);
        int required = 0;
        for (char c : t) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (need[uc] == 0) required++;
            need[uc]++;
        }

        int formed = 0;
        int left = 0;
        int bestLen = INT_MAX;
        int bestL = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            unsigned char c = static_cast<unsigned char>(s[right]);
            window[c]++;
            if (need[c] > 0 && window[c] == need[c]) {
                formed++;
            }

            while (left <= right && formed == required) {
                int curLen = right - left + 1;
                if (curLen < bestLen) {
                    bestLen = curLen;
                    bestL = left;
                }

                unsigned char d = static_cast<unsigned char>(s[left]);
                window[d]--;
                if (need[d] > 0 && window[d] < need[d]) {
                    formed--;
                }
                left++;
            }
        }

        return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "ADOBECODEBANC", t = "ABC"

窗口扩展过程（右指针）：
ADOBEC -> 已覆盖 A,B,C
开始收缩左边界，直到不覆盖为止
最终最小窗口为 "BANC"
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：哈希表滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(k)
- 优点：通用，字符集不固定也可用
- 缺点：哈希常数较大

方法二：数组计数滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(字符集大小)
- 优点：更快
- 缺点：依赖字符集大小
*/

/*
特殊情况 (Edge Cases)
--------------------
1. s 为空或 t 为空
2. s 长度小于 t
3. t 中包含重复字符
4. s 中不存在完整覆盖
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";
    cout << "测试用例 1 - 输出: " << solution.minWindow(s1, t1)
         << " (期望: BANC)" << endl;

    // 测试用例 2
    string s2 = "a";
    string t2 = "a";
    cout << "测试用例 2 - 输出: " << solution.minWindow(s2, t2)
         << " (期望: a)" << endl;

    // 测试用例 3
    string s3 = "a";
    string t3 = "aa";
    cout << "测试用例 3 - 输出: " << solution.minWindow(s3, t3)
         << " (期望: )" << endl;

    return 0;
}
