
# 树问题模式指南

## 常见题型分类
- 二叉树遍历（前序/中序/后序/层序）
- 路径问题（路径和、最长路径）
- 构造与恢复（由遍历序列构造树）
- 二叉搜索树性质（验证、排名）

## 模式识别技巧
- 题目出现“遍历”“路径”“祖先/子孙”常对应 DFS/BFS
- 需要层次结果时优先考虑 BFS
- 需要从根到叶或任意路径时考虑 DFS + 回溯

## 思路要点
- 树天然无环，递归是最直观解法
- 需要统计路径时注意回溯恢复
- BST 题常用中序有序性质

## 经典题目
- 94 Binary Tree Inorder Traversal
- 102 Binary Tree Level Order Traversal
- 124 Binary Tree Maximum Path Sum
- 236 Lowest Common Ancestor
- 230 Kth Smallest Element in a BST

## 对应算法模板
- core_templates/dfs_template.cpp
- core_templates/bfs_template.cpp
