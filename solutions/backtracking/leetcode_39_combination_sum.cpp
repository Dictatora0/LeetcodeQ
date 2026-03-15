/*
LeetCode 39. 组合总和 (Combination Sum)

题目概述 (Problem Summary)
-------------------------
给你一个无重复元素的整数数组 candidates 和一个目标整数 target，
找出 candidates 中可以使数字和为目标数 target 的所有不同组合，
并以列表形式返回。你可以按任意顺序返回这些组合。

candidates 中的同一个数字可以无限制重复被选取。
如果至少一个数字的被选数量不同，则两种组合是不同的。

关键约束 (Key Constraints)
-------------------------
- 1 <= candidates.length <= 30
- 2 <= candidates[i] <= 40
- candidates 的所有元素互不相同
- 1 <= target <= 40

示例 (Example)
-------------
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7。注意 2 可以使用多次。
7 也是一个候选，7 = 7。
仅有这两种组合。

输入：candidates = [2,3,5], target = 8
输出：[[2,2,2,2],[2,3,3],[3,5]]

输入：candidates = [2], target = 1
输出：[]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 从给定数组中选择若干个数（可重复选择），使其和等于目标值

关键观察：
1. 这是一个典型的回溯问题（组合问题）
2. 每个数字可以被无限次使用
3. 需要找出所有满足条件的组合
4. 可以通过剪枝优化：
   - 如果当前和已经超过 target，停止搜索
   - 排序后，如果当前数字已经大于剩余目标，后面的数字都不用考虑

回溯决策树：
以 candidates = [2,3,6,7], target = 7 为例：

                        [] (target=7)
            /          |         |        \
          [2]         [3]       [6]       [7]✓
        (t=5)        (t=4)     (t=1)     (t=0)
       / | | \       / | \       |
    [2,2] [2,3]✓  [3,3] [3,6]  [6,6]
    (t=3) (t=2)   (t=1) (t=-2)  (t=-5)
    / | \
 [2,2,2] [2,2,3]✓
 (t=1)   (t=0)
  / |
[2,2,2,2]
(t=-1)

每个节点的选择：
- 可以选择当前数字（重复使用）
- 可以选择后面的数字（避免重复组合）

根据这些观察，可以得到几种典型解法：
1. 回溯法 + 剪枝 - 标准解法
2. 回溯法 + 排序 + 剪枝 - 优化解法
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 - 回溯法 + 排序 + 剪枝 (Approach 1: My Original Solution - Backtracking with Sorting and Pruning)

核心思想
--------
使用回溯法遍历所有可能的组合，通过排序和剪枝优化搜索过程。
维护一个当前路径 path 和剩余目标值 target。

算法流程：
1. 对 candidates 排序（为剪枝做准备）
2. 从索引 0 开始回溯
3. 对于当前位置，尝试选择当前数字及之后的数字：
   a. 如果当前数字大于剩余目标，停止搜索（剪枝）
   b. 将数字加入路径
   c. 递归处理（注意：可以重复使用当前数字，所以索引不变）
   d. 回溯：移除刚加入的数字
4. 当剩余目标为 0 时，将当前路径加入结果

为什么使用回溯？
- 需要遍历所有可能的组合
- 每个数字可以被重复使用
- 可以通过剪枝提前终止无效搜索

关键技巧：
1. 排序：使得可以提前剪枝
2. 索引控制：从 index 开始而不是 0，避免重复组合
3. 重复使用：递归时传入 i 而不是 i+1，允许重复选择

复杂度分析
---------
时间复杂度：O(S)
- S 是所有可行解的长度之和
- 最坏情况下，candidates = [1], target = n，有 2^n 种组合
- 实际情况下，由于剪枝，复杂度远小于理论上界

空间复杂度：O(target)
- 递归调用栈的深度最多为 target（每次至少减少 1）
- 不计算结果数组的空间

其中：
target = 目标值
candidates.length = 候选数组长度
*/
class Solution {
public:
    vector<vector<int>> ans;  // 存储所有满足条件的组合
    vector<int> path;         // 当前路径（正在构建的组合）

