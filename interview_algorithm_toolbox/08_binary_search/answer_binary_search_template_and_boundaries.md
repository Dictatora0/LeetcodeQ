# 答案二分标准代码骨架 + 左右边界怎么取

这页只做一件事：

把笔试里最常用的答案二分写法和“左右边界怎么取”压成一页速查。

很多人不是不会二分，而是：

- 不知道 `check(mid)` 通过时该收左边还是右边
- 不知道 `left` 和 `right` 应该从哪里来
- 最后写成死循环，或者把答案卡在搜索区间外

---

## 先判断能不能做答案二分

题目通常满足这两个条件：

1. 题目要你求最小值或最大值。
2. 给定一个猜测答案 `mid` 后，能判断“是否可行”，并且这个可行性具有单调性。

常见单调性：

- `mid` 越大越容易可行
- `mid` 越小越容易可行

如果没有单调性，就不要硬套答案二分。

---

## 最常用模板 1：求最小可行值

适用情况：

- 题目问“最小多少”
- 并且 `check(mid)` 为 `true` 后，说明 `mid` 可行
- 更大的值也都可行

例如：

- 最小运输容量
- 最小最大段和
- 最短生产时间
- 最小初始生命值

### 标准骨架

```cpp
long long left = ...;   // 答案下界
long long right = ...;  // 答案上界

while (left < right) {
    long long mid = left + (right - left) / 2;

    if (check(mid)) {
        right = mid;
    } else {
        left = mid + 1;
    }
}

cout << left << '\n';
```

### 为什么这样写

- `check(mid) == true` 表示 `mid` 已经可行
- 但我们要找的是“最小可行值”
- 所以答案可能还在左半边，包括 `mid` 自己
- 因此写 `right = mid`

如果 `check(mid) == false`：

- 说明 `mid` 太小，不可行
- 那答案只能在右边
- 所以写 `left = mid + 1`

---

## 最常用模板 2：求最大可行值

适用情况：

- 题目问“最大多少”
- 并且 `check(mid)` 为 `true` 后，说明 `mid` 可行
- 更小的值也都可行

### 标准骨架

```cpp
long long left = ...;   // 答案下界
long long right = ...;  // 答案上界

while (left < right) {
    long long mid = left + (right - left + 1) / 2;

    if (check(mid)) {
        left = mid;
    } else {
        right = mid - 1;
    }
}

cout << left << '\n';
```

### 为什么这里要用上取中点

这里我们在 `check(mid) == true` 时写的是：

```cpp
left = mid;
```

如果还用普通中点：

```cpp
mid = (left + right) / 2;
```

当 `left + 1 == right` 时，`mid` 会等于 `left`，这样可能死循环。

所以求“最大可行值”时，常用：

```cpp
mid = left + (right - left + 1) / 2;
```

也就是偏右的中点。

---

## 左右边界到底怎么取

最稳的原则不是“拍脑袋猜个数”，而是：

1. `left` 要足够小，最好是答案不可能比它更小
2. `right` 要足够大，保证真正答案一定不超过它
3. 也可以理解成：
   整个答案一定落在 `[left, right]` 里

---

## 常见取法 1：左边界取理论最小值

例如最小运输容量、最小最大段和：

- 单个元素都必须被装进去
- 所以答案不可能小于数组最大值

于是：

```cpp
left = max_element(...)
```

典型文件：

- [answer_binary_search_minimum_capacity.cpp](./answer_binary_search_minimum_capacity.cpp)
- [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp)

---

## 常见取法 2：右边界取“最粗暴但一定可行”的值

还是以运输容量、最大段和为例：

- 如果容量等于所有元素总和
- 或者最大允许段和等于所有元素总和
- 那一定可行，因为全放一段都行

于是：

```cpp
right = sum(a)
```

这种边界虽然不一定最紧，但通常已经够好，而且很稳。

---

## 常见取法 3：按题意直接推出上界

例如最短生产时间：

