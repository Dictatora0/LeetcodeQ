/*
题目 / 示例名称：区间内奇数个数查询
核心知识点：前缀计数、条件转 0/1、区间查询
适用场景：多次查询某个区间内“满足条件的元素有多少个”
关键思路：
1. 把每个元素是否为奇数转成 0 或 1。
2. `prefix[i]` 表示前 i 个数里奇数的个数。
3. 区间 `[l, r]` 内奇数个数是 `prefix[r] - prefix[l - 1]`。
时间复杂度：预处理 O(n)，每次查询 O(1)
空间复杂度：O(n)
常见错误：
1. 只会做区间和，却没意识到“条件计数”也能做成前缀和。
2. 条件数组忘记转成 0/1，公式不统一。
3. 下标是 1-based 时公式仍照搬 0-based。
示例输入：
5 3
1 2 3 4 5
1 5
2 4
3 3
示例输出：
3
1
1
手动推演：
奇数标记数组是 [1,0,1,0,1]。
所以 [2,4] 中只有数字 3 是奇数，答案为 1。
对比说明：
- 区间和：直接存原值前缀和。
- 区间条件计数：先把“满足条件”转成 0/1 再做前缀和。
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

    // prefix[i] 表示前 i 个数中“满足条件”的元素个数。
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        // 先把“是否为奇数”转成 0/1，再做前缀和。
        // 如果 x 是奇数，本轮给前缀计数加 1；否则加 0。
        prefix[i] = prefix[i - 1] + (x % 2 != 0 ? 1 : 0);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        // 区间奇数个数就是这段 0/1 数组的区间和。
        // prefix[r] 覆盖了前 r 个数，prefix[l - 1] 覆盖了前 l-1 个数。
        // 两者相减，剩下的正好是 [l, r] 这段的贡献。
        cout << prefix[r] - prefix[l - 1] << '\n';
    }

    return 0;
}
