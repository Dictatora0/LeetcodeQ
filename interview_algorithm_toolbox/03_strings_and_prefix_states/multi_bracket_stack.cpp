/*
题目 / 示例名称：多类型括号合法性判断
核心知识点：栈、括号匹配、顺序约束
适用场景：字符串包含 `()[]{}`
关键思路：左括号入栈；遇到右括号时，必须与栈顶左括号类型匹配
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 试图只统计每种括号个数，忽略嵌套顺序。
2. 遇到右括号时没先判空栈。
3. 最后忘记检查栈是否清空。
示例输入：
{[()()]}
示例输出：
YES
手动推演：
入栈顺序是 { [ (，遇到 ) 时依次和最近的 ( 匹配，最终栈清空。
对比说明：
- 单类型括号只需 balance。
- 多类型括号需要“最近未匹配左括号”这个信息，所以必须用栈。
*/

#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    unordered_map<char, char> match = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    stack<char> st;

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else {
            if (st.empty()) {
                cout << "NO\n";
                return 0;
            }
            if (st.top() != match[ch]) {
                cout << "NO\n";
                return 0;
            }
            st.pop();
        }
    }

    cout << (st.empty() ? "YES" : "NO") << '\n';
    return 0;
}
