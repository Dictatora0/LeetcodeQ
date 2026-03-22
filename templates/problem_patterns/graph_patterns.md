
# 图问题模式指南

## 一眼识别信号（3 秒判断）
- 题目描述里有“节点-边”关系，或网格可抽象为图
- 关键词是“连通性/可达性/最短路径/依赖关系”
- 需要从一个状态扩展到相邻状态（四方向、邻接表、转换规则）

## 常见题型分类
- 连通块统计：
  岛屿数量、朋友圈、省份数量（DFS/BFS/并查集）
- 无权最短路：
  最少步数、最短转换次数（BFS）
- 有向依赖关系：
  课程安排、编译顺序（拓扑排序）
- 动态连通：
  边不断加入后判断是否连通（并查集）

## 选型速判
- “最少步数/最短路径（每条边权重相同）”：
  BFS
- “要遍历所有可达节点/所有连通块”：
  DFS 或 BFS
- “在线合并集合、反复判断连通”：
  并查集
- “先后依赖且需要判断环或给出顺序”：
  拓扑排序

## 图题通用检查项
- 如何建图：
  邻接表、矩阵、隐式图（字符串变换/状态搜索）
- 是否需要 `visited`：
  遍历图几乎总需要，防止重复访问或死循环
- 起点数量：
  单源 BFS 还是多源 BFS
- 终止条件：
  找到目标就返回，还是要遍历完整图

## 常用模板

### 1) DFS 连通块
```cpp
void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v);
    }
}
```

### 2) BFS 最短步数
```cpp
queue<int> q;
q.push(start);
visited[start] = true;
int steps = 0;

while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
        int u = q.front(); q.pop();
        if (u == target) return steps;
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    steps++;
}
```

### 3) 拓扑排序（Kahn）
```cpp
queue<int> q;
for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);

while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : graph[u]) {
        if (--indeg[v] == 0) q.push(v);
    }
}
```

## 高频易错点
- 入队后没立刻标记 visited，导致重复入队
- 网格题越界判断漏掉一个方向
- 拓扑排序只写 BFS，不判断是否处理了全部节点（漏环检测）
- 并查集只写 `union`，忘了路径压缩影响性能

## 面试口述模板（30 秒）
- “我先把问题抽象成图，节点是 `...`，边是 `...`。”
- “因为题目求最少步数，选择 BFS 分层扩展，首次到达即最短。”
- “如果是连通性统计，用 DFS/BFS 遍历所有分量。”
- “若存在动态合并需求，使用并查集把单次操作降到近 O(1)。”

## 推荐刷题路径
- 入门：
  LC 200, LC 733, LC 547
- 进阶：
  LC 994, LC 207, LC 417, LC 752
- 综合：
  LC 127, LC 684, LC 210, LC 743

## 对应算法模板
- `core_templates/dfs_template.cpp`
- `core_templates/bfs_template.cpp`
- `core_templates/union_find_template.cpp`
- `interview_ready/dfs_template.cpp`
- `interview_ready/bfs_template.cpp`
- `interview_ready/union_find_template.cpp`
