/*
LeetCode 496. 下一个更大元素 I (Next Greater Element I)

题目概述 (Problem Summary)
-------------------------
给你两个没有重复元素的数组 nums1 和 nums2，其中 nums1 是 nums2 的子集。
请你找出 nums1 中每个元素在 nums2 中的下一个比其大的值。

nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置右侧的第一个比 x 大的元素。
如果不存在，对应位置输出 -1。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums1.length <= nums2.length <= 1000
- 0 <= nums1[i], nums2[i] <= 10^4
- nums1 和 nums2 中所有整数互不相同
- nums1 中的所有整数同样出现在 nums2 中

示例 (Example)
-------------
输入：nums1 = [4,1,2], nums2 = [1,3,4,2]
输出：[-1,3,-1]
解释：
- 4 在 nums2 中，右侧没有更大的数，返回 -1
- 1 在 nums2 中，右侧第一个更大的数是 3
- 2 在 nums2 中，右侧没有更大的数，返回 -1

输入：nums1 = [2,4], nums2 = [1,2,3,4]
输出：[3,-1]
解释：
- 2 在 nums2 中，右侧第一个更大的数是 3
- 4 在 nums2 中，右侧没有更大的数，返回 -1

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对 nums2 中每个元素，找到右侧第一个更大的元素
- 然后根据 nums1 查询对应的结果

为什么用单调栈 + 哈希表？
1. 单调栈：用于找到 nums2 中每个元素的下一个更大元素
2. 哈希表：存储 nums2 中每个元素对应的下一个更大元素，方便 nums1 查询

单调栈的定义：
- 单调递减栈：从栈底到栈顶元素递减（本题使用）

栈中存什么？
- 存储 nums2 中的元素值（因为元素互不相同，可以直接存值）

什么时候入栈？
- 当前元素 <= 栈顶元素时，入栈

什么时候出栈？
- 当前元素 > 栈顶元素时，栈顶找到了答案，出栈并记录到哈希表

单调栈原理图解 (Monotonic Stack Visualization)
--------------------------------------------
nums2 = [1, 3, 4, 2]

遍历过程：
i=0, num=1: 栈空，入栈 -> 栈: [1]
i=1, num=3: 3>1，1出栈，map[1]=3 -> 栈: [3]
i=2, num=4: 4>3，3出栈，map[3]=4 -> 栈: [4]
i=3, num=2: 2<4，入栈 -> 栈: [4,2]

遍历结束，栈中剩余 [4,2]，它们没有更大元素，map[4]=-1, map[2]=-1

哈希表：{1:3, 3:4, 4:-1, 2:-1}

查询 nums1 = [4,1,2]:
- map[4] = -1
- map[1] = 3
- map[2] = -1
结果：[-1, 3, -1]

单调栈模板代码 (Monotonic Stack Template)
---------------------------------------
// 单调递减栈 + 哈希表模板（找每个元素的下一个更大元素）
unordered_map<int, int> nextGreaterMap(vector<int>& nums) {
    unordered_map<int, int> map;
    stack<int> st;  // 单调递减栈

    for (int num : nums) {
        // 当前元素大于栈顶，栈顶找到答案
        while (!st.empty() && num > st.top()) {
            map[st.top()] = num;
            st.pop();
        }
        st.push(num);
    }

    // 栈中剩余元素没有更大元素
    while (!st.empty()) {
        map[st.top()] = -1;
        st.pop();
    }

    return map;
}

时间复杂度分析：
- 遍历 nums2：O(n)，每个元素最多入栈、出栈各一次
- 查询 nums1：O(m)
- 总时间复杂度：O(m + n)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
方法一：单调栈 + 哈希表 (Approach 1: Monotonic Stack + Hash Map)

核心思想
--------
1. 用单调栈遍历 nums2，找到每个元素的下一个更大元素
2. 用哈希表存储映射关系：元素 -> 下一个更大元素
3. 遍历 nums1，从哈希表中查询结果

算法流程：
1. 遍历 nums2，维护单调递减栈
2. 当前元素大于栈顶时，栈顶找到答案，记录到哈希表
3. 栈中剩余元素没有更大元素，记录为 -1
4. 遍历 nums1，从哈希表查询结果

复杂度分析
---------
时间复杂度：O(m + n) - m 是 nums1 长度，n 是 nums2 长度
空间复杂度：O(n) - 哈希表和栈的空间
*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map;  // 存储 nums2 中每个元素的下一个更大元素
        stack<int> st;  // 单调递减栈

        // 遍历 nums2，构建哈希表
        for (int num : nums2) {
            // 当前元素大于栈顶，栈顶找到了答案
            while (!st.empty() && num > st.top()) {
                map[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        // 栈中剩余元素没有更大元素
        while (!st.empty()) {
            map[st.top()] = -1;
            st.pop();
        }

        // 查询 nums1 中每个元素的结果
        vector<int> result;
        for (int num : nums1) {
            result.push_back(map[num]);
        }

        return result;
    }
};

/*
方法二：暴力枚举 (Approach 2: Brute Force)

核心思想
--------
对 nums1 中的每个元素，在 nums2 中找到它的位置，然后向右遍历找第一个更大的元素。

算法流程：
1. 对 nums1 中的每个元素 x
2. 在 nums2 中找到 x 的位置 i
3. 从 i+1 开始向右遍历，找到第一个大于 x 的元素
4. 如果找不到，返回 -1

复杂度分析
---------
时间复杂度：O(m * n) - 对每个 nums1 元素，在 nums2 中查找和遍历
空间复杂度：O(1) - 不计结果数组
*/
class Solution_BruteForce {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;

