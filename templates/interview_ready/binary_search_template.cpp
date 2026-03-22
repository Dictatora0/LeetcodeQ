/*
 * ============================================================================
 * 二分查找算法 - 面试必备完整模板
 * Binary Search Algorithm - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 二分查找是在有序数组中查找目标值的高效算法，每次将搜索范围缩小一半。
 *
 * 【通俗解释】
 * 想象你在字典中查单词：
 * - 翻到中间，看是在前半部分还是后半部分
 * - 继续在对应的半部分中间查找
 * - 重复直到找到或确定不存在
 *
 * 【为什么有效】
 * 1. 对数时间：每次减半，O(logn)
 * 2. 简单高效：代码简洁，性能优秀
 * 3. 应用广泛：不仅查找，还能求边界、最值
 *
 * 【与其他算法对比】
 * - vs 线性查找：O(logn) vs O(n)
 * - vs 哈希表：二分不需要额外空间
 * - vs 跳表：二分更简单
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别二分查找题目】
 *
 * ✅ 关键词识别：
 * 1. "有序数组" - 90% 可用二分
 * 2. "查找目标值" - 基础二分
 * 3. "第一个/最后一个" - 边界二分
 * 4. "最小的最大值/最大的最小值" - 二分答案
 * 5. "旋转数组" - 变形二分
 *
 * ✅ 题目特征：
 * - 数组有序或部分有序
 * - 查找、插入位置
 * - 满足单调性
 * - 可以二分答案
 *
 * ❌ 不适合二分：
 * - 无序且不能排序
 * - 需要遍历所有元素
 * - 不满足单调性
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：基础二分查找（查找目标值）
// 时间复杂度：O(logn)
// 空间复杂度：O(1)
// ============================================================================

class BasicBinarySearch {
public:
    int binarySearch(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;  // 防止溢出

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;  // 在右半部分
            } else {
                right = mid - 1;  // 在左半部分
            }
        }

        return -1;  // 未找到
    }
};

// ============================================================================
// 模板 2：左边界二分（查找第一个 >= target 的位置）
// 时间复杂度：O(logn)
// 空间复杂度：O(1)
// ============================================================================

class LeftBoundBinarySearch {
public:
    int leftBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();  // 注意：right = size()

        while (left < right) {  // 注意：left < right
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;  // 注意：right = mid
            }
        }

        return left;  // 返回 left
    }
};

// ============================================================================
// 模板 3：右边界二分（查找最后一个 <= target 的位置）
// 时间复杂度：O(logn)
// 空间复杂度：O(1)
// ============================================================================

class RightBoundBinarySearch {
public:
    int rightBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] <= target) {
                left = mid + 1;  // 注意：left = mid + 1
            } else {
                right = mid;
            }
        }

        return left - 1;  // 注意：返回 left - 1
    }
};

// ============================================================================
// 模板 4：二分答案（在答案范围内二分）
// 时间复杂度：O(n * logm) m 为答案范围
// 空间复杂度：O(1)
// ============================================================================

class BinarySearchAnswer {
public:
    int binarySearchAnswer(vector<int>& nums, int low, int high) {
        int left = low;
        int right = high;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (check(nums, mid)) {
                right = mid;  // 答案可能更小
            } else {
                left = mid + 1;  // 答案一定更大
            }
        }

        return left;
    }

private:
    bool check(vector<int>& nums, int value) {
        // 检查 value 是否满足条件
        return true;
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：搜索插入位置
// LeetCode 35: Search Insert Position
// ============================================================================

class Solution_SearchInsert {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};

// ============================================================================
// 变体 2：在排序数组中查找元素的第一个和最后一个位置
// LeetCode 34: Find First and Last Position
// ============================================================================

class Solution_SearchRange {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};

        int left = findLeft(nums, target);
        int right = findRight(nums, target);

        if (left <= right) {
            return {left, right};
        }

        return {-1, -1};
    }

private:
    int findLeft(vector<int>& nums, int target) {
        int left = 0, right = nums.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

    int findRight(vector<int>& nums, int target) {
        int left = 0, right = nums.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left - 1;
    }
};

// ============================================================================
// 变体 3：搜索旋转排序数组
// LeetCode 33: Search in Rotated Sorted Array
// ============================================================================

class Solution_SearchRotated {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) return mid;

            // 判断哪一半是有序的
            if (nums[left] <= nums[mid]) {
                // 左半部分有序
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // 右半部分有序
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};

// ============================================================================
// 变体 4：寻找峰值
// LeetCode 162: Find Peak Element
// ============================================================================

class Solution_FindPeakElement {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[mid + 1]) {
                // 峰值在左侧（包括 mid）
                right = mid;
            } else {
                // 峰值在右侧
                left = mid + 1;
            }
        }

        return left;
    }
};

// ============================================================================
// 变体 5：x 的平方根
// LeetCode 69: Sqrt(x)
// ============================================================================

class Solution_MySqrt {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;

        int left = 1, right = x;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long square = (long long)mid * mid;

            if (square == x) {
                return mid;
            } else if (square < x) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return right;  // 返回 right
    }
};

// ============================================================================
// 变体 6：分割数组的最大值（二分答案）
// LeetCode 410: Split Array Largest Sum
// ============================================================================

class Solution_SplitArray {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = *max_element(nums.begin(), nums.end());
        int right = 0;
        for (int num : nums) right += num;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (canSplit(nums, k, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }

private:
    bool canSplit(vector<int>& nums, int k, int maxSum) {
        int count = 1, sum = 0;

        for (int num : nums) {
            if (sum + num > maxSum) {
                count++;
                sum = num;
            } else {
                sum += num;
            }
        }

        return count <= k;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【30 秒讲清二分】
 * 1. 先说明可二分依据：
 *    "数组有序/答案空间有单调性，因此可以二分缩小范围。"
 * 2. 再说明区间定义：
 *    "我统一用 [left, right] 或 [left, right) 之一，避免边界混乱。"
 * 3. 最后给收缩逻辑：
 *    "通过 mid 判断目标落在左半还是右半，每轮排除一半。"
 *
 * 【面试官高频追问】
 * Q1: 如何避免溢出？
 * A1: mid = left + (right - left) / 2。
 *
 * Q2: 为什么答案二分成立？
 * A2: check(x) 具有单调性，存在清晰分界点。
 */

