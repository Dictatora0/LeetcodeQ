/*
LeetCode 215. 数组中的第K个最大元素 (Kth Largest Element in an Array)

题目概述 (Problem Summary)
-------------------------
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

关键约束 (Key Constraints)
-------------------------
- 1 <= k <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4

示例 (Example)
-------------
输入：nums = [3,2,1,5,6,4], k = 2
输出：5
解释：排序后数组为 [6,5,4,3,2,1]，第 2 大的元素是 5

输入：nums = [3,2,3,1,2,4,5,5,6], k = 4
输出：4
解释：排序后数组为 [6,5,5,4,3,3,2,2,1]，第 4 大的元素是 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- Top K 问题的经典应用：在无序数组中找第 K 大的元素
- 不需要完全排序，只需要找到第 K 大的元素

关键观察：
1. 如果完全排序，时间复杂度是 O(n log n)，但题目要求 O(n)
2. 使用堆可以优化到 O(n log k)，适合 k 较小的情况
3. 使用快速选择算法可以达到平均 O(n)，最坏 O(n²)
4. Top K 问题的核心：维护 k 个最大元素，用小顶堆

为什么用小顶堆而不是大顶堆？
- 要找第 K 大的元素，维护一个大小为 k 的小顶堆
- 堆顶是这 k 个元素中最小的，也就是第 K 大的元素
- 如果新元素比堆顶大，说明堆顶不是前 k 大的，需要替换
- 如果用大顶堆，无法确定第 K 大的位置

堆的大小如何确定？
- 维护大小为 k 的小顶堆
- 堆中始终保存当前遇到的最大的 k 个元素
- 堆顶就是第 K 大的元素

堆的变化过程示例（nums = [3,2,1,5,6,4], k = 2）：
初始：heap = []
遍历 3：heap = [3]
遍历 2：heap = [2, 3]（堆满了，大小为 k=2）
遍历 1：1 < 2（堆顶），不入堆，heap = [2, 3]
遍历 5：5 > 2（堆顶），弹出 2，加入 5，heap = [3, 5]
遍历 6：6 > 3（堆顶），弹出 3，加入 6，heap = [5, 6]
遍历 4：4 < 5（堆顶），不入堆，heap = [5, 6]
结果：堆顶 5 就是第 2 大的元素

C++ priority_queue 使用技巧
---------------------------
1. 默认是大顶堆：priority_queue<int>
2. 小顶堆的三种写法：
   - priority_queue<int, vector<int>, greater<int>>
   - priority_queue<int, vector<int>, greater<>>（C++14）
   - 自定义比较器
3. 堆的基本操作：
   - push(x)：插入元素，O(log n)
   - pop()：删除堆顶，O(log n)
   - top()：访问堆顶，O(1)
   - size()：堆大小，O(1)
   - empty()：判空，O(1)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

/*
方法一：小顶堆 (Approach 1: Min Heap)

核心思想
--------
维护一个大小为 k 的小顶堆，堆中保存当前遇到的最大的 k 个元素。
遍历完数组后，堆顶就是第 k 大的元素。

算法流程：
1. 创建一个小顶堆
2. 遍历数组中的每个元素：
   a. 如果堆的大小 < k，直接将元素加入堆
   b. 如果堆的大小 = k：
      - 如果当前元素 > 堆顶，弹出堆顶，加入当前元素
      - 否则，跳过当前元素
3. 遍历结束后，堆顶就是第 k 大的元素

为什么这样做是对的？
- 小顶堆维护的是最大的 k 个元素
- 堆顶是这 k 个元素中最小的
- 所以堆顶就是第 k 大的元素

复杂度分析
---------
时间复杂度：O(n log k)
- 遍历 n 个元素：O(n)
- 每次堆操作（push/pop）：O(log k)
- 总共最多 n 次堆操作

空间复杂度：O(k)
- 堆的大小固定为 k

其中：
n = nums.length
k = 第 k 大

适用场景：
- k 远小于 n 时效率很高
- 数据流场景，可以动态维护 Top K
*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 创建小顶堆（使用 greater<int> 作为比较器）
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // 遍历数组中的每个元素
        for (int num : nums) {
            if (minHeap.size() < k) {
                // 堆未满，直接加入
                minHeap.push(num);
            } else {
                // 堆已满，判断是否需要替换堆顶
                if (num > minHeap.top()) {
                    minHeap.pop();      // 弹出堆顶（当前第 k 大中最小的）
                    minHeap.push(num);  // 加入新元素
                }
            }
        }

        // 堆顶就是第 k 大的元素
        return minHeap.top();
    }
};

/*
方法二：快速选择算法 (Approach 2: Quick Select)

核心思想
--------
基于快速排序的分区思想，每次分区后确定一个元素的最终位置。
如果这个位置正好是第 k 大的位置，直接返回；否则在对应的子数组中继续查找。

算法流程：
1. 随机选择一个基准元素（pivot）
2. 将数组分为三部分：大于 pivot、等于 pivot、小于 pivot
3. 判断第 k 大的元素在哪一部分：
   - 如果 k <= 大于 pivot 的元素个数，在左边部分查找
   - 如果 k > 大于 pivot 的元素个数 + 等于 pivot 的元素个数，在右边部分查找
   - 否则，pivot 就是第 k 大的元素
4. 递归处理对应的子数组

为什么平均时间复杂度是 O(n)？
- 第一次分区：处理 n 个元素
- 第二次分区：平均处理 n/2 个元素
- 第三次分区：平均处理 n/4 个元素
- ...
- 总时间：n + n/2 + n/4 + ... = 2n = O(n)

复杂度分析
---------
时间复杂度：平均 O(n)，最坏 O(n²)
- 平均情况：每次分区都能将问题规模减半，T(n) = T(n/2) + O(n) = O(n)
- 最坏情况：每次都选到最大或最小元素，T(n) = T(n-1) + O(n) = O(n²)
- 可以通过随机化避免最坏情况

空间复杂度：O(log n)
- 递归调用栈的深度，平均情况下为 O(log n)

优点：
- 平均时间复杂度 O(n)，满足题目要求
- 原地操作，空间效率高

缺点：
- 会修改原数组
- 最坏情况下性能退化到 O(n²)
*/
class Solution_QuickSelect {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 第 k 大 = 第 n-k+1 小（从 0 开始索引是 n-k）
        // 但这里我们直接找第 k 大
        return quickSelect(nums, 0, nums.size() - 1, k);
    }