    // 回溯函数
    // candidates: 候选数组
    // target: 剩余目标值
    // index: 当前搜索的起始位置
    void backtrack(vector<int>& candidates, int target, int index) {
        // 递归终止条件：剩余目标为 0，找到一个有效组合
        if (target == 0) {
            ans.emplace_back(path);  // 将当前路径加入结果
            return;
        }

        // 遍历候选数组，从 index 开始（避免重复组合）
        for (int i = index; i < candidates.size(); i++) {
            // 剪枝：如果当前数字已经大于剩余目标，后面的数字都不用考虑
            // 前提：candidates 已排序
            if (candidates[i] > target) {
                break;  // 直接跳出循环
            }

            path.push_back(candidates[i]);  // 做选择：将数字加入路径

            // 递归：注意传入 i 而不是 i+1
            // 因为每个数字可以被无限次使用
            backtrack(candidates, target - candidates[i], i);

            path.pop_back();  // 撤销选择：回溯，移除刚加入的数字
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // 排序：为剪枝做准备
        sort(candidates.begin(), candidates.end());

        // 从索引 0 开始回溯
        backtrack(candidates, target, 0);

        return ans;
    }
};

/*
方法二：回溯法（不排序）(Approach 2: Backtracking without Sorting)

核心思想
--------
不对数组排序，使用 continue 而不是 break 进行剪枝。

算法流程：
与方法一类似，但剪枝时使用 continue 跳过当前数字，
而不是 break 跳出循环。

复杂度分析
---------
时间复杂度：O(S)
- 与方法一相同，但实际运行时间可能更长（无法提前终止循环）

空间复杂度：O(target)
- 与方法一相同

优缺点对比：
- 优点：不需要修改输入数组
- 缺点：无法利用排序进行更有效的剪枝
*/
class Solution_NoSort {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void backtrack(vector<int>& candidates, int target, int index) {
        if (target == 0) {
            ans.emplace_back(path);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            // 剪枝：如果当前数字大于剩余目标，跳过
            if (candidates[i] > target) {
                continue;  // 使用 continue 而不是 break
            }

            path.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0);
        return ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：candidates = [2,3,6,7], target = 7

排序后：candidates = [2,3,6,7]

回溯决策树（完整展示）：

