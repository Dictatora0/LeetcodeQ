/*
题目 / 示例名称：单类型括号合法性判断
核心知识点：前缀状态、balance 计数器
适用场景：字符串只包含 '(' 和 ')'，需要判断是否为合法括号序列
关键思路：遇到左括号就加一，遇到右括号就减一；任何前缀都不能让 balance 变成负数
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 只判断左括号和右括号数量相等，却忽略前缀非法。
2. 中途 `balance < 0` 仍继续扫，浪费时间也不清晰。
3. 最后忘记检查 `balance == 0`。
示例输入：
(()())
示例输出：
YES
手动推演：
balance 依次为 1,2,1,2,1,0，全程非负且最终回到 0，所以合法。
对比说明：
- 单类型括号只需要计数器。
- 多类型括号光靠计数器不够，必须记录匹配顺序。
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

    int balance = 0;

    for (char ch : s) {
        if (ch == '(') {
            ++balance;
        } else {
            --balance;
        }

        if (balance < 0) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << (balance == 0 ? "YES" : "NO") << '\n';
    return 0;
}
