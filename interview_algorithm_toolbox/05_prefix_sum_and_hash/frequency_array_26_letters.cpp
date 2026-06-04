/*
题目 / 示例名称：26 个字母的频率查询
核心知识点：频次数组、O(1) 查询
适用场景：给定一个小写字符串，后续多次询问某个字母出现次数
关键思路：先用长度为 26 的数组统计，再用 `query - 'a'` 直接查询
时间复杂度：预处理 O(n)，每次查询 O(1)
空间复杂度：O(1)
常见错误：
1. 把字符当作数组下标直接用，导致下标超出 0..25。
2. 题目不是小写字母，却强行用 26 长度数组。
3. 可以 O(1) 查还去遍历整串，浪费时间。
示例输入：
abacaba
4
a
b
c
z
示例输出：
4
2
1
0
手动推演：
freq['a'] = 4, freq['b'] = 2, freq['c'] = 1，其余都是 0。
对比说明：
- 小范围固定字符集：频次数组优先。
- 字符集很大或不固定：再考虑哈希表。
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

    int q;
    cin >> q;
    while (q--) {
        char query;
        cin >> query;
        cout << freq[query - 'a'] << '\n';
    }

    return 0;
}
