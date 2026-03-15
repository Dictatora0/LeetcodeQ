/*
LeetCode 373. 查找和最小的 K 对数字 (Find K Pairs with Smallest Sums)

题目概述 (Problem Summary)
-------------------------
给定两个以升序排列的整数数组 nums1 和 nums2，以及一个整数 k。
定义一对值 (u, v)，其中第一个元素来自 nums1，第二个元素来自 nums2。
请找到和最小的 k 对数字 (u1, v1), (u2, v2) ... (uk, vk)。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums1.length, nums2.length <= 10^5
- -10^9 <= nums1[i], nums2[i] <= 10^9
- nums1 和 nums2 均为升序排列
- 1 <= k <= 10^4
- k <= nums1.length * nums2.length

示例 (Example)
-------------
输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出：[[1,2],[1,4],[1,6]]
解释：返回序列中的前 3 对数：
[1,2], [1,4], [1,6], [7,2], [7,4], [11,2], [7,6], [11,4], [11,6]

输入：nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出：[[1,1],[1,1]]
解释：返回序列中的前 2 对数：
[1,1], [1,1], [1,2], [1,2], [1,3], [1,3], [2,1], [2,2], [2,3]

输入：nums1 = [1,2], nums2 = [3], k = 3
输出：[[1,3],[2,3]]
解释：也可以返回 [[1,3],[2,3]]，因为只有 2 对数字

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在两个有序数组的笛卡尔积中，找和最小的 k 对数字
- 类似于合并 k 个有序链表，但这里是二维的

关键观察：
1. 如果暴力枚举所有对，有 m*n 对，然后排序取前 k 个，时间 O(mn log(mn))
2. 利用数组有序的性质：nums1[i] + nums2[j] <= nums1[i+1] + nums2[j]
3. 可以用小顶堆维护当前和最小的候选对
4. 每次取出和最小的对，将其"下一个"候选对加入堆

为什么用小顶堆？
- 需要快速找到当前和最小的对
- 小顶堆的堆顶就是和最小的对，O(1) 时间
- 取出后，将相关的候选对加入堆，O(log k) 时间

堆的大小如何确定？
- 最多 k 个元素（候选对）
- 实际大小 <= min(k, m, n)

如何避免重复？
- 关键问题：同一对 (i, j) 可能从多个路径到达
- 解决方案 1：使用 set 记录已访问的对（空间 O(k)）
- 解决方案 2：优化入堆策略，只从 (i, j) 扩展到 (i+1, j)，初始时将所有 (i, 0) 加入堆

堆的变化过程示例（nums1 = [1,7,11], nums2 = [2,4,6], k = 3）：
初始：heap = [(1,2,索引0,0), (7,2,索引1,0), (11,2,索引2,0)]
      （只加入 (i, 0) 的对，避免重复）

取出 (1,2)，加入 (1,4)：
heap = [(1,4,索引0,1), (7,2,索引1,0), (11,2,索引2,0)]

取出 (1,4)，加入 (1,6)：
heap = [(1,6,索引0,2), (7,2,索引1,0), (11,2,索引2,0)]

取出 (1,6)，nums1[0] 的所有对都已处理：
heap = [(7,2,索引1,0), (11,2,索引2,0)]

结果：[[1,2], [1,4], [1,6]]

C++ priority_queue 存储对信息
-----------------------------
1. 使用 tuple<int, int, int> 存储 (和, nums1索引, nums2索引)
2. 或使用 struct 存储对的信息
3. 自定义比较器，按和排序
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

/*
方法一：小顶堆 + 优化（避免重复）(Approach 1: Min Heap + Optimized)

核心思想
--------
使用小顶堆维护候选对，每次取出和最小的对。
优化：只从 (i, j) 扩展到 (i, j+1)，初始时将所有 (i, 0) 加入堆，避免重复。

算法流程：
1. 将所有 (i, 0) 对加入堆（i 从 0 到 min(k, m)-1）
   - 为什么只加入前 k 个？因为最多需要 k 对，后面的不可能是前 k 小
2. 循环 k 次（或直到堆为空）：
   a. 取出堆顶对 (i, j)
   b. 将该对加入结果
   c. 如果 j+1 < n，将 (i, j+1) 加入堆
3. 返回结果

为什么这样不会重复？
- 每个 (i, j) 只会从 (i, j-1) 扩展而来
- 初始时加入所有 (i, 0)，保证所有对都能被访问到
- 不会有两条路径到达同一个 (i, j)

为什么初始只加入前 k 个 (i, 0)？
- 如果 nums1[k] + nums2[0] 已经很大，后面的对不可能是前 k 小
- 优化：减少堆的初始大小

复杂度分析
---------
时间复杂度：O(k log k)
- 初始化堆：O(min(k, m) log k)
- 取出 k 个对：O(k log k)
- 总时间：O(k log k)

空间复杂度：O(k)
- 堆的大小最多为 k

其中：
m = nums1.length
n = nums2.length
k = 需要的对数

优点：
- 时间复杂度优秀，O(k log k)
- 不需要 set 记录已访问的对
- 代码简洁

缺点：
- 需要理解扩展策略
*/
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> result;

        // 小顶堆：存储 (和, nums1索引, nums2索引)
        // 按和排序，和小的优先级高
        auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<0>(a) > get<0>(b);  // 和大的优先级低
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> minHeap(cmp);

        // 初始化：将所有 (i, 0) 加入堆（i 从 0 到 min(k, m)-1）
        for (int i = 0; i < min(k, m); i++) {
            minHeap.push({nums1[i] + nums2[0], i, 0});
        }

        // 取出 k 个和最小的对
        while (k > 0 && !minHeap.empty()) {
            auto [sum, i, j] = minHeap.top();
            minHeap.pop();

            // 将该对加入结果
            result.push_back({nums1[i], nums2[j]});
            k--;

            // 如果 j+1 < n，将 (i, j+1) 加入堆
            if (j + 1 < n) {
                minHeap.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }

        return result;
    }
};

