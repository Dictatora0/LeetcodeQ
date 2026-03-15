/*
LeetCode 78. 子集 (Subsets)

题目概述 (Problem Summary)
-------------------------
给你一个整数数组 nums，数组中的元素互不相同。
返回该数组所有可能的子集（幂集）。

解集不能包含重复的子集。你可以按任意顺序返回解集。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10
- nums 中的所有元素互不相同

示例 (Example)
-------------
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

输入：nums = [0]
输出：[[],[0]]


算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 生成一个集合的所有子集（包括空集和集合本身）

关键观察：
1. 这是一个典型的回溯问题（组合问题）
2. 长度为 n 的数组有 2^n 个子集
3. 每个元素都有两种状态：选或不选
4. 子集问题的特点：收集所有节点，而不仅仅是叶子节点

回溯决策树：
以 nums = [1,2,3] 为例：

                        []
                    /        \
                  [1]         []
                /    \       /   \
            [1,2]   [1]    [2]   []
           /   \    / \    / \   / \
      [1,2,3][1,2][1,3][1][2,3][2][3][]

每个节点代表一个子集，每层代表是否选择当前元素。

另一种理解方式（更符合代码实现）：

                        [] ✓
            /           |           \
          [1]✓         [2]✓         [3]✓
         /    \          |
      [1,2]✓  [1,3]✓   [2,3]✓
       /
   [1,2,3]✓

从每个位置开始，选择当前元素及之后的元素。

根据这些观察，可以得到几种典型解法：
1. 回溯法 - 标准解法
2. 迭代法 - 逐个添加元素
3. 位运算法 - 利用二进制表示
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
方法一：我的原始解法 - 回溯法 (Approach 1: My Original Solution - Backtracking)

核心思想
--------
使用回溯法遍历所有可能的子集。
关键：在回溯的每个节点都收集结果，而不仅仅是叶子节点。

算法流程：
1. 从空集开始
2. 对于每个位置，尝试选择当前元素及之后的元素：
   a. 将当前子集加入结果（关键：每个节点都是一个有效子集）
   b. 选择一个元素加入子集
   c. 递归处理下一个位置
   d. 回溯：移除刚加入的元素
3. 返回所有收集到的子集

为什么使用回溯？
- 需要遍历所有可能的组合
- 每个元素只能选择一次
- 自然地表达"选择-递归-撤销"的过程

关键点：
- 在进入递归前就收集结果（包括空集）
- 使用 startIndex 避免重复子集

复杂度分析
---------
时间复杂度：O(n × 2^n)
- 一共有 2^n 个子集
- 每个子集平均长度为 n/2
- 复制每个子集需要 O(n) 时间

空间复杂度：O(n)
- 递归调用栈的深度为 n
- 不计算结果数组的空间

其中：
n = nums.length
*/
class Solution {
public:
    vector<vector<int>> ans;  // 存储所有子集
    vector<int> path;         // 当前路径（正在构建的子集）

    // 回溯函数
    // nums: 输入数组
    // startIndex: 当前搜索的起始位置
    void backtrack(vector<int>& nums, int startIndex){
        // 关键：在进入递归前就收集结果
        // 每个节点都代表一个有效的子集
        ans.emplace_back(path);

        // 遍历数组，从 startIndex 开始（避免重复子集）
        for (int i = startIndex; i < nums.size(); i++){
            // 注意：原代码有误，应该是 nums[i] 而不是 i
            path.push_back(nums[i]);  // 做选择：将元素加入子集

            backtrack(nums, i + 1);   // 递归：处理下一个位置

            path.pop_back();          // 撤销选择：回溯，移除刚加入的元素
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        // 从索引 0 开始回溯
        backtrack(nums, 0);
        return ans;
    }
};

/*
方法二：迭代法 (Approach 2: Iterative)

核心思想
--------
从空集开始，逐个添加元素。
每添加一个新元素，就将其加入到现有的所有子集中，生成新的子集。

算法流程：
1. 初始化结果为 [[]]（只包含空集）
2. 对于数组中的每个元素：
   a. 遍历当前所有子集
   b. 将当前元素加入每个子集，生成新子集
   c. 将新子集加入结果
3. 返回结果

示例：nums = [1,2,3]
- 初始：[[]]
- 添加 1：[[], [1]]
- 添加 2：[[], [1], [2], [1,2]]
- 添加 3：[[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]

复杂度分析
---------
时间复杂度：O(n × 2^n)
- 与回溯法相同

空间复杂度：O(1)
- 不计算结果数组的空间
- 没有递归调用栈

其中：
n = nums.length
*/
class Solution_Iterative {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        result.push_back({});  // 初始化：空集

