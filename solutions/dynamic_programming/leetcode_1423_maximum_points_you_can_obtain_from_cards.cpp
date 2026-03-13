/*
LeetCode 1423. 可获得的最大点数 (Maximum Points You Can Obtain from Cards)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 cardPoints 和一个整数 k，每次可以从数组的最左端或最右端取一张卡，
共取 k 张卡，求能够获得的最大点数。

关键约束 (Key Constraints)
-------------------------
- 1 <= cardPoints.length <= 10^5
- 1 <= cardPoints[i] <= 10^4
- 1 <= k <= cardPoints.length

示例 (Example)
-------------
输入：cardPoints = [1,2,3,4,5,6,1], k = 3
输出：12
解释：取 1 (左) + 6 (右) + 5 (右) = 12

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 从两端取 k 张，等价于丢弃中间连续的 n-k 张，使得剩余和最大

关键观察：
1. 总和固定，最大得分 = 总和 - 最小的连续子数组和（长度 n-k）
2. 只需找到长度为 n-k 的最小子数组和即可
3. 滑动窗口可线性完成

根据这些观察，可以得到两种典型解法：
1. 滑动窗口求最小连续和
2. 前缀和枚举左右取的组合
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
计算数组总和，找到长度为 n-k 的最小连续子数组和，
最大得分 = 总和 - 最小子数组和。

算法流程：
1. 计算 total
2. 计算长度为 window = n-k 的窗口和
3. 滑动窗口找到最小值 minWindow
4. 返回 total - minWindow

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = static_cast<int>(cardPoints.size());
        int window = n - k;
        int total = 0;
        for (int x : cardPoints) total += x;
        if (window == 0) return total;

        int cur = 0;
        for (int i = 0; i < window; ++i) cur += cardPoints[i];
        int minWindow = cur;

        for (int i = window; i < n; ++i) {
            cur += cardPoints[i];
            cur -= cardPoints[i - window];
            minWindow = min(minWindow, cur);
        }

        return total - minWindow;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Prefix Sum)

优化思路
--------
前缀和预处理后，枚举左侧取 i 张，右侧取 k-i 张，
计算最大和。

复杂度分析
---------
时间复杂度：O(k)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = static_cast<int>(cardPoints.size());
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + cardPoints[i];
        }

        int best = 0;
        for (int left = 0; left <= k; ++left) {
            int right = k - left;
            int leftSum = prefix[left];
            int rightSum = prefix[n] - prefix[n - right];
            best = max(best, leftSum + rightSum);
        }

        return best;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
cardPoints = [1,2,3,4,5,6,1], k = 3
总和 = 22
n-k = 4，找长度为 4 的最小子数组和
最小窗口和为 10（例如 [2,3,4,1]）
最大得分 = 22 - 10 = 12
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：最优空间
- 缺点：需要理解“丢弃中间段”的等价转换

方法二：前缀和枚举
- 时间复杂度：O(k)
- 空间复杂度：O(n)
- 优点：直观枚举左右取法
- 缺点：空间略多
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = n：全部取走
2. k = 1：取两端最大值
3. n-k = 0：窗口长度为 0，直接返回总和
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> cardPoints1 = {1,2,3,4,5,6,1};
    int k1 = 3;
    cout << "测试用例 1 - 输出: " << solution.maxScore(cardPoints1, k1)
         << " (期望: 12)" << endl;

    // 测试用例 2
    vector<int> cardPoints2 = {2,2,2};
    int k2 = 2;
    cout << "测试用例 2 - 输出: " << solution.maxScore(cardPoints2, k2)
         << " (期望: 4)" << endl;

    return 0;
}
