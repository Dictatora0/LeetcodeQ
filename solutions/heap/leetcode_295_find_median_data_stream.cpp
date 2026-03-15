/*
LeetCode 295. 数据流的中位数 (Find Median from Data Stream)

题目概述 (Problem Summary)
-------------------------
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

例如：
- [2,3,4] 的中位数是 3
- [2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：
- void addNum(int num) - 从数据流中添加一个整数到数据结构中
- double findMedian() - 返回目前所有元素的中位数

关键约束 (Key Constraints)
-------------------------
- -10^5 <= num <= 10^5
- 在调用 findMedian 之前，数据结构中至少有一个元素
- 最多会对 addNum、findMedian 进行 5 * 10^4 次调用

进阶：
- 如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
- 如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？

示例 (Example)
-------------
输入：
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
输出：
[null, null, null, 1.5, null, 2.0]

解释：
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
medianFinder.addNum(3);    // arr = [1, 2, 3]
medianFinder.findMedian(); // 返回 2.0

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 动态维护一个数据流的中位数
- 需要支持快速插入和快速查询中位数

关键观察：
1. 如果用数组存储并排序，插入 O(n)，查询 O(1)，总体效率低
2. 如果用有序数组 + 二分插入，插入 O(n)（移动元素），查询 O(1)
3. 使用对顶堆：插入 O(log n)，查询 O(1)，最优解

对顶堆的核心思想：
- 用两个堆将数据分成两部分：较小的一半和较大的一半
- 大顶堆（maxHeap）：存储较小的一半，堆顶是这一半中最大的
- 小顶堆（minHeap）：存储较大的一半，堆顶是这一半中最小的
- 中位数就在两个堆顶之间

为什么叫"对顶堆"？
- 两个堆的堆顶"相对"，大顶堆的堆顶是左半部分最大值，小顶堆的堆顶是右半部分最小值
- 中位数就在这两个堆顶之间

堆的大小如何维护？
- 保持两个堆的大小平衡：|maxHeap.size() - minHeap.size()| <= 1
- 如果总数是奇数，让 maxHeap 多一个元素（或 minHeap 多一个，统一即可）
- 如果总数是偶数，两个堆大小相等

如何确定新元素放入哪个堆？
1. 如果 maxHeap 为空或 num <= maxHeap.top()，放入 maxHeap
2. 否则，放入 minHeap
3. 调整两个堆的大小，保持平衡

对顶堆的变化过程示例：
addNum(1)：
  maxHeap: [1]
  minHeap: []
  中位数：1

addNum(2)：
  maxHeap: [1]
  minHeap: [2]
  中位数：(1 + 2) / 2 = 1.5

addNum(3)：
  maxHeap: [1, 2]（2 从 minHeap 移到 maxHeap，保持平衡）
  minHeap: [3]
  中位数：2（maxHeap 的堆顶）

C++ priority_queue 对顶堆实现
-----------------------------
1. 大顶堆（默认）：priority_queue<int>
2. 小顶堆：priority_queue<int, vector<int>, greater<int>>
3. 平衡维护：
   - 插入后，如果某个堆的大小超过另一个堆 + 1，移动堆顶元素
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
方法一：对顶堆 (Approach 1: Two Heaps)

核心思想
--------
使用大顶堆和小顶堆将数据分成两部分，动态维护中位数。

数据结构：
- maxHeap（大顶堆）：存储较小的一半，堆顶是最大值
- minHeap（小顶堆）：存储较大的一半，堆顶是最小值

不变量（Invariant）：
1. maxHeap.size() == minHeap.size() 或 maxHeap.size() == minHeap.size() + 1
2. maxHeap 中的所有元素 <= minHeap 中的所有元素
3. 即：maxHeap.top() <= minHeap.top()

算法流程：
addNum(num)：
1. 如果 maxHeap 为空或 num <= maxHeap.top()，将 num 加入 maxHeap
2. 否则，将 num 加入 minHeap
3. 平衡两个堆：
   - 如果 maxHeap.size() > minHeap.size() + 1，将 maxHeap 的堆顶移到 minHeap
   - 如果 minHeap.size() > maxHeap.size()，将 minHeap 的堆顶移到 maxHeap

findMedian()：
1. 如果 maxHeap.size() > minHeap.size()，返回 maxHeap.top()
2. 否则，返回 (maxHeap.top() + minHeap.top()) / 2.0

为什么这样做是对的？
- 两个堆将数据分成两部分，中位数就在堆顶之间
- 通过维护堆的大小平衡，确保中位数在堆顶
- 大顶堆的堆顶是左半部分最大值，小顶堆的堆顶是右半部分最小值

复杂度分析
---------
时间复杂度：
- addNum：O(log n)，堆的插入和删除操作
- findMedian：O(1)，直接访问堆顶

空间复杂度：O(n)
- 两个堆存储所有元素

其中：
n = 当前数据流中的元素个数

优点：
- 插入和查询都很高效
- 适合动态数据流
- 可以扩展到求其他百分位数

缺点：
- 需要维护两个堆，实现稍复杂
*/
class MedianFinder {
private:
    // 大顶堆：存储较小的一半，堆顶是最大值
    priority_queue<int> maxHeap;

