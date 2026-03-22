
# 二分查找模式指南

## 一眼识别信号（3 秒判断）
- 输入天然有序，或可以通过条件判断形成单调区间
- 目标是“找某个边界位置”而不是遍历所有值
- 题目要求 O(log n) 或“每次排除一半”
- 可以把答案空间抽象成“可行/不可行”的单调布尔函数

## 常见题型分类
- 标准查找：
  在有序数组中找某个值是否存在
- 左右边界：
  找第一个 `>= target`、最后一个 `<= target`
- 旋转数组二分：
  局部有序，先判断哪一半有序再缩区间
- 答案二分：
  不直接在数组上找，而是在“答案范围”上二分可行性

## 区间写法要先定死
- 闭区间 `[left, right]`：
  循环条件 `left <= right`
- 左闭右开 `[left, right)`：
  循环条件 `left < right`
- 同一道题不要混用两种写法，最容易出边界 bug

## 三个核心模板

### 1) 标准二分（找目标）
```cpp
int left = 0, right = n - 1;
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
}
return -1;
```

### 2) 左边界（第一个 >= target）
```cpp
int left = 0, right = n;
while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) left = mid + 1;
    else right = mid;
}
return left;
```

### 3) 答案二分（最小可行值）
```cpp
int left = low, right = high;
while (left < right) {
    int mid = left + (right - left) / 2;
    if (check(mid)) right = mid;
    else left = mid + 1;
}
return left;
```

## 高频易错点
- `mid = (left + right) / 2` 可能溢出
- 更新边界时没有排除 `mid`，导致死循环
- 左边界和右边界模板混用，返回值错一位
- `check(mid)` 写反，导致答案朝错误方向收缩

## 面试口述模板（30 秒）
- “这题存在单调性，我可以用二分把复杂度降到 O(log n)。”
- “我使用 `[left, right)` 写法，保证循环不变式一致。”
- “`check(mid)` 表示 `...`，可行则收缩右边界，不可行收缩左边界。”
- “最终 `left` 落在第一个满足条件的位置。”

## 推荐刷题路径
- 入门：
  LC 704, LC 35, LC 34
- 进阶：
  LC 33, LC 153, LC 162
- 综合：
  LC 875, LC 410, LC 1011

## 对应算法模板
- `core_templates/binary_search_template.cpp`
- `interview_ready/binary_search_template.cpp`
