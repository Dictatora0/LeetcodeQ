# LeetCode 算法学习仓库

这是一个以 C++ 为主的刷题仓库，目标不是只“刷过题”，而是把常见题型整理成可复习、可讲解、可运行的面试素材。

## 当前概览

- `solutions/`：**129** 份按专题整理的题解，批量编译全部通过
- `solutions/cpp/`：**108** 份历史代码，用于保留原始思路和迁移前版本
- `templates/`：算法模板、题型识别和代码片段
- `notes/`：学习日志与面试准备笔记

目前覆盖的核心专题包括：

- 数组、链表、二叉树、动态规划
- 滑动窗口、前缀和、单调栈、堆
- 贪心、回溯、图、设计题、Trie、位运算

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
│   ├── core_templates/         # 核心算法模板
│   ├── interview_ready/        # 面试导向模板
│   ├── problem_patterns/       # 题型识别
│   └── code_snippets/          # 常用片段
├── scripts/
│   ├── run_cpp.sh              # 单题编译运行
│   └── compile_all.sh          # 批量编译
└── notes/
    ├── learning_log/           # 学习日志
    └── interview_prep/         # 面试补强笔记
```

## 使用方法

### 编译单个题目

```bash
./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp
./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp --build-only
MODE=debug ./scripts/run_cpp.sh solutions/binary_tree/leetcode_101_symmetric_tree.cpp
```

### 批量编译专题题解

```bash
./scripts/compile_all.sh
./scripts/compile_all.sh solutions/binary_tree
MODE=debug ./scripts/compile_all.sh
```

## 推荐阅读入口

- 复习算法模板：[`templates/interview_ready/README.md`](templates/interview_ready/README.md)
- 看题型识别：[`templates/PATTERN_RECOGNITION_GUIDE.md`](templates/PATTERN_RECOGNITION_GUIDE.md)
- 看模板体系说明：[`templates/README.md`](templates/README.md)
- 看学习笔记：[`notes/README.md`](notes/README.md)
- 看本轮面试补强建议：[`notes/interview_prep/internship_interview_gap_analysis.md`](notes/interview_prep/internship_interview_gap_analysis.md)

## 代码特点

分类目录下的大多数题解都尽量包含：

- 中文题意概述
- 思路拆解与关键观察
- 至少一种可面试讲清楚的解法
- 复杂度分析
- `main()` 示例或测试输出

`solutions/cpp/` 则保留原始版本，可能包含：

- 更简洁但未充分整理的实现
- 迁移前代码
- `TODO` 或占位测试

因此面试准备时，建议优先阅读 `solutions/` 下的专题版本。

## 面试导向建议

从当前仓库分布看，你在动态规划、二叉树、链表、数组上的积累已经不错；接下来更值得补的是：

- 双指针
- 二分边界题 / 二分答案
- 图搜索
- 并查集

建议先补这一组高频题：

- `33`, `34`, `153`
- `11`, `26`
- `236`, `124`
- `547`, `684`

详细说明见 [`notes/interview_prep/internship_interview_gap_analysis.md`](notes/interview_prep/internship_interview_gap_analysis.md)。

## 开发环境

- 编译器：`g++` / `clang++`
- C++ 标准：`C++17`
- 系统：macOS / Linux / Windows (WSL)

---

最后更新：2026-03-21
