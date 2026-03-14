/*
LeetCode 46. 全排列 (Permutations)

题目概述 (Problem Summary)
-------------------------
给定一个不含重复数字的数组 nums，返回其所有可能的全排列。你可以按任意顺序返回答案。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 6
- -10 <= nums[i] <= 10
- nums 中的所有整数互不相同

示例 (Example)
-------------
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

输入：nums = [0,1]
输出：[[0,1],[1,0]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 从 n 个不同元素中选出 n 个元素的所有排列方式
- 这是一个典型的回溯问题，需要枚举所有可能的排列组合

关键观察：
1. 全排列问题的核心是"选择"：每次从剩余未使用的元素中选一个
2. 需要记录哪些元素已经被使用，避免重复选择
3. 当选择的元素数量等于数组长度时，得到一个完整的排列
4. 回溯的本质是"做选择 -> 递归 -> 撤销选择"

回溯三要素：
1. 路径（path）：已经做出的选择
2. 选择列表：当前可以做的选择（未使用的元素）
3. 结束条件：到达决策树底层，无法再做选择

决策树示例（nums = [1,2,3]）：
                    []
          /         |         \
        [1]        [2]        [3]
       /   \      /   \      /   \
    [1,2] [1,3] [2,1] [2,3] [3,1] [3,2]
      |     |     |     |     |     |
   [1,2,3][1,3,2][2,1,3][2,3,1][3,1,2][3,2,1]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：回溯 + used 数组 (Approach 1: Backtracking with Used Array)

核心思想
--------
使用回溯算法遍历决策树，用 used 数组标记已使用的元素。

算法流程：
1. 维护三个关键数据结构：
   - result: 存储所有排列结果
   - path: 当前正在构建的排列
   - used: 标记数组，记录每个元素是否已被使用
2. 回溯函数 backtrack：
   a. 终止条件：path.size() == nums.size()，说明得到一个完整排列
   b. 遍历所有元素：
      - 如果元素已使用（used[i] == true），跳过
      - 做选择：将元素加入 path，标记为已使用
      - 递归：继续选择下一个元素
      - 撤销选择：从 path 移除元素，标记为未使用（回溯）

为什么需要 used 数组？
- 因为全排列中每个元素只能使用一次
- used 数组确保同一个元素不会在一个排列中出现多次
- 这是排列问题和组合问题的关键区别

复杂度分析
---------
时间复杂度：O(n! * n)
- 共有 n! 个排列
- 每个排列需要 O(n) 时间复制到结果中

空间复杂度：O(n)
- used 数组：O(n)
- path 数组：O(n)
- 递归调用栈深度：O(n)
- 不计算结果数组的空间

其中：
n = nums.length
*/
class Solution {
public:
    // result: 存储所有排列结果
    vector<vector<int>> result;

    // used: 标记数组，used[i] = true 表示 nums[i] 已被使用
    vector<bool> used;

    // path: 当前正在构建的排列路径
    vector<int> path;

    // 回溯函数
    // nums: 原始数组
    void backtrack(vector<int>& nums) {
        // 终止条件：找到一个完整的排列
        if (path.size() == nums.size()) {
            result.push_back(path);  // 将当前排列加入结果
            return;
        }

        // 遍历所有元素，尝试将每个未使用的元素加入排列
        for (int i = 0; i < nums.size(); i++) {
            // 剪枝：如果当前元素已被使用，跳过
            if (used[i]) {
                continue;
            }

            // 做选择：选择当前元素
            path.push_back(nums[i]);
            used[i] = true;

            // 递归：继续构建排列
            backtrack(nums);

            // 撤销选择：回溯
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        // 初始化 used 数组，所有元素初始都未使用
        used.resize(nums.size(), false);

        // 从空排列开始回溯
        backtrack(nums);

        return result;
    }
};

/*
方法二：回溯 + 交换 (Approach 2: Backtracking with Swap)

核心思想
--------
通过交换元素位置来生成排列，不需要额外的 used 数组。

算法流程：
1. 使用 start 参数表示当前要填充的位置
2. 对于位置 start，尝试将 [start, n-1] 范围内的每个元素放到该位置
3. 通过交换实现：swap(nums[start], nums[i])
4. 递归处理下一个位置
5. 回溯：交换回来

优点：
- 不需要额外的 used 数组，空间效率更高
- 直接在原数组上操作

缺点：
- 需要修改原数组（可以通过传值解决）
- 代码理解难度稍高

复杂度分析
---------
时间复杂度：O(n! * n)
- 与方法一相同

空间复杂度：O(n)
- 只需要递归调用栈，不需要 used 数组
- 比方法一节省空间
*/
class Solution_Swap {
public:
    vector<vector<int>> result;

