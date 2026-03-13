
# 前缀和模式指南

## 常见题型分类
- 区间和/子数组和
- 统计满足条件的区间数量
- 二维矩阵区域和

## 模式识别技巧
- 出现“连续区间”和“区间和”
- 需要多次查询区间和
- 与哈希表结合统计数量

## 思路要点
- prefix[0]=0 是关键
- 子数组和为 k 使用哈希表统计前缀和次数
- 二维前缀和注意边界

## 经典题目
- 560 Subarray Sum Equals K
- 1248 Count Number of Nice Subarrays
- 304 Range Sum Query 2D
- 974 Subarray Sums Divisible by K

## 对应算法模板
- core_templates/prefix_sum_template.cpp
