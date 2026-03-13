/*
LeetCode 135. 分发糖果 (Candy)

题目概述 (Problem Summary)
-------------------------
有 n 个孩子站成一排，每个孩子有评分 ratings[i]。
需要分发糖果，满足：
1. 每个孩子至少 1 颗糖
2. 相邻孩子中评分更高的孩子必须拿更多糖
求最少需要多少糖果。

关键约束 (Key Constraints)
-------------------------
- 1 <= ratings.length <= 2 * 10^4
- 0 <= ratings[i] <= 2 * 10^4

示例 (Example)
-------------
输入：ratings = [1,0,2]
输出：5
解释：分配 [2,1,2] 总和为 5

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在相邻约束下，为每个位置分配最小糖果数

关键观察：
1. 只看单向比较不足，需要同时满足左侧与右侧关系
2. 可以先从左到右满足“比左邻高”规则
3. 再从右到左满足“比右邻高”规则，取最大值

根据这些观察，可以得到两种典型解法：
1. 双向扫描贪心
2. 单次扫描并记录坡度（更复杂）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用两次扫描：
left[i] 表示满足左侧规则的最少糖果数，
right[i] 表示满足右侧规则的最少糖果数。
最终取 max(left[i], right[i])。

算法流程：
1. 初始化 left 全为 1
2. 从左到右，如果 ratings[i] > ratings[i-1]，left[i] = left[i-1] + 1
3. 从右到左，如果 ratings[i] > ratings[i+1]，right[i] = right[i+1] + 1
4. 累加 max(left[i], right[i])

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        vector<int> left(n, 1);
        vector<int> right(n, 1);

        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
        }

        int total = 0;
        for (int i = 0; i < n; ++i) {
            total += max(left[i], right[i]);
        }

        return total;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - One Pass with Slopes)

优化思路
--------
记录上升段和下降段长度，根据坡度变化计算糖果数量。
实现复杂，适合进阶学习。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int candy(vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        if (n == 0) return 0;

        int total = 1;
        int up = 0, down = 0, peak = 0;

        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                up++;
                peak = up;
                down = 0;
                total += 1 + up;
            } else if (ratings[i] == ratings[i - 1]) {
                up = down = peak = 0;
                total += 1;
            } else {
                down++;
                up = 0;
                total += 1 + down;
                if (down > peak) total += 1; // 峰顶需要补偿
            }
        }

        return total;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
ratings = [1,0,2]

左扫：left = [1,1,2]
右扫：right = [2,1,1]
取 max：[2,1,2] 总和 = 5
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：双向扫描
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：易理解，稳定
- 缺点：需要额外数组

方法二：单次扫描坡度
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：实现复杂，易出错
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全部相同评分：每人 1 颗
2. 单调递增：糖果数为 1..n
3. 单调递减：糖果数为 n..1
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> ratings1 = {1, 0, 2};
    cout << "测试用例 1 - 输出: " << solution.candy(ratings1)
         << " (期望: 5)" << endl;

    // 测试用例 2
    vector<int> ratings2 = {1, 2, 2};
    cout << "测试用例 2 - 输出: " << solution.candy(ratings2)
         << " (期望: 4)" << endl;

    return 0;
}
