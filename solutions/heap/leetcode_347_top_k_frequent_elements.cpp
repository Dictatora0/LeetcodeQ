/*
LeetCode 347. 前 K 个高频元素 (Top K Frequent Elements)

题目概述 (Problem Summary)
-------------------------
给你一个整数数组 nums 和一个整数 k，请你返回其中出现频率前 k 高的元素。
你可以按任意顺序返回答案。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k 的取值范围是 [1, 数组中不相同的元素的个数]
- 题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

你必须设计并实现时间复杂度优于 O(n log n) 的算法。

示例 (Example)
-------------
输入：nums = [1,1,1,2,2,3], k = 2
输出：[1,2]
解释：1 出现 3 次，2 出现 2 次，3 出现 1 次，前 2 个高频元素是 1 和 2

输入：nums = [1], k = 1
输出：[1]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- Top K 问题的变种：不是找第 K 大的值，而是找频率前 K 高的元素
- 需要先统计频率，再找 Top K

关键观察：
1. 需要两步：统计频率 + 找 Top K
2. 统计频率用哈希表，时间 O(n)
3. 找 Top K 可以用堆、桶排序、快速选择
4. 题目要求时间复杂度优于 O(n log n)

为什么用小顶堆？
- 维护大小为 k 的小顶堆（按频率排序）
- 堆中保存频率最高的 k 个元素
- 堆顶是这 k 个元素中频率最低的
- 如果新元素频率更高，替换堆顶

堆的大小如何确定？
- 固定为 k
- 堆中始终保存频率最高的 k 个元素
- 遍历完所有元素后，堆中就是答案

堆的变化过程示例（nums = [1,1,1,2,2,3], k = 2）：
统计频率：{1:3, 2:2, 3:1}

遍历频率表：
- (1, 3)：heap = [(1, 3)]
- (2, 2)：heap = [(2, 2), (1, 3)]（堆满了）
- (3, 1)：1 < 2（堆顶频率），不入堆

结果：heap = [(2, 2), (1, 3)]，答案是 [1, 2]

C++ priority_queue 自定义比较器
-------------------------------
1. 使用 lambda 表达式（C++11）：
   auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
       return a.second > b.second;  // 小顶堆
   };
   priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

2. 使用函数对象：
   struct Compare {
       bool operator()(pair<int,int>& a, pair<int,int>& b) {
           return a.second > b.second;
       }
   };
   priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> pq;

3. 注意：priority_queue 的比较器是"反"的
   - 返回 true 表示 a 的优先级低于 b
   - 小顶堆：return a > b（大的优先级低）
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/*
方法一：小顶堆 + 哈希表 (Approach 1: Min Heap + Hash Map)

核心思想
--------
先用哈希表统计每个元素的频率，然后用小顶堆维护频率最高的 k 个元素。

算法流程：
1. 用哈希表统计每个元素的出现频率
2. 创建一个小顶堆（按频率排序）
3. 遍历哈希表：
   a. 如果堆的大小 < k，直接加入
   b. 如果堆的大小 = k：
      - 如果当前元素频率 > 堆顶频率，弹出堆顶，加入当前元素
      - 否则，跳过
4. 将堆中的元素提取出来作为结果

为什么用小顶堆而不是大顶堆？
- 要维护频率最高的 k 个元素
- 小顶堆的堆顶是这 k 个元素中频率最低的
- 当新元素频率更高时，可以替换堆顶
- 如果用大顶堆，无法判断是否需要替换

复杂度分析
---------
时间复杂度：O(n log k)
- 统计频率：O(n)
- 遍历哈希表：O(m)，m 是不同元素的个数，m <= n
- 每次堆操作：O(log k)
- 总共最多 m 次堆操作：O(m log k)
- 总时间：O(n + m log k) = O(n log k)（因为 m <= n）

空间复杂度：O(n)
- 哈希表：O(m)，m <= n
- 堆：O(k)
- 总空间：O(n)

其中：
n = nums.length
k = 前 k 个高频元素
m = 不同元素的个数

优点：
- 时间复杂度 O(n log k)，满足题目要求
- k 较小时效率很高
- 适合数据流场景
*/
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 步骤 1：统计每个元素的频率
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        // 步骤 2：创建小顶堆（按频率排序）
        // pair<元素值, 频率>
        // 比较器：频率小的优先级高（小顶堆）
        auto cmp = [](pair<int, int>& a, pair<int, int>& b) {
            return a.second > b.second;  // 频率大的优先级低
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

        // 步骤 3：遍历哈希表，维护大小为 k 的小顶堆
        for (auto& [num, freq] : freqMap) {
            if (minHeap.size() < k) {
                // 堆未满，直接加入
                minHeap.push({num, freq});
            } else {
                // 堆已满，判断是否需要替换堆顶
                if (freq > minHeap.top().second) {
                    minHeap.pop();
                    minHeap.push({num, freq});
                }
            }
        }

        // 步骤 4：提取堆中的元素
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }

        return result;
    }
};

