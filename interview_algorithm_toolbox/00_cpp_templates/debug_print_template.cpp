/*
题目 / 示例名称：本地调试输出模板
核心知识点：调试打印、`cerr`、`#ifdef LOCAL`
适用场景：本地调试数组、指针、窗口状态，但提交到 OJ 时不想保留调试输出
关键思路：把调试函数写成独立工具，并用编译宏控制是否启用
时间复杂度：O(n)
空间复杂度：O(1) 额外空间
常见错误：
1. 直接把调试输出写到 `cout`，导致格式错误。
2. 调试结束后忘记删除输出。
3. 本地调试时打印太多内容，看不出重点。
示例输入：
5
1 3 5 7 9
示例输出：
25
手动推演：
标准输出只保留总和；如果本地使用 `-DLOCAL` 编译，还会在错误流打印数组内容。
对比说明：
- `cout` 是正式答案输出。
- `cerr` 常用于本地调试，通常不会参与在线判题结果比对。
*/

#include <iostream>
#include <vector>

using namespace std;

void debugVector(const vector<long long>& values, const string& name) {
#ifdef LOCAL
    cerr << name << " = [";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            cerr << ", ";
        }
        cerr << values[i];
    }
    cerr << "]\n";
#else
    (void)values;
    (void)name;
#endif
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<long long> values(n);
    long long sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> values[i];
        sum += values[i];
    }

    debugVector(values, "values");
    cout << sum << '\n';
    return 0;
}
