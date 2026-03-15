/*
LeetCode 287. 寻找重复数 (Find the Duplicate Number)

题目概述 (Problem Summary)
-------------------------
给定一个包含 n + 1 个整数的数组 nums，其数字都在 [1, n] 范围内（包括 1 和 n）。

可知至少存在一个重复的整数。假设 nums 只有一个重复的整数，返回这个重复的数。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

关键约束 (Key Constraints)
-------------------------
- 1 <= n <= 10^5
- nums.length == n + 1
- 1 <= nums[i] <= n
- nums 中只有一个整数出现两次或多次，其余整数均只出现一次

进阶要求：
- 如何证明 nums 中至少存在一个重复的数字？
- 你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？

示例 (Example)
-------------
示例 1：
输入：nums = [1,3,4,2,2]
输出：2

示例 2：
输入：nums = [3,1,3,4,2]
输出：3

示例 3：
输入：nums = [3,3,3,3,3]
输出：3

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在不修改数组、不使用额外空间的情况下，找到重复的数字

关键观察：
1. 数组有 n+1 个元素，值的范围是 [1, n]
2. 根据抽屉原理，至少有一个数字重复
3. 如何将数组问题转化为链表问题？

数组转链表的核心思想：
- 将数组看作链表：nums[i] 表示从节点 i 指向节点 nums[i]
- 例如：nums = [1,3,4,2,2]
  - 节点 0 -> 节点 1（nums[0] = 1）
  - 节点 1 -> 节点 3（nums[1] = 3）
  - 节点 3 -> 节点 2（nums[3] = 2）
  - 节点 2 -> 节点 4（nums[2] = 4）
  - 节点 4 -> 节点 2（nums[4] = 2）

链表结构：
  0 -> 1 -> 3 -> 2 -> 4
                 ^    |
                 |____|

- 因为有重复数字，所以会有两个节点指向同一个节点
- 这就形成了一个环！
- 重复的数字就是环的入口

为什么一定有环？
- 从索引 0 开始，按照 nums[i] 跳转
- 因为值的范围是 [1, n]，不会跳到索引 0
- 因为有 n+1 个元素，值只有 n 个，必然有重复
- 重复的值会被多次指向，形成环的入口

根据这些观察，可以得到几种典型解法：
1. 快慢指针（Floyd 判圈算法）- O(n) 时间，O(1) 空间（最优解）
2. 二分查找 - O(n log n) 时间，O(1) 空间
3. 位运算 - O(n) 时间，O(1) 空间
4. 哈希表 - O(n) 时间，O(n) 空间（不满足空间要求）
5. 排序 - O(n log n) 时间，O(1) 空间（会修改数组，不满足要求）
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
方法一：快慢指针（Floyd 判圈算法）(Approach 1: Fast-Slow Pointers - Floyd's Cycle Detection)

核心思想
--------
将数组看作链表，使用快慢指针找环的入口。
环的入口就是重复的数字。

算法流程：
1. 第一阶段：使用快慢指针检测环并找到相遇点
   - slow 每次走 1 步：slow = nums[slow]
   - fast 每次走 2 步：fast = nums[nums[fast]]
   - 当 slow == fast 时，找到相遇点

2. 第二阶段：找环的入口（重复数字）
   - 一个指针从起点（索引 0）开始
   - 另一个指针从相遇点开始
   - 两个指针同时每次走 1 步
   - 相遇点就是环的入口（重复数字）

数组转链表图解：

nums = [1,3,4,2,2]

数组索引和值：
  索引：0  1  2  3  4
  值：  1  3  4  2  2

链表结构（索引 -> nums[索引]）：
  0 -> 1 -> 3 -> 2 -> 4
                 ^    |
                 |____|

  环的入口是索引 2，nums[2] = 4，但重复的数字是 2
  注意：环的入口索引对应的是被重复指向的值

  更准确的理解：
  - 索引 3 指向 2（nums[3] = 2）
  - 索引 4 也指向 2（nums[4] = 2）
  - 所以 2 是环的入口，也是重复的数字

复杂度分析
---------
时间复杂度：O(n)
- 第一阶段：找相遇点，最多 n 步
- 第二阶段：找环入口，最多 n 步
- 总共 O(n)

空间复杂度：O(1)
- 只使用了两个指针变量

其中：
n = 数组长度 - 1
*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 第一阶段：使用快慢指针找相遇点
        int slow = nums[0];  // 慢指针，每次走 1 步
        int fast = nums[0];  // 快指针，每次走 2 步

        // 找到快慢指针的相遇点
        // 注意：这里使用 do-while，因为初始时 slow == fast
        do {
            slow = nums[slow];           // 慢指针走 1 步
            fast = nums[nums[fast]];     // 快指针走 2 步
        } while (slow != fast);

        // 第二阶段：找环的入口（重复数字）
        // 一个指针从起点开始，另一个从相遇点开始
        int ptr1 = nums[0];  // 从起点开始
        int ptr2 = slow;     // 从相遇点开始

        // 两个指针同时每次走 1 步
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }

        // 相遇点就是环的入口，即重复的数字
        return ptr1;
    }
};

/*
方法二：二分查找 (Approach 2: Binary Search)

核心思想
--------
利用抽屉原理和二分查找。
对于数字 mid，统计数组中小于等于 mid 的数字个数。
如果个数大于 mid，说明重复数字在 [1, mid] 范围内。

算法流程：
1. 初始化左右边界：left = 1, right = n
2. 二分查找：
   - 计算 mid = (left + right) / 2
   - 统计数组中小于等于 mid 的数字个数 count
   - 如果 count > mid，说明重复数字在 [1, mid]，right = mid
   - 否则，重复数字在 [mid+1, n]，left = mid + 1
3. 返回 left（或 right，此时 left == right）

为什么这样可行？
- 如果没有重复，小于等于 mid 的数字个数应该正好是 mid
- 如果有重复，且重复数字 <= mid，则个数会 > mid
- 利用这个性质可以二分查找重复数字

复杂度分析
---------
时间复杂度：O(n log n)
- 二分查找：O(log n)
- 每次统计个数：O(n)
- 总共：O(n log n)

空间复杂度：O(1)
- 只使用了常数个变量

其中：
n = 数组长度 - 1
*/
class Solution_BinarySearch {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size() - 1;
        int left = 1;
        int right = n;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // 统计小于等于 mid 的数字个数
            int count = 0;
            for (int num : nums) {
                if (num <= mid) {
                    count++;
                }
            }