private:
    // 在 nums[left...right] 中查找第 k 大的元素
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        // 随机选择 pivot，避免最坏情况
        int pivotIndex = left + rand() % (right - left + 1);
        int pivot = nums[pivotIndex];

        // 三路分区：将数组分为 大于、等于、小于 pivot 三部分
        vector<int> greater, equal, less;
        for (int i = left; i <= right; i++) {
            if (nums[i] > pivot) {
                greater.push_back(nums[i]);
            } else if (nums[i] == pivot) {
                equal.push_back(nums[i]);
            } else {
                less.push_back(nums[i]);
            }
        }

        // 判断第 k 大的元素在哪一部分
        if (k <= greater.size()) {
            // 在大于 pivot 的部分
            // 将 greater 复制回 nums[left...left+greater.size()-1]
            for (int i = 0; i < greater.size(); i++) {
                nums[left + i] = greater[i];
            }
            return quickSelect(nums, left, left + greater.size() - 1, k);
        } else if (k <= greater.size() + equal.size()) {
            // pivot 就是第 k 大的元素
            return pivot;
        } else {
            // 在小于 pivot 的部分
            // 将 less 复制回 nums[right-less.size()+1...right]
            int newLeft = right - less.size() + 1;
            for (int i = 0; i < less.size(); i++) {
                nums[newLeft + i] = less[i];
            }
            return quickSelect(nums, newLeft, right, k - greater.size() - equal.size());
        }
    }
};

/*
方法三：排序 (Approach 3: Sorting)

核心思想
--------
最直接的方法：对数组排序，然后返回第 k 大的元素。

算法流程：
1. 对数组进行降序排序
2. 返回索引为 k-1 的元素

复杂度分析
---------
时间复杂度：O(n log n)
- 排序的时间复杂度

空间复杂度：O(log n)
- 排序算法的递归栈空间

优点：
- 代码简单，易于实现
- 稳定可靠

缺点：
- 时间复杂度较高，不满足题目的 O(n) 要求
- 做了很多不必要的工作（完全排序）
*/
class Solution_Sort {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 降序排序
        sort(nums.begin(), nums.end(), greater<int>());
        // 返回第 k 大的元素（索引为 k-1）
        return nums[k - 1];
    }
};