/*
方法二：桶排序 (Approach 2: Bucket Sort)

核心思想
--------
利用频率的范围有限（最多 n），用桶排序的思想，将相同频率的元素放在同一个桶中。
然后从高频到低频遍历桶，取出前 k 个元素。

算法流程：
1. 用哈希表统计每个元素的频率
2. 创建 n+1 个桶，桶 i 存储频率为 i 的所有元素
3. 将元素按频率放入对应的桶中
4. 从高频到低频遍历桶，取出前 k 个元素

为什么桶的大小是 n+1？
- 频率的范围是 [1, n]
- 需要 n+1 个桶（索引 0 到 n）
- 索引 i 的桶存储频率为 i 的元素

复杂度分析
---------
时间复杂度：O(n)
- 统计频率：O(n)
- 建立桶：O(m)，m 是不同元素的个数
- 遍历桶：O(n)
- 总时间：O(n)

空间复杂度：O(n)
- 哈希表：O(m)
- 桶数组：O(n)
- 总空间：O(n)

优点：
- 时间复杂度 O(n)，最优
- 不需要排序或堆操作

缺点：
- 空间复杂度较高（需要 n 个桶）
- 只适用于频率范围有限的情况
*/
class Solution_Bucket {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();

        // 步骤 1：统计频率
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        // 步骤 2：创建桶，bucket[i] 存储频率为 i 的所有元素
        vector<vector<int>> bucket(n + 1);
        for (auto& [num, freq] : freqMap) {
            bucket[freq].push_back(num);
        }

        // 步骤 3：从高频到低频遍历桶，取出前 k 个元素
        vector<int> result;
        for (int freq = n; freq >= 1 && result.size() < k; freq--) {
            for (int num : bucket[freq]) {
                result.push_back(num);
                if (result.size() == k) {
                    break;
                }
            }
        }

        return result;
    }
};

/*
方法三：快速选择 (Approach 3: Quick Select)

核心思想
--------
将频率问题转化为第 K 大问题，使用快速选择算法。

算法流程：
1. 统计频率，得到 (元素, 频率) 对
2. 对这些对使用快速选择，找到频率第 k 大的分界点
3. 返回频率 >= 分界点的所有元素

复杂度分析
---------
时间复杂度：平均 O(n)，最坏 O(n²)
- 统计频率：O(n)
- 快速选择：平均 O(m)，m 是不同元素的个数
- 总时间：平均 O(n)

空间复杂度：O(n)
- 哈希表：O(m)
- 辅助数组：O(m)

优点：
- 平均时间复杂度 O(n)
- 不需要完全排序

缺点：
- 实现较复杂
- 最坏情况性能差
*/
class Solution_QuickSelect {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 步骤 1：统计频率
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        // 步骤 2：将 (元素, 频率) 对转换为数组
        vector<pair<int, int>> freqArray;
        for (auto& [num, freq] : freqMap) {
            freqArray.push_back({num, freq});
        }

        // 步骤 3：使用快速选择找到频率第 k 大的元素
        // 注意：这里我们找的是第 k 大，所以是 k-1 索引（降序）
        quickSelect(freqArray, 0, freqArray.size() - 1, k);

