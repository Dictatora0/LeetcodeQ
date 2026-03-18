/*
LeetCode 45. 跳跃游戏 II (Jump Game II)

题目概述 (Problem Summary)
-------------------------
给定一个长度为 n 的非负整数数组 nums。你初始位于下标 0。
数组中的每个元素 nums[i] 表示你从位置 i 最多可以跳跃的长度。

你的目标是使用最少的跳跃次数到达最后一个下标。
题目保证一定可以到达最后一个下标。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- 0 <= nums[i] <= 1000
- 题目保证可以到达最后一个下标

示例 (Example)
-------------
输入：nums = [2,3,1,1,4]
输出：2
解释：跳到下标 1，再跳到最后一个下标

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在所有可行跳法中，找到到达终点的最少步数
- 每次跳跃其实是在选择“下一步能扩展到的最远区间”

关键观察：
1. 如果站在一个区间 [L, R] 内，当前这一步都只算作跳 1 次
2. 在扫描这个区间时，可以同时算出下一步最远能到哪里
3. 一旦走到当前区间的末尾，就必须做出一次跳跃决策

这和按层遍历 BFS 很像：
- 当前区间是这一层
- nextEnd 是下一层最远边界

根据这些观察，可以得到两种典型解法：
1. 贪心分层扫描 ⭐
2. 朴素 DP（会更慢）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：贪心分层扫描 (Approach 1: Greedy Layer Scan)

核心思想
--------
把“一次跳跃内能到达的所有位置”看成一个区间。
在扫描这个区间的过程中，持续更新下一次跳跃最远能到的位置。

变量含义：
- curEnd：当前这一步所能覆盖到的最远边界
- nextEnd：从当前区间内任一点继续跳一步，所能到达的最远边界
- steps：已经使用的跳跃次数

算法流程：
1. 从左到右扫描，但不用扫描最后一个位置
2. 每到一个位置 i，都更新 nextEnd = max(nextEnd, i + nums[i])
3. 如果 i 走到了 curEnd，说明当前这一步覆盖的区间扫完了：
   - 必须跳一次，steps++
   - 更新 curEnd = nextEnd
4. 扫描结束后，steps 就是最少跳跃次数

为什么是最优的？
- 在同一步内，扫描完所有能到达的位置后再决定下一步边界
- 这样每一步都尽量把下一层扩得最远
- 本质是对 BFS 分层的贪心实现

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 1) return 0;

        int steps = 0;
        int curEnd = 0;
        int nextEnd = 0;

        for (int i = 0; i < n - 1; ++i) {
            nextEnd = max(nextEnd, i + nums[i]);
            if (i == curEnd) {
                ++steps;
                curEnd = nextEnd;
            }
        }

        return steps;
    }
};

/*
方法二：动态规划 (Approach 2: DP)

核心思想
--------
dp[i] 表示到达位置 i 的最少步数。
从每个位置 i 出发，尝试更新它后面能跳到的位置。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n)

优点：
- 思路直接

缺点：
- 题目规模较大时明显慢于贪心
*/
class Solution_DP {
public:
    int jump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const int INF = 1e9;
        vector<int> dp(n, INF);
        dp[0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int step = 1; step <= nums[i] && i + step < n; ++step) {
                dp[i + step] = min(dp[i + step], dp[i] + 1);
            }
        }

        return dp[n - 1];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [2,3,1,1,4]

开始：
steps = 0, curEnd = 0, nextEnd = 0

i = 0:
nextEnd = max(0, 0 + 2) = 2
i == curEnd，当前层扫描完
steps = 1, curEnd = 2

i = 1:
nextEnd = max(2, 1 + 3) = 4

i = 2:
nextEnd = max(4, 2 + 1) = 4
i == curEnd，当前层扫描完
steps = 2, curEnd = 4

已经可以覆盖终点，答案是 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：贪心分层扫描
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：最优解法，面试首选
- 缺点：第一次接触时不如 DP 直观

方法二：动态规划
- 时间复杂度：O(n^2)
- 空间复杂度：O(n)
- 优点：好理解
- 缺点：效率较低
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：已经在终点，答案为 0
2. nums[i] 为 0 也没问题，因为题目保证整体可达
*/

int main() {
    Solution solution;

    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "测试用例 1 - 输出: " << solution.jump(nums1)
         << " (期望: 2)" << endl;

    vector<int> nums2 = {2, 3, 0, 1, 4};
    cout << "测试用例 2 - 输出: " << solution.jump(nums2)
         << " (期望: 2)" << endl;

    return 0;
}
