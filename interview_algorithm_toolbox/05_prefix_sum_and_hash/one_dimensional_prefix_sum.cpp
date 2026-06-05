/*
题目 / 示例名称：一维前缀和区间查询
核心知识点：前缀和、区间和、1-based 下标
适用场景：数组不修改，但要回答多次区间求和查询
关键思路：定义 `prefix[i]` 为前 i 个数的和，则 `[l, r]` 的和等于 `prefix[r] - prefix[l - 1]`
时间复杂度：预处理 O(n)，每次查询 O(1)
空间复杂度：O(n)
常见错误：
1. `prefix` 开成 n 个元素，结果访问 `prefix[0]` 或 `prefix[n]` 混乱。
2. 忘记题目输入是 1-based 还是 0-based。
3. 区间和用 int，累计后溢出。
示例输入：
5 3
1 2 3 4 5
1 3
2 5
4 4
示例输出：
6
14
4
手动推演：
prefix = [0,1,3,6,10,15]
[2,5] 的和 = prefix[5] - prefix[1] = 15 - 1 = 14
对比说明：
- 少量查询：暴力也能做。
- 多次查询：前缀和是标准做法。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) {
        return 0;
    }

    // prefix[i] 表示前 i 个数的和，因此下标从 0 开到 n 最稳。
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        // prefix[i] 表示前 i 个数的和。
        // 这样后面就能用“两个前缀和相减”直接得到任意区间和。
        // 这里使用 1-based 前缀和，所以 prefix[0] 自然就是“前 0 个数的和”。
        prefix[i] = prefix[i - 1] + x;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        // 区间 [l, r] 的和 = 前 r 个数的和 - 前 l-1 个数的和。
        // 这个公式之所以成立，是因为前 l-1 个数的部分被相减后正好抵消掉了。
        cout << prefix[r] - prefix[l - 1] << '\n';
    }

    return 0;
}
