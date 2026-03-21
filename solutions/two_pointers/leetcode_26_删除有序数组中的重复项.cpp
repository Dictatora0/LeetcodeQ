/*
LeetCode 26. 删除有序数组中的重复项 (Remove Duplicates from Sorted Array)

题目概述 (Problem Summary)
-------------------------
给你一个非严格递增排列的数组 nums,请你原地删除重复出现的元素,使每个元素只出现一次,
返回删除后数组的新长度。元素的相对顺序应该保持一致。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k,你需要做以下事情确保你的题解可以被通过:
- 更改数组 nums,使 nums 的前 k 个元素包含唯一元素,并按照它们最初在 nums 中出现的顺序排列
- nums 的其余元素与 nums 的大小不重要
- 返回 k

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 3 × 10^4
- -100 <= nums[i] <= 100
- nums 已按非严格递增排列

示例 (Example)
-------------
输入:nums = [1,1,2]
输出:2, nums = [1,2,_]
解释:函数应该返回新的长度 2,并且原数组 nums 的前两个元素被修改为 1, 2。
不需要考虑数组中超出新长度后面的元素。

输入:nums = [0,0,1,1,1,2,2,3,3,4]
输出:5, nums = [0,1,2,3,4,_,_,_,_,_]
解释:函数应该返回新的长度 5,并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
不需要考虑数组中超出新长度后面的元素。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题?
- 在有序数组中原地删除重复元素,保留唯一元素

关键观察:
1. 数组已经排序,重复元素一定相邻
2. 需要原地修改,不能使用额外数组
3. 只需要保证前 k 个元素是唯一的,后面的元素不重要

核心技巧:快慢双指针
- slow:指向下一个唯一元素应该放置的位置
- fast:遍历数组,寻找新的唯一元素
- 当 nums[fast] != nums[fast-1] 时,说明找到了新的唯一元素
- 将 nums[fast] 复制到 nums[slow],然后 slow++

为什么这个方法有效?
- slow 左边(不包括 slow)都是已处理的唯一元素
- fast 用于扫描数组,寻找新的唯一元素
- 因为数组有序,只需要比较相邻元素就能判断是否重复
- 原地修改,空间复杂度 O(1)

根据这些观察,可以得到双指针解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一:快慢双指针 (Approach 1: Slow-Fast Two Pointers)

核心思想
--------
使用快慢双指针,slow 指向下一个唯一元素的位置,fast 遍历数组寻找唯一元素。

算法流程:
1. 特殊情况:如果数组为空,返回 0
2. 初始化 slow=1(第一个元素一定是唯一的)
3. 从 fast=1 开始遍历数组:
   a. 如果 nums[fast] != nums[fast-1],说明找到新的唯一元素
   b. 将 nums[fast] 复制到 nums[slow]
   c. slow++
4. 返回 slow(唯一元素的个数)

为什么这个算法正确?
- 第一个元素一定是唯一的,所以 slow 从 1 开始
- nums[fast] != nums[fast-1] 保证了找到的是新的唯一元素
- slow 始终指向下一个唯一元素应该放置的位置
- 最终 slow 的值就是唯一元素的个数

复杂度分析
---------
时间复杂度:O(n),遍历数组一次
空间复杂度:O(1),只使用常数额外空间
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 特殊情况:空数组
        if (nums.empty()) {
            return 0;
        }

        // slow:指向下一个唯一元素应该放置的位置
        // 初始化为 1,因为第一个元素一定是唯一的
        int slow = 1;

        // fast:遍历数组,寻找新的唯一元素
        // 从 1 开始,因为第一个元素已经处理
        for (int fast = 1; fast < nums.size(); fast++) {
            // 关键:比较 nums[fast] 和 nums[fast-1]
            // 如果不相等,说明 nums[fast] 是新的唯一元素
            if (nums[fast] != nums[fast - 1]) {
                // 将新的唯一元素复制到 slow 位置
                nums[slow] = nums[fast];
                // slow 向前移动,指向下一个位置
                slow++;
            }
            // 如果相等,说明 nums[fast] 是重复元素,跳过
        }

        // slow 的值就是唯一元素的个数
        // 因为 slow 指向下一个位置,所以它的值就是已处理元素的数量
        return slow;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [0,0,1,1,1,2,2,3,3,4]

初始状态:
- slow=1, fast=1
- nums = [0,0,1,1,1,2,2,3,3,4]

第 1 轮:fast=1
- nums[1]=0, nums[0]=0, 相等,跳过
- slow=1

第 2 轮:fast=2
- nums[2]=1, nums[1]=0, 不相等
- nums[slow]=nums[1]=1
- slow=2
- nums = [0,1,1,1,1,2,2,3,3,4]

第 3 轮:fast=3
- nums[3]=1, nums[2]=1, 相等,跳过
- slow=2

第 4 轮:fast=4
- nums[4]=1, nums[3]=1, 相等,跳过
- slow=2

第 5 轮:fast=5
- nums[5]=2, nums[4]=1, 不相等
- nums[slow]=nums[2]=2
- slow=3
- nums = [0,1,2,1,1,2,2,3,3,4]

第 6 轮:fast=6
- nums[6]=2, nums[5]=2, 相等,跳过
- slow=3

第 7 轮:fast=7
- nums[7]=3, nums[6]=2, 不相等
- nums[slow]=nums[3]=3
- slow=4
- nums = [0,1,2,3,1,2,2,3,3,4]

第 8 轮:fast=8
- nums[8]=3, nums[7]=3, 相等,跳过
- slow=4

第 9 轮:fast=9
- nums[9]=4, nums[8]=3, 不相等
- nums[slow]=nums[4]=4
- slow=5
- nums = [0,1,2,3,4,2,2,3,3,4]

循环结束,返回 slow=5
最终 nums 的前 5 个元素为 [0,1,2,3,4]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空数组:返回 0
2. 只有一个元素:返回 1
3. 所有元素相同:返回 1
4. 所有元素不同:返回 n
*/

