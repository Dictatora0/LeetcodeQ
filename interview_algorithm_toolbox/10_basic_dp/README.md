# 10 - 基础动态规划

这一目录优先放短期笔试最常考、最值得先掌握的基础 DP，包括一维 DP 和入门二维网格 DP。

## 建议阅读顺序

1. `climbing_stairs.cpp`
2. `house_robber_linear.cpp`
3. `min_path_sum_grid.cpp`
4. `edit_distance_basic.cpp`
5. `palindrome_substring_interval_dp.cpp`
6. `max_subarray_sum.cpp`
7. `lis_n2.cpp`
8. `zero_one_knapsack_basic.cpp`
9. `complete_knapsack_basic.cpp`
10. `coin_change_count_ways.cpp`

## 本目录重点

- 先写清状态含义，再写转移
- 一维 DP 经常能压缩成几个变量
- “选或不选当前元素”是最常见的一维 DP 转移原型
- 网格 DP 的关键是先想清楚“状态来自上方、左方还是更多方向”
- 双串 DP 的关键是先定义“前 i 个字符”和“前 j 个字符”的状态含义
- 区间 DP 的关键是先想清楚“当前区间依赖哪些更短区间”
- 最大子数组和和 LIS 是面试高频基础题
- 0/1 背包和完全背包最关键的差异，是容量循环方向
- 计数型一维 DP 最关键的差异，是初始条件和循环顺序
