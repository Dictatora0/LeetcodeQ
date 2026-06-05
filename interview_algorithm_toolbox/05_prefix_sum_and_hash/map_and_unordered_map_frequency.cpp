/*
题目 / 示例名称：map 与 unordered_map 频率统计
核心知识点：`map`、`unordered_map`、频率统计
适用场景：既想理解“按键有序输出”，又想理解“均摊 O(1) 查询”
关键思路：
1. 用 `map` 统计并按键升序输出。
2. 用 `unordered_map` 做后续查询。
时间复杂度：构建 `map` 为 O(n log n)，构建 `unordered_map` 均摊 O(n)
空间复杂度：O(n)
常见错误：
1. 想按顺序输出却用了 `unordered_map`。
2. 忘记 `unordered_map` 不保证遍历顺序。
3. 需要极稳最坏复杂度时却只背均摊复杂度。
示例输入：
6 3
5 2 5 7 2 5
5
2
9
示例输出：
ordered
2 2
5 3
7 1
queries
3
2
0
手动推演：
数字 5 出现 3 次，2 出现 2 次，7 出现 1 次。
对比说明：
- `map`：自动有序，适合要按 key 升序输出的题。
- `unordered_map`：查找快，适合“只问某个值出现了几次”。
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) {
        return 0;
    }

    vector<int> a(n);
    // ordered_frequency 用于“按 key 升序输出频率表”。
    map<int, int> ordered_frequency;
    // hash_frequency 用于“按值快速查询出现次数”。
    unordered_map<int, int> hash_frequency;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        // map 会按 key 自动排序，适合后面有序输出。
        ++ordered_frequency[a[i]];
        // unordered_map 更适合后面做“出现次数查询”。
        ++hash_frequency[a[i]];
    }

    cout << "ordered\n";
    for (const auto& [value, count] : ordered_frequency) {
        // 遍历 map 时，value 是按升序出现的。
        cout << value << ' ' << count << '\n';
    }

    cout << "queries\n";
    while (q--) {
        int x;
        cin >> x;
        // 没出现过的 key 会得到默认值 0。
        cout << hash_frequency[x] << '\n';
    }

    return 0;
}