        // 逐个添加元素
        for(int num : nums){
            int size = result.size();  // 当前子集数量

            // 遍历现有的所有子集
            for(int i = 0; i < size; i++){
                // 将当前元素加入现有子集，生成新子集
                vector<int> newSubset = result[i];
                newSubset.push_back(num);
                result.push_back(newSubset);
            }
        }

        return result;
    }
};

/*
方法三：位运算法 (Approach 3: Bit Manipulation)

核心思想
--------
利用二进制数表示子集。
对于长度为 n 的数组，有 2^n 个子集，
可以用 0 到 2^n-1 的二进制数表示每个子集。

二进制表示：
- 第 i 位为 1：选择 nums[i]
- 第 i 位为 0：不选择 nums[i]

示例：nums = [1,2,3]
- 000 (0) → []
- 001 (1) → [1]
- 010 (2) → [2]
- 011 (3) → [1,2]
- 100 (4) → [3]
- 101 (5) → [1,3]
- 110 (6) → [2,3]
- 111 (7) → [1,2,3]

算法流程：
1. 遍历 0 到 2^n-1 的所有数字
2. 对于每个数字，检查其二进制表示的每一位
3. 如果第 i 位为 1，将 nums[i] 加入当前子集
4. 将当前子集加入结果

复杂度分析
---------
时间复杂度：O(n × 2^n)
- 与回溯法相同

空间复杂度：O(1)
- 不计算结果数组的空间
- 没有递归调用栈

其中：
n = nums.length
*/
class Solution_BitManipulation {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int subsetCount = 1 << n;  // 2^n 个子集
        vector<vector<int>> result;

