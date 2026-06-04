/*
题目 / 示例名称：字符串基础遍历
核心知识点：范围 for、字符分类、计数
适用场景：需要统计字符串里某些字符类别出现次数
关键思路：逐字符检查属于哪一类，然后分别累加
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 把字符和字符串混淆，例如拿 `string` 和 `'a'` 比。
2. 字符区间判断漏写等号。
3. 频繁用复杂函数做分类，结果把简单题写重。
示例输入：
aB3cD4
示例输出：
lowercase 2
uppercase 2
digits 2
手动推演：
小写字母是 a、c，大写字母是 B、D，数字是 3、4。
对比说明：
- `for (char ch : s)` 写法简洁，适合遍历每个字符。
- 如果需要修改字符，可以改用下标遍历。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    int lowercase_count = 0;
    int uppercase_count = 0;
    int digit_count = 0;

    for (char ch : s) {
        if ('a' <= ch && ch <= 'z') {
            ++lowercase_count;
        } else if ('A' <= ch && ch <= 'Z') {
            ++uppercase_count;
        } else if ('0' <= ch && ch <= '9') {
            ++digit_count;
        }
    }

    cout << "lowercase " << lowercase_count << '\n';
    cout << "uppercase " << uppercase_count << '\n';
    cout << "digits " << digit_count << '\n';
    return 0;
}
