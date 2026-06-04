/*
题目 / 示例名称：queue 基础使用
核心知识点：队列、FIFO、push / front / pop
适用场景：BFS、按进入顺序处理任务
关键思路：先入队的元素先出队，这就是 BFS 能一层一层扩展的原因
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 把栈和队列的弹出顺序混淆。
2. 没判空就访问 `front()`。
3. BFS 里忘记在入队时标记访问，导致重复入队。
示例输入：
5
10 20 30 40 50
示例输出：
10 20 30 40 50
手动推演：
元素按输入顺序进入队列，也按相同顺序离开队列。
对比说明：
- `stack` 是后进先出。
- `queue` 是先进先出。
*/

#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        q.push(x);
    }

    bool first = true;
    while (!q.empty()) {
        if (!first) {
            cout << ' ';
        }
        first = false;
        cout << q.front();
        q.pop();
    }
    cout << '\n';
    return 0;
}
