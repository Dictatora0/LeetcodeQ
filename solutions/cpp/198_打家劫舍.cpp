#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
LeetCode 198. 打家劫舍
题型：线性动态规划
核心思路：到第 i 间房时，只能在“不偷当前房”与“偷当前房并接上 i-2”之间取较大值。
复杂度：时间 O(n)，空间 O(n)
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {1, 2, 3, 1};
    vector<int> nums2 = {2, 7, 9, 3, 1};

    cout << "case 1: " << solution.rob(nums1) << " (expected 4)" << endl;
    cout << "case 2: " << solution.rob(nums2) << " (expected 12)" << endl;

    return 0;
}
