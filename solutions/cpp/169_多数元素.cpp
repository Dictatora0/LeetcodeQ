#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = nums[0];

        for(int num:nums){
            if(count==0){
                candidate = num;
            }

            if(num==candidate){
                count++;
            }else{
                count--;
            }
        }
        return candidate;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
