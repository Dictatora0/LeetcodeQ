/*
LeetCode 15. 三数之和 (3Sum)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums，找出所有和为 0 且不重复的三元组。
三元组中元素下标必须不同，结果不能包含重复组合。

关键约束 (Key Constraints)
-------------------------
- 3 <= nums.length <= 3000
- -10^5 <= nums[i] <= 10^5
- 需要去重

示例 (Example)
-------------
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：唯一满足条件的三元组为 (-1,-1,2) 与 (-1,0,1)

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在数组中找所有不重复的三元组，使其和为 0

关键观察：
1. 固定一个数后，问题转化为“两数之和为目标”的问题
2. 排序后可以用双指针线性解决两数之和并去重
3. 去重需要跳过相同的元素

根据这些观察，可以得到两种典型解法：
1. 排序 + 双指针（最常用）
2. 排序 + 哈希集合（对比方法）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
先排序，然后枚举第一个数 i，使用双指针在区间 (i+1..n-1) 内找和为 -nums[i] 的两数。
通过跳过相同元素实现去重。

算法流程：
1. 排序数组
2. 遍历 i，若 nums[i] == nums[i-1] 则跳过以避免重复
3. 双指针 l/r 寻找两数和为 -nums[i]
4. 找到后记录并跳过重复的 l 和 r

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(1)（不计输出）
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 去重
            int target = -nums[i];
            int l = i + 1, r = n - 1;

            while (l < r) {
                int sum = nums[l] + nums[r];
                if (sum == target) {
                    result.push_back({nums[i], nums[l], nums[r]});
                    int leftVal = nums[l];
                    int rightVal = nums[r];
                    while (l < r && nums[l] == leftVal) l++;
                    while (l < r && nums[r] == rightVal) r--;
                } else if (sum < target) {
                    l++;
                } else {
                    r--;
                }
            }
        }

        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Hash Set per i)

优化思路
--------
排序后固定 i，使用哈希集合记录遍历过的数，
当发现 target - nums[j] 在集合中时，得到一个三元组。
仍需去重处理。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            unordered_set<int> seen;
            for (int j = i + 1; j < n; ++j) {
                int need = -nums[i] - nums[j];
                if (seen.count(need)) {
                    result.push_back({nums[i], need, nums[j]});
                    // 跳过重复 j
                    while (j + 1 < n && nums[j] == nums[j + 1]) j++;
                }
                seen.insert(nums[j]);
            }
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [-1,0,1,2,-1,-4]
排序后：[-4,-1,-1,0,1,2]

i=-4 -> target=4，找不到
i=-1 -> target=1，双指针找到 (-1,-1,2) 与 (-1,0,1)
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：排序 + 双指针
- 时间复杂度：O(n^2)
- 空间复杂度：O(1)
- 优点：最常用，空间最优
- 缺点：需要排序并处理去重

方法二：哈希集合
- 时间复杂度：O(n^2)
- 空间复杂度：O(n)
- 优点：思路直接
- 缺点：额外空间与去重复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全为正数或全为负数：无解
2. 多个重复元素：需要严格去重
3. 数组长度小于 3：无解
*/

static void printTriples(const vector<vector<int>>& triples) {
    cout << "[";
    for (size_t i = 0; i < triples.size(); ++i) {
        cout << "[" << triples[i][0] << ", " << triples[i][1] << ", " << triples[i][2] << "]";
        if (i + 1 < triples.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> res1 = solution.threeSum(nums1);
    cout << "测试用例 1 - 输出: ";
    printTriples(res1);
    cout << " (期望包含: [-1,-1,2], [-1,0,1])" << endl;

    // 测试用例 2
    vector<int> nums2 = {0,0,0,0};
    vector<vector<int>> res2 = solution.threeSum(nums2);
    cout << "测试用例 2 - 输出: ";
    printTriples(res2);
    cout << " (期望: [[0, 0, 0]])" << endl;

    return 0;
}