            // 如果个数大于 mid，说明重复数字在 [1, mid]
            if (count > mid) {
                right = mid;
            } else {
                // 否则，重复数字在 [mid+1, n]
                left = mid + 1;
            }
        }

        return left;
    }
};

/*
方法三：位运算 (Approach 3: Bit Manipulation)

核心思想
--------
利用异或运算的性质：a ^ a = 0, a ^ 0 = a
将数组索引和数组值进行异或，重复的数字会被保留。

算法流程：
1. 将所有数组元素异或
2. 将所有索引（0 到 n）异或
3. 结果就是重复的数字

注意：这个方法只适用于重复数字出现两次的情况。

复杂度分析
---------
时间复杂度：O(n)
- 遍历数组一次

空间复杂度：O(1)
- 只使用了常数个变量

其中：
n = 数组长度 - 1
*/
class Solution_BitManipulation {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size() - 1;
        int result = 0;

        // 将所有数组元素异或
        for (int num : nums) {
            result ^= num;
        }

        // 将所有索引（1 到 n）异或
        // 注意：索引从 1 开始，因为数组值范围是 [1, n]
        for (int i = 1; i <= n; i++) {
            result ^= i;
        }

        return result;
    }
};

/*
方法四：哈希表（不满足空间要求）(Approach 4: Hash Set - Not Meeting Space Requirement)

核心思想
--------
使用哈希表记录出现过的数字，第一个重复出现的就是答案。

算法流程：
1. 创建哈希集合 seen
2. 遍历数组：
   - 如果数字已在 seen 中，返回该数字
   - 否则将数字加入 seen

复杂度分析
---------
时间复杂度：O(n)
- 遍历数组一次

空间复杂度：O(n)
- 需要哈希表存储数字

其中：
n = 数组长度 - 1
*/
class Solution_HashSet {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> seen;