        // 步骤 4：提取前 k 个元素
        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(freqArray[i].first);
        }

        return result;
    }

private:
    // 快速选择：将频率前 k 大的元素放在数组前 k 个位置
    void quickSelect(vector<pair<int, int>>& arr, int left, int right, int k) {
        if (left >= right) return;

        // 随机选择 pivot
        int pivotIndex = left + rand() % (right - left + 1);
        int pivotFreq = arr[pivotIndex].second;

        // 三路分区
        int i = left, j = left, t = right;
        while (j <= t) {
            if (arr[j].second > pivotFreq) {
                swap(arr[i++], arr[j++]);
            } else if (arr[j].second < pivotFreq) {
                swap(arr[j], arr[t--]);
            } else {
                j++;
            }
        }

        // 判断 k 在哪个区间
        if (k <= i - left) {
            quickSelect(arr, left, i - 1, k);
        } else if (k > j - left) {
            quickSelect(arr, j, right, k - (j - left));
        }
        // 否则，前 k 个元素已经在正确位置
    }
};

/*
三种方法对比 (Comparison)
------------------------
方法一：小顶堆 + 哈希表
- 时间复杂度：O(n log k)
- 空间复杂度：O(n)
- 适用场景：k 较小，数据流场景
- 优点：实现简单，k 小时效率高
- 缺点：k 大时不如桶排序

方法二：桶排序
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 适用场景：需要 O(n) 时间复杂度
- 优点：时间复杂度最优
- 缺点：空间复杂度较高

方法三：快速选择
- 时间复杂度：平均 O(n)，最坏 O(n²)
- 空间复杂度：O(n)
- 适用场景：需要 O(n) 平均时间
- 优点：平均时间复杂度优秀
- 缺点：实现复杂，最坏情况差

推荐方案：
- 面试中：方法一（小顶堆）最常用，易于实现和理解
- 追求极致性能：方法二（桶排序）
- 大数据场景：方法一（堆）适合流式处理
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums = [1,1,1,2,2,3], k = 2

方法一：小顶堆 + 哈希表
---------------------
步骤 1：统计频率
freqMap = {1: 3, 2: 2, 3: 1}

步骤 2：创建小顶堆（按频率排序）
minHeap = []

步骤 3：遍历哈希表
遍历 (1, 3)：
- 堆大小 0 < k=2，直接加入
- minHeap = [(1, 3)]

遍历 (2, 2)：
- 堆大小 1 < k=2，直接加入
- minHeap = [(2, 2), (1, 3)]（堆顶是 (2, 2)，频率为 2）

遍历 (3, 1)：
- 堆大小 2 = k=2，堆已满
- 1 < 2（堆顶频率），不加入
- minHeap = [(2, 2), (1, 3)]

步骤 4：提取结果
result = [2, 1]（顺序可能不同）

方法二：桶排序
------------
步骤 1：统计频率
freqMap = {1: 3, 2: 2, 3: 1}

步骤 2：创建桶
bucket[0] = []
bucket[1] = [3]（频率为 1 的元素）
bucket[2] = [2]（频率为 2 的元素）
bucket[3] = [1]（频率为 3 的元素）
bucket[4] = []
bucket[5] = []
bucket[6] = []

步骤 3：从高频到低频遍历桶
遍历 bucket[6] 到 bucket[4]：都是空的
遍历 bucket[3]：取出 1，result = [1]
遍历 bucket[2]：取出 2，result = [1, 2]（已经有 k=2 个元素）

结果：[1, 2]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：
   - 输入：nums = [1], k = 1
   - 输出：[1]

2. 所有元素相同：
   - 输入：nums = [1,1,1,1], k = 1
   - 输出：[1]

3. k 等于不同元素的个数：
   - 输入：nums = [1,2,3], k = 3
   - 输出：[1,2,3]（顺序可能不同）

4. 多个元素频率相同：
   - 输入：nums = [1,1,2,2,3,3], k = 2
   - 输出：任意两个元素（题目保证答案唯一，所以不会出现这种情况）

5. 包含负数：
   - 输入：nums = [-1,-1,2,2,2], k = 1
   - 输出：[2]
*/

