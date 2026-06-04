# 08 - 二分查找

这一目录重点解决“边界明明会背，写起来却总错”的问题。

## 建议阅读顺序

1. `binary_search_exact.cpp`
2. `lower_bound_upper_bound_demo.cpp`
3. `first_position_ge_target.cpp`
4. `last_position_le_target.cpp`
5. `answer_binary_search_minimum_capacity.cpp`
6. `answer_binary_search_minimize_max_segment_sum.cpp`
7. `answer_binary_search_minimum_production_time.cpp`
8. `answer_binary_search_minimum_initial_health_grid.cpp`

## 本目录重点

- 精确查找常用闭区间 `[left, right]`
- 找第一个满足条件的位置常用左闭右开 `[left, right)`
- `lower_bound`：第一个 `>= target`
- `upper_bound`：第一个 `> target`
- 如果“答案越大越容易满足”，通常可以做答案二分
- 很多答案二分题的 check 本质上是线性贪心
- 也有答案二分题的 check 只是数学计数，不需要贪心
- 还有一些答案二分题的 check 需要 DP 才能正确判断
