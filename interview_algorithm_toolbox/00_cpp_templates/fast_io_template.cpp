/*
题目 / 示例名称：Fast IO 基础模板
核心知识点：`ios::sync_with_stdio(false)`、`cin.tie(nullptr)`、`\n`
适用场景：输入规模较大，但题目逻辑本身不复杂
关键思路：先把输入输出模板写稳，再做具体算法
时间复杂度：O(n)
空间复杂度：O(1) 额外空间
常见错误：
1. 使用 `endl` 频繁刷新缓冲区，导致性能下降。
2. 同时混用 `cin/cout` 与 `scanf/printf`。
3. 把 fast io 忘在 main 之后的逻辑里，导致模板不统一。
示例输入：
6
10 20 30 40 50 60
示例输出：
210
手动推演：
这只是最小快读模板示例，把 6 个数求和即可。
对比说明：
- `'\n'` 只换行，不强制刷新缓冲区，通常比 `endl` 更适合笔试。
- 如果题目数据很小，不开 fast io 也能过，但统一模板更不容易失误。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        sum += x;
    }

    cout << sum << '\n';
    return 0;
}
