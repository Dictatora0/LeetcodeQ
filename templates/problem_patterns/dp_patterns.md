
# 动态规划模式指南

## 常见题型分类
- 最优解（最大/最小）
- 计数问题（路径数、方案数）
- 选择与不选择（打家劫舍）
- 区间 DP（回文子串）

## 模式识别技巧
- 题目需要“最优/最少/最多/数量”
- 子问题重叠且有最优子结构
- 可以写出状态转移关系

## 思路要点
- 明确状态与转移是核心
- 先写递归关系，再转迭代
- 能滚动就滚动，节省空间

## 经典题目
- 70 Climbing Stairs
- 198 House Robber
- 64 Minimum Path Sum
- 1143 Longest Common Subsequence
- 322 Coin Change

## 对应算法模板
- core_templates/dp_template.cpp
