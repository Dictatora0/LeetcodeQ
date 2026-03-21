#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();

        int ans = nums[0];
        int maxF = nums[0];
        int minF = nums[0];

        for (int i = 1; i < n;i++){
            int mx = maxF;
            int mn = minF;

            maxF = max(nums[i], max(mx * nums[i], mn * nums[i]));
            minF = min(nums[i], min(mx * nums[i], mn * nums[i]));

            ans = max(maxF, ans);
        }

            return ans;
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
