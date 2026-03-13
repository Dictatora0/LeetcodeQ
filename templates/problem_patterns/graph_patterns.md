
# 图问题模式指南

## 常见题型分类
- 连通性与岛屿问题
- 最短路径（无权图 BFS）
- 拓扑排序（有向无环图）
- 并查集连通

## 模式识别技巧
- 题目包含“连通块/岛屿/分组”考虑 DFS/BFS 或并查集
- “最少步数”通常对应 BFS
- “先后依赖关系”考虑拓扑排序

## 思路要点
- 图遍历一定要 visited
- 无权最短路用 BFS
- 动态连通问题优先并查集

## 经典题目
- 200 Number of Islands
- 207 Course Schedule
- 417 Pacific Atlantic Water Flow
- 684 Redundant Connection
- 743 Network Delay Time

## 对应算法模板
- core_templates/dfs_template.cpp
- core_templates/bfs_template.cpp
- core_templates/union_find_template.cpp
