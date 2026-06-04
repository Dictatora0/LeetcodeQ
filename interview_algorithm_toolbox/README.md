# 笔试算法知识库

这套 `interview_algorithm_toolbox/` 面向短期 ACM 风格线上笔试复习，目标不是覆盖所有竞赛算法，而是把 90 分钟、3 题左右的高收益知识点整理成可以反复阅读、单独编译、直接改写的教学型 C++ 示例库。

## 适用场景

- 复习 ACM 输入输出、常见容器、基础模板
- 提升对“看到题先判断题型”的速度
- 笔试前 1 到 7 天做集中冲刺
- 面试或笔试前快速回看高频易错点
- 笔试前最后 10 分钟做压缩式速查

## 推荐阅读顺序

1. `00_cpp_templates/`
2. `01_simulation_and_counting/`
3. `02_sorting_and_comparators/`
4. `03_strings_and_prefix_states/`
5. `04_bitwise_operations/`
6. `05_prefix_sum_and_hash/`
7. `06_two_pointers_and_sliding_window/`
8. `07_greedy_and_intervals/`
9. `08_binary_search/`
10. `09_basic_math/`
11. `10_basic_dp/`
12. `11_dfs_bfs/`
13. `12_real_past_problems/`
14. `13_common_mistakes/`
15. `90_minute_exam_checklist.md`
16. `90_minute_mock_set.md`
17. `14_mock_problem_solutions/`
18. `90_minute_mock_answer_skeleton.md`

## 知识点识别表

| 题目关键词 | 首先考虑 |
| --- | --- |
| 最多、最少、统计数量 | 遍历、计数、贪心 |
| 排序输出 | `sort`、自定义比较器 |
| 分数比较 | 交叉相乘 |
| 任意前缀满足条件 | 前缀状态、`balance` |
| 括号是否合法 | 计数器或栈 |
| 二进制、最低位、第 k 位 | 位运算 |
| `n <= 1e9` | 数学规律、周期、二分 |
| 多次区间求和 | 前缀和 |
| 连续子数组、连续子串 | 双指针、滑动窗口 |
| 数组有序 | 二分、双指针 |
| 网格最短路 | BFS |
| 网格连通块 | DFS 或 BFS |

## 目录索引

- `00_cpp_templates/`
  解决 ACM 输入输出、快读、调试、常用代码片段复用问题。
- `01_simulation_and_counting/`
  解决基础扫描、计数、频率统计、`long long` 求和问题。
- `02_sorting_and_comparators/`
  解决排序、区间排序、结构体排序、稳定排序、自定义比较器易错点问题。
- `03_strings_and_prefix_states/`
  解决字符串遍历、前缀状态、栈基础、括号匹配、栈消除问题。
- `04_bitwise_operations/`
  解决二进制表示、`bitset`、取位、改位、末尾连续 1、删最低位 1、`lowbit` 等问题。
- `05_prefix_sum_and_hash/`
  解决前缀和、前缀计数、前缀和取模统计、和为 k 的子数组个数、和为 k 的最长区间、最长前缀状态区间、频次数组、`map` / `unordered_map`、`set` / `unordered_set`。
- `06_two_pointers_and_sliding_window/`
  解决有序数组双指针、去重、固定窗口、最长连续区间、无重复子串。
- `07_greedy_and_intervals/`
  解决简单贪心、区间调度、区间覆盖、排序后逐步选择。
- `08_binary_search/`
  解决手写二分、边界二分、`lower_bound`、`upper_bound`、答案二分、贪心 check、数学 check、DP check。
- `09_basic_math/`
  解决奇偶、整除、取模、`gcd`、`lcm`、等差 / 等比数列。
- `10_basic_dp/`
  解决一维 DP、最大子数组和、基础 LIS、`0/1` 背包、完全背包、计数型一维 DP。
- `11_dfs_bfs/`
  解决队列入门、网格连通块、网格最短路。
- `12_real_past_problems/`
  收录四道重点往届真题与二进制题的暴力/优化对照版本。
- `13_common_mistakes/`
  集中处理溢出、整数除法、比较器、下标、输出格式、循环边界和多测重置。
- `90_minute_exam_checklist.md`
  压缩总结 90 分钟笔试的开题顺序、题型识别和最后检查动作。
