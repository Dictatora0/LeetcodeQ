#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while(left<right){
            int mid = left + (right - left) / 2;
            if (nums[mid]>nums[right]){
                left = mid + 1;
            }else{
                right = mid;
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