/*
关键点总结 (Key Points)
---------------------
1. 快慢双指针是处理数组原地修改的经典技巧
2. slow 指向"下一个位置",fast 用于"扫描"
3. 为什么比较 nums[fast] 和 nums[fast-1]?
   - 因为数组有序,重复元素一定相邻
   - 只需要比较相邻元素就能判断是否重复
4. 为什么 slow 从 1 开始?
   - 第一个元素一定是唯一的,不需要处理
   - slow=1 表示第二个位置是下一个唯一元素的位置
5. 为什么返回 slow?
   - slow 指向下一个位置,它的值就是已处理元素的数量
   - 例如:slow=5 表示前 5 个位置(索引 0-4)是唯一元素
6. 这个模板可以推广到"保留 k 个重复元素"的问题
*/

/*
方法二:另一种写法 (Approach 2: Alternative Implementation)

核心思想
--------
slow 指向最后一个唯一元素的位置,而不是下一个位置。

算法流程:
1. 初始化 slow=0
2. 从 fast=1 开始遍历:
   a. 如果 nums[fast] != nums[slow],说明找到新的唯一元素
   b. slow++
   c. nums[slow] = nums[fast]
3. 返回 slow+1

这种写法和方法一本质相同,只是 slow 的含义不同。
*/
class Solution_Alternative {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // slow 指向最后一个唯一元素的位置
        int slow = 0;

        for (int fast = 1; fast < nums.size(); fast++) {
            // 如果找到新的唯一元素
            if (nums[fast] != nums[slow]) {
                slow++;                  // slow 向前移动
                nums[slow] = nums[fast]; // 复制新元素
            }
        }

        // 返回 slow+1,因为 slow 是索引,需要加 1 得到数量
        return slow + 1;
    }
};

int main() {
    Solution solution;

    // 测试用例 1:标准情况
    vector<int> nums1 = {1, 1, 2};
    int result1 = solution.removeDuplicates(nums1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 2)" << endl;
    cout << "数组前 " << result1 << " 个元素: ";
    for (int i = 0; i < result1; i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;

    // 测试用例 2:多个重复元素
    vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int result2 = solution.removeDuplicates(nums2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 5)" << endl;
    cout << "数组前 " << result2 << " 个元素: ";
    for (int i = 0; i < result2; i++) {
        cout << nums2[i] << " ";
    }
    cout << endl;

    // 测试用例 3:所有元素相同
    vector<int> nums3 = {1, 1, 1, 1};
    int result3 = solution.removeDuplicates(nums3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: 1)" << endl;
    cout << "数组前 " << result3 << " 个元素: ";
    for (int i = 0; i < result3; i++) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    // 测试用例 4:所有元素不同
    vector<int> nums4 = {1, 2, 3, 4, 5};
    int result4 = solution.removeDuplicates(nums4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 5)" << endl;
    cout << "数组前 " << result4 << " 个元素: ";
    for (int i = 0; i < result4; i++) {
        cout << nums4[i] << " ";
    }
    cout << endl;

    // 测试用例 5:只有一个元素
    vector<int> nums5 = {1};
    int result5 = solution.removeDuplicates(nums5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 1)" << endl;
    cout << "数组前 " << result5 << " 个元素: ";
    for (int i = 0; i < result5; i++) {
        cout << nums5[i] << " ";
    }
    cout << endl;

    return 0;
}