/*
方法二：小顶堆（朴素版本，使用 set 避免重复）(Approach 2: Min Heap with Set)

核心思想
--------
使用小顶堆维护候选对，使用 set 记录已访问的对，避免重复。

算法流程：
1. 将 (0, 0) 加入堆和 set
2. 循环 k 次（或直到堆为空）：
   a. 取出堆顶对 (i, j)
   b. 将该对加入结果
   c. 尝试将 (i+1, j) 和 (i, j+1) 加入堆（如果未访问过）
3. 返回结果

复杂度分析
---------
时间复杂度：O(k log k)
- 取出 k 个对：O(k log k)
- set 操作：O(k log k)
- 总时间：O(k log k)

空间复杂度：O(k)
- 堆：O(k)
- set：O(k)

优点：
- 逻辑直观，易于理解
- 可以处理各种扩展策略

缺点：
- 需要额外的 set 空间
- 代码稍复杂
*/
class Solution_Set {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> result;

        // 小顶堆：存储 (和, nums1索引, nums2索引)
        auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<0>(a) > get<0>(b);
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> minHeap(cmp);

        // set 记录已访问的对（避免重复）
        set<pair<int, int>> visited;

        // 初始化：将 (0, 0) 加入堆
        minHeap.push({nums1[0] + nums2[0], 0, 0});
        visited.insert({0, 0});

        // 取出 k 个和最小的对
        while (k > 0 && !minHeap.empty()) {
            auto [sum, i, j] = minHeap.top();
            minHeap.pop();

            // 将该对加入结果
            result.push_back({nums1[i], nums2[j]});
            k--;

            // 尝试将 (i+1, j) 加入堆
            if (i + 1 < m && visited.find({i + 1, j}) == visited.end()) {
                minHeap.push({nums1[i + 1] + nums2[j], i + 1, j});
                visited.insert({i + 1, j});
            }

            // 尝试将 (i, j+1) 加入堆
            if (j + 1 < n && visited.find({i, j + 1}) == visited.end()) {
                minHeap.push({nums1[i] + nums2[j + 1], i, j + 1});
                visited.insert({i, j + 1});
            }
        }

        return result;
    }
};

