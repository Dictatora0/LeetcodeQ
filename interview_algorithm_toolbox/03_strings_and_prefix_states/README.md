# 03 - 字符串与前缀状态

这一目录重点处理字符串扫描、前缀合法性判断、括号匹配和栈式消除。

## 建议阅读顺序

1. `string_traversal.cpp`
2. `longest_consecutive_characters.cpp`
3. `palindrome_two_pointers.cpp`
4. `stack_basic_demo.cpp`
5. `single_bracket_balance.cpp`
6. `multi_bracket_stack.cpp`
7. `adjacent_character_elimination.cpp`
7. 真题联动：[`../12_real_past_problems/ab_transformation_string.cpp`](../12_real_past_problems/ab_transformation_string.cpp)

## 本目录重点

- 遍历字符串时，优先先定义“当前位置想维护什么状态”
- 栈的先进后出特性，决定了它很适合处理“最近未匹配元素”
- 单类型括号常用 `balance`
- 多类型括号必须上栈
- “不断删除相邻模式串”常能转成栈问题
