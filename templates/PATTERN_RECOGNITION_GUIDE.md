# 算法题型分类与识别指南

**目标**: 3 秒内识别题型，30 秒内确定解法

---

## 🎯 快速识别流程图

```
看到题目
    ↓
是否要求"连续"？
    ├─ 是 → 滑动窗口 / 前缀和
    └─ 否 → 继续判断
        ↓
是否有"有序"？
    ├─ 是 → 二分查找 / 双指针
    └─ 否 → 继续判断
        ↓
是否是树/图？
    ├─ 是 → DFS / BFS
    └─ 否 → 继续判断
        ↓
是否要"所有可能"？
    ├─ 是 → 回溯
    └─ 否 → 继续判断
        ↓
是否求"最优解"？
    ├─ 是 → 动态规划 / 贪心
    └─ 否 → 哈希表 / 模拟
```

---

## 📚 详细题型分类

### 1️⃣ 滑动窗口（Sliding Window）

#### 识别特征
- ✅ 关键词：**连续子数组/子串**、**最长/最短**
- ✅ 要求：满足某个条件的连续区间
- ✅ 优化：从 O(n²) 到 O(n)

#### 典型题目模式
```
"找出最长的连续子串，使得..."
"找出最短的连续子数组，包含..."
"找出所有长度为 K 的子数组..."
"计算有多少个连续子数组满足..."
```

#### 解题步骤
1. 确定窗口内维护什么（计数/和/频次）
2. 确定窗口扩大条件（right++）
3. 确定窗口收缩条件（left++）
4. 更新结果的时机

#### 高频题目
| 题号 | 题目 | 难度 | 窗口类型 |
|------|------|------|---------|
| 3 | 无重复字符的最长子串 | Medium | 可变窗口 |
| 76 | 最小覆盖子串 | Hard | 可变窗口 |
| 209 | 长度最小的子数组 | Medium | 可变窗口 |
| 239 | 滑动窗口最大值 | Hard | 固定窗口 |
| 438 | 找到字符串中所有字母异位词 | Medium | 固定窗口 |
| 567 | 字符串的排列 | Medium | 固定窗口 |

#### 面试技巧
- 先问清楚是固定窗口还是可变窗口
- 明确窗口收缩的条件（这是关键）
- 注意边界条件（空字符串、单字符）

---

### 2️⃣ 双指针（Two Pointers）

#### 识别特征
- ✅ 关键词：**有序数组**、**两数之和**、**去重**
- ✅ 要求：O(n) 时间复杂度
- ✅ 特点：两个指针相向或同向移动

#### 典型题目模式
```
"在有序数组中找两个数..."
"移除数组中的重复元素..."
"判断链表是否有环..."
"合并两个有序数组..."
```

#### 三种类型

**类型 1：对撞指针（有序数组）**
```cpp
int left = 0, right = n - 1;
while (left < right) {
    if (满足条件) return;
    else if (sum < target) left++;
    else right--;
}
```

**类型 2：快慢指针（链表）**
```cpp
ListNode *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
}
```

**类型 3：同向指针（原地修改）**
```cpp
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (满足条件) {
        nums[slow++] = nums[fast];
    }
}
```

#### 高频题目
| 题号 | 题目 | 难度 | 指针类型 |
|------|------|------|---------|
| 15 | 三数之和 | Medium | 对撞指针 |
| 167 | 两数之和 II | Medium | 对撞指针 |
| 141 | 环形链表 | Easy | 快慢指针 |
| 142 | 环形链表 II | Medium | 快慢指针 |
| 26 | 删除有序数组中的重复项 | Easy | 同向指针 |
| 283 | 移动零 | Easy | 同向指针 |

---

### 3️⃣ DFS（深度优先搜索）

#### 识别特征
- ✅ 关键词：**树/图遍历**、**路径**、**连通性**
- ✅ 要求：遍历所有可能的路径
- ✅ 特点：递归实现，深度优先