/*
堆的原理图解 (Heap Visualization)
--------------------------------
小顶堆（按频率排序）的性质：
- 父节点的频率 <= 子节点的频率
- 堆顶是频率最小的元素

示例：nums = [1,1,1,2,2,3,4,4,4,4], k = 2
统计频率：{1:3, 2:2, 3:1, 4:4}

维护大小为 2 的小顶堆：

遍历 (1, 3)：
    (1,3)
heap = [(1,3)]

遍历 (2, 2)：
    (2,2)
     /
   (1,3)
heap = [(2,2), (1,3)]（堆满了）

遍历 (3, 1)：
- 1 < 2（堆顶频率），不加入
heap = [(2,2), (1,3)]

遍历 (4, 4)：
- 4 > 2（堆顶频率），弹出 (2,2)，加入 (4,4)
弹出后：
    (1,3)
heap = [(1,3)]

加入 (4,4)：
    (1,3)
     /
   (4,4)
heap = [(1,3), (4,4)]

但实际上堆会自动调整，最终：
    (3,3)
     /
   (4,4)
heap = [(3,3), (4,4)]

结果：频率最高的 2 个元素是 4 和 1
*/

int main() {
    Solution solution;
    Solution_Bucket solutionBucket;
    Solution_QuickSelect solutionQS;

    // 测试用例 1：标准情况
    vector<int> nums1 = {1, 1, 1, 2, 2, 3};
    int k1 = 2;
    cout << "测试用例 1 - 输入: [1,1,1,2,2,3], k = 2" << endl;
    vector<int> result1 = solution.topKFrequent(nums1, k1);
    cout << "方法一（小顶堆）: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "] (期望: [1,2] 或 [2,1])" << endl;

    vector<int> nums1_copy = nums1;
    vector<int> result1_bucket = solutionBucket.topKFrequent(nums1_copy, k1);
    cout << "方法二（桶排序）: [";
    for (int i = 0; i < result1_bucket.size(); i++) {
        cout << result1_bucket[i];
        if (i < result1_bucket.size() - 1) cout << ",";
    }
    cout << "]" << endl << endl;

    // 测试用例 2：只有一个元素
    vector<int> nums2 = {1};
    int k2 = 1;
    cout << "测试用例 2 - 输入: [1], k = 1" << endl;
    vector<int> result2 = solution.topKFrequent(nums2, k2);
    cout << "方法一（小顶堆）: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "] (期望: [1])" << endl << endl;

    // 测试用例 3：所有元素相同
    vector<int> nums3 = {1, 1, 1, 1};
    int k3 = 1;
    cout << "测试用例 3 - 输入: [1,1,1,1], k = 1" << endl;
    vector<int> result3 = solution.topKFrequent(nums3, k3);
    cout << "方法一（小顶堆）: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "] (期望: [1])" << endl << endl;

    // 测试用例 4：k 等于不同元素的个数
    vector<int> nums4 = {1, 2, 3};
    int k4 = 3;
    cout << "测试用例 4 - 输入: [1,2,3], k = 3" << endl;
    vector<int> result4 = solution.topKFrequent(nums4, k4);
    cout << "方法一（小顶堆）: [";
    for (int i = 0; i < result4.size(); i++) {
        cout << result4[i];
        if (i < result4.size() - 1) cout << ",";
    }
    cout << "] (期望: [1,2,3] 任意顺序)" << endl << endl;

    // 测试用例 5：包含负数
    vector<int> nums5 = {-1, -1, 2, 2, 2};
    int k5 = 1;
    cout << "测试用例 5 - 输入: [-1,-1,2,2,2], k = 1" << endl;
    vector<int> result5 = solution.topKFrequent(nums5, k5);
    cout << "方法一（小顶堆）: [";
    for (int i = 0; i < result5.size(); i++) {
        cout << result5[i];
        if (i < result5.size() - 1) cout << ",";
    }
    cout << "] (期望: [2])" << endl;

    return 0;
}
