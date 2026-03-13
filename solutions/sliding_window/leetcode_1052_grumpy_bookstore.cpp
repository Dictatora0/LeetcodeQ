/*
LeetCode 1052. 爱生气的书店老板 (Grumpy Bookstore Owner)

题目概述 (Problem Summary)
-------------------------
书店老板在某些时段会生气，生气时顾客不满意。
给定 customers[i]（第 i 分钟的顾客数）和 grumpy[i]（是否生气），
老板有一次持续 X 分钟的“冷静技巧”，在这段时间里不生气。
求最多能让多少顾客满意。

关键约束 (Key Constraints)
-------------------------
- 1 <= customers.length <= 2 * 10^4
- 0 <= customers[i] <= 1000
- grumpy[i] 为 0 或 1
- 1 <= X <= customers.length

示例 (Example)
-------------
输入：customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
输出：16
解释：
基础满意：grumpy=0 的分钟顾客数之和 = 1 + 1 + 1 + 7 = 10
选择冷静窗口 [2,3,4]（0-based），可额外挽回 2 + 1 + 1 = 4
最终 10 + 6 = 16（最佳窗口在 [5,6,7]，额外 6）

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 选一个长度为 X 的窗口，使“生气时损失的顾客数”最大化被挽回

关键观察：
1. 基础满意度 = 所有 grumpy=0 的 customers 之和
2. 冷静技巧窗口只影响 grumpy=1 的分钟
3. 需要找长度为 X 的窗口，使窗口内 grumpy=1 的 customers 之和最大

根据这些观察，可以得到两种典型解法：
1. 滑动窗口求最大增益
2. 前缀和求窗口增益（等价）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
先计算基础满意度，再用滑动窗口计算可额外挽回的最大顾客数。

算法流程：
1. 计算基础满意度（grumpy=0 的 customers 之和）
2. 计算首个窗口内“生气损失”人数
3. 右移窗口，维护窗口内损失人数的最大值
4. 返回基础满意度 + 最大增益

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int n = static_cast<int>(customers.size());
        int base = 0;

        for (int i = 0; i < n; ++i) {
            if (grumpy[i] == 0) {
                base += customers[i]; // 本来就满意
            }
        }

        int extra = 0;
        for (int i = 0; i < X; ++i) {
            if (grumpy[i] == 1) {
                extra += customers[i];
            }
        }

        int maxExtra = extra;
        for (int right = X; right < n; ++right) {
            int left = right - X;
            if (grumpy[right] == 1) extra += customers[right];
            if (grumpy[left] == 1) extra -= customers[left];
            maxExtra = max(maxExtra, extra);
        }

        return base + maxExtra;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Prefix Sum)

优化思路
--------
构造一个 loss 数组，只保留 grumpy=1 时的 customers，
然后用前缀和快速计算任意长度为 X 的窗口损失人数。

为什么可行：
- loss 数组的窗口和等于可挽回人数

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int n = static_cast<int>(customers.size());
        vector<int> loss(n, 0);
        int base = 0;

        for (int i = 0; i < n; ++i) {
            if (grumpy[i] == 0) {
                base += customers[i];
            } else {
                loss[i] = customers[i];
            }
        }

        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + loss[i];
        }

        int maxExtra = 0;
        for (int i = 0; i + X <= n; ++i) {
            int extra = prefix[i + X] - prefix[i];
            maxExtra = max(maxExtra, extra);
        }

        return base + maxExtra;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
customers = [1,0,1,2,1,1,7,5]
grumpy    = [0,1,0,1,0,1,0,1]
X = 3

基础满意度 = 1 + 1 + 1 + 7 = 10
窗口 [5,6,7] 内 loss = 1 + 0 + 5 = 6
最大增益 = 6
最终满意度 = 10 + 6 = 16
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：最省空间
- 缺点：需要手动维护窗口

方法二：前缀和
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：窗口求和直观
- 缺点：额外数组
*/

/*
特殊情况 (Edge Cases)
--------------------
1. X = 1：选择单分钟最大损失
2. X = n：直接全部冷静
3. 全部 grumpy=0：结果为总顾客数
4. 全部 grumpy=1：结果为最大窗口和
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> customers1 = {1, 0, 1, 2, 1, 1, 7, 5};
    vector<int> grumpy1 = {0, 1, 0, 1, 0, 1, 0, 1};
    int X1 = 3;
    cout << "测试用例 1 - 输出: " << solution.maxSatisfied(customers1, grumpy1, X1)
         << " (期望: 16)" << endl;

    // 测试用例 2
    vector<int> customers2 = {2, 6, 6, 9};
    vector<int> grumpy2 = {1, 0, 1, 1};
    int X2 = 1;
    cout << "测试用例 2 - 输出: " << solution.maxSatisfied(customers2, grumpy2, X2)
         << " (期望: 17)" << endl;

    return 0;
}
