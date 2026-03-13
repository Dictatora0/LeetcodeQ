
/*
算法名称：前缀和 Prefix Sum

算法核心思想
-----------
用 prefix[i] 记录前 i 个元素的累积和，
将区间和查询转化为 O(1) 计算：sum(l,r)=prefix[r]-prefix[l-1]。

思路要点
-------
- 一维前缀和用于数组区间和
- 二维前缀和用于子矩阵求和
- 前缀和 + 哈希表可以统计满足条件的区间数量
- 差分数组可以高效处理区间加法

什么时候使用
-----------
适用场景：
- 子数组和/区间和
- 多次查询区间和
- 区间计数问题（和为 k）
- 需要大量区间更新（差分）

常见算法变体
-----------
1) 一维前缀和
2) 二维前缀和
3) 前缀和 + 哈希表（子数组和为 k）
4) 前缀和取模（子数组和可整除 k）
5) 差分数组（区间更新）

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)

ASCII 示例
---------
nums: [1,2,3]
prefix: [0,1,3,6]
区间 [2,3] 和 = prefix[3] - prefix[1] = 5

典型题目扩展
-----------
- 560 Subarray Sum Equals K
- 1248 Count Number of Nice Subarrays
- 304 Range Sum Query 2D
- 974 Subarray Sums Divisible by K
- 238 Product of Array Except Self（前缀/后缀）

可直接使用的代码模板
------------------
见下方 PrefixSum_Template

常见错误
--------
- 忘记初始化 prefix[0]=0
- 哈希表统计时漏掉 cnt[0]=1
- 二维前缀和边界处理错误
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class PrefixSum_Template {
public:
    // 一维前缀和构建
    vector<int> buildPrefix(const vector<int>& nums) {
        vector<int> prefix(nums.size() + 1, 0);
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        return prefix;
    }

    // 二维前缀和构建
    vector<vector<int>> buildPrefix2D(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> pref(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + grid[i-1][j-1];
            }
        }
        return pref;
    }

    int query2D(const vector<vector<int>>& pref, int r1, int c1, int r2, int c2) {
        int a = r1 + 1, b = c1 + 1, c = r2 + 1, d = c2 + 1;
        return pref[c][d] - pref[a-1][d] - pref[c][b-1] + pref[a-1][b-1];
    }

    // 子数组和为 k 的数量
    int subarraySumK(const vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        int sum = 0, ans = 0;
        for (int x : nums) {
            sum += x;
            if (cnt.count(sum - k)) ans += cnt[sum - k];
            cnt[sum]++;
        }
        return ans;
    }

    // 子数组和可整除 k 的数量
    int subarrayDivByK(const vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        int sum = 0, ans = 0;
        for (int x : nums) {
            sum += x;
            int mod = ((sum % k) + k) % k;
            if (cnt.count(mod)) ans += cnt[mod];
            cnt[mod]++;
        }
        return ans;
    }

    // 差分数组：区间加法
    vector<int> buildDiff(const vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n, 0);
        diff[0] = nums[0];
        for (int i = 1; i < n; ++i) diff[i] = nums[i] - nums[i - 1];
        return diff;
    }

    void rangeAdd(vector<int>& diff, int l, int r, int delta) {
        diff[l] += delta;
        if (r + 1 < (int)diff.size()) diff[r + 1] -= delta;
    }

    vector<int> restoreFromDiff(const vector<int>& diff) {
        int n = diff.size();
        vector<int> nums(n, 0);
        nums[0] = diff[0];
        for (int i = 1; i < n; ++i) nums[i] = nums[i - 1] + diff[i];
        return nums;
    }
};

int main() {
    PrefixSum_Template solver;
    vector<int> nums = {1, 2, 3};
    auto prefix = solver.buildPrefix(nums);
    cout << "prefix[3] = " << prefix[3] << endl;
    cout << "子数组和为 3 的数量: " << solver.subarraySumK(nums, 3) << endl;
    return 0;
}
