
# 树问题模式指南

## 一眼识别信号（3 秒判断）
- 输入是二叉树 / N 叉树结构
- 关键词出现“遍历、路径、祖先、层序、子树”
- 子问题天然按“当前节点 + 左右子树”拆解

## 常见题型分类
- 遍历与视图：
  前中后序、层序、右视图、锯齿层序
- 路径问题：
  根到叶路径、任意路径最大和、路径计数
- 结构判断：
  对称树、平衡树、同构、子树判断
- 构造与恢复：
  由遍历序列建树、序列化/反序列化
- BST 专题：
  验证 BST、第 k 小、前驱后继、区间裁剪

## 选型速判：DFS 还是 BFS
- 需要层次输出、最短层数、逐层统计：
  BFS
- 需要递归聚合子树信息（高度、路径和、是否平衡）：
  DFS 后序
- 需要记录从根到当前节点路径：
  DFS + 回溯

## DFS 三种写法
- 前序：
  先处理当前节点，再递归子树（适合“构造答案”）
- 中序：
  左-中-右（BST 里常用于有序序列）
- 后序：
  先拿到左右子树结果，再处理当前节点（树形 DP 常用）

## 树题通用模板（递归）
```cpp
int dfs(TreeNode* node) {
    if (!node) return base;

    int L = dfs(node->left);
    int R = dfs(node->right);

    // 用 L、R 计算当前节点答案
    return state;
}
```

## 层序模板（BFS）
```cpp
queue<TreeNode*> q;
q.push(root);
while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
        TreeNode* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}
```

## 高频易错点
- 路径回溯时忘记 `pop_back`
- “根到叶”与“任意节点到任意节点”混淆
- BST 校验只比较父子，没维护全局上下界
- 递归返回值语义不清，导致组合逻辑错误

## 面试口述模板（30 秒）
- “树天然适合递归，我先定义函数返回值表示 `...`。”
- “当前节点答案由左右子树状态合并得到。”
- “如果题目要按层输出，我切换到 BFS，按 `size` 分层处理。”
- “整体时间 O(n)，递归栈空间 O(h)。”

## 推荐刷题路径
- 入门：
  LC 94, LC 104, LC 226, LC 102
- 进阶：
  LC 236, LC 230, LC 437, LC 199
- 综合：
  LC 124, LC 297, LC 98, LC 543

## 对应算法模板
- `core_templates/dfs_template.cpp`
- `core_templates/bfs_template.cpp`
- `interview_ready/dfs_template.cpp`
- `interview_ready/bfs_template.cpp`
