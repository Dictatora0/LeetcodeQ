/*
题目 / 示例名称：1-based 下标防错示例
核心知识点：数组下标、1-based 与 0-based 转换
适用场景：题目中的位置编号从 1 开始，但你又想少做转换
关键思路：如果题面天然是 1-based，下标数组直接开成 `n + 1` 往往更稳
时间复杂度：O(n + q)
空间复杂度：O(n)
常见错误：
1. 数组只开 n 个元素，却访问到 `a[n]`。
2. 前缀和明明是 1-based，却按 0-based 套公式。
3. 读入位置后忘记减一或忘记不该减一。
示例输入：
5 3
10 20 30 40 50
1
3
5
示例输出：
10
30
50
手动推演：
输入位置本来就是 1、3、5，所以直接访问 `a[1]`、`a[3]`、`a[5]`。
对比说明：
- 题面 1-based：可以直接用 `vector<int> a(n + 1)`。
- 题面 0-based：就别强行转成 1-based，保持一致最重要。
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

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        // 题面本来就是 1-based，这里直接从 1 读到 n。
        cin >> a[i];
    }

    while (q--) {
        int index;
        cin >> index;
        // 直接访问 a[index]，不需要再做 -1 转换。
        cout << a[index] << '\n';
    }

    return 0;
}