/*
两种方法对比 (Comparison)
------------------------
方法一：小顶堆 + 优化
- 时间复杂度：O(k log k)
- 空间复杂度：O(k)
- 适用场景：标准解法，推荐使用
- 优点：不需要 set，空间效率高
- 缺点：需要理解扩展策略

方法二：小顶堆 + set
- 时间复杂度：O(k log k)
- 空间复杂度：O(k)
- 适用场景：逻辑直观，易于理解
- 优点：扩展策略灵活
- 缺点：需要额外的 set 空间

推荐方案：
- 面试中：方法一（优化版本）更优
- 理解困难：可以先实现方法二，再优化到方法一
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 3

方法一：小顶堆 + 优化
-------------------
初始化：将所有 (i, 0) 加入堆
minHeap = [
    (1+2=3, 0, 0),
    (7+2=9, 1, 0),
    (11+2=13, 2, 0)
]
堆顶：(3, 0, 0)

第 1 次取出：
- 取出 (3, 0, 0)，即 [1, 2]
- result = [[1, 2]]
- 加入 (0, 1)：(1+4=5, 0, 1)
- minHeap = [(5, 0, 1), (9, 1, 0), (13, 2, 0)]

第 2 次取出：
- 取出 (5, 0, 1)，即 [1, 4]
- result = [[1, 2], [1, 4]]
- 加入 (0, 2)：(1+6=7, 0, 2)
- minHeap = [(7, 0, 2), (9, 1, 0), (13, 2, 0)]

第 3 次取出：
- 取出 (7, 0, 2)，即 [1, 6]
- result = [[1, 2], [1, 4], [1, 6]]
- j+1 = 3 >= n，不加入新对
- minHeap = [(9, 1, 0), (13, 2, 0)]

结果：[[1, 2], [1, 4], [1, 6]]

方法二：小顶堆 + set
------------------
初始化：将 (0, 0) 加入堆
minHeap = [(3, 0, 0)]
visited = {(0, 0)}

第 1 次取出：
- 取出 (3, 0, 0)，即 [1, 2]
- result = [[1, 2]]
- 尝试加入 (1, 0)：(9, 1, 0)，未访问过，加入
- 尝试加入 (0, 1)：(5, 0, 1)，未访问过，加入
- minHeap = [(5, 0, 1), (9, 1, 0)]
- visited = {(0, 0), (1, 0), (0, 1)}

第 2 次取出：
- 取出 (5, 0, 1)，即 [1, 4]
- result = [[1, 2], [1, 4]]
- 尝试加入 (1, 1)：(11, 1, 1)，未访问过，加入
- 尝试加入 (0, 2)：(7, 0, 2)，未访问过，加入
- minHeap = [(7, 0, 2), (9, 1, 0), (11, 1, 1)]
- visited = {(0, 0), (1, 0), (0, 1), (1, 1), (0, 2)}

第 3 次取出：
- 取出 (7, 0, 2)，即 [1, 6]
- result = [[1, 2], [1, 4], [1, 6]]

结果：[[1, 2], [1, 4], [1, 6]]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k 大于所有对的数量：
   - 输入：nums1 = [1,2], nums2 = [3], k = 3
   - 输出：[[1,3],[2,3]]（只有 2 对）

2. 一个数组只有一个元素：
   - 输入：nums1 = [1], nums2 = [1,2,3], k = 2
   - 输出：[[1,1],[1,2]]

3. 两个数组都只有一个元素：
   - 输入：nums1 = [1], nums2 = [2], k = 1
   - 输出：[[1,2]]

4. k = 1：
   - 输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 1
   - 输出：[[1,2]]

5. 包含负数：
   - 输入：nums1 = [-1,0,1], nums2 = [-1,0,1], k = 3
   - 输出：[[-1,-1],[-1,0],[0,-1]] 或 [[-1,-1],[-1,0],[-1,1]]

6. 有重复元素：
   - 输入：nums1 = [1,1,2], nums2 = [1,2,3], k = 2
   - 输出：[[1,1],[1,1]]
*/

/*
堆的原理图解 (Heap Visualization)
--------------------------------
小顶堆（存储对的和）的性质：
- 父节点的和 <= 子节点的和
- 堆顶是和最小的对

示例：nums1 = [1,7,11], nums2 = [2,4,6], k = 3

初始堆（存储 (i, 0) 的对）：
        (3, 0, 0)
       /          \
   (9, 1, 0)    (13, 2, 0)

取出 (3, 0, 0)，加入 (5, 0, 1)：
        (5, 0, 1)
       /          \
   (9, 1, 0)    (13, 2, 0)

取出 (5, 0, 1)，加入 (7, 0, 2)：
        (7, 0, 2)
       /          \
   (9, 1, 0)    (13, 2, 0)

取出 (7, 0, 2)：
        (9, 1, 0)
           \
         (13, 2, 0)

扩展策略图解：
nums1 = [1, 7, 11]
nums2 = [2, 4, 6]

所有可能的对（按和排序）：
(0,0):3  (0,1):5  (0,2):7
(1,0):9  (1,1):11 (1,2):13
(2,0):13 (2,1):15 (2,2):17

扩展路径（方法一）：
初始：(0,0), (1,0), (2,0)
从 (0,0) 扩展到 (0,1)
从 (0,1) 扩展到 (0,2)
从 (1,0) 扩展到 (1,1)
...

每个对只从左边扩展而来，不会重复
*/

