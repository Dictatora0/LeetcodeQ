/*
LeetCode 134. 加油站 (Gas Station)

题目概述 (Problem Summary)
-------------------------
在一条环形路线有 n 个加油站，第 i 个加油站有 gas[i] 的汽油，
从 i 到 i+1 需要消耗 cost[i] 的汽油。
如果可以绕行一圈，返回起始加油站索引，否则返回 -1。

关键约束 (Key Constraints)
-------------------------
- 1 <= gas.length <= 10^5
- gas.length == cost.length
- gas[i], cost[i] >= 0

示例 (Example)
-------------
输入：gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出：3
解释：从 3 号站出发可以完成一圈

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到一个起点，使累计油量始终非负

关键观察：
1. 若总油量 < 总消耗，则无解
2. 如果从起点 i 出发在某个 j 处油量为负，
   则 i 到 j 之间的任何站都不可能作为起点
3. 因此可以贪心地在失败位置后重新选择起点

根据这些观察，可以得到两种典型解法：
1. 一次遍历贪心
2. 暴力尝试（对比）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
统计总油量与总消耗判断是否有解，
同时用贪心策略寻找可行起点。

算法流程：
1. totalGas += gas[i], totalCost += cost[i]
2. cur += gas[i] - cost[i]
3. 若 cur < 0，说明当前起点无法到达 i+1，
   起点更新为 i+1，cur 重置为 0
4. 若 totalGas < totalCost 返回 -1，否则返回起点

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = static_cast<int>(gas.size());
        int totalGas = 0, totalCost = 0;
        int cur = 0;
        int start = 0;

        for (int i = 0; i < n; ++i) {
            totalGas += gas[i];
            totalCost += cost[i];
            cur += gas[i] - cost[i];

            if (cur < 0) {
                start = i + 1;
                cur = 0;
            }
        }

        return totalGas < totalCost ? -1 : start;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Brute Force)

优化思路
--------
从每个站点尝试出发，模拟是否能绕一圈。
该方法用于对比学习，复杂度较高。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = static_cast<int>(gas.size());
        for (int start = 0; start < n; ++start) {
            int tank = 0;
            bool ok = true;
            for (int step = 0; step < n; ++step) {
                int i = (start + step) % n;
                tank += gas[i] - cost[i];
                if (tank < 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) return start;
        }
        return -1;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
gas = [1,2,3,4,5]
cost= [3,4,5,1,2]

累计差值：
1-3=-2 -> 起点失败，start=1
2-4=-2 -> 起点失败，start=2
3-5=-2 -> 起点失败，start=3
从 3 开始：
4-1=3, 5-2=6, 1-3=4, 2-4=2, 3-5=0 -> 可行
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：贪心一次遍历
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：最优解法
- 缺点：思路需要证明

方法二：暴力模拟
- 时间复杂度：O(n^2)
- 空间复杂度：O(1)
- 优点：直观
- 缺点：效率低
*/

/*
特殊情况 (Edge Cases)
--------------------
1. totalGas < totalCost：无解
2. 只有一个站点：判断 gas[0] >= cost[0]
3. 多个可行起点：题目保证唯一可行解
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> gas1 = {1,2,3,4,5};
    vector<int> cost1 = {3,4,5,1,2};
    cout << "测试用例 1 - 输出: " << solution.canCompleteCircuit(gas1, cost1)
         << " (期望: 3)" << endl;

    // 测试用例 2
    vector<int> gas2 = {2,3,4};
    vector<int> cost2 = {3,4,3};
    cout << "测试用例 2 - 输出: " << solution.canCompleteCircuit(gas2, cost2)
         << " (期望: -1)" << endl;

    return 0;
}
