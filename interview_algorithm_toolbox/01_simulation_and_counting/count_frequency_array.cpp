/*
题目 / 示例名称：用频次数组统计小写字母个数
核心知识点：字符串遍历、频次数组、字符到下标映射
适用场景：字符范围很小且固定，例如 26 个小写字母、10 个数字
关键思路：把 `ch - 'a'` 当成数组下标，出现一次就给对应格子加一
时间复杂度：O(n)
空间复杂度：O(1)，因为数组长度固定为 26
常见错误：
1. 忘记确认输入是否只包含小写字母。
2. 写成 `freq[ch]`，导致下标不是 0 到 25。
3. 没想清楚什么时候频次数组比 `unordered_map` 更适合。
示例输入：
abacaba
示例输出：
a 4
b 2
c 1
手动推演：
字符串中 a 出现 4 次，b 出现 2 次，c 出现 1 次。
对比说明：
- 26 个小写字母：优先频次数组，常数更小。
- 字符范围未知或很大：再考虑 `unordered_map<char, int>`。
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

    vector<int> freq(26, 0);
    for (char ch : s) {
        ++freq[ch - 'a'];
    }



    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            cout << static_cast<char>('a' + i) << ' ' << freq[i] << '\n';
        }
    }

    return 0;
}