/*
多指针优化的思想 (Multi-Pointer Optimization)
-------------------------------------------
为什么方法一不会重复？

可以把问题看作 m 个有序链表的合并：
- 链表 0：(0,0) -> (0,1) -> (0,2) -> ...
- 链表 1：(1,0) -> (1,1) -> (1,2) -> ...
- 链表 2：(2,0) -> (2,1) -> (2,2) -> ...

每个链表都是有序的（和递增）
我们要合并这 m 个有序链表，找前 k 个最小的元素

这就是"合并 k 个有序链表"的问题！
- 初始时，将所有链表的头节点加入堆
- 每次取出堆顶，将其下一个节点加入堆
- 不会重复，因为每个节点只会被访问一次

这就是方法一的核心思想：将二维问题转化为一维的多路归并问题
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    cout << "测试用例 1 - 标准情况" << endl;
    vector<int> nums1_1 = {1, 7, 11};
    vector<int> nums2_1 = {2, 4, 6};
    int k1 = 3;
    vector<vector<int>> result1 = solution.kSmallestPairs(nums1_1, nums2_1, k1);
    cout << "输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 3" << endl;
    cout << "输出：[";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[[1,2],[1,4],[1,6]]" << endl << endl;

    // 测试用例 2：有重复元素
    cout << "测试用例 2 - 有重复元素" << endl;
    vector<int> nums1_2 = {1, 1, 2};
    vector<int> nums2_2 = {1, 2, 3};
    int k2 = 2;
    vector<vector<int>> result2 = solution.kSmallestPairs(nums1_2, nums2_2, k2);
    cout << "输入：nums1 = [1,1,2], nums2 = [1,2,3], k = 2" << endl;
    cout << "输出：[";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[[1,1],[1,1]]" << endl << endl;

    // 测试用例 3：k 大于所有对的数量
    cout << "测试用例 3 - k 大于所有对的数量" << endl;
    vector<int> nums1_3 = {1, 2};
    vector<int> nums2_3 = {3};
    int k3 = 3;
    vector<vector<int>> result3 = solution.kSmallestPairs(nums1_3, nums2_3, k3);
    cout << "输入：nums1 = [1,2], nums2 = [3], k = 3" << endl;
    cout << "输出：[";
    for (int i = 0; i < result3.size(); i++) {
        cout << "[" << result3[i][0] << "," << result3[i][1] << "]";
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[[1,3],[2,3]]" << endl << endl;

    // 测试用例 4：k = 1
    cout << "测试用例 4 - k = 1" << endl;
    vector<int> nums1_4 = {1, 7, 11};
    vector<int> nums2_4 = {2, 4, 6};
    int k4 = 1;
    vector<vector<int>> result4 = solution.kSmallestPairs(nums1_4, nums2_4, k4);
    cout << "输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 1" << endl;
    cout << "输出：[";
    for (int i = 0; i < result4.size(); i++) {
        cout << "[" << result4[i][0] << "," << result4[i][1] << "]";
        if (i < result4.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[[1,2]]" << endl << endl;

    // 测试用例 5：包含负数
    cout << "测试用例 5 - 包含负数" << endl;
    vector<int> nums1_5 = {-1, 0, 1};
    vector<int> nums2_5 = {-1, 0, 1};
    int k5 = 3;
    vector<vector<int>> result5 = solution.kSmallestPairs(nums1_5, nums2_5, k5);
    cout << "输入：nums1 = [-1,0,1], nums2 = [-1,0,1], k = 3" << endl;
    cout << "输出：[";
    for (int i = 0; i < result5.size(); i++) {
        cout << "[" << result5[i][0] << "," << result5[i][1] << "]";
        if (i < result5.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望：[[-1,-1],[-1,0],[0,-1]] 或类似" << endl;

    return 0;
}
