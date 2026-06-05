/*
题目 / 示例名称：最后一个小于等于 target 的位置
核心知识点：upper_bound 思想、边界转换
适用场景：找最右满足条件的位置
关键思路：先找第一个 `> target` 的位置，再减一得到最后一个 `<= target` 的位置
时间复杂度：O(log n)
空间复杂度：O(1)
常见错误：
1. 直接硬写右边界，细节容易乱。
2. 找不到时返回 `-1` 的情况没处理。
3. 忘记 `left` 可能最后等于 0。
示例输入：
7 4
1 2 4 4 4 6 9
示例输出：
4
手动推演：
第一个 >4 的位置是 5，所以最后一个 <=4 的位置是 4。
对比说明：
- 右边界题通常可以转成 `upper_bound - 1`。
- 这种转化往往比直接硬写“最后一个满足”更稳。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    if (!(cin >> n >> target)) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int left = 0;
    int right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] > target) {
            // mid 已经太大，右边更不可能是答案。
            right = mid;
        } else {
            // mid 仍然满足 <= target，尝试把边界推进到更右边。
            left = mid + 1;
        }
    }

    // 循环结束后，left 指向第一个 > target 的位置，所以答案是 left - 1。
    cout << (left - 1) << '\n';
    return 0;
}
