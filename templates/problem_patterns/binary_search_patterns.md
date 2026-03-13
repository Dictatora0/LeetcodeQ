
# 二分查找模式指南

## 常见题型分类
- 有序数组查找
- 左右边界/插入位置
- 答案单调的最小/最大值

## 模式识别技巧
- 题目包含“有序”“排序后”
- 目标函数单调（可行/不可行）
- 需要找最小满足条件的值

## 思路要点
- 区间定义要统一（闭区间/左闭右开）
- mid 计算避免溢出
- 边界更新要保证区间收缩

## 经典题目
- 704 Binary Search
- 33 Search in Rotated Sorted Array
- 875 Koko Eating Bananas
- 410 Split Array Largest Sum
- 153 Find Minimum in Rotated Sorted Array

## 对应算法模板
- core_templates/binary_search_template.cpp
