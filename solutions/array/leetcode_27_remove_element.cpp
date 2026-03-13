/*
LeetCode 27. 移除元素 (Remove Element)

题目概述 (Problem Summary)
-------------------------
给定一个数组 nums 和一个值 val，原地移除所有等于 val 的元素，
并返回新数组的长度。元素顺序可以改变。

关键约束 (Key Constraints)
-------------------------
- 0 <= nums.length <= 100
- 0 <= nums[i], val <= 50
- 需要原地修改

示例 (Example)
-------------
输入：nums = [3,2,2,3], val = 3
输出：2，nums 前两个元素为 [2,2]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在数组中原地“过滤”指定值

关键观察：
1. 可以用快慢指针覆盖不等于 val 的元素
2. 如果不要求保持顺序，可用“交换到末尾”减少写入

根据这些观察，可以得到两种典型解法：
1. 快慢指针（保持顺序）
2. 左右指针（不保证顺序）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用快慢指针，slow 指向写入位置，fast 遍历数组。
当 nums[fast] != val 时，将其写入 nums[slow] 并 slow++。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
            if (nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Swap with End)

优化思路
--------
用左右指针，当 nums[left] == val 时，与末尾元素交换并缩小范围。
由于不要求保持顺序，可以减少写入次数。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [3,2,2,3], val = 3

快慢指针：
fast=0(3) 跳过
fast=1(2) -> nums[0]=2
fast=2(2) -> nums[1]=2
fast=3(3) 跳过
新长度=2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：稳定保持顺序
- 缺点：可能多次写入

方法二：交换末尾
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：减少写入
- 缺点：顺序被打乱
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组为空：返回 0
2. 全部等于 val：返回 0
3. 没有等于 val：返回原长度
*/

static void printVector(const vector<int>& nums, int len) {
    cout << "[";
    for (int i = 0; i < len; ++i) {
        cout << nums[i];
        if (i + 1 < len) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {3, 2, 2, 3};
    int len1 = solution.removeElement(nums1, 3);
    cout << "测试用例 1 - 输出长度: " << len1 << " 数组: ";
    printVector(nums1, len1);
    cout << " (期望长度: 2)" << endl;

    // 测试用例 2
    vector<int> nums2 = {0,1,2,2,3,0,4,2};
    int len2 = solution.removeElement(nums2, 2);
    cout << "测试用例 2 - 输出长度: " << len2 << " 数组: ";
    printVector(nums2, len2);
    cout << " (期望长度: 5)" << endl;

    return 0;
}