#### 典型题目模式
```
"计算二叉树的最大深度..."
"找出所有从根到叶子的路径..."
"判断图中是否存在环..."
"计算岛屿数量..."
```

#### 三种场景

**场景 1：树 DFS（不需要 visited）**
```cpp
void dfs(TreeNode* node) {
    if (!node) return;
    // 处理当前节点
    dfs(node->left);
    dfs(node->right);
}
```

**场景 2：图 DFS（需要 visited）**
```cpp
void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v, visited);
    }
}
```

**场景 3：网格 DFS（四个方向）**
```cpp
void dfs(int x, int y) {
    if (越界 || 不满足条件) return;
    grid[x][y] = 已访问;
    dfs(x+1, y); dfs(x-1, y);
    dfs(x, y+1); dfs(x, y-1);
}
```

#### 高频题目
| 题号 | 题目 | 难度 | DFS 类型 |
|------|------|------|---------|
| 104 | 二叉树的最大深度 | Easy | 树 DFS |
| 200 | 岛屿数量 | Medium | 网格 DFS |
| 437 | 路径总和 III | Medium | 树 DFS |
| 543 | 二叉树的直径 | Easy | 树 DFS |
| 207 | 课程表 | Medium | 图 DFS |

---

### 4️⃣ BFS（广度优先搜索）

#### 识别特征
- ✅ 关键词：**最短路径**、**层序遍历**、**最少步数**
- ✅ 要求：找最短/最少
- ✅ 特点：队列实现，层次遍历

#### 典型题目模式
```
"找出从 A 到 B 的最短路径..."
"计算需要的最少步数..."
"按层序遍历二叉树..."
"找出距离为 K 的所有节点..."
```

#### 核心模板
```cpp
queue<Node> q;
q.push(start);
int steps = 0;

while (!q.empty()) {
    int size = q.size(); // 当前层的节点数
    for (int i = 0; i < size; i++) {
        Node cur = q.front();
        q.pop();

        if (cur == target) return steps;

        for (Node next : cur.neighbors()) {
            if (!visited.count(next)) {
                q.push(next);
                visited.insert(next);
            }
        }
    }
    steps++;
}
```

#### 高频题目
| 题号 | 题目 | 难度 | BFS 类型 |
|------|------|------|---------|
| 102 | 二叉树的层序遍历 | Medium | 层序遍历 |
| 994 | 腐烂的橘子 | Medium | 多源 BFS |
| 127 | 单词接龙 | Hard | 最短路径 |
| 199 | 二叉树的右视图 | Medium | 层序遍历 |

---

### 5️⃣ 回溯（Backtracking）

#### 识别特征
- ✅ 关键词：**所有可能**、**排列**、**组合**、**子集**
- ✅ 要求：枚举所有解
- ✅ 特点：DFS + 撤销选择

#### 典型题目模式
```
"找出所有可能的排列..."
"找出所有和为 target 的组合..."
"生成所有的子集..."
"解数独..."
```

#### 三种经典问题

**问题 1：排列（需要 used 数组）**
```cpp
void backtrack(vector<int>& path, vector<bool>& used) {
    if (path.size() == n) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        path.push_back(nums[i]);
        used[i] = true;
        backtrack(path, used);
        path.pop_back();
        used[i] = false;
    }
}
```

**问题 2：组合（需要 start 索引）**
```cpp
void backtrack(int start, vector<int>& path) {
    if (path.size() == k) {
        result.push_back(path);
        return;
    }
    for (int i = start; i < n; i++) {
        path.push_back(i);
        backtrack(i + 1, path);
        path.pop_back();
    }
}
```

**问题 3：子集（每个节点都是答案）**
```cpp
void backtrack(int start, vector<int>& path) {
    result.push_back(path); // 每个节点都是答案
    for (int i = start; i < n; i++) {
        path.push_back(nums[i]);
        backtrack(i + 1, path);
        path.pop_back();
    }
}
```

