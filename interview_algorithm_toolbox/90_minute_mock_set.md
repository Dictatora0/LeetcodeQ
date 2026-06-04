# 90 分钟 3 题模拟题单

这份题单和 [90_minute_exam_checklist.md](./90_minute_exam_checklist.md) 配套使用。
标准答案骨架模板：
- [90_minute_mock_answer_skeleton.md](./90_minute_mock_answer_skeleton.md)

使用方式：
1. 给自己定时 `90` 分钟。
2. 不看本仓库答案和对应示例，先独立完成。
3. 做完后再回到知识库对应专题复盘。
4. 复盘时不要只看答案，优先看“为什么是这个题型、为什么这套模板能成立”。

## 建议顺序

1. `Problem A`
2. `Problem B`
3. `Problem C`

## Problem A - 排序后的榜单输出

### 题意

给定 `n` 个选手的信息，每个选手有：
- 名字 `name`
- 通过题数 `solved`
- 罚时 `penalty`

请按照以下规则输出最终榜单：
1. 通过题数多的排前面
2. 如果通过题数相同，罚时小的排前面
3. 如果前两项都相同，名字字典序小的排前面

### 输入格式

第一行一个整数 `n`。

接下来 `n` 行，每行输入：

```text
name solved penalty
```

### 输出格式

输出排序后的榜单，每行一个选手信息：

```text
name solved penalty
```

### 数据范围

- `1 <= n <= 2e5`
- `0 <= solved <= 20`
- `0 <= penalty <= 1e9`

### 样例输入

```text
5
alice 3 120
bob 4 300
cindy 4 250
david 3 120
emma 4 250
```

### 样例输出

```text
cindy 4 250
emma 4 250
bob 4 300
alice 3 120
david 3 120
```

### 推荐识别

- 关键词：排序输出、多关键字、结构体
- 首先考虑：`sort` + 普通比较函数

### 复盘链接

- [struct_multi_key_sort.cpp](./02_sorting_and_comparators/struct_multi_key_sort.cpp)
- [comparator_common_mistakes.cpp](./02_sorting_and_comparators/comparator_common_mistakes.cpp)

### 题解链接

- [problem_a_ranklist_solution.cpp](./14_mock_problem_solutions/problem_a_ranklist_solution.cpp)

### 参考复盘路线

1. 先看 [struct_multi_key_sort.cpp](./02_sorting_and_comparators/struct_multi_key_sort.cpp)，确认你是否把主关键字和次关键字顺序写对了。
2. 再看 [interval_sort.cpp](./02_sorting_and_comparators/interval_sort.cpp)，对比“区间排序”和“榜单排序”的共同点，都是先定义清楚比较器语义。
3. 最后看 [comparator_common_mistakes.cpp](./02_sorting_and_comparators/comparator_common_mistakes.cpp)，专门检查自己有没有写出 `<=` / `>=` 这种错误比较器。

## Problem B - 最长平衡 0/1 区间

### 题意

给定一个只包含 `0` 和 `1` 的长度为 `n` 的数组，求其中 `0` 和 `1` 个数相等的最长连续子数组长度。

### 输入格式

第一行一个整数 `n`。

第二行 `n` 个整数，每个数是 `0` 或 `1`。

### 输出格式

输出一个整数，表示最长长度。

### 数据范围

- `1 <= n <= 2e5`

### 样例输入

```text
8
0 1 0 0 1 1 0 1
```

### 样例输出

```text
8
```

### 推荐识别

- 关键词：最长连续子数组、0 和 1 数量相等
- 首先考虑：前缀和 + 哈希表记录第一次出现位置

### 复盘链接

- [longest_subarray_equal_zero_one.cpp](./05_prefix_sum_and_hash/longest_subarray_equal_zero_one.cpp)
- [prefix_count_query.cpp](./05_prefix_sum_and_hash/prefix_count_query.cpp)

### 题解链接

- [problem_b_longest_balanced_zero_one_solution.cpp](./14_mock_problem_solutions/problem_b_longest_balanced_zero_one_solution.cpp)

### 参考复盘路线

1. 先看 [longest_subarray_equal_zero_one.cpp](./05_prefix_sum_and_hash/longest_subarray_equal_zero_one.cpp)，确认你是否想到把 `0` 变成 `-1`。
2. 再看 [subarray_sum_divisible_by_k.cpp](./05_prefix_sum_and_hash/subarray_sum_divisible_by_k.cpp)，对比“统计个数”和“求最长长度”时哈希表存的到底是什么。
3. 最后看 [prefix_count_query.cpp](./05_prefix_sum_and_hash/prefix_count_query.cpp)，巩固“前缀状态 -> 区间性质”的基本转化。

## Problem C - 0/1 背包最大价值

### 题意

有 `n` 件物品，第 `i` 件物品的重量为 `weight[i]`，价值为 `value[i]`。每件物品最多选一次，背包容量为 `m`。

请问在总重量不超过 `m` 的前提下，最多能获得多少总价值。

### 输入格式

第一行两个整数 `n` 和 `m`。

接下来 `n` 行，每行两个整数：

```text
weight value
```

### 输出格式

输出一个整数，表示最大总价值。

### 数据范围

- `1 <= n <= 200`
- `1 <= m <= 5000`
- `1 <= weight, value <= 1e4`

### 样例输入

```text
4 7
1 2
3 4
4 5
5 7
```

### 样例输出

```text
9
```

### 样例说明

选择重量为 `3`、价值为 `4` 的物品和重量为 `4`、价值为 `5` 的物品，总重量 `7`，总价值 `9`。

### 推荐识别

- 关键词：每件最多一次、最大价值、容量限制
- 首先考虑：`0/1` 背包，一维 DP，容量倒序

### 复盘链接

- [zero_one_knapsack_basic.cpp](./10_basic_dp/zero_one_knapsack_basic.cpp)
- [complete_knapsack_basic.cpp](./10_basic_dp/complete_knapsack_basic.cpp)

### 题解链接

- [problem_c_zero_one_knapsack_solution.cpp](./14_mock_problem_solutions/problem_c_zero_one_knapsack_solution.cpp)

### 参考复盘路线

1. 先看 [zero_one_knapsack_basic.cpp](./10_basic_dp/zero_one_knapsack_basic.cpp)，确认你是否真的理解为什么容量要倒序。
2. 再看 [complete_knapsack_basic.cpp](./10_basic_dp/complete_knapsack_basic.cpp)，对比“同样是一维 DP，为什么这里必须正序”。
3. 最后看 [coin_change_count_ways.cpp](./10_basic_dp/coin_change_count_ways.cpp)，理解“求最大值”和“求方案数”的转移语义差异。

## 使用建议

- `0 ~ 5` 分钟：读完三题，先做 A
- `5 ~ 25` 分钟：完成 A
- `25 ~ 55` 分钟：完成 B
- `55 ~ 82` 分钟：主攻 C
- `82 ~ 90` 分钟：统一检查边界、输出格式、`long long`

## 整体复盘路线

1. 先复盘 `Problem A`，确保比较器和排序稳定性没有丢分。
2. 再复盘 `Problem B`，重点总结“前缀状态 + 哈希”到底是存“计数”还是存“第一次位置”。
3. 最后复盘 `Problem C`，把 `0/1` 背包和完全背包的循环方向差异彻底记牢。
4. 如果 90 分钟内第三题没做完，优先补写状态定义和 check 思路，再回看对应教学文件。

## 评分目标

- 稳妥目标：A + B
- 提升目标：A + B + C
- 如果 C 没写完，也至少把状态定义和转移写清楚，方便复盘
