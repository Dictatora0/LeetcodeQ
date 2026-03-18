#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
LeetCode 55. 跳跃游戏
题型：贪心
核心思路：维护当前位置之前能覆盖到的最远下标，只要当前位置没有超过这个边界，就还能继续推进。
复杂度：时间 O(n)，空间 O(1)
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int far = 0;
        for (int i = 0; i < n; ++i) {
            if (i > far) {
                return false;
            }
            far = max(far, i + nums[i]);
            if (far >= n - 1) {
                return true;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {3, 2, 1, 0, 4};

    cout << boolalpha;
    cout << "case 1: " << solution.canJump(nums1) << " (expected true)" << endl;
    cout << "case 2: " << solution.canJump(nums2) << " (expected false)" << endl;

    return 0;
}
