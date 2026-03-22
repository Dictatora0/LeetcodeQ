/*
LeetCode 90. Subsets II (子集 II)

题目概述 (Problem Summary)
-------------------------
给定一个可能包含重复元素的数组 nums，返回所有可能的子集（幂集），
且结果中不能出现重复子集。

示例
----
输入：nums = [1,2,2]
输出：[[],[1],[2],[1,2],[2,2],[1,2,2]]

关键词
------
- 回溯
- 排序 + 同层去重
- 子集问题（每个节点都是答案）

算法思路 (Algorithm Thinking)
----------------------------
和 LC 78（元素互不相同）相比，这题多了“重复元素去重”。

标准做法：
1. 先排序，让相同元素相邻
2. 回溯时每到一个节点先收集答案
3. 同层遇到重复值跳过：i > start && nums[i] == nums[i-1]

为什么子集题“每个节点都是答案”？
- 因为任意长度的 path 都是合法子集
- 不需要等到叶子节点才加入结果

常见变体
--------
1. LeetCode 78 子集：无重复元素，去掉去重逻辑
2. LeetCode 491 递增子序列：除了去重还要维护非降序约束
3. 组合类问题（LC 77/216）：需要固定长度或和约束

面试追问
--------
Q1: 去重条件为什么是 i > start 而不是 i > 0？
A1: 只去掉同层重复分支，跨层同值可能是合法子集的一部分。

Q2: 时间复杂度是多少？
A2: 最坏 O(n * 2^n)，去重会减少实际搜索分支。

Q3: 迭代法能做吗？
A3: 能。处理重复元素时要只扩展“上一轮新增区间”，实现更绕。
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> path;
        backtrack(nums, 0, path, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        result.push_back(path);  // 子集题：每个节点都是答案

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            if (i > start && nums[i] == nums[i - 1]) continue;  // 同层去重

            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, result);
            path.pop_back();
        }
    }
};

/*
示例推演
--------
nums = [1,2,2]（排序后不变）

start=0, path=[] -> 收集 []
- 选 1 -> path=[1]，收集 [1]
  - 选 2 -> path=[1,2]，收集 [1,2]
    - 选 2 -> path=[1,2,2]，收集 [1,2,2]
- 回到第一层，i=1 选 2 -> path=[2]，收集 [2]
  - 选下一个 2 -> path=[2,2]，收集 [2,2]
- 第一层 i=2 时与 i=1 同层重复，跳过

最终 6 个子集，且无重复。

易错点
------
1. 忘记排序，去重条件无法生效
2. 把去重写成 i>0，导致漏解
3. 只在叶子收集答案，会丢失短子集

复杂度
------
时间：O(n * 2^n)
空间：O(n)（递归深度，不含答案）
*/

static vector<vector<int>> normalize(vector<vector<int>> v) {
    for (auto& subset : v) {
        sort(subset.begin(), subset.end());
    }
    sort(v.begin(), v.end());
    return v;
}

int main() {
    Solution sol;

    {
        vector<int> nums = {1, 2, 2};
        vector<vector<int>> expected = {
            {}, {1}, {2}, {1, 2}, {2, 2}, {1, 2, 2}
        };
        assert(normalize(sol.subsetsWithDup(nums)) == normalize(expected));
    }

    {
        vector<int> nums = {0};
        vector<vector<int>> expected = {
            {}, {0}
        };
        assert(normalize(sol.subsetsWithDup(nums)) == normalize(expected));
    }

    {
        vector<int> nums = {1, 2, 2, 2};
        // 不同子集数量 = (1 的取法 2 种) * (2 的取法 4 种) = 8
        assert(sol.subsetsWithDup(nums).size() == 8);
    }

    cout << "LeetCode 90 tests passed.\n";
    return 0;
}
