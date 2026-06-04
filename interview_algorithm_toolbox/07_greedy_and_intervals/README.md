# 07 - 贪心与区间

这一目录重点训练“排序后局部最优”这种最常见的贪心套路。

## 建议阅读顺序

1. `interval_scheduling.cpp`
2. `longest_pair_chain.cpp`
3. `minimum_points_cover_intervals.cpp`
4. `greedy_sorting_pattern.cpp`

## 本目录重点

- 当题目要求“最多选多少个不冲突对象”时，先想按结束时间排序
- 贪心不是拍脑袋，要能解释为什么当前局部选择不会害死后面
- 简单贪心常和排序、双指针一起出现
- “最少用多少个点 / 资源覆盖所有区间”通常也能按右端点贪心
