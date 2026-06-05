/*
题目 / 示例名称：和能被 k 整除的子数组个数
核心知识点：前缀和、取模统计、同余、哈希计数
适用场景：题目要求统计“子数组和满足某个模条件”的数量
关键思路：
1. 设 prefix[i] 表示前 i 个数的前缀和。
2. 子数组 [l, r] 的和等于 prefix[r] - prefix[l - 1]。
3. 如果这个差能被 k 整除，那么说明：
   prefix[r] % k == prefix[l - 1] % k。
4. 因此问题转化为：
   统计前缀和模 k 后，每个余数出现过多少次。
5. 当前前缀和余数为 rem 时，之前所有余数也等于 rem 的前缀，都能和当前前缀组成一个合法子数组。
时间复杂度：O(n)
空间复杂度：O(k) 或 O(不同余数个数)
常见错误：
1. 没意识到“差能被 k 整除”可以转成“两个前缀和余数相同”。
2. 负数取模后可能为负，没有手动修正到 0..k-1。
3. 忘记初始化 `remainder_count[0] = 1`，漏掉从下标 1 开始的合法子数组。
4. 把题目要的“个数”写成了只判断是否存在。
示例输入：
6 5
4 5 0 -2 -3 1
示例输出：
7
手动推演：
前缀和依次为：
4, 9, 9, 7, 4, 5
对 5 取模后为：
4, 4, 4, 2, 4, 0
相同余数之间都能形成和可被 5 整除的子数组。
对比说明：
- 区间和查询：直接做前缀和。
- 统计“满足模条件的子数组个数”：前缀和 + 余数频次统计。
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    unordered_map<long long, long long> remainder_count;
    // 余数 0 先出现一次，对应“前缀和还没开始累加”的状态。
    remainder_count[0] = 1;

    long long prefix_sum = 0;
    long long answer = 0;

    for (int i = 0; i < n; ++i) {
        prefix_sum += a[i];

        // C++ 中负数取模可能为负，因此统一修正到 [0, k - 1]。
        long long remainder = ((prefix_sum % k) + k) % k;

        // 之前所有余数相同的前缀，都能和当前前缀组成一个合法子数组。
        answer += remainder_count[remainder];

        // 把当前余数记下来，供后续位置继续配对使用。
        ++remainder_count[remainder];
    }

    cout << answer << '\n';
    return 0;
}