    // start: 当前要填充的位置索引
    void backtrack(vector<int>& nums, int start) {
        // 终止条件：所有位置都已填充
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        // 尝试将 [start, n-1] 范围内的每个元素放到位置 start
        for (int i = start; i < nums.size(); i++) {
            // 做选择：将 nums[i] 放到位置 start
            swap(nums[start], nums[i]);

            // 递归：处理下一个位置
            backtrack(nums, start + 1);

            // 撤销选择：交换回来（回溯）
            swap(nums[start], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        backtrack(nums, 0);
        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums = [1, 2, 3]

使用方法一（used 数组）的执行过程：

初始状态：
- path = []
- used = [false, false, false]
- result = []

第一层递归（选择第一个元素）：
1. 选择 1：path = [1], used = [true, false, false]
   第二层递归（选择第二个元素）：
   - 选择 2：path = [1,2], used = [true, true, false]
     第三层递归（选择第三个元素）：
     - 选择 3：path = [1,2,3] -> 加入 result
     - 回溯：path = [1,2], used = [true, true, false]
   - 回溯：path = [1], used = [true, false, false]
   - 选择 3：path = [1,3], used = [true, false, true]
     第三层递归：
     - 选择 2：path = [1,3,2] -> 加入 result
     - 回溯
   - 回溯：path = [1], used = [true, false, false]
   回溯：path = [], used = [false, false, false]

2. 选择 2：path = [2], used = [false, true, false]
   ...类似过程

3. 选择 3：path = [3], used = [false, false, true]
   ...类似过程

最终 result = [[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：回溯 + used 数组
- 时间复杂度：O(n! * n)
- 空间复杂度：O(n)（used + path + 递归栈）
- 优点：逻辑清晰，易于理解
- 缺点：需要额外的 used 数组

方法二：回溯 + 交换
- 时间复杂度：O(n! * n)
- 空间复杂度：O(n)（仅递归栈）
- 优点：空间效率更高，不需要额外数组
- 缺点：需要修改原数组，理解难度稍高

两种方法时间复杂度相同，方法二空间效率略高。
实际应用中，方法一更常用，因为代码更直观。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：nums = [1]，返回 [[1]]
2. 两个元素：nums = [1,2]，返回 [[1,2], [2,1]]
3. 包含负数：nums = [-1,0,1]，算法同样适用
4. 最大规模：nums.length = 6，共有 6! = 720 个排列
*/

/*
回溯算法模板总结 (Backtracking Template Summary)
---------------------------------------------
回溯算法的通用框架：

void backtrack(路径, 选择列表) {
    if (满足结束条件) {
        result.add(路径);
        return;
    }

    for (选择 in 选择列表) {
        // 剪枝：排除不合法的选择
        if (不合法) continue;

        // 做选择
        将该选择从选择列表移除;
        路径.add(选择);

        // 递归
        backtrack(路径, 选择列表);

        // 撤销选择（回溯）
        路径.remove(选择);
        将该选择再加入选择列表;
    }
}

关键点：
1. 路径：记录已经做出的选择
2. 选择列表：当前可以做的选择
3. 结束条件：到达决策树底层
4. 剪枝：提前排除不合法的选择，提高效率
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> result1 = solution.permute(nums1);
    cout << "测试用例 1 - 输入: [1,2,3]" << endl;
    cout << "输出: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[";
        for (int j = 0; j < result1[i].size(); j++) {
            cout << result1[i][j];
            if (j < result1[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "排列总数: " << result1.size() << " (期望: 6)" << endl << endl;

    // 测试用例 2：两个元素
    vector<int> nums2 = {0, 1};
    vector<vector<int>> result2 = solution.permute(nums2);
    cout << "测试用例 2 - 输入: [0,1]" << endl;
    cout << "输出: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[";
        for (int j = 0; j < result2[i].size(); j++) {
            cout << result2[i][j];
            if (j < result2[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "排列总数: " << result2.size() << " (期望: 2)" << endl << endl;

    // 测试用例 3：单个元素
    vector<int> nums3 = {1};
    vector<vector<int>> result3 = solution.permute(nums3);
    cout << "测试用例 3 - 输入: [1]" << endl;
    cout << "排列总数: " << result3.size() << " (期望: 1)" << endl;

    return 0;
}
