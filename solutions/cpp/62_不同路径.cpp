#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LeetCode 62: 不同路径

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n,1);
        for(int i = 1;i < m;i++){
            for(int j = 1;j<n;j++){
                dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    
    return 0;
}
