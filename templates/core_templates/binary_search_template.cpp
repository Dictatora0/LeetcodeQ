
/*
算法名称：二分查找 Binary Search

算法核心思想
-----------
在有序区间内，通过比较中点与目标值，
将搜索区间缩小一半，从而实现对数级查找。

思路要点
-------
- 明确区间是闭区间 [l, r] 还是左闭右开 [l, r)
- mid 计算用 l + (r-l)/2 防溢出
- 边界更新必须保证区间收缩
- 如果找边界，优先使用 lower/upper_bound 思路

什么时候使用
-----------
适用场景：
- 有序数组查找目标值
- 找“最小可行值 / 最大可行值”（答案单调）
- 旋转数组、边界查找

常见算法变体
-----------
1) 精确查找（返回目标下标）
2) 下界 lower_bound（第一个 >= target）
3) 上界 upper_bound（第一个 > target）
4) 答案二分（可行性单调）

复杂度分析
---------
时间复杂度：O(log n)
空间复杂度：O(1)

ASCII 示例
---------
数组：[-1,0,3,5,9,12], target=9
mid=2 -> 3 < 9
mid=4 -> 9 命中

典型题目扩展
-----------
- 704 Binary Search
- 35 Search Insert Position
- 33 Search in Rotated Sorted Array
- 875 Koko Eating Bananas
- 410 Split Array Largest Sum

可直接使用的代码模板
------------------
见下方 BinarySearch_Template

常见错误
--------
- 边界条件（l, r 是否包含）混乱
- 忘记处理 target 不存在
- 循环条件与更新不匹配
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class BinarySearch_Template {
public:
    // 精确查找
    int search(vector<int>& nums, int target) {
        int l = 0, r = static_cast<int>(nums.size()) - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) return m;
            if (nums[m] < target) l = m + 1;
            else r = m - 1;
        }
        return -1;
    }

    // lower_bound: 第一个 >= target 的位置
    int lowerBound(vector<int>& nums, int target) {
        int l = 0, r = static_cast<int>(nums.size());
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] < target) l = m + 1;
            else r = m;
        }
        return l;
    }

    // upper_bound: 第一个 > target 的位置
    int upperBound(vector<int>& nums, int target) {
        int l = 0, r = static_cast<int>(nums.size());
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] <= target) l = m + 1;
            else r = m;
        }
        return l;
    }

    // first/last occurrence
    int firstEqual(vector<int>& nums, int target) {
        int idx = lowerBound(nums, target);
        if (idx < (int)nums.size() && nums[idx] == target) return idx;
        return -1;
    }

    int lastEqual(vector<int>& nums, int target) {
        int idx = upperBound(nums, target) - 1;
        if (idx >= 0 && idx < (int)nums.size() && nums[idx] == target) return idx;
        return -1;
    }

    // 答案二分示例：最小 x 使 x*x >= target
    int firstSquareGE(int target) {
        int l = 0, r = target;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (m * 1LL * m >= target) r = m;
            else l = m + 1;
        }
        return l;
    }

    // 通用答案二分模板：找最小满足 check 的值
    int firstTrue(int l, int r, function<bool(int)> check) {
        while (l < r) {
            int m = l + (r - l) / 2;
            if (check(m)) r = m;
            else l = m + 1;
        }
        return l;
    }
};

int main() {
    vector<int> nums = {-1, 0, 3, 5, 9, 12, 12};
    BinarySearch_Template solver;
    cout << "search 9 -> " << solver.search(nums, 9) << endl;
    cout << "first 12 -> " << solver.firstEqual(nums, 12) << endl;
    cout << "last 12 -> " << solver.lastEqual(nums, 12) << endl;
    cout << "firstSquareGE(20) -> " << solver.firstSquareGE(20) << endl;
    return 0;
}
