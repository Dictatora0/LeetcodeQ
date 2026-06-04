/*
题目 / 示例名称：stack 基础使用演示
核心知识点：栈、LIFO、push / top / pop
适用场景：括号匹配、相邻消除、单调栈之前的基础容器理解
关键思路：先入栈的元素会后出栈，所以输出顺序和输入顺序相反
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 没判空就直接访问 `top()`。
2. 把栈和队列的弹出顺序混淆。
3. 以为 `pop()` 会返回栈顶元素，实际上它只负责删除。
示例输入：
5
1 2 3 4 5
示例输出：
5 4 3 2 1
手动推演：
依次入栈 1,2,3,4,5，栈顶最后是 5，所以出栈顺序是 5,4,3,2,1。
对比说明：
- 栈：后进先出。
- 队列：先进先出，见 `11_dfs_bfs/queue_basic_demo.cpp`。
*/

#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    stack<int> st;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        st.push(x);
    }

    bool first = true;
    while (!st.empty()) {
        if (!first) {
            cout << ' ';
        }
        first = false;

        cout << st.top();
        st.pop();
    }
    cout << '\n';

    return 0;
}
