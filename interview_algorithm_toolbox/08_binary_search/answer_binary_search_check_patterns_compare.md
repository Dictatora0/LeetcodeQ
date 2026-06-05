# 答案二分三种 check 怎么识别

这份对照文档只解决一个非常实际的问题：

看到一道“最小值 / 最大值 + 可行性判断”的题时，怎么快速判断它属于：

1. 答案二分 + 贪心 check
2. 答案二分 + 数学 check
3. 答案二分 + DP check

如果这个判断做错，后面的实现方向往往也会跟着错。

---

## 先统一一个总框架

答案二分通常长这样：

1. 题目要求最小化某个值，或者最大化某个值。
2. 你猜一个答案 `mid`。
3. 把原问题转化成：
   “当答案限制为 `mid` 时，能不能做到？”
4. 如果“能做到”关于 `mid` 具有单调性，就可以二分。

例如：

- 最大允许段和越大，越容易分段成功。
- 允许的总时间越长，越容易生产够目标数量。
- 初始生命值越大，越容易走到终点。

真正难的地方通常不在二分本身，而在 `check(mid)` 怎么写。

---

## 一张表先看懂

| check 类型 | 典型信号 | 常见题面措辞 | 代表文件 |
| --- | --- | --- | --- |
| 贪心 check | 从左到右扫描时，局部决策天然明确 | 最多分成 m 段、每段不超过 limit、最小化最大值 | [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp) |
| 数学 check | 给定答案后，只需要做公式计算或线性计数 | 给定时间能做多少、给定容量能装多少、给定速度能完成多少 | [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)、[answer_binary_search_minimum_capacity.cpp](./answer_binary_search_minimum_capacity.cpp) |
| DP check | 给定答案后，存在多条路径 / 多种状态转移，需要比较“全局最优可行状态” | 路径是否可达、剩余资源是否足够、局部最优不代表全局最优 | [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp) |

---

## 第一类：答案二分 + 贪心 check

对应文件：

- [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp)

### 怎么识别

看到下面这些信号，优先怀疑“贪心 check”：

- 数组按原顺序处理，通常不能打乱顺序。
- 需要分段、装载、切分、安排。
- 给定一个限制 `limit` 后，每一步“能塞就塞、不能塞就切开”。
- 局部决策很自然，而且提前切开不会更优。

### 为什么能用贪心

以“最小化分段后的最大段和”为例：

- 给定最大允许段和 `limit`。
- 从左到右尽量把元素放进当前段。
- 如果再放一个就会超过 `limit`，那这一刀是被迫切开的。

这里的关键不是“我想贪心”，而是：

- 如果当前段还能放，你却提前切开，只会让段数变多，不会更好。
- 所以“尽量塞满当前段”会得到给定 `limit` 下的最少段数。

这就是贪心成立的理由。

### 看到什么题面时优先想到它

- “把数组分成不超过 `m` 段”
- “每段和不超过 `x`”
- “最小化最大的负担 / 最大长度 / 最大段和”
- “每辆车最多装 `x`，问最小 `x`”

### 常见误判

- 以为“答案二分”就一定要配贪心。
- 实际上很多题给定 `mid` 后根本没有“能塞就塞”的局部决策，而只是统计。

---

## 第二类：答案二分 + 数学 check

对应文件：

- [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)
- [answer_binary_search_minimum_capacity.cpp](./answer_binary_search_minimum_capacity.cpp)

### 怎么识别

看到下面这些信号，优先怀疑“数学 check”：

- 给定 `mid` 后，不需要选路径，也不需要做复杂状态转移。
- 每个元素、每台机器、每个工人对答案的贡献可以独立计算。
- `check(mid)` 本质上只是：
  统计总量、累加贡献、判断是否达到目标。

### 为什么它不是贪心

以“最短生产时间”为例：

- 给定总时间 `T`。
- 每台机器独立生产 `floor(T / time[i])` 件。
- 总产量是各台机器贡献之和。

这里没有“决策顺序”问题，也没有“我该不该现在切开”这种选择。
你只是把所有机器能做的数量算出来。

所以它不是贪心，而是纯数学计数。

### 看到什么题面时优先想到它

- “最少多少时间才能生产够 `target` 件产品”
- “给定速度 / 时间 / 长度，最多完成多少”
- “如果容量是 `mid`，一共能装多少 / 运多少 / 做多少”
- “每个对象的贡献互不影响，可以直接求和”

### 常见误判