                        [] (target=7, index=0)
            /          |         |        \
          [2]         [3]       [6]       [7]✓
        (t=5,i=0)   (t=4,i=1)  (t=1,i=2) (t=0,i=3)
       / | | \       / | \       |
    [2,2] [2,3] [2,6] [2,7]  [3,3] [3,6] [3,7]  [6,6]
    (t=3) (t=2)✓(t=-1)(t=-2) (t=1) (t=-2)(t=-3) (t=-5)
    i=0   i=1   剪枝  剪枝   i=1   剪枝  剪枝   剪枝
   / | | \
[2,2,2] [2,2,3]✓ [2,2,6] [2,2,7]
(t=1)   (t=0)    (t=-3)  (t=-4)
i=0     i=1      剪枝    剪枝
 / | | \
[2,2,2,2] [2,2,2,3] [2,2,2,6] [2,2,2,7]
(t=-1)    (t=-2)    (t=-5)    (t=-6)
剪枝      剪枝      剪枝      剪枝

执行过程：

初始：path = [], target = 7, index = 0

1. 选择 2：path = [2], target = 5, index = 0
   1.1 选择 2：path = [2,2], target = 3, index = 0
       1.1.1 选择 2：path = [2,2,2], target = 1, index = 0
             1.1.1.1 选择 2：target = -1 < 0，剪枝
             1.1.1.2 选择 3：target = -2 < 0，剪枝
             ...
       1.1.2 选择 3：path = [2,2,3], target = 0 → 加入结果 ✓
       1.1.3 选择 6：target = -3 < 0，剪枝
       1.1.4 选择 7：target = -4 < 0，剪枝
   1.2 选择 3：path = [2,3], target = 2, index = 1
       1.2.1 选择 3：target = -1 < 0，剪枝
       ...
   1.3 选择 6：target = -1 < 0，剪枝
   1.4 选择 7：target = -2 < 0，剪枝

2. 选择 3：path = [3], target = 4, index = 1
   2.1 选择 3：path = [3,3], target = 1, index = 1
       2.1.1 选择 3：target = -2 < 0，剪枝
       ...
   2.2 选择 6：target = -2 < 0，剪枝
   2.3 选择 7：target = -3 < 0，剪枝

3. 选择 6：path = [6], target = 1, index = 2
   3.1 选择 6：target = -5 < 0，剪枝
   3.2 选择 7：target = -6 < 0，剪枝

4. 选择 7：path = [7], target = 0 → 加入结果 ✓

最终结果：[[2,2,3], [7]]
*/

/*
回溯模板 (Backtracking Template)
-------------------------------
组合总和是回溯算法的经典应用，特点是可以重复选择同一个元素。

标准回溯模板：

void backtrack(参数) {
    if (终止条件) {
        收集结果;
        return;
    }

    for (选择 : 选择列表) {
        if (剪枝条件) continue/break;
        做选择;
        backtrack(参数);
        撤销选择;
    }
}

本题的具体应用：
- 终止条件：target == 0
- 选择列表：candidates[index...n-1]
- 剪枝条件：candidates[i] > target
- 做选择：path.push_back(candidates[i])
- 撤销选择：path.pop_back()

关键点：
1. 不需要 used 数组（可以重复使用元素）
2. 使用 index 参数避免重复组合（[2,3] 和 [3,2] 是同一个组合）
3. 递归时传入 i 而不是 i+1（允许重复选择）
4. 排序 + break 比 continue 更高效

与其他组合问题的区别：
- 组合总和 I：可以重复使用，递归传入 i
- 组合总和 II：不可重复使用，需要去重，递归传入 i+1
- 组合：固定组合大小，不可重复使用，递归传入 i+1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：回溯法 + 排序 + 剪枝
- 时间复杂度：O(S) + O(n log n)
- 空间复杂度：O(target)
- 优点：剪枝效率高，可以提前终止循环
- 缺点：需要修改输入数组（排序）

方法二：回溯法（不排序）
- 时间复杂度：O(S)
- 空间复杂度：O(target)
- 优点：不修改输入数组
- 缺点：剪枝效率低，无法提前终止循环

推荐使用方法一，因为：
1. 排序的时间复杂度相对较小
2. 剪枝效率显著提高
3. 实际运行时间更短
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 无解情况：candidates = [2], target = 1
   - 返回 []

2. 单个数字即为答案：candidates = [2,3,5], target = 5
   - 返回 [[5]]

3. 需要重复使用：candidates = [2], target = 8
   - 返回 [[2,2,2,2]]

4. 多种组合：candidates = [2,3,5], target = 8
   - 返回 [[2,2,2,2],[2,3,3],[3,5]]

5. 所有数字都大于目标：candidates = [10,20], target = 5
   - 返回 []
*/

/*
优化技巧 (Optimization Techniques)
---------------------------------
1. 排序 + break：
   - 对 candidates 排序
   - 当 candidates[i] > target 时，直接 break
   - 效果：避免遍历后面的更大数字

2. 提前终止：
   - 如果 target < 0，立即返回
   - 效果：避免无效递归

3. 使用 emplace_back：
   - 使用 emplace_back 代替 push_back
   - 效果：避免不必要的拷贝

4. 索引控制：
   - 从 index 开始而不是 0
   - 效果：避免重复组合，减少搜索空间

5. 记忆化（不适用）：
   - 本题不适合记忆化，因为路径不同
   - 但可以记录 (target, index) 是否有解
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;
    vector<vector<int>> result1 = solution.combinationSum(candidates1, target1);
    cout << "测试用例 1 (candidates = [2,3,6,7], target = 7):" << endl;
    for(const auto& combination : result1) {
        cout << "[";
        for(int i = 0; i < combination.size(); i++) {
            cout << combination[i];
            if(i < combination.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[2,2,3],[7]])" << endl;

    // 测试用例 2：需要多次重复
    vector<int> candidates2 = {2, 3, 5};
    int target2 = 8;
    vector<vector<int>> result2 = solution.combinationSum(candidates2, target2);
    cout << "\n测试用例 2 (candidates = [2,3,5], target = 8):" << endl;
    for(const auto& combination : result2) {
        cout << "[";
        for(int i = 0; i < combination.size(); i++) {
            cout << combination[i];
            if(i < combination.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[2,2,2,2],[2,3,3],[3,5]])" << endl;

    // 测试用例 3：无解
    vector<int> candidates3 = {2};
    int target3 = 1;
    vector<vector<int>> result3 = solution.combinationSum(candidates3, target3);
    cout << "\n测试用例 3 (candidates = [2], target = 1):" << endl;
    if(result3.empty()) {
        cout << "[]";
    }
    cout << "\n(期望: [])" << endl;

    // 测试用例 4：单个数字即为答案
    vector<int> candidates4 = {1};
    int target4 = 1;
    vector<vector<int>> result4 = solution.combinationSum(candidates4, target4);
    cout << "\n测试用例 4 (candidates = [1], target = 1):" << endl;
    for(const auto& combination : result4) {
        cout << "[";
        for(int i = 0; i < combination.size(); i++) {
            cout << combination[i];
            if(i < combination.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[1]])" << endl;

    return 0;
}
