/*
LeetCode 31. 下一个排列 (Next Permutation)

题目概述 (Problem Summary)
-------------------------
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须原地修改，只允许使用常数额外空间。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 100
- 必须原地修改

示例 (Example)
-------------
输入：nums = [1,2,3]
输出：[1,3,2]

输入：nums = [3,2,1]
输出：[1,2,3]

输入：nums = [1,1,5]
输出：[1,5,1]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到字典序中下一个更大的排列

关键观察：
1. 从后往前找第一个升序位置 i（nums[i] < nums[i+1]）
2. 如果找不到，说明整个数组降序，反转即可
3. 如果找到了，从后往前找第一个比 nums[i] 大的数 nums[j]
4. 交换 nums[i] 和 nums[j]
5. 将 i 后面的部分反转（变为升序）

为什么这样做？
- i 是需要变大的位置
- j 是能让 i 变大的最小选择
- 反转 i 后面的部分，使其变为最小排列

根据这些观察，可以得到一种典型解法：
1. 三步法：找升序位置 -> 交换 -> 反转
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - Three Steps)

核心思想
--------
通过三个步骤找到下一个排列：
1. 从后往前找第一个升序位置
2. 从后往前找第一个比它大的数并交换
3. 反转后面的部分

算法流程：
1. 从后往前找第一个 nums[i] < nums[i+1] 的位置 i
2. 如果找到了：
   - 从后往前找第一个 nums[j] > nums[i] 的位置 j
   - 交换 nums[i] 和 nums[j]
3. 反转 i+1 到末尾的部分

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;

        // 1. 从后往前找第一个升序位置
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // 2. 如果找到了，继续从后往前找第一个比 nums[i] 大的数
        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        // 3. 把 i 后面的部分反转
        reverse(nums.begin() + i + 1, nums.end());
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：nums = [1,2,3]
1. 从后往前找升序：i=1 (nums[1]=2 < nums[2]=3)
2. 从后往前找比 2 大的数：j=2 (nums[2]=3)
3. 交换：[1,3,2]
4. 反转 i+1 到末尾：[1,3,2]（只有一个元素，不变）
结果：[1,3,2]

示例 2：nums = [3,2,1]
1. 从后往前找升序：找不到，i=-1
2. 跳过交换步骤
3. 反转整个数组：[1,2,3]
结果：[1,2,3]

示例 3：nums = [1,5,8,4,7,6,5,3,1]
1. 从后往前找升序：i=3 (nums[3]=4 < nums[4]=7)
2. 从后往前找比 4 大的数：j=6 (nums[6]=5)
3. 交换：[1,5,8,5,7,6,4,3,1]
4. 反转 i+1 到末尾：[1,5,8,5,1,3,4,6,7]
结果：[1,5,8,5,1,3,4,6,7]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组长度为 1：不变
2. 数组完全降序：反转为升序
3. 数组完全升序：交换最后两个元素
4. 存在重复元素：注意边界条件（>= 和 <=）
*/

/*
易错点 (Common Mistakes)
-----------------------
1. 边界条件：nums[i] >= nums[i+1]（不是 >）
2. 边界条件：nums[j] <= nums[i]（不是 <）
3. 反转范围：i+1 到末尾（不是 i 到末尾）
4. 特殊情况：i=-1 时也要反转整个数组
*/

/*
算法正确性证明 (Correctness Proof)
---------------------------------
1. 为什么从后往前找升序位置？
   - i 后面的部分是降序的，已经是最大排列
   - i 是需要变大的最右位置

2. 为什么从后往前找第一个比 nums[i] 大的数？
   - i 后面是降序的，从后往前找到的是最小的比 nums[i] 大的数
   - 这样能保证下一个排列是最接近当前排列的

3. 为什么要反转 i 后面的部分？
   - 交换后，i 后面仍然是降序的
   - 反转后变为升序，是最小的排列
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ",";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // 测试用例 1：基本情况
    vector<int> nums1 = {1, 2, 3};
    solution.nextPermutation(nums1);
    cout << "测试用例 1 - 输出: ";
    printVector(nums1);
    cout << " (期望: [1,3,2])" << endl;

    // 测试用例 2：完全降序
    vector<int> nums2 = {3, 2, 1};
    solution.nextPermutation(nums2);
    cout << "测试用例 2 - 输出: ";
    printVector(nums2);
    cout << " (期望: [1,2,3])" << endl;

    // 测试用例 3：有重复元素
    vector<int> nums3 = {1, 1, 5};
    solution.nextPermutation(nums3);
    cout << "测试用例 3 - 输出: ";
    printVector(nums3);
    cout << " (期望: [1,5,1])" << endl;

    // 测试用例 4：复杂情况
    vector<int> nums4 = {1, 5, 8, 4, 7, 6, 5, 3, 1};
    solution.nextPermutation(nums4);
    cout << "测试用例 4 - 输出: ";
    printVector(nums4);
    cout << " (期望: [1,5,8,5,1,3,4,6,7])" << endl;

    return 0;
}
