# 05 - 前缀和与哈希

这一目录处理“多次查询、频率统计、去重、查找配对”这类高频笔试题。

## 建议阅读顺序

1. `one_dimensional_prefix_sum.cpp`
2. `prefix_count_query.cpp`
3. `subarray_sum_divisible_by_k.cpp`
4. `subarray_count_sum_equals_k.cpp`
5. `longest_subarray_sum_equals_k.cpp`
6. `sum_equals_k_compare.md`
7. `longest_subarray_equal_zero_one.cpp`
8. `frequency_array_26_letters.cpp`
9. `map_and_unordered_map_frequency.cpp`
10. `set_and_unordered_set_demo.cpp`
11. `two_sum_hash.cpp`

## 本目录重点

- 区间和：优先前缀和
- 区间内满足某条件的元素个数：优先前缀计数
- 子数组和满足模条件：前缀和 + 余数频次统计
- 和为 k 的子数组个数：前缀和 + 哈希统计出现次数
- 和为 k 的最长区间：前缀和 + 哈希记录第一次出现位置
- 最长满足条件区间：前缀状态 + 哈希记录第一次出现位置
- 值域小：优先频次数组
- 需要按键有序输出：`map` / `set`
- 只关心均摊查询速度：`unordered_map` / `unordered_set`
- 无序数组里查两数和：优先哈希
