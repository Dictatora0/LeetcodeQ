/*
LeetCode 11. 盛最多水的容器 (Container With Most Water)

题目概述 (Problem Summary)
-------------------------
给定一个长度为 n 的整数数组 height。有 n 条垂直线,第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。

找出其中的两条线,使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

注意:你不能倾斜容器。

关键约束 (Key Constraints)
-------------------------
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4

示例 (Example)
-------------
输入:height = [1,8,6,2,5,4,8,3,7]
输出:49
解释:图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。
在此情况下,容器能够容纳水(蓝色部分)的最大值为 49。

输入:height = [1,1]
输出:1

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题?
- 找到两条线,使得它们与 x 轴构成的容器面积最大

关键观察:
1. 容器的面积 = 两条线之间的距离 × 两条线中较短的那条
   - area = (right - left) × min(height[left], height[right])
2. 暴力解法:枚举所有可能的两条线,时间复杂度 O(n²)
3. 优化思路:使用双指针从两端向中间移动

核心技巧:双指针 + 贪心策略
- 初始化:left=0, right=n-1(最大宽度)
- 每次移动较短的那条线:
  * 如果 height[left] < height[right],移动 left++
  * 否则,移动 right--
- 为什么要移动较短的线?
  * 容器的高度由较短的线决定
  * 移动较长的线,宽度减小,高度不会增加,面积一定减小
  * 移动较短的线,虽然宽度减小,但高度可能增加,面积可能增大

为什么这个贪心策略正确?
- 假设 height[left] < height[right]
- 如果移动 right,新的面积 = (right-1-left) × min(height[left], height[right-1])
  * 宽度减小:(right-1-left) < (right-left)
  * 高度不会增加:min(height[left], height[right-1]) <= height[left]
  * 所以面积一定减小
- 如果移动 left,新的面积 = (right-left-1) × min(height[left+1], height[right])
  * 宽度减小,但高度可能增加(如果 height[left+1] > height[left])
  * 面积可能增大

根据这些观察,可以得到双指针解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一:双指针解法 (Approach 1: Two Pointers)

核心思想
--------
使用双指针从两端向中间移动,每次移动较短的那条线。

算法流程:
1. 初始化 left=0, right=n-1
2. 初始化 maxArea=0
3. 当 left < right 时循环:
   a. 计算当前面积:area = (right - left) × min(height[left], height[right])
   b. 更新最大面积:maxArea = max(maxArea, area)
   c. 移动较短的线:
      - 如果 height[left] < height[right],left++
      - 否则,right--
4. 返回 maxArea

为什么这个算法正确?
- 双指针保证了从最大宽度开始搜索
- 贪心策略保证了不会错过最优解
- 每次移动都是向可能更优的方向前进

复杂度分析
---------
时间复杂度:O(n),每个元素最多被访问一次
空间复杂度:O(1),只使用常数额外空间
*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxArea = 0;

        // 双指针从两端向中间移动
        while (left < right) {
            // 计算当前容器的面积
            // 宽度 = right - left
            // 高度 = 两条线中较短的那条
            int width = right - left;
            int h = min(height[left], height[right]);
            int area = width * h;

            // 更新最大面积
            maxArea = max(maxArea, area);

            // 关键:移动较短的那条线
            // 为什么?因为容器的高度由较短的线决定
            // 移动较长的线,宽度减小,高度不会增加,面积一定减小
            // 移动较短的线,宽度减小,但高度可能增加,面积可能增大
            if (height[left] < height[right]) {
                left++;   // 左边的线较短,移动左指针
            } else {
                right--;  // 右边的线较短或相等,移动右指针
            }
        }

        return maxArea;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
height = [1,8,6,2,5,4,8,3,7]

第 1 轮:
- left=0, right=8
- height[0]=1, height[8]=7
- area = 8 × min(1,7) = 8 × 1 = 8
- maxArea = 8
- height[0] < height[8],移动 left,left=1

第 2 轮:
- left=1, right=8
- height[1]=8, height[8]=7
- area = 7 × min(8,7) = 7 × 7 = 49
- maxArea = 49
- height[1] > height[8],移动 right,right=7

第 3 轮:
- left=1, right=7
- height[1]=8, height[7]=3
- area = 6 × min(8,3) = 6 × 3 = 18
- maxArea = 49
- height[1] > height[7],移动 right,right=6

第 4 轮:
- left=1, right=6
- height[1]=8, height[6]=8
- area = 5 × min(8,8) = 5 × 8 = 40
- maxArea = 49
- height[1] == height[6],移动 right,right=5

第 5 轮:
- left=1, right=5
- height[1]=8, height[5]=4
- area = 4 × min(8,4) = 4 × 4 = 16
- maxArea = 49
- height[1] > height[5],移动 right,right=4

第 6 轮:
- left=1, right=4
- height[1]=8, height[4]=5
- area = 3 × min(8,5) = 3 × 5 = 15
- maxArea = 49
- height[1] > height[4],移动 right,right=3

第 7 轮:
- left=1, right=3
- height[1]=8, height[3]=2
- area = 2 × min(8,2) = 2 × 2 = 4
- maxArea = 49
- height[1] > height[3],移动 right,right=2

第 8 轮:
- left=1, right=2
- height[1]=8, height[2]=6
- area = 1 × min(8,6) = 1 × 6 = 6
- maxArea = 49
- height[1] > height[2],移动 right,right=1

第 9 轮:
- left=1, right=1, left >= right
- 循环结束

返回 maxArea = 49
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有两条线:直接计算面积
2. 所有线高度相同:面积 = (n-1) × height[0]
3. 高度递增或递减:最大面积在两端
*/

/*
关键点总结 (Key Points)
---------------------
1. 容器面积 = 宽度 × 高度(较短的线)
2. 双指针从两端开始,保证初始宽度最大
3. 贪心策略:每次移动较短的线
4. 为什么移动较短的线?
   - 移动较长的线:宽度↓,高度不变或↓,面积一定↓
   - 移动较短的线:宽度↓,高度可能↑,面积可能↑
5. 时间复杂度 O(n),比暴力解法 O(n²) 快得多
6. 这是一个经典的双指针 + 贪心问题
*/

int main() {
    Solution solution;

    // 测试用例 1:标准情况
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int result1 = solution.maxArea(height1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 49)" << endl;

    // 测试用例 2:只有两条线
    vector<int> height2 = {1, 1};
    int result2 = solution.maxArea(height2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 1)" << endl;

    // 测试用例 3:高度递增
    vector<int> height3 = {1, 2, 3, 4, 5};
    int result3 = solution.maxArea(height3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: 6)" << endl;
    // 解释:最大面积在 height[0]=1 和 height[4]=5 之间,area = 4 × 1 = 4
    // 或者 height[1]=2 和 height[4]=5 之间,area = 3 × 2 = 6

    // 测试用例 4:所有线高度相同
    vector<int> height4 = {5, 5, 5, 5};
    int result4 = solution.maxArea(height4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 15)" << endl;
    // 解释:最大面积在两端,area = 3 × 5 = 15

    // 测试用例 5:高度差异大
    vector<int> height5 = {1, 2, 1};
    int result5 = solution.maxArea(height5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 2)" << endl;
    // 解释:最大面积在 height[0]=1 和 height[2]=1 之间,area = 2 × 1 = 2

    return 0;
}
