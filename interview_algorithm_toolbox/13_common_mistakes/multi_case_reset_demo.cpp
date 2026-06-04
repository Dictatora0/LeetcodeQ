/*
题目 / 示例名称：多组数据重置示例
核心知识点：多测重置、局部变量、容器清空
适用场景：第一行给出 T，每组都要独立计算答案
关键思路：把每组专属变量和容器定义在循环内部，天然完成重置
时间复杂度：O(总输入规模)
空间复杂度：O(每组 n)
常见错误：
1. `vector` 定义在循环外，忘记清空。
2. 计数器在上一组基础上继续累加。
3. `unordered_map` 没有 `clear()` 就复用。
示例输入：
2
5
1 1 2 3 3
4
2 2 2 2
示例输出：
3
1
手动推演：
第一组不同元素有 1、2、3 共 3 个；第二组只有 2 这一种。
对比说明：
- 最稳妥的重置方式，就是别复用上一组状态。
- 如果必须复用容器，也要显式 `clear()`。
*/

#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        int n;
        cin >> n;

        unordered_set<int> distinct_values;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            distinct_values.insert(x);
        }

        cout << distinct_values.size() << '\n';
    }

    return 0;
}
