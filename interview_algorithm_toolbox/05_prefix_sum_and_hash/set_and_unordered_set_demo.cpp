/*
题目 / 示例名称：set 与 unordered_set 去重演示
核心知识点：去重、自动排序、哈希集合
适用场景：题目要求判断是否有重复、统计不同元素个数、输出去重后的有序结果
关键思路：
1. `set`：插入后自动去重并保持有序。
2. `unordered_set`：只关心是否出现过、是否重复时更直接。
时间复杂度：`set` 为 O(n log n)，`unordered_set` 为均摊 O(n)
空间复杂度：O(n)
常见错误：
1. 需要有序输出却用了 `unordered_set`。
2. 看到“去重”就先排序，其实很多题只要哈希集合即可。
3. 误以为 `unordered_set` 的遍历顺序稳定。
示例输入：
7
4 2 4 1 3 2 5
示例输出：
duplicate YES
unique_count 5
ordered 1 2 3 4 5
手动推演：
4 和 2 都重复出现，所以有重复；不同元素是 1,2,3,4,5 共 5 个。
对比说明：
- 判重：`unordered_set` 非常自然。
- 既要去重又要升序输出：`set` 更省心。
*/

#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    // ordered_unique 保存去重后的有序结果。
    set<int> ordered_unique;
    // seen 只负责快速判断“之前是否出现过”。
    unordered_set<int> seen;
    bool has_duplicate = false;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        if (seen.count(x)) {
            // 之前见过这个数，说明存在重复。
            has_duplicate = true;
        }
        // unordered_set 负责判重。
        seen.insert(x);
        // set 负责去重并维护有序结果。
        ordered_unique.insert(x);
    }

    cout << "duplicate " << (has_duplicate ? "YES" : "NO") << '\n';
    // ordered_unique.size() 就是不同元素个数。
    cout << "unique_count " << ordered_unique.size() << '\n';
    cout << "ordered";
    for (int x : ordered_unique) {
        // set 的遍历顺序天然是从小到大。
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
