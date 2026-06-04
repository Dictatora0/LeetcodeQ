# 04 - 二进制与位运算

这一目录重点解决“公式背过了，但位运算含义不够清楚”的问题。

## 建议阅读顺序

1. `binary_basics.cpp`
2. `integer_to_binary_string.cpp`
3. `bitset_demo.cpp`
4. `get_set_clear_toggle_bit.cpp`
5. `count_set_bits.cpp`
6. `power_of_two.cpp`
7. `trailing_ones.cpp`
8. `lowbit_demo.cpp`
9. 真题联动：[`../12_real_past_problems/binary_suffix_ones_sum_bruteforce.cpp`](../12_real_past_problems/binary_suffix_ones_sum_bruteforce.cpp)
10. 真题联动：[`../12_real_past_problems/binary_suffix_ones_sum_optimized.cpp`](../12_real_past_problems/binary_suffix_ones_sum_optimized.cpp)

## 本目录重点

- `x & 1`：判断最低位是否为 1
- `1LL << k`：表示 `2^k`
- `(x >> k) & 1`：读取第 k 位
- `x & (x - 1)`：删除最低位的一个 1
- `x & (-x)`：只保留最低位的 1
- 末尾连续若干个 1 的长度，常和规律题、贡献法一起出现
