# 00 - C++ 模板与工具箱

这一目录解决“拿到题以后先把骨架写稳”的问题。

## 建议阅读顺序

1. `acm_single_case.cpp`
2. `acm_multiple_cases.cpp`
3. `fast_io_template.cpp`
4. `debug_print_template.cpp`
5. `cpp_interview_toolbox.cpp`

## 文件说明

- `acm_single_case.cpp`
  单组数据模板，适合绝大多数基础题。
- `acm_multiple_cases.cpp`
  多测模板，重点看每轮变量重置。
- `fast_io_template.cpp`
  复习快读、`\n`、`endl` 差异。
- `debug_print_template.cpp`
  复习如何本地调试但不污染评测输出。
- `cpp_interview_toolbox.cpp`
  复习常用片段：排序、`1-based / 0-based` 前缀和、哈希、位运算、二分、`gcd/lcm`，以及 `DFS / BFS` 速查。

## 编译示例

```bash
g++ -std=c++17 -Wall -Wextra -O2 acm_single_case.cpp -o /tmp/acm_single_case
```
