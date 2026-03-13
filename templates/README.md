
# 算法模板库（Algorithm Template System）

本目录包含三层模板体系，用于快速识别题型并复用代码。

## 目录结构
- core_templates/：核心算法模板（可直接复制使用）
- problem_patterns/：题型识别指南（模式归纳）
- code_snippets/：常用代码片段（工具与辅助）

## 算法分类表

| Algorithm | Typical Problems | Difficulty |
|---|---|---|
| Two Pointers | 有序数组两数之和 | Easy |
| Sliding Window | 最长/最短子串 | Medium |
| DFS | 树遍历、路径搜索 | Easy |
| BFS | 层序遍历、最短路径 | Easy |
| Binary Search | 有序数组查找 | Easy |
| Monotonic Stack | Next Greater Element | Medium |
| Prefix Sum | 子数组和统计 | Medium |
| Union Find | 连通分量 | Medium |
| Dynamic Programming | 最优解、计数 | Medium |

## 算法学习路线

推荐学习顺序：
1. Two Pointers
2. Sliding Window
3. DFS / BFS
4. Binary Search
5. Stack / Monotonic Stack
6. Prefix Sum
7. Union Find
8. Dynamic Programming
9. Backtracking

## 如何使用模板

步骤：
1. 识别题目模式（参考 problem_patterns）
2. 定位对应 core_templates
3. 复制模板并替换为题目逻辑
4. 补充边界条件与测试用例

## 质量要求
- 代码 C++17 可编译
- 注释清晰，便于复用
- 模板可直接用于面试与刷题
