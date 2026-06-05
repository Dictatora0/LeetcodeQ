# 11 - DFS 与 BFS

这一目录保留短期笔试最常见的搜索基础题，包括网格搜索和入门状态图 BFS。

## 建议阅读顺序

1. `queue_basic_demo.cpp`
2. `dfs_grid_connected_components.cpp`
3. `bfs_grid_shortest_path.cpp`
4. `multi_source_bfs_grid.cpp`
5. `bfs_minimum_operations_state_graph.cpp`
6. `topological_sort_kahn.cpp`
7. `dijkstra_shortest_path.cpp`

## 本目录重点

- BFS 的核心容器是队列
- 网格连通块常用 DFS 或 BFS
- 网格最短路优先考虑 BFS
- 多个起点同时扩散：优先想到多源 BFS
- 不是网格、而是“数字状态 / 操作次数最短”：优先想到状态图 BFS
- “先做谁再做谁”的依赖关系：优先想到拓扑排序
- 带正权的最短路：优先想到 Dijkstra
