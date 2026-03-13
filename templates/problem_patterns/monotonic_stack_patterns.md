
# 单调栈模式指南

## 常见题型分类
- 下一个更大/更小元素
- 柱状图最大矩形
- 左右最近更大/更小边界

## 模式识别技巧
- 题目包含“下一个更大/更小”
- 需要为每个位置找最近边界
- 需要 O(n) 求区间性质

## 思路要点
- 栈里一般存索引
- 递增/递减栈选择取决于“找大还是找小”
- 计算区间宽度时注意边界

## 经典题目
- 496 Next Greater Element I
- 739 Daily Temperatures
- 84 Largest Rectangle in Histogram
- 42 Trapping Rain Water
- 907 Sum of Subarray Minimums

## 对应算法模板
- core_templates/monotonic_stack_template.cpp
