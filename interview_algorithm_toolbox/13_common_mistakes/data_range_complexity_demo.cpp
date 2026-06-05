/*
题目 / 示例名称：数据范围与复杂度判断示例
核心知识点：数据范围、复杂度估计、算法选择
适用场景：拿到题目先判断 O(n)、O(n log n)、O(n^2) 是否可能通过
关键思路：把可承受操作次数粗略看成 1e8 级别，再估计不同复杂度的大概规模
时间复杂度：O(log n)，这里只做少量数学计算
空间复杂度：O(1)
常见错误：
1. 看见题就写，完全不先看数据范围。
2. `n = 2e5` 还写 O(n^2)。
3. 把经验值当绝对规则，不结合语言和常数因子判断。
示例输入：
100000
示例输出：
O(n) YES
O(n log n) YES
O(n^2) NO
O(n^3) NO
手动推演：
当 n = 1e5 时，O(n^2) 大约是 1e10 次操作，通常超时。
对比说明：
- 这是经验判断，不是数学定理。
- 笔试里先做这个判断，能帮你快速排除错误方向。
*/

#include <cmath>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long double n;
    if (!(cin >> n)) {
        return 0;
    }

    const long double limit = 1e8L;
    // n log n 是竞赛里很常见的一条经验边界线。
    long double nlogn = (n <= 1.0L ? 0.0L : n * log2(n));

    cout << "O(n) " << (n <= limit ? "YES" : "NO") << '\n';
    cout << "O(n log n) " << (nlogn <= limit ? "YES" : "NO") << '\n';
    cout << "O(n^2) " << (n * n <= limit ? "YES" : "NO") << '\n';
    cout << "O(n^3) " << (n * n * n <= limit ? "YES" : "NO") << '\n';
    return 0;
}
