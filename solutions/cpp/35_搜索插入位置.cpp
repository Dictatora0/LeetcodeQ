#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = left + (right - left) / 2;

        while(left<=right){
            if(nums[mid]==target){
                return mid;
            }else if(nums[mid]>target){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
