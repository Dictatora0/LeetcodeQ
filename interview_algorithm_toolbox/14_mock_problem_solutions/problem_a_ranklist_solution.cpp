/*
题目 / 示例名称：模拟题 Problem A - 排序后的榜单输出
核心知识点：结构体排序、多关键字比较器、严格弱序
适用场景：榜单题、成绩排序题、区间排序题中的多关键字比较
关键思路：
1. 定义结构体保存选手信息。
2. 自定义比较器，按：
   - solved 降序
   - penalty 升序
   - name 升序
3. 用 `sort` 排序后直接输出。
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 比较器写成 `>=` 或 `<=`。
2. 主关键字相等时没有补次关键字。
3. 把“名字字典序小”写反。
示例输入：
5
alice 3 120
bob 4 300
cindy 4 250
david 3 120
emma 4 250
示例输出：
cindy 4 250
emma 4 250
bob 4 300
alice 3 120
david 3 120
手动推演：
4 题通过的人一定排在 3 题通过的人前面。
4 题通过里，250 的罚时优于 300，所以 cindy 和 emma 排在 bob 前。
250 和 250 相同，再按名字字典序，cindy 在 emma 前。
对比说明：
- 这题本质是多关键字排序。
- 和 `struct_multi_key_sort.cpp` 一样，关键在于把比较器拆层写清楚。
*/

/*
5 分钟应急写法：
1. 先把结构体 `Player` 写出来，只保留 `name`、`solved`、`penalty` 三个字段。
2. 立刻写普通比较函数，顺序固定为：
   - `solved` 降序
   - `penalty` 升序
   - `name` 升序
3. 主程序里只做三件事：
   - 读入
   - `sort(players.begin(), players.end(), comparePlayer);`
   - 逐行输出
4. 如果时间特别紧，不要再纠结 `stable_sort`、Lambda、封装类，普通结构体 + 普通比较函数最稳。
5. 最后 10 秒只检查：
   - 比较器有没有写成 `>=` / `<=`
   - 名字字典序方向有没有写反
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    string name;
    int solved;
    long long penalty;
};

bool comparePlayer(const Player& a, const Player& b) {
    // compare(a, b) 返回 true，表示 a 应排在 b 前面。
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
