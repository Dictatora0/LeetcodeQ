
# 滑动窗口模式指南

## 常见题型分类
- 最长子串/最长子数组
- 最短覆盖子串
- 固定窗口统计

## 模式识别技巧
- 题目强调“连续子数组/子串”
- 需要“最短/最长”满足条件的区间
- 条件满足后可以收缩左边界

## 思路要点
- 明确窗口内维护的状态（计数/和/频次）
- 右扩左缩保证线性复杂度
- 处理重复字符或计数时注意更新顺序

## 经典题目
- 3 Longest Substring Without Repeating Characters
- 76 Minimum Window Substring
- 209 Minimum Size Subarray Sum
- 239 Sliding Window Maximum
- 438 Find All Anagrams in a String

## 对应算法模板
- core_templates/sliding_window_template.cpp
