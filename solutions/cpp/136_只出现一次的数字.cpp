#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            res ^= nums[i];
        }
        //异或运算满足交换律
        return res;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
