#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        int i = 0;

        while(i<=right){
            if(nums[i]==0){
                swap(nums[left],nums[i]);
                i++;
                left++;
            }else if(nums[i]==1){
                i++;
            }else{
                swap(nums[i], nums[right]); 
                right--;
            }
        }
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
