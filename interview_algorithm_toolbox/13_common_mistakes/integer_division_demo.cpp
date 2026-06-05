/*
题目 / 示例名称：整数除法与向上取整
核心知识点：整数除法、强制类型转换、ceil division
适用场景：平均值、分组数量、页数、桶数、轮数
关键思路：
1. `a / b` 在整数类型下会直接截断小数部分。
2. 如果要得到小数结果，至少一边转成 `double`。
3. 正整数向上取整常用 `(a + b - 1) / b`。
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. `5 / 2` 以为会得到 2.5。
2. 需要向上取整时仍然直接写 `a / b`。
3. 忘记公式 `(a + b - 1) / b` 只适用于正整数场景。
示例输入：
5 2
示例输出：
int_div 2
real_div 2.5
ceil_div_positive 3
手动推演：
5 / 2 在整数除法里先算成 2；如果要分成几组，通常应该向上取整得到 3。
对比说明：
- “平均值”通常需要浮点。
- “至少需要多少组”通常要向上取整。
*/

#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    if (!(cin >> a >> b)) {
        return 0;
    }

    // 整数相除会直接截断小数部分。
    cout << "int_div " << (a / b) << '\n';
    cout << fixed << setprecision(1);
    // 至少一边转成 double，才能得到真正的小数结果。
    cout << "real_div " << (static_cast<double>(a) / static_cast<double>(b)) << '\n';
    cout.unsetf(ios::floatfield);
    // 正整数向上取整常用 (a + b - 1) / b。
    cout << "ceil_div_positive " << ((a + b - 1) / b) << '\n';
    return 0;
}