#### 高频题目
| 题号 | 题目 | 难度 | 回溯类型 |
|------|------|------|---------|
| 46 | 全排列 | Medium | 排列 |
| 78 | 子集 | Medium | 子集 |
| 39 | 组合总和 | Medium | 组合 |
| 22 | 括号生成 | Medium | 特殊回溯 |
| 51 | N 皇后 | Hard | 棋盘回溯 |

---

### 6️⃣ 二分查找（Binary Search）

#### 识别特征
- ✅ 关键词：**有序数组**、**查找**、**第 K 个**
- ✅ 要求：O(log n) 时间复杂度
- ✅ 特点：每次排除一半

#### 典型题目模式
```
"在有序数组中查找目标值..."
"找出第一个大于等于 target 的位置..."
"在旋转数组中查找..."
"找出第 K 小的元素..."
```

#### 三种模板

**模板 1：标准二分（查找目标值）**
```cpp
int left = 0, right = n - 1;
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
}
```

**模板 2：左边界（第一个 >= target）**
```cpp
int left = 0, right = n;
while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) left = mid + 1;
    else right = mid;
}
return left;
```

**模板 3：右边界（最后一个 <= target）**
```cpp
int left = 0, right = n;
while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] <= target) left = mid + 1;
    else right = mid;
}
return left - 1;
```

#### 高频题目
| 题号 | 题目 | 难度 | 二分类型 |
|------|------|------|---------|
| 704 | 二分查找 | Easy | 标准二分 |
| 34 | 在排序数组中查找元素的第一个和最后一个位置 | Medium | 左右边界 |
| 33 | 搜索旋转排序数组 | Medium | 旋转数组 |
| 153 | 寻找旋转排序数组中的最小值 | Medium | 旋转数组 |

---

### 7️⃣ 动态规划（Dynamic Programming）

#### 识别特征
- ✅ 关键词：**最优解**、**最大/最小**、**计数**
- ✅ 要求：子问题重叠、最优子结构
- ✅ 特点：状态转移方程

#### 典型题目模式
```
"找出最大/最小的..."
"有多少种方法..."
"能否达到..."
"最长的...序列..."
```

#### 解题步骤
1. 定义状态（dp[i] 表示什么）
2. 找状态转移方程
3. 确定初始状态
4. 确定遍历顺序
5. 空间优化（可选）

#### 经典问题分类

**类型 1：线性 DP**
- 爬楼梯、打家劫舍、最大子数组和

**类型 2：背包 DP**
- 0-1 背包、完全背包、多重背包

**类型 3：区间 DP**
- 最长回文子串、戳气球

**类型 4：树形 DP**
- 打家劫舍 III、二叉树的直径

#### 高频题目
| 题号 | 题目 | 难度 | DP 类型 |
|------|------|------|---------|
| 70 | 爬楼梯 | Easy | 线性 DP |
| 53 | 最大子数组和 | Medium | 线性 DP |
| 198 | 打家劫舍 | Medium | 线性 DP |
| 300 | 最长递增子序列 | Medium | 线性 DP |
| 322 | 零钱兑换 | Medium | 背包 DP |

---

### 8️⃣ 单调栈（Monotonic Stack）

#### 识别特征
- ✅ 关键词：**下一个更大/更小**、**直方图**
- ✅ 要求：O(n) 时间复杂度
- ✅ 特点：栈内元素单调递增或递减

#### 典型题目模式
```
"找出每个元素右边第一个比它大的..."
"找出每个元素左边第一个比它小的..."
"计算直方图中最大的矩形..."
"接雨水..."
```

#### 核心模板
```cpp
stack<int> st; // 存索引
for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[i] > nums[st.top()]) {
        int idx = st.top();
        st.pop();
        // nums[i] 是 nums[idx] 右边第一个更大的元素
    }
    st.push(i);
}
```

#### 高频题目
| 题号 | 题目 | 难度 | 单调栈类型 |
|------|------|------|-----------|
| 739 | 每日温度 | Medium | 单调递减栈 |
| 42 | 接雨水 | Hard | 单调递减栈 |
| 84 | 柱状图中最大的矩形 | Hard | 单调递增栈 |
| 496 | 下一个更大元素 I | Easy | 单调递减栈 |

