/*
LeetCode 169. 多数元素 (Majority Element)

题目概述 (Problem Summary)
-------------------------
给定一个大小为 n 的数组 nums，返回其中的多数元素。
多数元素是指在数组中出现次数 严格大于 ⌊n/2⌋ 的元素。

关键约束 (Key Constraints)
-------------------------
- n == nums.length
- 1 <= n <= 5 * 10^4
- -10^9 <= nums[i] <= 10^9
- 题目保证多数元素总是存在

示例 (Example)
-------------
输入：nums = [3,2,3]
输出：3

输入：nums = [2,2,1,1,1,2,2]
输出：2

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到出现次数超过半数的元素

关键观察：
1. 多数元素的出现次数 > n/2，意味着它比所有其他元素加起来还多
2. 如果把多数元素记为 +1，其他元素记为 -1，最终和一定为正
3. Boyer-Moore 投票算法利用了"抵消"的思想
4. 排序后中位数一定是多数元素（因为它占据超过一半）

根据这些观察，可以得到四种典型解法：
1. Boyer-Moore 投票算法（最优 O(n) 时间 O(1) 空间）
2. 哈希表统计
3. 排序
4. 分治
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
方法一：Boyer-Moore 投票算法 (Approach 1: Boyer-Moore Voting Algorithm)

核心思想
--------
把数组看作一场"投票"，多数元素的票数超过半数。
使用"抵消"策略：遇到相同元素 count++，遇到不同元素 count--。
当 count 为 0 时，更换候选人。

算法原理：
- 多数元素的数量 > 其他所有元素数量之和
- 即使多数元素被其他元素"抵消"，最后剩下的一定还是多数元素

算法流程：
1. 初始化候选人 candidate 和计数器 count = 0
2. 遍历数组：
   - 如果 count == 0，选择当前元素为候选人
   - 如果当前元素 == 候选人，count++
   - 否则 count--
3. 返回候选人

复杂度分析
---------
时间复杂度：O(n) - 只需遍历一次数组
空间复杂度：O(1) - 只使用常数额外空间
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }

            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }

        return candidate;
    }
};

/*
方法二：哈希表统计 (Approach 2: Hash Map)

核心思想
--------
使用哈希表统计每个元素的出现次数，
找到出现次数 > n/2 的元素。

算法流程：
1. 遍历数组，用哈希表记录每个元素的出现次数
2. 遍历哈希表，找到出现次数 > n/2 的元素

复杂度分析
---------
时间复杂度：O(n) - 遍历数组一次
空间复杂度：O(n) - 哈希表存储
*/
class Solution_HashMap {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        int n = static_cast<int>(nums.size());

        for (int num : nums) {
            counts[num]++;
            if (counts[num] > n / 2) {
                return num;
            }
        }

        return -1; // 题目保证存在多数元素，不会到这里
    }
};

/*
方法三：排序 (Approach 3: Sorting)

核心思想
--------
将数组排序后，中间位置（n/2）的元素一定是多数元素。
因为多数元素出现次数 > n/2，无论它在哪里开始，
都一定会占据中间位置。

算法流程：
1. 对数组排序
2. 返回 nums[n/2]

复杂度分析
---------
时间复杂度：O(n log n) - 排序的时间复杂度
空间复杂度：O(log n) - 排序的栈空间
*/
class Solution_Sorting {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

/*
方法四：分治 (Approach 4: Divide and Conquer)

核心思想
--------
如果 a 是数组 nums 的多数元素，那么：
- a 必定是 nums 左半部分或右半部分的多数元素之一
- 递归地在左右两部分找多数元素，然后合并结果

算法流程：
1. 递归终止：数组只有一个元素时，返回该元素
2. 分治：将数组分成左右两部分，分别找多数元素
3. 合并：统计左右两个候选元素在整个区间的出现次数，返回较多的

复杂度分析
---------
时间复杂度：O(n log n) - T(n) = 2T(n/2) + O(n)
空间复杂度：O(log n) - 递归栈深度
*/
class Solution_DivideConquer {
private:
    int countInRange(vector<int>& nums, int num, int left, int right) {
        int count = 0;
        for (int i = left; i <= right; ++i) {
            if (nums[i] == num) {
                count++;
            }
        }
        return count;
    }

