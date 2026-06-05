# 90 分钟模拟题标准答案骨架模板

这份模板和 [90_minute_mock_set.md](./90_minute_mock_set.md) 配套使用。

用途：
- 做题前快速看“这题代码骨架应该长什么样”
- 做完后对照检查自己是否写漏了关键状态
- 笔试里时间不够时，至少把最核心的结构先搭起来

## Problem A 标准答案骨架

### 识别信号

- 排序输出
- 多关键字
- 结构体

### 思路骨架

1. 定义结构体 `Player`
2. 写普通比较函数 `comparePlayer`
3. 读入数组
4. `sort(players.begin(), players.end(), comparePlayer);`
5. 逐行输出

### 代码骨架

```cpp
struct Player {
    string name;
    int solved;
    long long penalty;
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
    cin >> n;
    vector<Player> players(n);
    for (int i = 0; i < n; ++i) {
        cin >> players[i].name >> players[i].solved >> players[i].penalty;
    }

    sort(players.begin(), players.end(), comparePlayer);

    for (const Player& player : players) {
        cout << player.name << ' ' << player.solved << ' ' << player.penalty << '\n';
    }
}
```

### 最后 10 秒检查

- 比较器是不是严格的
- 主关键字和次关键字方向有没有写反
- 输出格式是否一行一个选手

## Problem B 标准答案骨架

### 识别信号

- 最长连续子数组
- 0 和 1 数量相等
- 前缀状态相同

### 思路骨架

1. 把 `0` 变成 `-1`
2. 维护前缀和 `prefix_sum`
3. 哈希表记录某个前缀和第一次出现的位置
4. 若当前前缀和曾出现过，就更新最长长度

### 代码骨架

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    unordered_map<int, int> first_position;
    first_position[0] = 0;

    int prefix_sum = 0;
    int best_length = 0;

    for (int i = 1; i <= n; ++i) {
        prefix_sum += (a[i] == 0 ? -1 : 1);

        if (first_position.count(prefix_sum)) {
            best_length = max(best_length, i - first_position[prefix_sum]);
        } else {
            first_position[prefix_sum] = i;
        }
    }

    cout << best_length << '\n';
}
```

### 最后 10 秒检查

- 是否初始化了 `first_position[0] = 0`
- 哈希表存的是不是第一次出现位置
- 0 是否真的被转成了 -1

## Problem C 标准答案骨架

### 识别信号

- 每件最多一次
- 容量限制
- 最大价值

### 思路骨架

1. 定义 `dp[j]` 表示容量不超过 j 的最大价值
2. 外层枚举物品
3. 内层容量从大到小枚举
4. 转移 `dp[j] = max(dp[j], dp[j - w] + v)`

### 代码骨架

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    cin >> n >> capacity;

    vector<int> weight(n + 1), value(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i] >> value[i];
    }

    vector<long long> dp(capacity + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = capacity; j >= weight[i]; --j) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    cout << dp[capacity] << '\n';
}
```

### 最后 10 秒检查

- 容量是否倒序
- 是否把 0/1 背包误写成完全背包
- 价值总和是否需要 `long long`

## Problem C 没做完时怎么写半成品也尽量不亏

先说明一件事：

- 严格 ACM 赛制通常还是以 `AC` 为准，半成品本身不保证得分。
- 但在线笔试里，把第三题的核心骨架先搭出来，至少有 3 个现实收益：
  1. 你后面只要回头补细节，不用重新起稿。
  2. 可见样例和小数据更容易先跑通。
  3. 如果平台有部分分、人工复盘或面试追问，你不是一片空白。

### 最少先写出来的 4 件事

如果只剩 5 分钟，优先按这个顺序写：

1. 先写题型判断注释

```cpp
// 每件物品最多一次，这是 0/1 背包。
```

2. 先写状态定义

```cpp
// dp[j] 表示容量不超过 j 时的最大价值。
vector<long long> dp(capacity + 1, 0);
```

3. 先写双重循环骨架

```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = capacity; j >= weight[i]; --j) {
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
}
```

4. 先把答案输出写上

```cpp
cout << dp[capacity] << '\n';
```

很多时候第三题不是完全不会，而是来不及。
这时最亏的情况不是“没优化到极致”，而是连状态和循环方向都还没落到代码里。

### 如果你已经想到题型，但细节还没完全确认

那就先把这些注释写进代码：

```cpp
// 状态：dp[j] = 容量不超过 j 时的最大价值
// 转移：选或不选当前物品
// 为什么倒序：防止同一件物品在这一轮被重复使用
```

这样做的价值是：

- 你回头补代码时不会重新想一遍状态定义。
- 即使中途被打断，也能马上续写。

### 如果你连一维 DP 都没完全写稳

那就退一步，先把二维版本思路写出来也比空着强：

```cpp
// 可选备用思路：
// dp[i][j] 表示前 i 件物品、容量不超过 j 时的最大价值
// 转移：
// 1. 不选第 i 件：dp[i][j] = dp[i - 1][j]
// 2. 选第 i 件：dp[i][j] = dp[i - 1][j - weight[i]] + value[i]
```

二维版不一定是你最后要交的版本，但它能帮你把题意和转移关系先固定住。

### 最容易卡住时的应急检查顺序

如果样例没过，不要乱改，按这个顺序查：

1. 这题是不是 `0/1` 背包，不是完全背包？
2. 容量循环是不是倒序？
3. `j >= weight[i]` 的边界有没有写对？
4. `dp[j - weight[i]] + value[i]` 有没有下标写错？
5. 价值总和是否该用 `long long`？

### 第三题最后 2 分钟的保底策略

如果确定来不及完整对拍，至少保证代码里已经有：

- 输入读法
- 状态定义
- 循环方向
- 核心转移
- 最终输出

因为对 `0/1` 背包这类题，真正决定对错的就是这几行。

换句话说：

- 先把“题型识别 + 状态 + 循环方向”写对
- 再去补细枝末节

这比留一个空白文件更有价值。

## 统一口述骨架

如果笔试后要复盘或面试时要讲，可以统一按这个顺序说：

1. 这题我先识别成什么题型
2. 我定义的状态 / 结构是什么
3. 我为什么这样转移 / 排序 / 维护
4. 时间复杂度和空间复杂度是什么
5. 最容易错的边界是什么

## 对应完整题解

- Problem A：
  [problem_a_ranklist_solution.cpp](./14_mock_problem_solutions/problem_a_ranklist_solution.cpp)
- Problem B：
  [problem_b_longest_balanced_zero_one_solution.cpp](./14_mock_problem_solutions/problem_b_longest_balanced_zero_one_solution.cpp)
- Problem C：
  [problem_c_zero_one_knapsack_solution.cpp](./14_mock_problem_solutions/problem_c_zero_one_knapsack_solution.cpp)
