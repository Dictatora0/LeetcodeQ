#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int ans = nums.size();

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= target) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = lowerBound(nums, target);

        if (left == nums.size() || nums[left] != target) {
            return {-1, -1};
        }

        int right = lowerBound(nums, target + 1) - 1;

        return {left, right};
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
