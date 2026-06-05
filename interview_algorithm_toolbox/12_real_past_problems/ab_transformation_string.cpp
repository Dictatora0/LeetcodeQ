/*
题目 / 示例名称：ab 变换串
核心知识点：前缀状态、合法括号序列、计数器
适用场景：从“不断插入固定模式串”转化为“是否合法前缀结构”的题
关键思路：
1. 把 `a` 看成左括号，把 `b` 看成右括号。
2. 从空串开始不断插入 `ab`，等价于最后得到的串必须是合法括号序列。
3. 因而只需检查：
   - 任意前缀中 `a` 的数量不能少于 `b`
   - 最终 `a` 和 `b` 的数量必须相等
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 只检查 `a` 和 `b` 总数是否相等，例如 `abba` 数量相等但不合法。
2. 中途 `balance < 0` 后不立即返回。
3. 没意识到单类型括号只需计数器，多类型括号才需要栈。
示例输入：
8
a
b
ab
ba
aabb
abab
abba
aaabbb
示例输出：
NO
NO
YES
NO
YES
YES
NO
YES
手动推演：
`abba` 中前缀 `abb` 的 `b` 比 `a` 多，所以一定不可能通过插入 `ab` 得到。
反向看也能理解：如果不断删除相邻 `ab`，合法串最终一定能删空。
对比说明：
- 单类型括号：计数器就够。
- 多类型括号：顺序信息更复杂，要用栈。
*/

#include <iostream>

using namespace std;

bool isValidABString(const string& s) {
    int balance = 0;

    for (char ch : s) {
        if (ch == 'a') {
            // 把 a 当成左括号，看到一个就让 balance 加 1。
            ++balance;
        } else if (ch == 'b') {
            // 把 b 当成右括号，看到一个就让 balance 减 1。
            --balance;
        } else {
            return false;
        }

        // 一旦某个前缀里 b 比 a 多，就相当于右括号先出现，已经不可能合法。
        if (balance < 0) {
            return false;
        }
    }

    // 最后 balance 必须回到 0，表示 a 和 b 的总数也完全匹配。
    return balance == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        string s;
        cin >> s;
        // 合法就输出 YES，否则输出 NO。
        cout << (isValidABString(s) ? "YES" : "NO") << '\n';
    }

    return 0;
}