        for (int num : nums) {
            if (seen.count(num)) {
                return num;
            }
            seen.insert(num);
        }

        return -1;  // 不会到达这里
    }
};

/*
快慢指针找重复数模板代码 (Fast-Slow Pointer Template for Duplicate Number)
------------------------------------------------------------------------
这是使用快慢指针找重复数的标准模板：

int findDuplicate(vector<int>& nums) {
    // 第一阶段：找相遇点
    int slow = nums[0];
    int fast = nums[0];

    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // 第二阶段：找环入口（重复数字）
    int ptr1 = nums[0];
    int ptr2 = slow;

    while (ptr1 != ptr2) {
        ptr1 = nums[ptr1];
        ptr2 = nums[ptr2];
    }

    return ptr1;
}

关键点：
1. 将数组看作链表：nums[i] 表示从 i 指向 nums[i]
2. 第一阶段：快慢指针找相遇点（slow 走 1 步，fast 走 2 步）
3. 第二阶段：两指针同时走 1 步找环入口
4. 环入口就是重复的数字
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：nums = [1,3,4,2,2]

数组转链表：
  索引：0  1  2  3  4
  值：  1  3  4  2  2

  0 -> 1 -> 3 -> 2 -> 4
                 ^    |
                 |____|

第一阶段：找相遇点
初始：slow = 1, fast = 1

第 1 次循环：
- slow = nums[1] = 3
- fast = nums[nums[1]] = nums[3] = 2
- slow != fast，继续

第 2 次循环：
- slow = nums[3] = 2
- fast = nums[nums[2]] = nums[4] = 2
- slow == fast，相遇！相遇点是 2

第二阶段：找环入口
- ptr1 = nums[0] = 1（从起点开始）
- ptr2 = 2（从相遇点开始）

第 1 次循环：
- ptr1 = nums[1] = 3
- ptr2 = nums[2] = 4
- ptr1 != ptr2，继续

第 2 次循环：
- ptr1 = nums[3] = 2
- ptr2 = nums[4] = 2
- ptr1 == ptr2，找到环入口！

返回 2（重复的数字）

示例 2：nums = [3,1,3,4,2]

数组转链表：
  索引：0  1  2  3  4
  值：  3  1  3  4  2

  0 -> 3 -> 4 -> 2 -> 3（形成环）
       ^              |
       |______________|

第一阶段：找相遇点
- 快慢指针会在环内相遇

第二阶段：找环入口
- 两指针会在索引 3（值为 3）相遇

返回 3（重复的数字）

示例 3：nums = [3,3,3,3,3]

数组转链表：
  索引：0  1  2  3  4
  值：  3  3  3  3  3

  0 -> 3 -> 3（自环）
       ^    |
       |____|

第一阶段：找相遇点
- slow = nums[0] = 3
- fast = nums[nums[0]] = nums[3] = 3
- 第一次循环就相遇

第二阶段：找环入口
- ptr1 = nums[0] = 3
- ptr2 = 3
- 已经相遇

返回 3（重复的数字）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针（Floyd 判圈算法）
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(1) ✓ 最优
- 优点：时间和空间都是最优，满足所有要求
- 缺点：需要理解数组转链表的思想

方法二：二分查找
- 时间复杂度：O(n log n)
- 空间复杂度：O(1) ✓ 最优
- 优点：思路巧妙，利用抽屉原理
- 缺点：时间复杂度不是最优

方法三：位运算
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(1) ✓ 最优
- 优点：简洁高效
- 缺点：只适用于重复数字出现两次的情况

方法四：哈希表
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(n) ✗ 不满足要求
- 优点：思路直观
- 缺点：不满足空间复杂度要求

推荐使用方法一（快慢指针），这是最优解。
*/

