# LeetCode 算法学习仓库

这是一个以 C++ 为主的刷题与面试准备仓库。目标不只是“做出题”，而是沉淀可复习、可口述、可运行的算法资产。

## 当前概览

- `solutions/`：**150** 份专题题解（不含历史归档）
- `solutions/cpp/`：**108** 份历史代码（迁移前版本保留）
- `templates/`：模板体系（题型识别 + 面试模板 + 代码骨架）
- `notes/`：学习日志与面试补强文档
- `interview_algorithm_toolbox/`：面向 90 分钟 ACM 风格笔试的教学型复习知识库

当前覆盖专题包括数组、链表、二叉树、图、动态规划、滑动窗口、前缀和、单调栈、回溯、贪心、设计题、Trie、位运算等。

## 快速开始

### 1) 编译运行单题

```bash
./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp
./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp --build-only
MODE=debug ./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp
```

编译产物会统一写入 `build/` 目录，并保留源文件的相对路径，例如：

- `practice/demo.cpp` -> `build/release/practice/demo`
- `solutions/binary_tree/leetcode_101_symmetric_tree.cpp` -> `build/release/solutions/binary_tree/leetcode_101_symmetric_tree`

### 2) 批量编译题解

```bash
./scripts/compile_all.sh
./scripts/compile_all.sh solutions/binary_tree
MODE=debug ./scripts/compile_all.sh
```

### 3) 编译 / 验证笔试知识库

```bash
./scripts/compile_interview_toolbox.sh
./scripts/run_smoke_tests.sh
```

## 模板体系（推荐入口）

`templates/` 目录按“识别 -> 落地 -> 复盘”拆成三层：

- `problem_patterns/`：
  先判断题型，解决“这题该用什么算法”
- `interview_ready/`：
  看完整面试讲解，解决“这题怎么讲清楚”
- `core_templates/`：
  拿最小代码骨架，解决“这题怎么快速开写”

建议流程：
1. 先读 [`templates/PATTERN_RECOGNITION_GUIDE.md`](templates/PATTERN_RECOGNITION_GUIDE.md)
2. 再看 [`templates/README.md`](templates/README.md)
3. 最后按算法进入 [`templates/interview_ready/README.md`](templates/interview_ready/README.md)

## 仓库结构

```text
Leetcode/
├── solutions/
│   ├── array/                  # 数组
│   ├── backtracking/           # 回溯
│   ├── binary_search/          # 二分
│   ├── binary_tree/            # 二叉树
│   ├── bit_manipulation/       # 位运算
│   ├── design/                 # 设计题
│   ├── dynamic_programming/    # 动态规划
│   ├── graph/                  # 图
│   ├── greedy/                 # 贪心
│   ├── hash_table/             # 哈希
│   ├── heap/                   # 堆
│   ├── interval/               # 区间
│   ├── linked_list/            # 链表
│   ├── prefix_sum/             # 前缀和
│   ├── sliding_window/         # 滑动窗口
│   ├── stack/                  # 栈 / 单调栈
│   ├── trie/                   # Trie
│   ├── two_pointers/           # 双指针
│   └── cpp/                    # 历史代码归档
├── templates/
│   ├── core_templates/         # 最小代码模板
│   ├── interview_ready/        # 面试完整模板
│   ├── problem_patterns/       # 题型识别指南
│   └── code_snippets/          # 工具代码片段
├── interview_algorithm_toolbox/
│   ├── 00_cpp_templates/       # ACM 模板与 C++ 工具箱
│   ├── 12_real_past_problems/  # 四道重点真题复盘
│   ├── 13_common_mistakes/     # 高频错误清单
│   └── scripts/                # 编译与 smoke test 脚本
├── scripts/
│   ├── run_cpp.sh              # 单题编译运行
│   ├── compile_all.sh          # 原题解批量编译
│   ├── compile_interview_toolbox.sh # 知识库批量编译入口
│   └── run_smoke_tests.sh      # 知识库 smoke tests 入口
└── notes/
    ├── learning_log/           # 学习日志
    └── interview_prep/         # 面试补强笔记
```

## 阅读建议

- 想快速刷题：
  直接从 `solutions/` 对应专题开始
- 想系统补盲点：
  先看 `templates/problem_patterns/` 再回做题
- 想准备面试口述：
  重点看 `templates/interview_ready/*.cpp` 的第 5~10 部分
- 想短期冲刺 ACM 风格笔试：
  从 `interview_algorithm_toolbox/README.md` 开始
- 想在笔试前 10 分钟做压缩复习：
  直接看 `interview_algorithm_toolbox/90_minute_exam_checklist.md`
- 想做 90 分钟计时模拟：
  直接看 `interview_algorithm_toolbox/90_minute_mock_set.md`

## 推荐阅读链接

- 模板总览：[`templates/README.md`](templates/README.md)
- 题型识别总指南：[`templates/PATTERN_RECOGNITION_GUIDE.md`](templates/PATTERN_RECOGNITION_GUIDE.md)
- 面试模板索引：[`templates/interview_ready/README.md`](templates/interview_ready/README.md)
- 笔试复习知识库：[`interview_algorithm_toolbox/README.md`](interview_algorithm_toolbox/README.md)
- 90 分钟笔试速查：[`interview_algorithm_toolbox/90_minute_exam_checklist.md`](interview_algorithm_toolbox/90_minute_exam_checklist.md)
- 90 分钟模拟题单：[`interview_algorithm_toolbox/90_minute_mock_set.md`](interview_algorithm_toolbox/90_minute_mock_set.md)
- 笔记索引：[`notes/README.md`](notes/README.md)
- 面试补强建议：[`notes/interview_prep/internship_interview_gap_analysis.md`](notes/interview_prep/internship_interview_gap_analysis.md)
- 树图专项强化：[`notes/interview_prep/tree_graph_strengthening_plan.md`](notes/interview_prep/tree_graph_strengthening_plan.md)

## 环境要求

- 编译器：`g++` 或 `clang++`
- 标准：`C++17`
- 系统：macOS / Linux / Windows (WSL)

---

最后更新：2026-03-22