- 把“统计贡献”误当成“过程模拟 + 贪心”。
- 右边界取太小。
- 累加贡献时没有防溢出或没有及时截断。

---

## 第三类：答案二分 + DP check

对应文件：

- [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp)

### 怎么识别

看到下面这些信号，优先怀疑“DP check”：

- 给定 `mid` 后，是否可行依赖整条路径或多个阶段的状态。
- 局部最优选择不一定能推出全局可行。
- 同一个位置可能通过不同路径到达，而且到达时“剩余资源”不同。
- 你不仅要知道“能不能到”，还要知道“以什么状态到”。

### 为什么贪心不够

以“最小初始生命值”为例：

- 给定初始生命值 `H`。
- 从左上到右下，每一步都要求当前生命值始终 `>= 1`。
- 某条路径眼前看起来更好，不代表之后一定更好。

这时如果你只做局部选择，比如“每次优先走当前格子值更大的方向”，很容易错。

因为问题的本质是：

- 到达某个格子时，剩多少生命值？
- 这个剩余值是否足以支撑后续路线？

这就是状态转移问题，所以要用 DP 做 `check(H)`。

### 看到什么题面时优先想到它

- “给定初始值，问是否存在一条可行路径”
- “走图 / 走网格 / 分阶段转移”
- “每步状态会变化，后续可行性依赖当前剩余状态”
- “局部最优路线不可靠”

### 常见误判

- 试图用 BFS / DFS 暴搜，但复杂度顶不住。
- 试图只记“能否到达”，却不记“到达后的最好状态”。
- 误以为所有答案二分的 check 都能用贪心写。

---

## 一个快速判断流程

做题时可以按这个顺序问自己：

1. 我能不能先证明“答案越大越容易满足”或“答案越小越容易满足”？
   如果能，说明可能是答案二分。
2. 给定一个 `mid` 后，check 是不是只需要独立统计每个元素的贡献？
   如果是，优先数学 check。
3. 给定一个 `mid` 后，check 是不是从左到右做局部决策，而且“能塞就塞 / 能做就做”天然正确？
   如果是，优先贪心 check。
4. 给定一个 `mid` 后，check 是不是依赖路径、阶段、剩余资源等状态？
   如果是，优先 DP check。

可以把它压缩成一句话：

- 独立贡献求和：数学
- 线性扫描局部决策：贪心
- 路径 / 状态转移：DP

---

## 容易混淆的对比

### 对比 1：贪心 check vs 数学 check

贪心 check 的核心是“要做决策”：

- 例如当前段要不要继续放元素。
- 当前车还能不能继续装货。

数学 check 的核心是“没有决策，只是统计”：

- 机器在时间 `T` 内能做多少件。
- 每个元素对总贡献是多少。

如果你发现 `check(mid)` 里根本没有“选择”这件事，往往就不是贪心。

### 对比 2：贪心 check vs DP check

贪心 check 通常可以只维护少量局部变量：

- 当前段和
- 已使用段数

DP check 通常要维护“到达某状态时的最好结果”：

- 到达格子 `(i, j)` 时最多剩多少生命值
- 到达阶段 `i` 时还能保留多少资源

如果后续可行性取决于“到当前状态时还剩多少”，就更偏向 DP。

### 对比 3：数学 check vs DP check

数学 check 常见形式是：

- `sum(mid / a[i])`
- `count += ...`
- `need <= limit`

DP check 常见形式是：

- `dp[i][j]`
- `dp[i]`
- 从前一个状态转移到下一个状态

如果 `check` 写出来像一道独立的小 DP 题，那它就是 DP check。

---

## 笔试里怎么用这页

如果你在 90 分钟笔试里看到一题“最小值 / 最大值”：

1. 先不要急着写二分模板。
2. 先拿样例问自己：给一个猜测答案 `mid`，我怎么判断它是否可行？
3. 再判断这个判断过程属于：
   计数、贪心、还是 DP。

很多二分题不是卡在二分，而是卡在 check 识别错误。

---

## 建议联动阅读

1. [answer_binary_search_minimum_capacity.cpp](./answer_binary_search_minimum_capacity.cpp)
2. [answer_binary_search_minimize_max_segment_sum.cpp](./answer_binary_search_minimize_max_segment_sum.cpp)
3. [answer_binary_search_minimum_production_time.cpp](./answer_binary_search_minimum_production_time.cpp)
4. [answer_binary_search_minimum_initial_health_grid.cpp](./answer_binary_search_minimum_initial_health_grid.cpp)
5. [README.md](./README.md)
