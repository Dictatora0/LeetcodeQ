/*
LeetCode 49. 字母异位词分组 (Group Anagrams)

题目概述 (Problem Summary)
-------------------------
给定一个字符串数组，将字母异位词分组。
字母异位词指字符种类与次数完全相同，只是排列顺序不同。

关键约束 (Key Constraints)
-------------------------
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] 仅包含小写英文字母

示例 (Example)
-------------
输入：strs = ["eat","tea","tan","ate","nat","bat"]
输出：[["eat","tea","ate"],["tan","nat"],["bat"]]
解释：同组字符串互为字母异位词

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 需要一种“归类键”来识别互为异位词的字符串

关键观察：
1. 排序后的字符串是异位词的统一表示
2. 也可以用字符频次作为唯一特征
3. 使用哈希表：key -> 分组列表

根据这些观察，可以得到两种典型解法：
1. 排序字符串作为 key
2. 频次数组编码作为 key（更快）
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
对每个字符串排序，排序结果作为分组的 key。
同样的 key 说明互为异位词。

算法流程：
1. 遍历每个字符串 s
2. 复制并排序得到 key
3. 将原字符串放入 map[key]
4. 返回 map 中所有分组

复杂度分析
---------
时间复杂度：O(n * k log k)
空间复杂度：O(n * k)

其中：
n = 字符串数量
k = 平均字符串长度
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }

        vector<vector<string>> result;
        result.reserve(groups.size());
        for (auto& kv : groups) {
            result.push_back(kv.second);
        }
        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Frequency Key)

优化思路
--------
用长度为 26 的频次数组作为 key（编码为字符串）。
相比排序，频次统计是 O(k)。

为什么更快：
- 避免排序的 O(k log k)
- 频次构造稳定

复杂度分析
---------
时间复杂度：O(n * k)
空间复杂度：O(n * k)
*/
class Solution_Optimized {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            int count[26] = {0};
            for (char c : s) {
                count[c - 'a']++;
            }

            // 频次编码成字符串作为 key
            string key;
            key.reserve(26 * 2);
            for (int i = 0; i < 26; ++i) {
                key.push_back('#');
                key += to_string(count[i]);
            }

            groups[key].push_back(s);
        }

        vector<vector<string>> result;
        result.reserve(groups.size());
        for (auto& kv : groups) {
            result.push_back(kv.second);
        }
        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
strs = ["eat","tea","tan","ate","nat","bat"]

排序 key：
"eat" -> "aet"
"tea" -> "aet"
"tan" -> "ant"
"ate" -> "aet"
"nat" -> "ant"
"bat" -> "abt"

分组：
aet -> [eat, tea, ate]
ant -> [tan, nat]
abt -> [bat]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：排序 key
- 时间复杂度：O(n * k log k)
- 空间复杂度：O(n * k)
- 优点：实现简单
- 缺点：排序开销较大

方法二：频次数组 key
- 时间复杂度：O(n * k)
- 空间复杂度：O(n * k)
- 优点：更快
- 缺点：key 构造较繁琐
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：所有空字符串在同一组
2. 只有一个字符串：返回单组
3. 字符串长度不同：自然分到不同组
*/

static void printGroups(const vector<vector<string>>& groups) {
    cout << "[";
    for (size_t i = 0; i < groups.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < groups[i].size(); ++j) {
            cout << groups[i][j];
            if (j + 1 < groups[i].size()) cout << ", ";
        }
        cout << "]";
        if (i + 1 < groups.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result1 = solution.groupAnagrams(strs1);
    cout << "测试用例 1 - 输出: ";
    printGroups(result1);
    cout << " (期望包含分组: [eat,tea,ate], [tan,nat], [bat])" << endl;

    // 测试用例 2
    vector<string> strs2 = {""};
    vector<vector<string>> result2 = solution.groupAnagrams(strs2);
    cout << "测试用例 2 - 输出: ";
    printGroups(result2);
    cout << " (期望: [[]])" << endl;

    return 0;
}
