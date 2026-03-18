#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
LeetCode 121. 买卖股票的最佳时机
题型：贪心 / 状态机 DP
核心思路：一边遍历一边维护历史最低买入价，用当前价格减最低价更新最大利润。
复杂度：时间 O(n)，空间 O(1)
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;

        int ans = 0;
        int minPrice = prices[0];

        for (int price : prices) {
            ans = max(ans, price - minPrice);
            minPrice = min(minPrice, price);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    vector<int> prices2 = {7, 6, 4, 3, 1};

    cout << "case 1: " << solution.maxProfit(prices1) << " (expected 5)" << endl;
    cout << "case 2: " << solution.maxProfit(prices2) << " (expected 0)" << endl;

    return 0;
}