---

### 9️⃣ 前缀和（Prefix Sum）

#### 识别特征
- ✅ 关键词：**区间和**、**子数组和**、**连续**
- ✅ 要求：快速查询区间和
- ✅ 特点：预处理 + O(1) 查询

#### 典型题目模式
```
"找出和为 K 的子数组个数..."
"计算区间 [i, j] 的和..."
"找出和为 0 的最长子数组..."
```

#### 两种用法

**用法 1：区间和查询**
```cpp
vector<int> prefix(n + 1);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + nums[i];
}
// 查询 [left, right] 的和
int sum = prefix[right + 1] - prefix[left];
```

**用法 2：前缀和 + 哈希表**
```cpp
unordered_map<int, int> prefixCount;
prefixCount[0] = 1;
int sum = 0, count = 0;
for (int num : nums) {
    sum += num;
    count += prefixCount[sum - k];
    prefixCount[sum]++;
}
```

#### 高频题目
| 题号 | 题目 | 难度 | 前缀和类型 |
|------|------|------|-----------|
| 560 | 和为 K 的子数组 | Medium | 前缀和 + 哈希表 |
| 437 | 路径总和 III | Medium | 前缀和 + 哈希表 |
| 523 | 连续的子数组和 | Medium | 前缀和 + 哈希表 |
| 303 | 区域和检索 | Easy | 前缀和数组 |

---

### 🔟 并查集（Union Find）

#### 识别特征
- ✅ 关键词：**连通分量**、**合并集合**、**动态连通性**
- ✅ 要求：快速判断连通性
- ✅ 特点：路径压缩 + 按秩合并

#### 典型题目模式
```
"判断两个节点是否连通..."
"计算连通分量的个数..."
"判断图中是否有环..."
"合并集合..."
```

#### 核心模板
```cpp
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;

        // 按秩合并
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};
```

#### 高频题目
| 题号 | 题目 | 难度 | 并查集应用 |
|------|------|------|-----------|
| 200 | 岛屿数量 | Medium | 连通分量 |
| 547 | 省份数量 | Medium | 连通分量 |
| 684 | 冗余连接 | Medium | 环检测 |
| 721 | 账户合并 | Medium | 合并集合 |

---

## 🎯 面试实战技巧

### 1. 快速识别流程（30 秒内）

```
Step 1: 看关键词
    ↓
Step 2: 确定数据结构（数组/树/图）
    ↓
Step 3: 确定算法类型
    ↓
Step 4: 选择对应模板
```

### 2. 常见组合

| 组合 | 适用场景 | 示例题目 |
|------|---------|---------|
| 滑动窗口 + 哈希表 | 子串问题 | LeetCode 3, 76, 438 |
| DFS + 记忆化 | 树形 DP | LeetCode 337, 543 |
| BFS + 哈希表 | 最短路径 | LeetCode 127, 752 |
| 前缀和 + 哈希表 | 子数组和 | LeetCode 560, 437 |
| 单调栈 + DP | 直方图问题 | LeetCode 42, 84 |

### 3. 优化路径

```
暴力解法 (O(n³))
    ↓ 排序
O(n² log n)
    ↓ 双指针
O(n²)
    ↓ 哈希表
O(n)
    ↓ 滑动窗口
O(n)
```

---

## 📝 面试前检查清单

- [ ] 能在 30 秒内识别题型
- [ ] 熟记 10 大算法模板
- [ ] 能快速说出时间空间复杂度
- [ ] 知道每种算法的适用场景
- [ ] 能举出 2-3 个典型例题
- [ ] 知道常见的优化路径
- [ ] 能处理边界条件

---

**最后提醒**:
- 题型识别是面试的第一步，也是最重要的一步
- 多做题，培养题感
- 面试时不确定就问面试官
- 先说思路，再写代码

**祝你面试顺利！🎉**
