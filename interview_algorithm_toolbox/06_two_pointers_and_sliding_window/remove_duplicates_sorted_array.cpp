/*
题目 / 示例名称：有序数组原地去重
核心知识点：快慢指针、原地覆盖
适用场景：数组有序，要求把不同元素压缩到数组前部
关键思路：慢指针指向“当前已去重结果的最后一个位置”，快指针不断扫描新元素
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 数组无序却直接套模板。
2. 慢指针初始位置写错，导致覆盖越界。
3. 只求长度但忘了数组前缀已经被改写。
示例输入：
8
1 1 2 2 2 3 4 4
示例输出：
4
1 2 3 4
手动推演：
最终前 4 个位置保留 1,2,3,4，其余位置内容不再重要。
对比说明：
- 有序数组去重最适合快慢指针。
- 如果只是统计不同元素个数，也可以用 `set`，但空间更大。
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

    if (n == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // slow 指向“去重结果的最后一个有效位置”。
    int slow = 0;
    for (int fast = 1; fast < n; ++fast) {
        // 由于数组有序，相同元素一定挨在一起。
        // 因此只需拿 a[fast] 和当前去重结果尾部 a[slow] 比较。
        if (a[fast] != a[slow]) {
            // fast 找到一个新值，就把它覆盖到去重结果的下一个位置。
            ++slow;
            a[slow] = a[fast];
        } else {
            // 如果 a[fast] == a[slow]，说明它只是重复值，直接跳过即可。
        }
    }

    // slow 停在去重后最后一个有效元素位置，所以新长度是 slow + 1。
    int new_length = slow + 1;
    cout << new_length << '\n';
    for (int i = 0; i < new_length; ++i) {
        if (i > 0) {
            // 控制输出格式，避免最后多空格通常也是笔试常见细节。
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
