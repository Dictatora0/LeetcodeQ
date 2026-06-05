/*
题目 / 示例名称：答案二分 + 数学 check - 最短生产时间
核心知识点：答案二分、数学 check、单调性、计数
适用场景：题目要求“最小时间 / 最小长度 / 最小值”，并且 check 过程是纯计数或数学判断，不依赖贪心
关键思路：
1. 有 n 台机器，第 i 台机器每 `time[i]` 时间生产 1 件产品。
2. 给定总时间 T，第 i 台机器能生产 `floor(T / time[i])` 件。
3. 如果总产量 `sum(T / time[i]) >= target`，说明时间 T 可行。
4. 时间越大，总产量越多，因此“是否可行”关于 T 具有单调性，可以二分答案。
5. 这类 check 不是贪心，而是纯数学计数。
时间复杂度：O(n log answer)
空间复杂度：O(1)
常见错误：
1. 不先证明单调性就直接二分。
2. 统计总产量时可能溢出，没有提前截断。
3. 右边界取太小，导致答案不在搜索区间内。
4. 把这类数学 check 和“分段贪心 check”混在一起。
示例输入：
3 7
3 2 5
示例输出：
8
手动推演：
时间 8 时：
速度为 3 的机器生产 `8 / 3 = 2` 件
速度为 2 的机器生产 `8 / 2 = 4` 件
速度为 5 的机器生产 `8 / 5 = 1` 件
总共 7 件，可行。
时间 7 时只能生产 `2 + 3 + 1 = 6` 件，不可行。
所以答案是 8。
对比说明：
- `answer_binary_search_minimize_max_segment_sum.cpp` 是“答案二分 + 贪心 check”。
- 本文件是“答案二分 + 数学 check”。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canProduce(const vector<long long>& time_cost, long long target, long long total_time) {
    long long produced = 0;

    for (long long cost : time_cost) {
        // 每台机器在 total_time 时间内的产量可以独立计算。
        produced += total_time / cost;

        // 只要已经达到目标，就可以提前返回，避免累加过大。
        if (produced >= target) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    if (!(cin >> n >> target)) {
        return 0;
    }

    vector<long long> time_cost(n);
    long long min_time_cost = 0;

    for (int i = 0; i < n; ++i) {
        cin >> time_cost[i];
        if (i == 0 || time_cost[i] < min_time_cost) {
            // 记录最快机器，用来构造一个一定可行的右边界。
            min_time_cost = time_cost[i];
        }
    }

    long long left = 1;
    long long right = min_time_cost * target;

    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (canProduce(time_cost, target, mid)) {
            // 当前时间已经够，继续尝试更短时间。
            right = mid;
        } else {
            // 当前时间不够，必须放宽到更大值。
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
