/*
LeetCode 75. 颜色分类 (Sort Colors)

题目概述 (Problem Summary)
-------------------------
给定一个包含红色、白色和蓝色，共 n 个元素的数组 nums。
原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
使用整数 0、1 和 2 分别表示红色、白色和蓝色。

关键约束 (Key Constraints)
-------------------------
- n == nums.length
- 1 <= n <= 300
- nums[i] 为 0、1 或 2
- 必须原地排序，不使用库的 sort 函数
- 要求一趟扫描算法（one-pass algorithm）

示例 (Example)
-------------
输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]

输入：nums = [2,0,1]
输出：[0,1,2]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 三路快排（Dutch National Flag Problem）

关键观察：
1. 使用三个指针：left（0 的右边界）、right（2 的左边界）、i（当前遍历位置）
2. 遇到 0：与 left 交换，left++, i++
3. 遇到 1：i++
4. 遇到 2：与 right 交换，right--（注意 i 不动）
5. 循环条件：i <= right

为什么遇到 2 时 i 不动？
- 交换过来的元素还没有被检查过
- 可能是 0、1 或 2，需要再次判断

根据这些观察，可以得到两种典型解法：
1. 三指针（荷兰国旗问题）
2. 两趟遍历（计数排序）
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - Three Pointers)

核心思想
--------
使用三个指针维护三个区域：
- [0, left): 全是 0
- [left, i): 全是 1
- (right, n-1]: 全是 2
- [i, right]: 未处理区域

算法流程：
1. left = 0, right = n-1, i = 0
2. 当 i <= right 时：
   - 如果 nums[i] == 0：交换 nums[left] 和 nums[i]，left++, i++
   - 如果 nums[i] == 1：i++
   - 如果 nums[i] == 2：交换 nums[i] 和 nums[right]，right--
3. 循环结束

复杂度分析
---------
时间复杂度：O(n)，一趟扫描
空间复杂度：O(1)
*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        int i = 0;

        while (i <= right) {
            if (nums[i] == 0) {
                swap(nums[left], nums[i]);
                i++;
                left++;
            } else if (nums[i] == 1) {
                i++;
            } else {
                swap(nums[i], nums[right]);
                right--;
            }
        }
    }
};

/*
方法二：两趟遍历解法 (Approach 2: Two-Pass Solution - Counting Sort)

核心思想
--------
第一趟统计 0、1、2 的个数，第二趟按顺序填充。

算法流程：
1. 统计 0、1、2 的个数
2. 按顺序填充数组

复杂度分析
---------
时间复杂度：O(n)，两趟扫描
空间复杂度：O(1)
*/
class Solution_TwoPass {
public:
    void sortColors(vector<int>& nums) {
        int count0 = 0, count1 = 0, count2 = 0;

        // 第一趟：统计
        for (int num : nums) {
            if (num == 0) count0++;
            else if (num == 1) count1++;
            else count2++;
        }

        // 第二趟：填充
        int i = 0;
        while (count0-- > 0) nums[i++] = 0;
        while (count1-- > 0) nums[i++] = 1;
        while (count2-- > 0) nums[i++] = 2;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [2,0,2,1,1,0]

初始状态：
left=0, right=5, i=0
[2,0,2,1,1,0]
 ^         ^
 i         right

步骤 1：nums[0]=2，与 right 交换
left=0, right=4, i=0
[0,0,2,1,1,2]
 ^       ^
 i       right

步骤 2：nums[0]=0，与 left 交换
left=1, right=4, i=1
[0,0,2,1,1,2]
   ^     ^
   i     right

步骤 3：nums[1]=0，与 left 交换
left=2, right=4, i=2
[0,0,2,1,1,2]
     ^ ^
     i right

步骤 4：nums[2]=2，与 right 交换
left=2, right=3, i=2
[0,0,1,1,2,2]
     ^^
     i right

步骤 5：nums[2]=1，i++
left=2, right=3, i=3
[0,0,1,1,2,2]
       ^^
       i right

步骤 6：nums[3]=1，i++
left=2, right=3, i=4
[0,0,1,1,2,2]
         ^
         i > right，结束

结果：[0,0,1,1,2,2]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：三指针（一趟扫描）
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：一趟扫描，效率高
- 缺点：逻辑稍复杂

方法二：两趟遍历（计数排序）
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：逻辑简单
- 缺点：需要两趟扫描
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：不变
2. 全是同一种颜色：不变
3. 已经排好序：不变
4. 完全逆序：[2,2,1,1,0,0]
*/

/*
易错点 (Common Mistakes)
-----------------------
1. 遇到 2 时 i 不能自增（交换过来的元素未检查）
2. 循环条件是 i <= right（不是 i < right）
3. 遇到 0 时 i 要自增（因为 left 位置的元素已经检查过）
4. 初始化：right = n-1（不是 n）
*/

/*
相关问题 (Related Problems)
--------------------------
1. LeetCode 215. 数组中的第K个最大元素（快速选择）
2. LeetCode 283. 移动零（双指针）
3. LeetCode 26. 删除有序数组中的重复项（双指针）
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
    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    solution.sortColors(nums1);
    cout << "测试用例 1 - 输出: ";
    printVector(nums1);
    cout << " (期望: [0,0,1,1,2,2])" << endl;

    // 测试用例 2：简单情况
    vector<int> nums2 = {2, 0, 1};
    solution.sortColors(nums2);
    cout << "测试用例 2 - 输出: ";
    printVector(nums2);
    cout << " (期望: [0,1,2])" << endl;

    // 测试用例 3：全是同一种颜色
    vector<int> nums3 = {1, 1, 1};
    solution.sortColors(nums3);
    cout << "测试用例 3 - 输出: ";
    printVector(nums3);
    cout << " (期望: [1,1,1])" << endl;

    // 测试用例 4：完全逆序
    vector<int> nums4 = {2, 2, 1, 1, 0, 0};
    solution.sortColors(nums4);
    cout << "测试用例 4 - 输出: ";
    printVector(nums4);
    cout << " (期望: [0,0,1,1,2,2])" << endl;

    return 0;
}
