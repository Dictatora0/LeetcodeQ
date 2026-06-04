# 02 - 排序与比较器

这一目录重点解决“会用 `sort`，但比较器不稳”这个常见问题。

## 建议阅读顺序

1. `sort_ascending_descending.cpp`
2. `struct_single_key_sort.cpp`
3. `struct_multi_key_sort.cpp`
4. `interval_sort.cpp`
5. `stable_sort_demo.cpp`
6. `comparator_common_mistakes.cpp`
6. 真题联动：[`../12_real_past_problems/fraction_descending_sort.cpp`](../12_real_past_problems/fraction_descending_sort.cpp)

## 本目录重点

- 比较器的语义是“x 是否应排在 y 前面”
- 比较器必须满足严格弱序，不能写 `<=` 或 `>=`
- 结构体排序优先使用普通函数，笔试里更稳定
- `stable_sort` 什么时候有价值
- 区间题很多时候第一步就是先把区间按固定规则排好
