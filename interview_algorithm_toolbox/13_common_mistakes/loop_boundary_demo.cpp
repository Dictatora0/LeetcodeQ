/*
题目 / 示例名称：循环边界与相邻元素扫描
核心知识点：`<` 与 `<=`、相邻访问、越界防护
适用场景：需要比较 `a[i]` 和 `a[i + 1]`，或扫描长度为 n 的数组
关键思路：
1. 如果要访问 `a[i + 1]`，那么 i 最大只能到 `n - 2`。
2. 所以循环应写成 `for (int i = 0; i + 1 < n; ++i)`。
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 写成 `i <= n - 1` 后又访问 `a[i + 1]`，直接越界。
2. 看见 `n - 1` 就本能地写 `<=`，没结合访问内容判断。
3. 逻辑只差一个边界，样例刚好没炸，正式数据才出问题。
示例输入：
5
1 3 2 4 5
示例输出：
3
手动推演：
相邻上升对有 `(1,3)`、`(2,4)`、`(4,5)`，共 3 对。
对比说明：
- 只访问 `a[i]`：通常 `i < n`。
- 同时访问 `a[i]` 和 `a[i + 1]`：通常 `i + 1 < n` 更直观。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int increasing_pairs = 0;
    for (int i = 0; i + 1 < n; ++i) {
        if (a[i] < a[i + 1]) {
            ++increasing_pairs;
        }
    }

    cout << increasing_pairs << '\n';
    return 0;
}
