#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

/*
LeetCode 215. 数组中的第 K 个最大元素
题型：快速选择 / Top K
核心思路：把第 k 大转成第 n-k 小，用三路划分缩小搜索区间，直到目标下标落入等于 pivot 的区间。
复杂度：平均时间 O(n)，最坏 O(n^2)，空间 O(1)
*/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        int target = n - k;  // 转成第 target 小
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int pivot = nums[left + rand() % (right - left + 1)];

            int lt = left;   // nums[left..lt-1] < pivot
            int i = left;    // nums[lt..i-1] == pivot
            int gt = right;  // nums[gt+1..right] > pivot

            while (i <= gt) {
                if (nums[i] < pivot) {
                    swap(nums[lt], nums[i]);
                    lt++;
                    i++;
                } else if (nums[i] > pivot) {
                    swap(nums[i], nums[gt]);
                    gt--;
                } else {
                    i++;
                }
            }

            // 现在：
            // [left..lt-1] < pivot
            // [lt..gt] == pivot
            // [gt+1..right] > pivot

            if (target < lt) {
                right = lt - 1;
            } else if (target > gt) {
                left = gt + 1;
            } else {
                return nums[target];
            }
        }

        return -1;
    }
};


int main() {
    Solution s;
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};

    cout << "case 1: " << s.findKthLargest(nums1, 2) << " (expected 5)" << endl;
    cout << "case 2: " << s.findKthLargest(nums2, 4) << " (expected 4)" << endl;

    return 0;
}
