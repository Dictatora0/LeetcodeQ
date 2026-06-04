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
