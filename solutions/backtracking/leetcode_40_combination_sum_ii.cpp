/*
LeetCode 40. Combination Sum II (组合总和 II)

题目概述 (Problem Summary)
-------------------------
给定一个可能含重复元素的数组 candidates 和目标值 target，
找出所有和为 target 的不重复组合。

和 LeetCode 39 的关键区别：
1. candidates 可能有重复值
2. 每个元素最多使用一次

示例 (Example)
-------------
输入：candidates = [10,1,2,7,6,1,5], target = 8
输出：[[1,1,6],[1,2,5],[1,7],[2,6]]

关键词
------
- 回溯
- 排序 + 同层去重
- 组合问题（每个元素最多用一次）

算法思路 (Algorithm Thinking)
----------------------------
这题本质是“带去重约束的组合枚举”。

第一步必须排序，排序后有两个收益：
1. 同值元素相邻，能做“同层去重”
2. 可做剪枝：nums[i] > remain 时直接 break

回溯状态定义：
- remain：剩余需要凑出的和
- start：本层从哪个下标开始选（保证每个元素最多用一次）
- path：当前已选组合

核心剪枝和去重：
1. 同层去重：if (i > start && nums[i] == nums[i - 1]) continue;
2. 提前终止：if (nums[i] > remain) break;
3. 下一层从 i+1 开始（不能重复选同一下标）

为什么“同层去重”而不是“全局去重”？
- 同层去重是为避免“同一层选同值导致重复分支”
- 跨层仍允许选到同值（比如 [1,1,6] 的两个 1 是合法的）

常见变体
--------
1. LeetCode 39 组合总和：元素可重复使用（递归传 i）
2. LeetCode 216 组合总和 III：固定选 k 个数 + 值域约束
3. LeetCode 377 组合总和 IV：问方案数，转 DP

面试追问
--------
Q1: 为什么排序是必要步骤？
A1: 不排序就无法稳定地做同层去重，也无法高效剪枝。

Q2: 去重条件为什么是 i > start？
A2: 只跳过同一层重复选择；如果写成 i > 0 会误伤跨层合法分支。

Q3: 时间复杂度是多少？
A3: 最坏上界接近 O(2^n * n)，实际会被排序剪枝显著削减。

Q4: 如果要求返回方案数量而不是组合列表？
A4: 可以在回溯中计数；若允许重复且顺序相关，通常改用 DP 更好。
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> path;
        backtrack(candidates, target, 0, path, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, int remain, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        if (remain == 0) {
            result.push_back(path);
            return;
        }

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            if (i > start && nums[i] == nums[i - 1]) continue;  // 同层去重
            if (nums[i] > remain) break;  // 排序后可剪枝

            path.push_back(nums[i]);
            backtrack(nums, remain - nums[i], i + 1, path, result);  // 每个位置最多使用一次
            path.pop_back();
        }
    }
};

/*
示例推演 (Walkthrough)
----------------------
输入：candidates = [10,1,2,7,6,1,5], target = 8
排序后：nums = [1,1,2,5,6,7,10]

第一层（start=0）：
- 选 nums[0]=1，进入下一层
- nums[1]=1 与 nums[0] 同层重复，跳过（避免重复分支）
- 选 2、5、6、7 ... 分别探索

从 [1] 出发继续：
- 选第二个 1（跨层允许）得到 [1,1]
- 再选 6 得到 [1,1,6] 命中
- 选 2 后选 5 得到 [1,2,5] 命中
- 选 7 得到 [1,7] 命中

从 [2] 出发：
- 选 6 得到 [2,6] 命中

最终答案：
[1,1,6], [1,2,5], [1,7], [2,6]

易错点
------
1. 把同层去重写成 i>0，会误删合法方案
2. 递归传 i 而不是 i+1，会错误重复使用元素
3. 忘记排序，去重与剪枝都失效

复杂度分析
---------
时间复杂度：最坏 O(2^n * n)
空间复杂度：O(n)（递归栈 + path，不含答案存储）
*/

static vector<vector<int>> normalize(vector<vector<int>> v) {
    for (auto& comb : v) {
        sort(comb.begin(), comb.end());
    }
    sort(v.begin(), v.end());
    return v;
}

int main() {
    Solution sol;

    {
        vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
        int target = 8;
        vector<vector<int>> expected = {
            {1, 1, 6},
            {1, 2, 5},
            {1, 7},
            {2, 6}
        };
        assert(normalize(sol.combinationSum2(candidates, target)) == normalize(expected));
    }

    {
        vector<int> candidates = {2, 5, 2, 1, 2};
        int target = 5;
        vector<vector<int>> expected = {
            {1, 2, 2},
            {5}
        };
        assert(normalize(sol.combinationSum2(candidates, target)) == normalize(expected));
    }

    {
        vector<int> candidates = {1, 1, 1, 1};
        int target = 2;
        vector<vector<int>> expected = {
            {1, 1}
        };
        assert(normalize(sol.combinationSum2(candidates, target)) == normalize(expected));
    }

    cout << "LeetCode 40 tests passed.\n";
    return 0;
}