- 最慢情况是只靠最快机器干活
- 最快机器每 `min_time` 时间做 1 件
- 做 `target` 件最多需要：

```cpp
right = min_time * target
```

典型文件：

- [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)

注意这里可能溢出，所以通常要用 `long long`。

---

## 常见取法 4：用“最大可能损失”构造上界

例如最小初始生命值：

- 如果把所有负数格子的损失全吃一遍
- 再额外保证生命值至少为 `1`
- 这个值一定足够大

于是可以写：

```cpp
right = total_negative_loss + 1
```

典型文件：

- [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp)

这个边界不一定最紧，但足以保证答案在区间里。

---

## 一个最实用的边界思考模板

拿到题后，直接问自己这 3 句话：

1. 答案最小至少是多少？
   也就是有没有一个显然不能再小的下界。
2. 答案最大至多是多少？
   也就是有没有一个显然一定可行的上界。
3. 我能不能证明真正答案一定在这个区间里？

只要这三句能答出来，边界通常就稳了。

---

## 三个现成例子

### 例 1：最小化分段后的最大段和

对应：

- [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp)

边界：

```cpp
left = max(a);
right = sum(a);
```

理由：

- 小于最大元素一定不行
- 等于总和一定行

### 例 2：最短生产时间

对应：

- [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)

边界：

```cpp
left = 1;
right = min_time * target;
```

理由：

- 时间至少是 1
- 最坏只让最快机器独自生产，也一定能做完

### 例 3：最小初始生命值

对应：

- [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp)

边界：

```cpp
left = 1;
right = total_negative_loss + 1;
```

理由：

- 初始生命值至少为 1
- 把全局可能损失兜住，一定不会比真实答案小

---

## 什么时候 `check` 通过时收右边，什么时候收左边

可以直接背成一句话：

- 求最小可行值：`check(mid)` 通过就收右边
- 求最大可行值：`check(mid)` 通过就收左边

再展开一点：

### 求最小可行值

我们想找最左边那个 `true`。

所以：

- `true` 说明已经可行，但还想看看能不能更小
- 收右边：`right = mid`

### 求最大可行值

我们想找最右边那个 `true`。

所以：

- `true` 说明当前可以，但还想看看能不能更大
- 收左边：`left = mid`

---

## 高频错误

### 错误 1：左右边界没包住答案

例如真正答案可能比你取的 `right` 还大，那二分再正确也没用。

### 错误 2：`mid` 写成 `(left + right) / 2`

数据范围大时可能溢出。

更稳的写法：

```cpp
long long mid = left + (right - left) / 2;
```

或者求最大可行值时：

```cpp
long long mid = left + (right - left + 1) / 2;
```

### 错误 3：把“最小可行值模板”和“最大可行值模板”混用

这会直接造成死循环或错答案。

### 错误 4：没先证明单调性

二分不是因为题目里有“最小”两个字就能做，
而是因为可行性随答案变化呈单调关系。

### 错误 5：`check` 自己就写错了

答案二分真正的核心通常不是 while 循环，而是 `check(mid)` 的正确性。

可配合阅读：

- [answer_binary_search_check_patterns_compare.md](./answer_binary_search_check_patterns_compare.md)

---

## 笔试前 30 秒速记版

1. 先证单调性
2. 再写 `check(mid)`
3. 求最小可行值：

```cpp
while (l < r) {
    mid = l + (r - l) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
}
```

4. 求最大可行值：

```cpp
while (l < r) {
    mid = l + (r - l + 1) / 2;
    if (check(mid)) l = mid;
    else r = mid - 1;
}
```

5. 边界要保证答案一定在 `[l, r]` 里

---

## 建议联动阅读

1. [answer_binary_search_check_patterns_compare.md](./answer_binary_search_check_patterns_compare.md)
2. [answer_binary_search_minimum_capacity.cpp](./answer_binary_search_minimum_capacity.cpp)
3. [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp)
4. [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)
5. [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp)
6. [README.md](./README.md)