        for (int x : nums1) {
            // 在 nums2 中找到 x 的位置
            int pos = -1;
            for (int i = 0; i < nums2.size(); i++) {
                if (nums2[i] == x) {
                    pos = i;
                    break;
                }
            }

            // 从 pos+1 开始向右找第一个更大的元素
            int nextGreater = -1;
            for (int i = pos + 1; i < nums2.size(); i++) {
                if (nums2[i] > x) {
                    nextGreater = nums2[i];
                    break;
                }
            }

            result.push_back(nextGreater);
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums1 = [4, 1, 2], nums2 = [1, 3, 4, 2]

步骤 1：遍历 nums2，构建哈希表

i=0, num=1:
  栈空，入栈
  栈: [1]

i=1, num=3:
  3 > 1 (栈顶)，1 出栈，map[1] = 3
  入栈 3
  栈: [3]

i=2, num=4:
  4 > 3 (栈顶)，3 出栈，map[3] = 4
  入栈 4
  栈: [4]

i=3, num=2:
  2 < 4 (栈顶)，入栈
  栈: [4, 2]

遍历结束，栈中剩余 [4, 2]：
  map[4] = -1
  map[2] = -1

哈希表：{1: 3, 3: 4, 4: -1, 2: -1}

步骤 2：查询 nums1

nums1[0] = 4 -> map[4] = -1
nums1[1] = 1 -> map[1] = 3
nums1[2] = 2 -> map[2] = -1

最终结果：[-1, 3, -1]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈 + 哈希表
- 时间复杂度：O(m + n)
- 空间复杂度：O(n)
- 优点：时间最优，单调栈经典应用
- 缺点：需要额外空间存储哈希表

方法二：暴力枚举
- 时间复杂度：O(m * n)
- 空间复杂度：O(1)
- 优点：思路简单，不需要额外空间
- 缺点：时间复杂度高，数据量大时超时
*/

/*
特殊情况 (Edge Cases)
--------------------
1. nums1 只有一个元素：nums1=[1], nums2=[1,2] -> [2]
2. nums2 单调递减：nums1=[2,1], nums2=[3,2,1] -> [-1,-1]
3. nums2 单调递增：nums1=[1,2], nums2=[1,2,3] -> [2,3]
4. nums1 中元素都是 nums2 最大值：nums1=[5], nums2=[1,2,5] -> [-1]
5. nums1 和 nums2 相同：nums1=[1,2], nums2=[1,2] -> [2,-1]
*/

int main() {
    Solution solution;

    // 测试用例 1：标准示例
    vector<int> n1_1 = {4, 1, 2};
    vector<int> n2_1 = {1, 3, 4, 2};
    vector<int> r1 = solution.nextGreaterElement(n1_1, n2_1);
    cout << "测试用例 1 - 输出: [";
    for (int i = 0; i < r1.size(); i++) {
        cout << r1[i];
        if (i < r1.size() - 1) cout << ", ";
    }
    cout << "] (期望: [-1, 3, -1])" << endl;

    // 测试用例 2：标准示例
    vector<int> n1_2 = {2, 4};
    vector<int> n2_2 = {1, 2, 3, 4};
    vector<int> r2 = solution.nextGreaterElement(n1_2, n2_2);
    cout << "测试用例 2 - 输出: [";
    for (int i = 0; i < r2.size(); i++) {
        cout << r2[i];
        if (i < r2.size() - 1) cout << ", ";
    }
    cout << "] (期望: [3, -1])" << endl;

    // 测试用例 3：单调递减
    vector<int> n1_3 = {2, 1};
    vector<int> n2_3 = {3, 2, 1};
    vector<int> r3 = solution.nextGreaterElement(n1_3, n2_3);
    cout << "测试用例 3 - 输出: [";
    for (int i = 0; i < r3.size(); i++) {
        cout << r3[i];
        if (i < r3.size() - 1) cout << ", ";
    }
    cout << "] (期望: [-1, -1])" << endl;

    return 0;
}
