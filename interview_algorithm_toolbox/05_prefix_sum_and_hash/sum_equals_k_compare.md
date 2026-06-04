# 和为 k：个数 vs 最长区间

这一页专门对照：

- [subarray_count_sum_equals_k.cpp](./subarray_count_sum_equals_k.cpp)
- [longest_subarray_sum_equals_k.cpp](./longest_subarray_sum_equals_k.cpp)

## 共同前提

两题都基于同一个前缀和等式：

```text
prefix[i] - prefix[j] = k
```

等价于：

```text
prefix[j] = prefix[i] - k
```

所以扫描到当前位置 `i` 时，我们都在问：

```text
之前有没有出现过前缀和 prefix[i] - k
```

## 关键区别

| 目标 | 哈希表存什么 | 为什么 |
| --- | --- | --- |
| 统计个数 | 出现次数 | 每出现一次都能贡献一个新区间 |
| 求最长区间 | 第一次出现位置 | 越早出现，区间越长 |

## 统计个数的写法

```cpp
answer += count[prefix_sum - k];
++count[prefix_sum];
```

含义：
- 之前所有和为 `prefix_sum - k` 的前缀，都能和当前点组成合法区间
- 所以把它们的数量加到答案里

## 求最长区间的写法

```cpp
if (first_position.count(prefix_sum - k)) {
    best = max(best, i - first_position[prefix_sum - k]);
}
if (!first_position.count(prefix_sum)) {
    first_position[prefix_sum] = i;
}
```

含义：
- 我们只关心最早出现的位置，因为最早的位置配当前 i 才能形成最长区间
- 所以某个前缀和第一次出现后，就不要再覆盖

## 最容易混淆的地方

1. 统计个数时：
   不能只存第一次出现位置，因为那样会漏掉后续贡献。
2. 求最长区间时：
   不能存最后一次出现位置，因为那样区间会变短。
3. 两题都要初始化：

```cpp
prefix_sum = 0
```

对应的位置或次数：

```cpp
count[0] = 1
first_position[0] = 0
```

否则会漏掉从开头开始的合法区间。

## 什么时候优先想到这组模式

- 题面出现“连续子数组”
- 条件是“和为某个固定值 k”
- 数组里可能有负数，不能直接用普通滑动窗口

## 和记忆法

- `count` 题：
  “同一种前缀出现几次，就能贡献几次”
- `longest` 题：
  “要想最长，就一定要配最早的位置”
