/*
LeetCode 763. 划分字母区间 (Partition Labels)

题目概述 (Problem Summary)
-------------------------
给你一个字符串 s。我们要把这个字符串划分为尽可能多的片段，
并保证同一个字母最多只会出现在其中的一个片段中。

返回一个表示每个字符串片段长度的列表。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length <= 500
- s 仅由小写英文字母组成

示例 (Example)
-------------
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
- "ababcbaca"
- "defegde"
- "hijhklij"

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对字符串做区间划分
- 每个字符所在区间必须覆盖它的所有出现位置

关键观察：
1. 如果知道每个字符最后一次出现的位置，就能知道当前片段至少要延伸到哪里
2. 从左到右扫描时，当前片段的右边界应该始终等于：
   当前片段内所有字符的“最后出现位置”的最大值
3. 一旦扫描下标 i 到达当前右边界 end，就可以切出一段

这本质上是一个“动态维护区间右端点”的贪心题。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：记录最后出现位置 + 贪心分段
(Approach 1: Last Occurrence + Greedy Segment Expansion)

核心思想
--------
先预处理每个字符最后一次出现的位置。
然后扫描字符串，动态维护当前片段的右边界 end。

算法流程：
1. 预处理 lastIndex[c] = 字符 c 最后一次出现的位置
2. 从左到右扫描字符串：
   - end = max(end, lastIndex[s[i]])
3. 如果 i == end，说明当前片段里的字符都已经完整覆盖：
   - 记录这一段长度 end - start + 1
   - start = i + 1，开始下一段

为什么这样做是对的？
- 当前片段内只要出现过某个字符，就必须把它最后一次出现的位置也纳入当前片段
- 所以 end 一定要取这些字符最后位置的最大值
- 当 i 到达 end 时，说明当前片段已经闭合，可以安全切分

复杂度分析
---------
时间复杂度：O(n)
- 预处理一次 + 扫描一次

空间复杂度：O(1)
- 只需要长度为 26 的数组
*/
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int lastIndex[26] = {};
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<int> result;
        int start = 0;
        int end = 0;

        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            end = max(end, lastIndex[s[i] - 'a']);
            if (i == end) {
                result.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "ababcbacadefegdehijhklij"

先记录每个字符最后出现位置。

从左到右扫描：
- 起点 start = 0
- 看到 a，end 扩到 8
- 继续扫描到下标 8，期间 end 一直不会超过 8
- i == 8，切出长度 9

第二段：
- start = 9
- 看到 d，end 扩到 14
- 继续扫描到 15 时，end 被 e 扩到 15
- i == 15，切出长度 7

第三段剩余长度为 8

答案：[9,7,8]
*/

/*
复杂度总结 (Complexity Summary)
-------------------------------
- 时间复杂度：O(n)
- 空间复杂度：O(1)

为什么空间是 O(1)？
- 字符集固定为 26 个小写字母
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 所有字符都相同：只能切成 1 段
2. 所有字符都不同：每个字符单独成段
3. 字符重复分散出现：右边界会被不断推远
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << nums[i];
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    vector<int> result1 = solution.partitionLabels("ababcbacadefegdehijhklij");
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << "期望: [9, 7, 8]" << endl;

    vector<int> result2 = solution.partitionLabels("eccbbbbdec");
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << "期望: [10]" << endl;

    return 0;
}
