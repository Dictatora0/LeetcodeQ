/*
题目 / 示例名称：升序与降序排序基础
核心知识点：`sort`、升序、降序、`greater<int>()`
适用场景：题目要求把数组按大小顺序输出
关键思路：先用默认升序，再用 `greater<long long>()` 做降序
时间复杂度：O(n log n)
空间复杂度：O(log n)，排序递归栈
常见错误：
1. 忘记 `#include <algorithm>`。
2. 降序时误写比较器导致顺序反了。
3. 排完升序后直接在同一个数组上做降序，却没意识到原顺序已经改变。
示例输入：
5
3 1 4 1 5
示例输出：
1 1 3 4 5
5 4 3 1 1
手动推演：
第一行是从小到大，第二行是从大到小。
对比说明：
- `sort(v.begin(), v.end())`：默认升序。
- `sort(v.begin(), v.end(), greater<long long>())`：标准库现成的降序写法。
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<long long>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> ascending = a;
    vector<long long> descending = a;

    sort(ascending.begin(), ascending.end());
    sort(descending.begin(), descending.end(), greater<long long>());

    printVector(ascending);
    printVector(descending);
    return 0;
}