        // 遍历 0 到 2^n-1 的所有数字
        for(int mask = 0; mask < subsetCount; mask++){
            vector<int> subset;

            // 检查 mask 的每一位
            for(int i = 0; i < n; i++){
                // 如果第 i 位为 1，选择 nums[i]
                if(mask & (1 << i)){
                    subset.push_back(nums[i]);
                }
            }

            result.push_back(subset);
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums = [1,2,3]

回溯法执行过程：

初始：path = [], startIndex = 0
1. 收集 [] → ans = [[]]

2. i = 0, 选择 1：path = [1], startIndex = 1
   2.1 收集 [1] → ans = [[], [1]]
   2.2 i = 1, 选择 2：path = [1,2], startIndex = 2
       2.2.1 收集 [1,2] → ans = [[], [1], [1,2]]
       2.2.2 i = 2, 选择 3：path = [1,2,3], startIndex = 3
             2.2.2.1 收集 [1,2,3] → ans = [[], [1], [1,2], [1,2,3]]
             2.2.2.2 循环结束，回溯
       2.2.3 回溯：path = [1,2]
       2.2.4 循环结束，回溯
   2.3 回溯：path = [1]
   2.4 i = 2, 选择 3：path = [1,3], startIndex = 3
       2.4.1 收集 [1,3] → ans = [[], [1], [1,2], [1,2,3], [1,3]]
       2.4.2 循环结束，回溯
   2.5 回溯：path = [1]
   2.6 循环结束，回溯

3. 回溯：path = []
4. i = 1, 选择 2：path = [2], startIndex = 2
   4.1 收集 [2] → ans = [[], [1], [1,2], [1,2,3], [1,3], [2]]
   4.2 i = 2, 选择 3：path = [2,3], startIndex = 3
       4.2.1 收集 [2,3] → ans = [[], [1], [1,2], [1,2,3], [1,3], [2], [2,3]]
       4.2.2 循环结束，回溯
   4.3 回溯：path = [2]
   4.4 循环结束，回溯

5. 回溯：path = []
6. i = 2, 选择 3：path = [3], startIndex = 3
   6.1 收集 [3] → ans = [[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]]
   6.2 循环结束，回溯

7. 回溯：path = []
8. 循环结束

最终结果：[[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]]

迭代法执行过程：

初始：result = [[]]

1. 添加 1：
   - 现有子集：[[]]
   - 新子集：[[1]]
   - result = [[], [1]]

2. 添加 2：
   - 现有子集：[[], [1]]
   - 新子集：[[2], [1,2]]
   - result = [[], [1], [2], [1,2]]

3. 添加 3：
   - 现有子集：[[], [1], [2], [1,2]]
   - 新子集：[[3], [1,3], [2,3], [1,2,3]]
   - result = [[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]

位运算法执行过程：

n = 3, subsetCount = 2^3 = 8

mask = 0 (000) → []
mask = 1 (001) → [1]
mask = 2 (010) → [2]
mask = 3 (011) → [1,2]
mask = 4 (100) → [3]
mask = 5 (101) → [1,3]
mask = 6 (110) → [2,3]
mask = 7 (111) → [1,2,3]

最终结果：[[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]
*/

/*
回溯模板 (Backtracking Template)
-------------------------------
子集问题是回溯算法的经典应用，特点是收集所有节点而不仅仅是叶子节点。

标准回溯模板：

void backtrack(参数) {
    收集结果;  // 关键：在进入递归前就收集

    if (终止条件) {
        return;
    }

    for (选择 : 选择列表) {
        做选择;
        backtrack(参数);
        撤销选择;
    }
}

本题的具体应用：
- 收集结果：ans.emplace_back(path)（在循环前）
- 终止条件：startIndex >= nums.size()（隐式，通过循环条件）
- 选择列表：nums[startIndex...n-1]
- 做选择：path.push_back(nums[i])
- 撤销选择：path.pop_back()

关键点：
1. 在进入循环前就收集结果（包括空集）
2. 不需要 used 数组（不是排列问题）
3. 使用 startIndex 避免重复子集
4. 递归时传入 i+1（每个元素只能选择一次）

与其他组合问题的区别：
- 子集：收集所有节点
- 组合：只收集满足条件的叶子节点
- 排列：需要 used 数组，从 0 开始遍历
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：回溯法
- 时间复杂度：O(n × 2^n)
- 空间复杂度：O(n) - 递归栈
- 优点：代码简洁，易于理解
- 缺点：递归调用有额外开销

方法二：迭代法
- 时间复杂度：O(n × 2^n)
- 空间复杂度：O(1)
- 优点：避免递归，空间效率高
- 缺点：不够直观

方法三：位运算法
- 时间复杂度：O(n × 2^n)
- 空间复杂度：O(1)
- 优点：避免递归，思路独特
- 缺点：不够直观，需要理解位运算

三种方法时间复杂度相同，迭代法和位运算法空间效率更高。
回溯法最直观，推荐用于理解问题；迭代法最实用。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单个元素：nums = [0]
   - 返回 [[], [0]]

2. 两个元素：nums = [1,2]
   - 返回 [[], [1], [2], [1,2]]

3. 负数：nums = [-1,0,1]
   - 返回 [[], [-1], [0], [-1,0], [1], [-1,1], [0,1], [-1,0,1]]

4. 最大长度：nums.length = 10
   - 返回 2^10 = 1024 个子集
*/

/*
子集问题变体 (Subset Problem Variants)
-------------------------------------
1. 子集 I（本题）：
   - 元素互不相同
   - 返回所有子集

2. 子集 II（LeetCode 90）：
   - 元素可能重复
   - 返回所有不重复的子集
   - 需要排序 + 去重

3. 子集和问题：
   - 判断是否存在和为 target 的子集
   - 动态规划问题

4. 分割等和子集（LeetCode 416）：
   - 判断是否可以分割成两个和相等的子集
   - 动态规划问题
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> result1 = solution.subsets(nums1);
    cout << "测试用例 1 (nums = [1,2,3]):" << endl;
    for(const auto& subset : result1) {
        cout << "[";
        for(int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if(i < subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]])" << endl;
    cout << "共 " << result1.size() << " 个子集 (期望: 8)" << endl;

    // 测试用例 2：单个元素
    vector<int> nums2 = {0};
    vector<vector<int>> result2 = solution.subsets(nums2);
    cout << "\n测试用例 2 (nums = [0]):" << endl;
    for(const auto& subset : result2) {
        cout << "[";
        for(int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if(i < subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[],[0]])" << endl;

    // 测试用例 3：包含负数
    vector<int> nums3 = {-1, 0, 1};
    vector<vector<int>> result3 = solution.subsets(nums3);
    cout << "\n测试用例 3 (nums = [-1,0,1]):" << endl;
    cout << "共 " << result3.size() << " 个子集 (期望: 8)" << endl;

    // 测试用例 4：使用迭代法
    Solution_Iterative solution_iter;
    vector<int> nums4 = {1, 2};
    vector<vector<int>> result4 = solution_iter.subsets(nums4);
    cout << "\n测试用例 4 (迭代法, nums = [1,2]):" << endl;
    for(const auto& subset : result4) {
        cout << "[";
        for(int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if(i < subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[],[1],[2],[1,2]])" << endl;

    return 0;
}