    // 小顶堆：存储较大的一半，堆顶是最小值
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder() {
        // 构造函数，初始化两个堆
    }

    // 添加一个数字到数据结构中
    void addNum(int num) {
        // 步骤 1：决定将 num 加入哪个堆
        if (maxHeap.empty() || num <= maxHeap.top()) {
            // num 属于较小的一半，加入 maxHeap
            maxHeap.push(num);
        } else {
            // num 属于较大的一半，加入 minHeap
            minHeap.push(num);
        }

        // 步骤 2：平衡两个堆的大小
        // 保持 maxHeap.size() == minHeap.size() 或 maxHeap.size() == minHeap.size() + 1
        if (maxHeap.size() > minHeap.size() + 1) {
            // maxHeap 太大，移动堆顶到 minHeap
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            // minHeap 太大，移动堆顶到 maxHeap
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // 返回当前所有元素的中位数
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            // 奇数个元素，中位数是 maxHeap 的堆顶
            return maxHeap.top();
        } else {
            // 偶数个元素，中位数是两个堆顶的平均值
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

/*
方法二：有序数组 + 二分插入 (Approach 2: Sorted Array + Binary Search)

核心思想
--------
维护一个有序数组，每次插入时使用二分查找找到插入位置。

算法流程：
addNum(num)：
1. 使用二分查找找到 num 应该插入的位置
2. 在该位置插入 num

findMedian()：
1. 如果数组长度是奇数，返回中间元素
2. 如果数组长度是偶数，返回中间两个元素的平均值

复杂度分析
---------
时间复杂度：
- addNum：O(n)，二分查找 O(log n) + 插入 O(n)（需要移动元素）
- findMedian：O(1)，直接访问数组元素

空间复杂度：O(n)
- 存储所有元素

优点：
- 实现简单
- findMedian 是 O(1)

缺点：
- addNum 是 O(n)，效率低
- 不适合大规模数据流
*/
class MedianFinder_Array {
private:
    vector<int> data;

public:
    MedianFinder_Array() {}

    void addNum(int num) {
        // 使用二分查找找到插入位置
        auto it = lower_bound(data.begin(), data.end(), num);
        data.insert(it, num);
    }

    double findMedian() {
        int n = data.size();
        if (n % 2 == 1) {
            // 奇数个元素
            return data[n / 2];
        } else {
            // 偶数个元素
            return (data[n / 2 - 1] + data[n / 2]) / 2.0;
        }
    }
};

/*
两种方法对比 (Comparison)
------------------------
方法一：对顶堆
- addNum：O(log n)
- findMedian：O(1)
- 空间复杂度：O(n)
- 优点：插入和查询都高效，适合大规模数据流
- 缺点：实现稍复杂，需要维护两个堆

方法二：有序数组 + 二分插入
- addNum：O(n)
- findMedian：O(1)
- 空间复杂度：O(n)
- 优点：实现简单，findMedian 快
- 缺点：addNum 慢，不适合频繁插入

推荐方案：
- 面试中：方法一（对顶堆）是标准解法
- 实际应用：对顶堆适合动态数据流
- 如果插入次数远少于查询次数：可以考虑方法二
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
操作序列：addNum(1), addNum(2), findMedian(), addNum(3), findMedian()

使用方法一（对顶堆）：

初始状态：
maxHeap = []
minHeap = []

addNum(1)：
- maxHeap 为空，将 1 加入 maxHeap
- maxHeap = [1], minHeap = []
- 平衡检查：maxHeap.size()=1, minHeap.size()=0，差值为 1，满足条件

addNum(2)：
- 2 > maxHeap.top()=1，将 2 加入 minHeap
- maxHeap = [1], minHeap = [2]
- 平衡检查：maxHeap.size()=1, minHeap.size()=1，平衡

findMedian()：
- maxHeap.size() == minHeap.size()，偶数个元素
- 中位数 = (maxHeap.top() + minHeap.top()) / 2.0 = (1 + 2) / 2.0 = 1.5

addNum(3)：
- 3 > maxHeap.top()=1，将 3 加入 minHeap
- maxHeap = [1], minHeap = [2, 3]（堆顶是 2）
- 平衡检查：minHeap.size()=2 > maxHeap.size()=1
- 需要平衡：将 minHeap 的堆顶 2 移到 maxHeap
- maxHeap = [1, 2]（堆顶是 2）, minHeap = [3]

findMedian()：
- maxHeap.size()=2 > minHeap.size()=1，奇数个元素
- 中位数 = maxHeap.top() = 2
*/

/*
对顶堆的原理图解 (Two Heaps Visualization)
-----------------------------------------
对顶堆的结构：

数据：[1, 2, 3, 4, 5]

        maxHeap (大顶堆)    |    minHeap (小顶堆)
        存储较小的一半      |    存储较大的一半
              3             |           4
            /   \           |         /
           1     2          |        5

        堆顶：3             |    堆顶：4
        (左半部分最大)      |    (右半部分最小)

中位数 = (3 + 4) / 2 = 3.5

如果再加入 6：
        maxHeap             |    minHeap
              3             |           4
            /   \           |         /   \
           1     2          |        5     6

中位数 = 3（maxHeap 的堆顶，因为总数是奇数）

对顶堆的平衡维护：
1. 插入元素后，检查两个堆的大小
2. 如果 maxHeap 比 minHeap 大 2 个或以上，移动 maxHeap 的堆顶到 minHeap
3. 如果 minHeap 比 maxHeap 大，移动 minHeap 的堆顶到 maxHeap
4. 保持 maxHeap.size() == minHeap.size() 或 maxHeap.size() == minHeap.size() + 1

对顶堆的不变量：
- maxHeap 中的所有元素 <= minHeap 中的所有元素
- maxHeap.top() <= minHeap.top()
- |maxHeap.size() - minHeap.size()| <= 1
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：
   - addNum(1), findMedian() -> 1

2. 两个元素：
   - addNum(1), addNum(2), findMedian() -> 1.5

3. 所有元素相同：
   - addNum(5), addNum(5), addNum(5), findMedian() -> 5

4. 递增序列：
   - addNum(1), addNum(2), addNum(3), findMedian() -> 2

5. 递减序列：
   - addNum(3), addNum(2), addNum(1), findMedian() -> 2

6. 包含负数：
   - addNum(-1), addNum(0), addNum(1), findMedian() -> 0
*/

/*
进阶问题 (Follow-up)
-------------------
1. 如果数据流中所有整数都在 0 到 100 范围内：
   - 使用计数数组（桶）：count[101]
   - addNum：O(1)，count[num]++
   - findMedian：O(100) = O(1)，遍历计数数组找中位数
   - 空间复杂度：O(101) = O(1)

2. 如果数据流中 99% 的整数都在 0 到 100 范围内：
   - 混合方法：计数数组 + 两个有序数组（存储超出范围的数）
   - 大部分数用计数数组，少数超出范围的数用有序数组
   - 时间复杂度：接近 O(1)

3. 如果需要求其他百分位数（如 25%、75%）：
   - 对顶堆可以扩展：调整两个堆的大小比例
   - 例如求 25% 分位数：maxHeap 存储 25% 的数据，minHeap 存储 75% 的数据
*/

/*
对顶堆的应用场景 (Use Cases)
---------------------------
1. 动态维护中位数（本题）
2. 动态维护任意百分位数
3. 滑动窗口中位数（LeetCode 480）
4. 数据流中的第 K 大元素（需要调整堆的大小比例）
5. 在线算法中需要快速查询中间值的场景
*/

int main() {
    // 测试用例 1：标准情况
    cout << "测试用例 1 - 标准情况" << endl;
    MedianFinder mf1;
    mf1.addNum(1);
    cout << "addNum(1)" << endl;
    mf1.addNum(2);
    cout << "addNum(2)" << endl;
    cout << "findMedian(): " << mf1.findMedian() << " (期望: 1.5)" << endl;
    mf1.addNum(3);
    cout << "addNum(3)" << endl;
    cout << "findMedian(): " << mf1.findMedian() << " (期望: 2)" << endl << endl;

    // 测试用例 2：只有一个元素
    cout << "测试用例 2 - 只有一个元素" << endl;
    MedianFinder mf2;
    mf2.addNum(1);
    cout << "addNum(1)" << endl;
    cout << "findMedian(): " << mf2.findMedian() << " (期望: 1)" << endl << endl;

    // 测试用例 3：所有元素相同
    cout << "测试用例 3 - 所有元素相同" << endl;
    MedianFinder mf3;
    mf3.addNum(5);
    mf3.addNum(5);
    mf3.addNum(5);
    cout << "addNum(5) x 3" << endl;
    cout << "findMedian(): " << mf3.findMedian() << " (期望: 5)" << endl << endl;

    // 测试用例 4：递增序列
    cout << "测试用例 4 - 递增序列" << endl;
    MedianFinder mf4;
    mf4.addNum(1);
    mf4.addNum(2);
    mf4.addNum(3);
    mf4.addNum(4);
    mf4.addNum(5);
    cout << "addNum(1,2,3,4,5)" << endl;
    cout << "findMedian(): " << mf4.findMedian() << " (期望: 3)" << endl << endl;

    // 测试用例 5：包含负数
    cout << "测试用例 5 - 包含负数" << endl;
    MedianFinder mf5;
    mf5.addNum(-1);
    mf5.addNum(0);
    mf5.addNum(1);
    cout << "addNum(-1,0,1)" << endl;
    cout << "findMedian(): " << mf5.findMedian() << " (期望: 0)" << endl << endl;

    // 测试用例 6：偶数个元素
    cout << "测试用例 6 - 偶数个元素" << endl;
    MedianFinder mf6;
    mf6.addNum(1);
    mf6.addNum(2);
    mf6.addNum(3);
    mf6.addNum(4);
    cout << "addNum(1,2,3,4)" << endl;
    cout << "findMedian(): " << mf6.findMedian() << " (期望: 2.5)" << endl;

    return 0;
}
