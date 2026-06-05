/*
题目 / 示例名称：状态图 BFS - 最短操作次数
核心知识点：BFS、状态图、最短操作次数、去重访问
适用场景：题目给定起点和终点，以及若干离散操作，要求最少多少步把起点变成终点
关键思路：
1. 把“一个数字”看成图上的一个状态点。
2. 从状态 x 可以走到哪些状态，由允许的操作决定。
3. 本题允许三种操作：
   - `x - 1`
   - `x + 1`
   - `x * 2`
4. 每次操作代价都相同，都是 1 步，因此这是无权图最短路，直接用 BFS。
5. BFS 第一次到达目标状态时，得到的步数就是最少操作次数。
时间复杂度：O(limit)
空间复杂度：O(limit)
常见错误：
1. 用 DFS 找最短步数，复杂度高且容易错。
2. 状态入队时不立刻标记访问，导致重复入队。
3. 不给状态空间设置合理上界，导致越界或无限扩张。
示例输入：
5 17
示例输出：
4
手动推演：
一种最优路径是：
5 -> 4 -> 8 -> 16 -> 17
共 4 步。
对比说明：
- 网格最短路：状态是坐标 `(x, y)`
- 本题最短操作次数：状态是一个整数值
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int start, target;
    if (!(cin >> start >> target)) {
        return 0;
    }

    if (start == target) {
        cout << 0 << '\n';
        return 0;
    }

    // 这里取一个保守上界：
    // 如果目标更大，走到超过 2 * target 之后通常不会更优；
    // 如果起点更大，至少把 start 本身也包含进状态空间。
    int limit = max(start, target) * 2 + 10;
    limit = max(limit, 20);

    vector<int> dist(limit + 1, -1);
    queue<int> q;

    q.push(start);
    // 起点到自己的操作次数是 0。
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // 从当前状态出发，枚举题目允许的三种下一步操作。
        vector<int> next_states = {current - 1, current + 1, current * 2};

        for (int next : next_states) {
            if (next < 0 || next > limit) {
                continue;
            }
            if (dist[next] != -1) {
                continue;
            }

            // 第一次到达 next 时，就得到最少操作次数。
            dist[next] = dist[current] + 1;
            if (next == target) {
                cout << dist[next] << '\n';
                return 0;
            }
            // 只有首次到达才入队，避免重复搜索。
            q.push(next);
        }
    }

    // 按当前状态空间设置，这里理论上总能到达；保底输出 -1。
    cout << -1 << '\n';
    return 0;
}