- `90_minute_mock_set.md`
  提供一套 3 题模拟题单，便于和速查清单配合做计时训练。
- `14_mock_problem_solutions/`
  给模拟题单中的 3 道题提供完整教学型题解。
- `90_minute_mock_answer_skeleton.md`
  给 3 道模拟题提供标准答案骨架模板，适合限时写题前快速过一遍。

## 四道往届题索引

- [最大奇数乘积子集](./12_real_past_problems/maximum_odd_product_subset.cpp)
- [分数降序排序](./12_real_past_problems/fraction_descending_sort.cpp)
- [二进制后缀连续 1 求和：暴力版](./12_real_past_problems/binary_suffix_ones_sum_bruteforce.cpp)
- [二进制后缀连续 1 求和：优化版](./12_real_past_problems/binary_suffix_ones_sum_optimized.cpp)
- [ab 变换串](./12_real_past_problems/ab_transformation_string.cpp)

## 复习路线

### 笔试前 3 天路线

1. 先通读 `00` 到 `04`，把输入输出、排序、括号、位运算手写一遍。
2. 再读 `05` 到 `08`，重点记住前缀和、哈希、滑窗、二分边界模板。
3. 最后读 `10`、`11` 和 `12`，确保常见 DP、网格 BFS/DFS、真题规律题能讲清楚。

### 笔试前 1 小时快速复习路线

1. `00_cpp_templates/cpp_interview_toolbox.cpp`
2. `12_real_past_problems/README.md`
3. `13_common_mistakes/README.md`
4. `08_binary_search/README.md`
5. `04_bitwise_operations/README.md`
6. `90_minute_exam_checklist.md`
7. `90_minute_mock_set.md`
8. `90_minute_mock_answer_skeleton.md`

## 90 分钟 ACM 风格笔试做题顺序建议

1. 先读完 3 题，按“最稳 -> 中等 -> 最难”排序，不要按题面顺序开写。
2. 第一题优先拿模拟、计数、排序、字符串、哈希题。
3. 第二题优先拿二分、滑窗、贪心、基础 DP。
4. 第三题如果是规律题、位运算或网格 BFS，要先用样例手推再编码。
5. 每题写完立刻用样例、边界、空数据、单元素检查一轮。

## 提交前检查清单

- 是否开了 `ios::sync_with_stdio(false); cin.tie(nullptr);`
- `int` 是否会溢出，需要改成 `long long` 吗
- 多组数据是否重置了数组、哈希表、答案变量
- 数组下标是 0-based 还是 1-based
- `sort` 比较器是否使用了严格的 `<` / `>`
- 边界循环是 `< n` 还是 `<= n`
- 除法是不是发生了整数截断
- 是否存在空栈、空队列、空字符串访问
- 输出格式是否多空格、多换行、漏换行

## 编译方式

单文件编译：

```bash
g++ -std=c++17 -Wall -Wextra -O2 interview_algorithm_toolbox/01_simulation_and_counting/count_odd_numbers.cpp -o /tmp/count_odd_numbers
```

运行示例：

```bash
printf "5\n1 2 3 4 5\n" | /tmp/count_odd_numbers
```

一键批量编译：

```bash
./interview_algorithm_toolbox/scripts/compile_all.sh
```

一键 smoke tests：

```bash
./interview_algorithm_toolbox/scripts/run_smoke_tests.sh
```

90 分钟速查：

```bash
sed -n '1,220p' interview_algorithm_toolbox/90_minute_exam_checklist.md
```

90 分钟模拟题单：

```bash
sed -n '1,260p' interview_algorithm_toolbox/90_minute_mock_set.md
```

90 分钟标准答案骨架：

```bash
sed -n '1,260p' interview_algorithm_toolbox/90_minute_mock_answer_skeleton.md
```

## 目录内文件命名规则

- `*_demo.cpp`：适合快速复习的小型演示程序
- `*_template.cpp`：适合复制到笔试答题区的模板
- `*_optimized.cpp`：在复杂度上做了核心优化
- `README.md`：该目录的阅读顺序、文件用途、易混淆点

## 说明

- 本目录只做增量新增，不覆盖仓库原有 `practice/`、`solutions/`、`templates/` 内容。
- 优先使用清晰、稳定、适合笔试的写法，不使用炫技写法。
- 所有新增 `.cpp` 文件都可以独立编译。
