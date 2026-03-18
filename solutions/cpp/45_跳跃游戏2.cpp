#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
LeetCode 45. 跳跃游戏 II
题型：贪心 / 区间覆盖
核心思路：把每一步能到达的区间当作一层，扫描当前层时同步更新下一层最远边界，走到层末尾就加一步。
复杂度：时间 O(n)，空间 O(1)
*/
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 1) return 0;

        int step = 0;
        int curEnd = 0;
        int nextEnd = 0;
        for (int i = 0; i < n - 1; ++i) {
            nextEnd = max(nextEnd, i + nums[i]);
            if (i == curEnd) {
                step++;
                curEnd = nextEnd;
            }
        }
        return step;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {2, 3, 0, 1, 4};

    cout << "case 1: " << solution.jump(nums1) << " (expected 2)" << endl;
    cout << "case 2: " << solution.jump(nums2) << " (expected 2)" << endl;

    return 0;
}