/*
三种方法对比 (Comparison)
------------------------
方法一：小顶堆
- 时间复杂度：O(n log k)
- 空间复杂度：O(k)
- 适用场景：k << n，数据流场景
- 优点：k 小时效率高，不修改原数组
- 缺点：k 接近 n 时效率不如快速选择

方法二：快速选择
- 时间复杂度：平均 O(n)，最坏 O(n²)
- 空间复杂度：O(log n)
- 适用场景：需要 O(n) 时间复杂度
- 优点：平均时间复杂度最优
- 缺点：会修改原数组，最坏情况性能差

方法三：排序
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 适用场景：代码简洁性优先
- 优点：简单可靠
- 缺点：时间复杂度不是最优

推荐方案：
- 面试中：方法一（小顶堆）+ 方法二（快速选择）都要会
- 实际应用：k 小用堆，k 大用快速选择
- 题目要求 O(n)：必须用快速选择
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums = [3,2,1,5,6,4], k = 2

方法一：小顶堆
-------------
初始：minHeap = []

遍历 3：
- 堆大小 0 < k=2，直接加入
- minHeap = [3]

遍历 2：
- 堆大小 1 < k=2，直接加入
- minHeap = [2, 3]（堆顶是 2）

遍历 1：
- 堆大小 2 = k=2，堆已满
- 1 < 2（堆顶），不加入
- minHeap = [2, 3]

遍历 5：
- 堆大小 2 = k=2，堆已满
- 5 > 2（堆顶），弹出 2，加入 5
- minHeap = [3, 5]（堆顶是 3）

遍历 6：
- 堆大小 2 = k=2，堆已满
- 6 > 3（堆顶），弹出 3，加入 6
- minHeap = [5, 6]（堆顶是 5）

遍历 4：
- 堆大小 2 = k=2，堆已满
- 4 < 5（堆顶），不加入
- minHeap = [5, 6]

结果：堆顶 5 就是第 2 大的元素

方法二：快速选择
--------------
初始：nums = [3,2,1,5,6,4], k = 2

第一次分区（选择 pivot = 4）：
- greater = [5, 6]（大于 4 的元素）
- equal = [4]（等于 4 的元素）
- less = [3, 2, 1]（小于 4 的元素）
- k=2 <= greater.size()=2，在 greater 中查找第 2 大

第二次分区（在 [5, 6] 中选择 pivot = 5）：
- greater = [6]（大于 5 的元素）
- equal = [5]（等于 5 的元素）
- less = []（小于 5 的元素）
- k=2 > greater.size()=1 且 k=2 <= greater.size()+equal.size()=2
- 所以 pivot=5 就是第 2 大的元素

结果：5
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = 1（找最大值）：
   - 输入：nums = [3,2,1,5,6,4], k = 1
   - 输出：6

2. k = n（找最小值）：
   - 输入：nums = [3,2,1,5,6,4], k = 6
   - 输出：1

3. 所有元素相同：
   - 输入：nums = [5,5,5,5], k = 2
   - 输出：5

4. 只有一个元素：
   - 输入：nums = [1], k = 1
   - 输出：1

5. 包含负数：
   - 输入：nums = [-1,-2,-3], k = 2
   - 输出：-2
*/

/*
堆的原理图解 (Heap Visualization)
--------------------------------
小顶堆的性质：
- 父节点的值 <= 子节点的值
- 堆顶是最小元素
- 用数组表示：父节点 i，左子节点 2i+1，右子节点 2i+2

示例：维护大小为 3 的小顶堆，数组 [3,2,1,5,6,4]

初始：heap = []

加入 3：
    3
heap = [3]

加入 2：
    2
   /
  3
heap = [2, 3]

加入 1：
    1
   / \
  3   2
heap = [1, 3, 2]（堆满了，大小为 3）

遍历 5：5 > 1（堆顶），弹出 1，加入 5
弹出 1 后：
    2
   /
  3
heap = [2, 3]

加入 5：
    2
   / \
  3   5
heap = [2, 3, 5]

遍历 6：6 > 2（堆顶），弹出 2，加入 6
弹出 2 后：
    3
   /
  5
heap = [3, 5]

加入 6：
    3
   / \
  5   6
heap = [3, 5, 6]

遍历 4：4 > 3（堆顶），弹出 3，加入 4
最终：
    4
   / \
  5   6
heap = [4, 5, 6]

堆顶 4 就是第 3 大的元素
*/

int main() {
    Solution solution;
    Solution_QuickSelect solutionQS;
    Solution_Sort solutionSort;

    // 测试用例 1：标准情况
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    cout << "测试用例 1 - 输入: [3,2,1,5,6,4], k = 2" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums1, k1) << " (期望: 5)" << endl;

    vector<int> nums1_copy1 = nums1;
    cout << "方法二（快速选择）: " << solutionQS.findKthLargest(nums1_copy1, k1) << " (期望: 5)" << endl;

    vector<int> nums1_copy2 = nums1;
    cout << "方法三（排序）: " << solutionSort.findKthLargest(nums1_copy2, k1) << " (期望: 5)" << endl << endl;

    // 测试用例 2：有重复元素
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    cout << "测试用例 2 - 输入: [3,2,3,1,2,4,5,5,6], k = 4" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums2, k2) << " (期望: 4)" << endl << endl;

    // 测试用例 3：k = 1（找最大值）
    vector<int> nums3 = {3, 2, 1, 5, 6, 4};
    int k3 = 1;
    cout << "测试用例 3 - 输入: [3,2,1,5,6,4], k = 1" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums3, k3) << " (期望: 6)" << endl << endl;

    // 测试用例 4：k = n（找最小值）
    vector<int> nums4 = {3, 2, 1, 5, 6, 4};
    int k4 = 6;
    cout << "测试用例 4 - 输入: [3,2,1,5,6,4], k = 6" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums4, k4) << " (期望: 1)" << endl << endl;

    // 测试用例 5：所有元素相同
    vector<int> nums5 = {5, 5, 5, 5};
    int k5 = 2;
    cout << "测试用例 5 - 输入: [5,5,5,5], k = 2" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums5, k5) << " (期望: 5)" << endl << endl;

    // 测试用例 6：包含负数
    vector<int> nums6 = {-1, -2, -3};
    int k6 = 2;
    cout << "测试用例 6 - 输入: [-1,-2,-3], k = 2" << endl;
    cout << "方法一（小顶堆）: " << solution.findKthLargest(nums6, k6) << " (期望: -2)" << endl;

    return 0;
}
