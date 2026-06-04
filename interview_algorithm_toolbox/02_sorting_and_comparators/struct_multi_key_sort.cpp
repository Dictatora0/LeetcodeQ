/*
题目 / 示例名称：结构体多关键字排序
核心知识点：多关键字排序、自定义比较函数、严格顺序
适用场景：比赛榜单、区间排序、先按主关键字再按次关键字
关键思路：先比较最重要的关键字，不同就直接返回；相同再比较下一个关键字
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 主关键字相等时忘记写次关键字，导致结果不稳定。
2. 次关键字方向写反。
3. 直接把多个条件拼在一起，自己都看不懂。
示例输入：
4
alice 5 120
bob 6 200
cindy 6 180
david 5 110
示例输出：
cindy 6 180
bob 6 200
david 5 110
alice 5 120
手动推演：
先按 solved 降序，所以做题数为 6 的排前面；再按 penalty 升序，所以 180 在 200 前。
对比说明：
- “主关键字 + 次关键字 + 第三关键字”要按层次写。
- 不建议一行塞多个三元表达式，维护成本太高。
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    string name;
    int solved;
    int penalty;
};

bool comparePlayer(const Player& a, const Player& b) {
    if (a.solved != b.solved) {
        return a.solved > b.solved;
    }
    if (a.penalty != b.penalty) {
        return a.penalty < b.penalty;
    }
    return a.name < b.name;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Player> players(n);
    for (int i = 0; i < n; ++i) {
        cin >> players[i].name >> players[i].solved >> players[i].penalty;
    }

    sort(players.begin(), players.end(), comparePlayer);

    for (const Player& player : players) {
        cout << player.name << ' ' << player.solved << ' ' << player.penalty << '\n';
    }

    return 0;
}
