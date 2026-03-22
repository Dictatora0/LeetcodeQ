
# 前缀和模式指南

## 一眼识别信号（3 秒判断）
- 关键词是“区间和”“连续子数组和”“多次范围查询”
- 你发现自己在重复计算 `nums[l..r]` 的和
- 题目要求统计“和为 k 的子数组个数”或“可被 k 整除”

## 常见题型分类
- 区间和查询：
  数组不频繁更新，查询很多次
- 子数组计数：
  统计满足和条件的子数组个数（前缀和 + 哈希表）
- 二维区域和：
  矩阵子区域求和（二维前缀和）
- 同余类统计：
  和对 `k` 取模后的余数计数（LC 974 / LC 523）

## 核心公式
- 一维定义：
  `prefix[i] = nums[0] + ... + nums[i-1]`
- 区间和：
  `sum(l, r) = prefix[r+1] - prefix[l]`
- 子数组和为 `k`：
  若 `prefix[j] - prefix[i] = k`，则 `prefix[i] = prefix[j] - k`

## 高频模板

### 1) 一维区间和
```cpp
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + nums[i];
}
int rangeSum = prefix[r + 1] - prefix[l];
```

### 2) 子数组和计数（前缀和 + 哈希）
```cpp
unordered_map<int, int> cnt;
cnt[0] = 1; // 空前缀
int sum = 0, ans = 0;

for (int x : nums) {
    sum += x;
    if (cnt.count(sum - k)) ans += cnt[sum - k];
    cnt[sum]++;
}
```

### 3) 二维前缀和
```cpp
prefix[i][j] = matrix[i-1][j-1]
             + prefix[i-1][j]
             + prefix[i][j-1]
             - prefix[i-1][j-1];
```

## 高频易错点
- 忘记初始化 `prefix[0] = 0` 或 `cnt[0] = 1`
- 区间公式写成 `prefix[r] - prefix[l]`（少一位）
- 余数统计未处理负数：`((sum % k) + k) % k`
- 二维容斥公式加减号写反

## 和相似模式的区别
- vs 滑动窗口：
  滑动窗口更适合“动态约束”；前缀和更适合“区间和代数关系”
- vs 线段树：
  前缀和实现简单但不支持高频更新，线段树适合动态修改

## 面试口述模板（30 秒）
- “这题核心是连续区间和，我先做前缀和预处理。”
- “任意区间和可用两次前缀和相减 O(1) 得到。”
- “如果要求子数组个数，我再加哈希表统计前缀和出现次数。”
- “总复杂度 O(n)，空间 O(n)。”

## 推荐刷题路径
- 入门：
  LC 303, LC 560
- 进阶：
  LC 304, LC 523, LC 974
- 综合：
  LC 1248, LC 525, LC 437

## 对应算法模板
- `core_templates/prefix_sum_template.cpp`
- `interview_ready/prefix_sum_template.cpp`
