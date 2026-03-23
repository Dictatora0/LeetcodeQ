
# 算法模板库（Algorithm Template System）

目标：帮助你在面试和刷题中实现两件事。
- 3 秒识别题型
- 30 秒落地模板

## 目录总览

| 目录 | 作用 | 使用时机 |
|---|---|---|
| `interview_ready/` | 面试版完整模板（含讲解、易错点、真题、速查） | 你要系统复习或准备口述 |
| `problem_patterns/` | 题型识别指南（关键词、选型、陷阱） | 你还没确定用什么算法 |
| `code_snippets/` | 构树、快读快写、图遍历等工具代码 | 你要补辅助代码时 |

## 快速使用流程

1. 先看题目关键词，定位模式：
   `templates/problem_patterns/`
2. 再看完整讲解，确认思路与边界：
   `templates/interview_ready/`
3. 复制模板代码并填题目逻辑
4. 用 2-3 组边界样例自测：
   空输入、最小规模、极端重复值

## 算法速查表（从题面到模板）

| 题面信号 | 优先算法 | 入口 |
|---|---|---|
| 连续子数组/子串 + 最长/最短 | Sliding Window | `problem_patterns/sliding_window_patterns.md` |
| 有序数组 + O(log n) | Binary Search | `problem_patterns/binary_search_patterns.md` |
| 最少步数/层序遍历 | BFS | `interview_ready/bfs_template.cpp` |
| 所有路径/连通块 | DFS | `interview_ready/dfs_template.cpp` |
| 下一个更大/最近边界 | Monotonic Stack | `problem_patterns/monotonic_stack_patterns.md` |
| 区间和/子数组和 | Prefix Sum | `problem_patterns/prefix_sum_patterns.md` |
| 动态合并 + 连通性判断 | Union Find | `interview_ready/union_find_template.cpp` |
| 最优值/方案数 + 状态转移 | Dynamic Programming | `problem_patterns/dp_patterns.md` |
| 所有可能解 + 撤销选择 | Backtracking | `interview_ready/backtracking_template.cpp` |

## 推荐学习路线（2 周）

1. 基础指针与区间：
   Two Pointers → Sliding Window → Prefix Sum
2. 树图遍历：
   DFS → BFS → Union Find
3. 查找与结构：
   Binary Search → Monotonic Stack
4. 进阶搜索与优化：
   Backtracking → Dynamic Programming

## 面试落地建议

- 开口先说识别依据：
  “这题是连续区间最值问题，所以用滑动窗口。”
- 写码前先定模板变量语义：
  `left/right`、`visited`、`dp[i]` 的含义必须明确
- 写完立刻报复杂度：
  时间 + 空间 + 为什么成立

## 你现在可以怎么用

- 题目做不出来：
  先看 `templates/PATTERN_RECOGNITION_GUIDE.md`
- 知道算法但写不顺：
  看对应 `interview_ready/*.cpp` 的完整模板
- 面试前冲刺：
  重点看 `interview_ready/*.cpp` 的核心部分

## 质量标准

- C++17 可编译（模板中的可执行部分）
- 讲解可口述（不只是“能看懂”）
- 每份模板至少覆盖：
  识别信号、核心框架、易错点、复杂度、真题映射
