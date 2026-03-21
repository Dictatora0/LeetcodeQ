#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, 1e9);
        dp[0] = 0;
        for (int i = 1; i < n + 1;i++){
            for (int j = 1; j * j <= i;j++){
                dp[i] = min(dp[i], dp[i - j * j] + 1);
                }
            }
        
        return dp[n];
    }
};
int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
