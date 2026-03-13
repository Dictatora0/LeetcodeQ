/*
LeetCode 189. 轮转数组 (Rotate Array)

题目概述 (Problem Summary)
-------------------------
给定一个数组 nums，将数组中的元素向右轮转 k 个位置。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^5
- -2^31 <= nums[i] <= 2^31 - 1
- 0 <= k <= 10^5

示例 (Example)
-------------
输入：nums = [1,2,3,4,5,6,7], k = 3
输出：[5,6,7,1,2,3,4]
解释：向右轮转 3 位

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 通过排列元素实现右移，保持相对顺序

关键观察：
1. k 可以对 n 取模
2. 右移 k 等价于将数组拆成两段后交换顺序
3. “三次反转”可以在 O(1) 空间完成

根据这些观察，可以得到两种典型解法：
1. 三次反转（原地）
2. 额外数组或循环替换
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
将数组整体反转，再分别反转前 k 段和后 n-k 段，
即可得到右移 k 的结果。

算法流程：
1. k = k % n
2. 反转整个数组
3. 反转前 k 个元素
4. 反转后 n-k 个元素

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return;
        k %= n;
        if (k == 0) return;

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Extra Array)

优化思路
--------
使用额外数组，将 nums[i] 放到 (i+k)%n 位置。
实现简单但需要 O(n) 空间。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    void rotate(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return;
        k %= n;
        vector<int> temp(n);
        for (int i = 0; i < n; ++i) {
            temp[(i + k) % n] = nums[i];
        }
        nums.swap(temp);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1,2,3,4,5,6,7], k = 3

反转整体 -> [7,6,5,4,3,2,1]
反转前 3 -> [5,6,7,4,3,2,1]
反转后 4 -> [5,6,7,1,2,3,4]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：三次反转
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：原地、空间最优
- 缺点：需要理解反转技巧

方法二：额外数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：实现直观
- 缺点：额外空间
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = 0：数组不变
2. k >= n：需要取模
3. n = 1：数组不变
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {1,2,3,4,5,6,7};
    solution.rotate(nums1, 3);
    cout << "测试用例 1 - 输出: ";
    printVector(nums1);
    cout << " (期望: [5, 6, 7, 1, 2, 3, 4])" << endl;

    // 测试用例 2
    vector<int> nums2 = {-1,-100,3,99};
    solution.rotate(nums2, 2);
    cout << "测试用例 2 - 输出: ";
    printVector(nums2);
    cout << " (期望: [3, 99, -1, -100])" << endl;

    return 0;
}
