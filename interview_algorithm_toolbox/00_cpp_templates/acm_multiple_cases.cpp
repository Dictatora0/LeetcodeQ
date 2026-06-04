/*
题目 / 示例名称：ACM 多组测试数据模板
核心知识点：多组测试、变量重置、每组独立统计
适用场景：输入第一行给出 T，后面有 T 组独立测试
关键思路：把每组需要重置的变量定义在 while / for 循环内部，避免污染下一组
时间复杂度：O(T * n)
空间复杂度：O(1) 额外空间
常见错误：
1. 把 `sum`、`odd_count` 写在循环外，导致多组答案串起来。
2. 忘记每组重新创建容器或清空容器。
3. 输出格式把 `Case #` 写错。
示例输入：
3
5
1 2 3 4 5
4
2 4 6 8
1
7
示例输出：
Case 1: sum=15 odd=3
Case 2: sum=20 odd=0
Case 3: sum=7 odd=1
手动推演：
第 1 组 odd 为 1,3,5 共 3 个；第 2 组全偶；第 3 组只有 7。
对比说明：
- 变量写在循环内部最稳。
- 如果题目没有要求 `Case x:`，就只输出答案，不要多写字样。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }

    for (int case_id = 1; case_id <= t; ++case_id) {
        int n;
        cin >> n;

        // 每组数据都重新开始统计，避免上一组的状态残留。
        long long sum = 0;
        int odd_count = 0;

        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            sum += x;

            if (x % 2 != 0) {
                ++odd_count;
            }
        }

        cout << "Case " << case_id << ": sum=" << sum
             << " odd=" << odd_count << '\n';
    }

    return 0;
}
