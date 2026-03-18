/*
LeetCode 55. 跳跃游戏 (Jump Game)

题目概述 (Problem Summary)
-------------------------
给定一个非负整数数组 nums，你最初位于数组的第一个下标。
数组中的每个元素 nums[i] 表示你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- 0 <= nums[i] <= 10^5

示例 (Example)
-------------
输入：nums = [2,3,1,1,4]
输出：true
解释：可以从下标 0 跳到下标 1，再到最后一个下标

输入：nums = [3,2,1,0,4]
输出：false
解释：无论如何都会卡在下标 3，无法继续前进

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断覆盖范围能否一直推进到终点

关键观察：
1. 走到位置 i 的前提是：i 必须在当前最远可达范围内
2. 一旦到达位置 i，就能把最远可达位置更新为 max(far, i + nums[i])
3. 如果某一刻 i > far，说明当前位置根本走不到，直接失败

这是一个非常典型的“区间覆盖”贪心问题。

根据这些观察，可以得到两种典型解法：
1. 贪心维护最远可达位置 ⭐
2. DP 判断每个位置是否可达
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：贪心维护最远可达位置 (Approach 1: Greedy Reachability)

核心思想
--------
用 far 表示当前已经能够到达的最远下标。
从左到右扫描数组，只要当前位置没有超过 far，就说明还能继续推进。

算法流程：
1. 初始化 far = 0
2. 依次扫描位置 i：
   - 如果 i > far，说明 i 不可达，直接返回 false
   - 否则更新 far = max(far, i + nums[i])
   - 如果 far 已经 >= n - 1，提前返回 true
3. 扫描结束后返回 true

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int far = 0;

        for (int i = 0; i < n; ++i) {
            if (i > far) {
                return false;
            }
            far = max(far, i + nums[i]);
            if (far >= n - 1) {
                return true;
            }
        }

        return true;
    }
};

/*
方法二：动态规划 (Approach 2: DP)

核心思想
--------
dp[i] 表示下标 i 是否可达。
如果 i 可达，那么它后面最多 nums[i] 个位置也都可以被更新。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n)

优点：
- 容易从“状态定义”出发想到

缺点：
- 远慢于贪心
*/
class Solution_DP {
public:
    bool canJump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<bool> dp(n, false);
        dp[0] = true;

        for (int i = 0; i < n; ++i) {
            if (!dp[i]) continue;
            for (int step = 1; step <= nums[i] && i + step < n; ++step) {
                dp[i + step] = true;
            }
        }

        return dp[n - 1];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [3,2,1,0,4]

初始：far = 0
i = 0：far = max(0, 0 + 3) = 3
i = 1：1 <= 3，可达，far = max(3, 1 + 2) = 3
i = 2：2 <= 3，可达，far = max(3, 2 + 1) = 3
i = 3：3 <= 3，可达，far = max(3, 3 + 0) = 3
i = 4：4 > 3，不可达，返回 false
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：贪心
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：最优解，代码短
- 缺点：需要理解“覆盖范围”这个贪心视角

方法二：DP
- 时间复杂度：O(n^2)
- 空间复杂度：O(n)
- 优点：状态定义直接
- 缺点：性能较差
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：天然可达
2. 中间存在 0：只有在它之前已经覆盖到后面位置时才不影响结果
*/

int main() {
    Solution solution;

    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << boolalpha;
    cout << "测试用例 1 - 输出: " << solution.canJump(nums1)
         << " (期望: true)" << endl;

    vector<int> nums2 = {3, 2, 1, 0, 4};
    cout << "测试用例 2 - 输出: " << solution.canJump(nums2)
         << " (期望: false)" << endl;

    return 0;
}
