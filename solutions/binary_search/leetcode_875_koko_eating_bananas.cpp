/*
LeetCode 875. Koko Eating Bananas (爱吃香蕉的珂珂)

题目概述 (Problem Summary)
-------------------------
给定若干香蕉堆 piles，以及总小时数 h。
Koko 每小时选择一堆吃 k 根（不足 k 就吃完该堆）。
要求在 h 小时内吃完所有香蕉，求最小整数速度 k。

关键词
------
- 二分答案
- 单调性
- 可行性判断 check(k)

算法思路 (Algorithm Thinking)
----------------------------
这题不是“在数组上二分位置”，而是“在答案空间上二分速度”。

定义 check(k)：速度为 k 时，是否能在 h 小时内吃完。
- 若 check(k) 为真，说明 k 可行，更大的速度也可行
- 若 check(k) 为假，说明 k 不可行，更小的速度也不可行

可行性具有单调性，因此可二分最小可行值。

边界设定：
- 下界 left = 1（最慢每小时吃 1 根）
- 上界 right = max(piles)（每小时至少可清空一堆）

check 计算方式：
- 每堆耗时 = ceil(pile / k)
- 总耗时 = Σ ceil(pile / k)
- 判断总耗时 <= h

常见变体
--------
1. LeetCode 1011 在 D 天内送达包裹：最小运载能力
2. LeetCode 410 分割数组的最大值：最小化最大子段和
3. LeetCode 1283 使结果不超过阈值的最小除数

面试追问
--------
Q1: 为什么可以二分答案？
A1: check(k) 关于 k 单调，存在“不可行区 + 可行区”的分界点。

Q2: 为什么右边界可以取 max(piles)？
A2: 速度达到最大堆大小时，每堆最多 1 小时，一定是可行上界。

Q3: ceil(pile / k) 如何避免浮点？
A3: 使用整数式 `(pile + k - 1) / k`。

Q4: 为什么用 long long 统计小时？
A4: piles 规模大时总和可能超过 int，避免溢出。
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canFinish(piles, h, mid)) {
                right = mid;      // mid 可行，继续找更小可行速度
            } else {
                left = mid + 1;   // mid 不可行，排除左半区
            }
        }

        return left;
    }

private:
    bool canFinish(const vector<int>& piles, int h, int speed) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + speed - 1) / speed;  // ceil(pile / speed)
            if (hours > h) return false;
        }
        return true;
    }
};

/*
示例推演
--------
piles = [3,6,7,11], h = 8

left=1, right=11
- mid=6, hours=1+1+2+2=6 <= 8，可行，right=6
- mid=3, hours=1+2+3+4=10 > 8，不可行，left=4
- mid=5, hours=1+2+2+3=8 <= 8，可行，right=5
- mid=4, hours=1+2+2+3=8 <= 8，可行，right=4
left==right==4，答案 4

易错点
------
1. 把 right 设成 sum(piles) 虽可行但边界过大
2. check 中使用浮点 ceil，容易引入精度和性能问题
3. left/right 更新写错导致死循环

复杂度
------
时间：O(n log M)，n 为堆数，M 为最大堆大小
空间：O(1)
*/

int main() {
    Solution sol;

    {
        vector<int> piles = {3, 6, 7, 11};
        assert(sol.minEatingSpeed(piles, 8) == 4);
    }
    {
        vector<int> piles = {30, 11, 23, 4, 20};
        assert(sol.minEatingSpeed(piles, 5) == 30);
    }
    {
        vector<int> piles = {30, 11, 23, 4, 20};
        assert(sol.minEatingSpeed(piles, 6) == 23);
    }
    {
        vector<int> piles = {312884470};
        assert(sol.minEatingSpeed(piles, 312884469) == 2);
    }

    cout << "LeetCode 875 tests passed.\n";
    return 0;
}