/*
 * ============================================================================
 * 第六部分：易错点
 * ============================================================================
 */

/*
 * 【常见错误 1：区间与循环条件不匹配】
 * ❌ [left,right] 却写 while(left < right)
 * ✅ 闭区间对应 while(left <= right)
 *
 * 【常见错误 2：边界更新漏掉 mid】
 * ❌ right = mid（闭区间下可能死循环）
 * ✅ 闭区间写 right = mid - 1
 *
 * 【常见错误 3：边界题返回值错位】
 * ❌ 左边界题返回 right
 * ✅ 左边界返回 left（按模板定义）
 *
 * 【常见错误 4：答案二分 check 方向写反】
 * ✅ 可行时收右边界，不可行时收左边界（求最小可行值）
 */

/*
 * ============================================================================
 * 第七部分：复杂度分析
 * ============================================================================
 */

/*
 * 【时间复杂度】
 * 每次排除一半，循环次数约 log2(n)
 * 总时间：O(log n)
 *
 * 【空间复杂度】
 * 迭代实现仅常数变量：O(1)
 */

/*
 * ============================================================================
 * 第八部分：真题实战
 * ============================================================================
 */

/*
 * ⭐ 简单
 * 1. LC 704: 二分查找
 * 2. LC 35: 搜索插入位置
 *
 * ⭐⭐ 中等（高频）
 * 3. LC 34: 在排序数组中查找元素的第一个和最后一个位置 ⭐⭐⭐⭐⭐
 * 4. LC 33: 搜索旋转排序数组 ⭐⭐⭐⭐⭐
 * 5. LC 153: 寻找旋转排序数组中的最小值 ⭐⭐⭐⭐
 * 6. LC 162: 寻找峰值 ⭐⭐⭐⭐
 *
 * ⭐⭐⭐ 进阶（答案二分）
 * 7. LC 875: 爱吃香蕉的珂珂
 * 8. LC 410: 分割数组的最大值 ⭐⭐⭐⭐
 */

/*
 * ============================================================================
 * 第九部分：完整示例
 * ============================================================================
 */

void testBoundarySearch() {
    LeftBoundBinarySearch leftSolver;
    RightBoundBinarySearch rightSolver;
    vector<int> nums = {1, 2, 2, 2, 3, 4};

    cout << "target=2 左边界: " << leftSolver.leftBound(nums, 2) << endl;
    cout << "target=2 右边界: " << rightSolver.rightBound(nums, 2) << endl;
}

/*
 * ============================================================================
 * 第十部分：速查表
 * ============================================================================
 */

/*
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │                  Binary Search 算法速查表                                │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * 【标准查找】
 * while (left <= right) {
 *     mid = left + (right - left) / 2;
 *     if (nums[mid] == target) return mid;
 *     if (nums[mid] < target) left = mid + 1;
 *     else right = mid - 1;
 * }
 *
 * 【左边界】
 * while (left < right) {
 *     mid = left + (right - left) / 2;
 *     if (nums[mid] < target) left = mid + 1;
 *     else right = mid;
 * }
 *
 * 【答案二分】
 * if (check(mid)) right = mid;
 * else left = mid + 1;
 *
 * 【关键词】
 * ✓ 有序数组
 * ✓ 查找边界
 * ✓ 最小可行值 / 最大可行值
 */

int main() {
    BasicBinarySearch sol;
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    int target = 7;

    cout << "查找 " << target << " 的位置: " << sol.binarySearch(nums, target) << endl;
    testBoundarySearch();
    cout << "二分查找算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o binary_search binary_search_template.cpp && ./binary_search
 */
