/*
题目 / 示例名称：相邻相同字符消除
核心知识点：栈思想、字符串当栈用
适用场景：遇到“相邻字符相消 / 删除后继续相邻”的题
关键思路：把答案字符串当作栈。当前字符与栈顶相同就弹出，否则压入
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 删除一对字符后重新从头扫描，退化成 O(n^2)。
2. 忘记“删除后新的相邻字符还可能继续消除”。
3. 只会用 `stack<char>`，却不知道 `string` 也能当栈用。
示例输入：
abbaca
示例输出：
ca
手动推演：
读到 a -> [a]
读到 b -> [a,b]
读到 b -> 相同，弹出，变成 [a]
读到 a -> 相同，弹出，变成 []
读到 c -> [c]
读到 a -> [c,a]
对比说明：
- `stack<char>` 也能做。
- 用 `string` 做栈更方便最后直接输出结果。
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    string result;

    for (char ch : s) {
        if (!result.empty() && result.back() == ch) {
            result.pop_back();
        } else {
            result.push_back(ch);
        }
    }

    if (result.empty()) {
        cout << "EMPTY\n";
    } else {
        cout << result << '\n';
    }
    return 0;
}
