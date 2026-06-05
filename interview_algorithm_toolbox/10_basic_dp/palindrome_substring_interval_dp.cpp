/*
题目 / 示例名称：区间 DP 入门 - 回文子串判定
核心知识点：区间 DP、回文判定、按区间长度转移
适用场景：题目要求判断某个子串是否为回文，或先预处理所有回文子串信息
关键思路：
1. 设 `dp[l][r]` 表示子串 `s[l..r]` 是否为回文串。
2. 如果 `s[l] != s[r]`，那么 `dp[l][r] = false`。
3. 如果 `s[l] == s[r]`，还要继续看中间这段：
   - 当区间长度为 1 或 2 时，首尾相等就已经足够构成回文。
   - 当区间长度 >= 3 时，还需要 `dp[l + 1][r - 1] = true`。
4. 因此状态转移为：
   `dp[l][r] = (s[l] == s[r]) && (len <= 2 || dp[l + 1][r - 1])`
5. 因为 `dp[l][r]` 依赖更短的区间 `dp[l + 1][r - 1]`，
   所以要按区间长度从小到大枚举。
时间复杂度：预处理 O(n^2)，每次查询 O(1)
空间复杂度：O(n^2)
常见错误：
1. 没按区间长度递增转移，导致 `dp[l + 1][r - 1]` 还没算出来。
2. 忘记长度为 1 和 2 的特殊情况。
3. 把下标含义写乱，分不清是 0-based 还是 1-based。
示例输入：
abacaba
4
1 7
2 6
1 3
2 5
示例输出：
YES
YES
YES
NO
手动推演：
- `abacaba` 整串本身是回文。
- `bacab` 也是回文。
- `aba` 是回文。
- `baca` 不是回文，因为首尾字符 `b` 和 `a` 就不同。
对比说明：
- 一维 DP 常见于“前缀转移”。
- 区间 DP 常见于“答案依赖更短区间”的问题。
- 本题的 `dp[l][r]` 以后也可以扩展到“最长回文子串”等题型。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    int q;
    cin >> q;

    int n = static_cast<int>(s.size());
    // dp[l][r] = 1 表示子串 s[l..r] 是回文。
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // 区间 DP 要按长度从短到长处理，
    // 因为长区间依赖更短的内部区间。
    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;

            if (s[l] != s[r]) {
                // 首尾字符不同，当前子串不可能是回文。
                dp[l][r] = 0;
                continue;
            }

            if (len <= 2) {
                // 长度为 1：单个字符一定是回文。
                // 长度为 2：两个字符相等就是回文。
                dp[l][r] = 1;
            } else {
                // 更长的区间还要看中间这段是否已经是回文。
                dp[l][r] = dp[l + 1][r - 1];
            }
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        // 输入按 1-based 给出，这里转成 0-based 后直接查表即可。
        cout << (dp[l][r] ? "YES" : "NO") << '\n';
    }

    return 0;
}
