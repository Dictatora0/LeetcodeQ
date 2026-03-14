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
    int binarySearchAnswer(vector<int>& nums, int target) {
        int left = 最小可能答案;
        int right = 最大可能答案;

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
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 说明为什么用二分：有序、单调性
 * 2. 画图解释搜索过程
 * 3. 强调边界处理：left、right、mid 的取值
 *
 * 【易错点】
 * ❌ mid 计算溢出：用 left + (right - left) / 2
 * ❌ 死循环：left = mid 时要用 mid = left + (right - left + 1) / 2
 * ❌ 边界条件：left <= right vs left < right
 * ❌ 返回值：返回 left 还是 right
 *
 * 【复杂度】
 * 时间：O(logn)
 * 空间：O(1)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 35, LC 34, LC 33
 * ⭐⭐⭐⭐ LC 162, LC 69, LC 410
 *
 * 【速查表】
 * // 基础二分
 * int left = 0, right = n - 1;
 * while (left <= right) {
 *     int mid = left + (right - left) / 2;
 *     if (nums[mid] == target) return mid;
 *     else if (nums[mid] < target) left = mid + 1;
 *     else right = mid - 1;
 * }
 *
 * // 左边界
 * int left = 0, right = n;
 * while (left < right) {
 *     int mid = left + (right - left) / 2;
 *     if (nums[mid] < target) left = mid + 1;
 *     else right = mid;
 * }
 * return left;
 *
 * // 右边界
 * int left = 0, right = n;
 * while (left < right) {
 *     int mid = left + (right - left) / 2;
 *     if (nums[mid] <= target) left = mid + 1;
 *     else right = mid;
 * }
 * return left - 1;
 *
 * 【三种模板对比】
 * 1. 基础：left <= right, return mid
 * 2. 左边界：left < right, right = mid, return left
 * 3. 右边界：left < right, left = mid + 1, return left - 1
 */

int main() {
    BasicBinarySearch sol;
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    int target = 7;

    cout << "查找 " << target << " 的位置: " << sol.binarySearch(nums, target) << endl;
    cout << "二分查找算法模板测试完成" << endl;

    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o binary_search binary_search_template.cpp && ./binary_search
 */
