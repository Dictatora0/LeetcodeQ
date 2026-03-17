#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();

        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int left = 0, right = m;

        while (left <= right) {
            int i = left + (right - left) / 2;
            int j = (m + n + 1) / 2 - i;

            int nums1LeftMax  = (i == 0) ? INT_MIN : nums1[i - 1];
            int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
            int nums2LeftMax  = (j == 0) ? INT_MIN : nums2[j - 1];
            int nums2RightMin = (j == n) ? INT_MAX : nums2[j];

            if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
                if ((m + n) % 2 == 1) {
                    return max(nums1LeftMax, nums2LeftMax);
                } else {
                    return ((long long)max(nums1LeftMax, nums2LeftMax)
                          + min(nums1RightMin, nums2RightMin)) / 2.0;
                }
            } 
            else if (nums1LeftMax > nums2RightMin) {
                right = i - 1;
            } 
            else {
                left = i + 1;
            }
        }

        return 0.0;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
