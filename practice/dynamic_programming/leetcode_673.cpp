/*
 * LeetCode 673. xxx
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        // dp[i]：
        // 以 nums[i] 结尾的最长严格递增子序列的长度。
        //
        // 每个元素自身都可以构成一个长度为 1 的递增子序列，
        // 所以所有位置初始值均为 1。
        //
        // 例如 nums = [1, 3, 5]
        // 处理完成后：
        // dp = [1, 2, 3]
        vector<int> dp(n, 1);

        // count[i]：
        // 以 nums[i] 结尾，并且长度恰好为 dp[i] 的
        // 最长递增子序列一共有多少条。
        //
        // 每个元素自身都可以构成一条长度为 1 的子序列，
        // 所以所有位置初始值均为 1。
        //
        // 例如 nums = [1, 2, 2, 3]
        // 最后一个 3 前面有两个不同位置的 2：
        // [1, 第一个 2, 3]
        // [1, 第二个 2, 3]
        // 因此 count[3] = 2。
        vector<int> count(n, 1);

        // 记录整个数组中最长递增子序列的长度。
        int maxLength = 1;

        // 枚举每一个位置 i。
        // 当前目标是计算：
        // 1. 以 nums[i] 结尾的最长递增子序列长度 dp[i]
        // 2. 达到该长度的方案数量 count[i]
        for (int i = 0; i < n; i++)
        {

            // 枚举 nums[i] 前面的所有位置 j。
            // 如果 nums[j] < nums[i]，
            // 那么 nums[i] 可以接在以 nums[j] 结尾的递增子序列后面。
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {

                    // 情况一：
                    // 通过位置 j，可以构造出一个比当前记录更长的递增子序列。
                    //
                    // 例如：
                    // 当前 dp[i] = 2
                    // 但 dp[j] = 3
                    // 那么将 nums[i] 接到 nums[j] 后面，可以得到长度 4。
                    //
                    // 此时原来长度为 2 的方案已经不是最长方案，
                    // 所以需要覆盖掉原来的 count[i]。
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;

                        // 以 nums[j] 结尾的最长子序列有 count[j] 条。
                        // 把 nums[i] 接到这些子序列后面，
                        // 就会得到 count[j] 条新的最长子序列。
                        count[i] = count[j];
                    }

                    // 情况二：
                    // 通过位置 j，可以构造出另一批长度相同的最长递增子序列。
                    //
                    // 例如 nums = [1, 2, 2, 3]
                    // 当 i 指向 3 时：
                    // 从第一个 2 可以得到 [1, 第一个 2, 3]
                    // 从第二个 2 可以得到 [1, 第二个 2, 3]
                    //
                    // 两种方式得到的长度相同，因此需要累加方案数量。
                    else if (dp[j] + 1 == dp[i])
                    {
                        count[i] += count[j];
                    }
                }
            }

            // 更新整个数组中的最长递增子序列长度。
            maxLength = max(maxLength, dp[i]);
        }

        // 最终答案不一定只来自某一个位置。
        //
        // 例如 nums = [1, 3, 5, 4]
        // 最长递增子序列长度为 3：
        // [1, 3, 5]
        // [1, 3, 4]
        //
        // 它们分别以不同位置结尾。
        // 因此需要把所有 dp[i] == maxLength 的 count[i] 累加起来。
        int answer = 0;

        for (int i = 0; i < n; i++)
        {
            if (dp[i] == maxLength)
            {
                answer += count[i];
            }
        }

        return answer;
    }
};

int main()
{
    // TODO: 添加测试用例

    cout << "编译成功" << endl;
    return 0;
}
