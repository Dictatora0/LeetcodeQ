# 12 - 往届真题复盘

这一目录收录本轮重点教学文件。建议把这里当成“做题思路模板库”，不是只看答案，而是要学会识别题型和迁移套路。

## 建议阅读顺序

1. `maximum_odd_product_subset.cpp`
2. `fraction_descending_sort.cpp`
3. `binary_suffix_ones_sum_bruteforce.cpp`
4. `binary_suffix_ones_sum_optimized.cpp`
5. `ab_transformation_string.cpp`

## 核心迁移点

- `maximum_odd_product_subset.cpp`
  迁移到奇偶性、乘积性质、最大可选数量类题。
- `fraction_descending_sort.cpp`
  迁移到分数比较、比值排序、结构体比较器类题。
- `binary_suffix_ones_sum_bruteforce.cpp`
  用来验证规律，不适合大数据。
- `binary_suffix_ones_sum_optimized.cpp`
  迁移到周期、贡献法、位运算数学规律题。
- `ab_transformation_string.cpp`
  迁移到前缀合法性、括号等价、栈 / 计数器判断题。

## 二进制题两个版本如何配合复习

- 先看 `binary_suffix_ones_sum_bruteforce.cpp`
  目的：先把 `f(x)` 的定义和样例跑清楚。
- 再看 `binary_suffix_ones_sum_optimized.cpp`
  目的：理解为什么按位贡献后能从 O(n log n) 降到 O(log n)。

## 建议复盘方式

1. 自己先只看题意，尝试写 5 分钟草稿。
2. 如果卡住，先看“核心观察”和“为什么暴力不合适”。
3. 最后再看代码与注释，确认你是否真的能口述出算法。