/*
特殊情况处理 (Edge Cases)
------------------------
1. 最小情况：nums = [1,1]
   - 只有两个元素，都是 1
   - 返回 1

2. 重复数字在开头：nums = [2,1,2,3,4]
   - 正常检测，返回 2

3. 重复数字在末尾：nums = [1,2,3,4,4]
   - 正常检测，返回 4

4. 所有数字都相同：nums = [3,3,3,3,3]
   - 形成自环，返回 3

5. 重复数字出现多次：nums = [2,5,9,6,9,3,8,9,7,1,4]
   - 9 出现 3 次，正常检测，返回 9

数组转链表的关键理解：
- 数组索引是链表节点
- 数组值是链表的 next 指针
- 重复的值意味着多个节点指向同一个节点
- 这就形成了环，环的入口就是重复的值
*/

/*
为什么数组转链表一定有环？
------------------------
证明：
1. 数组有 n+1 个元素，索引范围是 [0, n]
2. 数组值的范围是 [1, n]
3. 从索引 0 开始，按照 nums[i] 跳转
4. 因为值的范围是 [1, n]，永远不会跳回索引 0
5. 因为有 n+1 个元素，但值只有 n 个可能
6. 根据抽屉原理，至少有一个值出现两次
7. 这个重复的值会被多次指向，形成环的入口

例如：nums = [1,3,4,2,2]
- 索引 0 不会被指向（因为值范围是 [1, n]）
- 索引 2 被索引 3 和索引 4 同时指向
- 所以索引 2 是环的入口
- nums[3] = 2, nums[4] = 2，所以 2 是重复的数字

数组转链表的巧妙之处：
- 将查找重复数字的问题转化为查找环入口的问题
- 利用 Floyd 判圈算法，O(1) 空间解决问题
*/

int main() {
    Solution solution;

    // 测试用例 1：重复数字在中间
    cout << "测试用例 1：nums = [1,3,4,2,2]" << endl;
    vector<int> nums1 = {1, 3, 4, 2, 2};
    cout << "结果: " << solution.findDuplicate(nums1) << endl;
    cout << "期望: 2" << endl << endl;

    // 测试用例 2：重复数字在开头
    cout << "测试用例 2：nums = [3,1,3,4,2]" << endl;
    vector<int> nums2 = {3, 1, 3, 4, 2};
    cout << "结果: " << solution.findDuplicate(nums2) << endl;
    cout << "期望: 3" << endl << endl;

    // 测试用例 3：所有数字都相同
    cout << "测试用例 3：nums = [3,3,3,3,3]" << endl;
    vector<int> nums3 = {3, 3, 3, 3, 3};
    cout << "结果: " << solution.findDuplicate(nums3) << endl;
    cout << "期望: 3" << endl << endl;

    // 测试用例 4：最小情况
    cout << "测试用例 4：nums = [1,1]" << endl;
    vector<int> nums4 = {1, 1};
    cout << "结果: " << solution.findDuplicate(nums4) << endl;
    cout << "期望: 1" << endl << endl;

    // 测试用例 5：重复数字出现多次
    cout << "测试用例 5：nums = [2,5,9,6,9,3,8,9,7,1,4]" << endl;
    vector<int> nums5 = {2, 5, 9, 6, 9, 3, 8, 9, 7, 1, 4};
    cout << "结果: " << solution.findDuplicate(nums5) << endl;
    cout << "期望: 9" << endl;

    return 0;
}