    int majorityElementRec(vector<int>& nums, int left, int right) {
        // 递归终止条件
        if (left == right) {
            return nums[left];
        }

        // 分治
        int mid = left + (right - left) / 2;
        int leftMajority = majorityElementRec(nums, left, mid);
        int rightMajority = majorityElementRec(nums, mid + 1, right);

        // 如果左右两边的多数元素相同，直接返回
        if (leftMajority == rightMajority) {
            return leftMajority;
        }

        // 否则，统计两个候选元素在整个区间的出现次数
        int leftCount = countInRange(nums, leftMajority, left, right);
        int rightCount = countInRange(nums, rightMajority, left, right);

        return leftCount > rightCount ? leftMajority : rightMajority;
    }

public:
    int majorityElement(vector<int>& nums) {
        return majorityElementRec(nums, 0, static_cast<int>(nums.size()) - 1);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [2,2,1,1,1,2,2]

Boyer-Moore 投票算法过程：
索引 0: num=2, count=0 -> candidate=2, count=1
索引 1: num=2, count=1 -> candidate=2, count=2
索引 2: num=1, count=2 -> candidate=2, count=1
索引 3: num=1, count=1 -> candidate=2, count=0
索引 4: num=1, count=0 -> candidate=1, count=1
索引 5: num=2, count=1 -> candidate=1, count=0
索引 6: num=2, count=0 -> candidate=2, count=1

最终 candidate = 2

为什么这样有效？
- 2 出现 4 次，1 出现 3 次
- 即使 2 被 1 抵消 3 次，还剩 1 次
- 最后剩下的一定是多数元素
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：Boyer-Moore 投票算法 ⭐ 最优解
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：时间和空间都是最优
- 缺点：需要理解投票算法原理

方法二：哈希表统计
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：直观易懂
- 缺点：需要额外空间

方法三：排序
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 优点：实现简单，利用了多数元素的性质
- 缺点：时间复杂度较高

方法四：分治
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 优点：展示了分治思想
- 缺点：实现复杂，性能不如方法一
*/

/*
特殊情况 (Edge Cases)
--------------------
1. n = 1：唯一元素就是多数元素
2. 所有元素相同：任意元素都是多数元素
3. 多数元素刚好出现 n/2 + 1 次：边界情况
*/

/*
Boyer-Moore 投票算法的正确性证明
-------------------------------
为什么最后剩下的一定是多数元素？

反证法：
假设最后剩下的不是多数元素，设为 x。
- x 的出现次数 <= n/2
- 多数元素 m 的出现次数 > n/2

在遍历过程中：
- x 每次被选为候选人时，count 从 0 开始增加
- x 最多被其他元素抵消 (n/2) 次
- 但 m 出现了 > n/2 次，必然有机会成为候选人
- 当 m 成为候选人后，它的数量优势保证了最后 count > 0

因此，最后剩下的一定是多数元素 m。
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

    // 测试用例 1：基本情况
    vector<int> nums1 = {3, 2, 3};
    cout << "测试用例 1 - 输入: ";
    printVector(nums1);
    cout << endl;
    cout << "输出: " << solution.majorityElement(nums1) << " (期望: 3)" << endl;
    cout << endl;

    // 测试用例 2：多数元素在不同位置
    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    cout << "测试用例 2 - 输入: ";
    printVector(nums2);
    cout << endl;
    cout << "输出: " << solution.majorityElement(nums2) << " (期望: 2)" << endl;
    cout << endl;

    // 测试用例 3：只有一个元素
    vector<int> nums3 = {1};
    cout << "测试用例 3 - 输入: ";
    printVector(nums3);
    cout << endl;
    cout << "输出: " << solution.majorityElement(nums3) << " (期望: 1)" << endl;
    cout << endl;

    // 测试用例 4：所有元素相同
    vector<int> nums4 = {5, 5, 5, 5, 5};
    cout << "测试用例 4 - 输入: ";
    printVector(nums4);
    cout << endl;
    cout << "输出: " << solution.majorityElement(nums4) << " (期望: 5)" << endl;
    cout << endl;

    // 测试用例 5：多数元素刚好超过半数
    vector<int> nums5 = {1, 2, 1, 2, 1};
    cout << "测试用例 5 - 输入: ";
    printVector(nums5);
    cout << endl;
    cout << "输出: " << solution.majorityElement(nums5) << " (期望: 1)" << endl;
    cout << endl;

    // 测试其他方法
    cout << "=== 测试其他方法 ===" << endl;
    Solution_HashMap solutionHash;
    Solution_Sorting solutionSort;
    Solution_DivideConquer solutionDC;

    vector<int> nums6 = {2, 2, 1, 1, 1, 2, 2};
    cout << "哈希表方法: " << solutionHash.majorityElement(nums6) << endl;

    vector<int> nums7 = {2, 2, 1, 1, 1, 2, 2};
    cout << "排序方法: " << solutionSort.majorityElement(nums7) << endl;

    vector<int> nums8 = {2, 2, 1, 1, 1, 2, 2};
    cout << "分治方法: " << solutionDC.majorityElement(nums8) << endl;

    return 0;
}

