# LeetCode 算法学习仓库

这是一个系统化的 LeetCode 算法学习仓库，包含 C++ 解题代码、详细的中文注释和多种解法对比。

## 📊 学习进度

详细进度统计请参考 [TRANSFORMATION_STATUS.md](TRANSFORMATION_STATUS.md)

## 📁 仓库结构

```
Leetcode/
├── solutions/              # 解题代码（按算法分类）
│   ├── array/             # 数组 (10 题)
│   ├── binary_tree/       # 二叉树 (13 题)
│   ├── dynamic_programming/  # 动态规划 (11 题)
│   ├── linked_list/       # 链表 (6 题)
│   ├── sliding_window/    # 滑动窗口 (6 题)
│   ├── hash_table/        # 哈希表 (5 题)
│   ├── two_pointers/      # 双指针 (1 题)
│   ├── greedy/            # 贪心 (2 题)
│   ├── binary_search/     # 二分查找 (1 题)
│   ├── stack/             # 栈 (2 题)
│   ├── graph/             # 图 (3 题)
│   ├── backtracking/      # 回溯 (1 题)
│   ├── trie/              # Trie (1 题)
│   └── cpp/               # 原始代码（历史版本，见 cpp/README.md）
├── templates/             # 算法模板库
│   ├── interview_ready/   # 面试级别模板 (10 个算法)
│   ├── INTERVIEW_CHEATSHEET.md  # 面试速查手册
│   └── PATTERN_RECOGNITION_GUIDE.md  # 题型识别指南
├── build/                 # 编译输出（自动生成）
├── scripts/               # 编译运行脚本
│   ├── run_cpp.sh        # 单题编译运行
│   └── compile_all.sh    # 批量编译
├── notes/                 # 个人学习笔记（可选）
├── TRANSFORMATION_STATUS.md  # 详细进度报告
├── COMPLETION_SUMMARY.md     # 最近会话总结
└── README.md             # 本文件
```

## 🚀 使用方法

### 编译单个题目

```bash
# 编译并运行（Release 模式，速度优先）
./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp

# 仅编译不运行
./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp --build-only

# 调试模式（包含调试符号）
MODE=debug ./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp
```

### 批量编译

```bash
# 编译所有题目
./scripts/compile_all.sh

# 编译特定分类
./scripts/compile_all.sh solutions/binary_tree

# Debug 模式批量编译
MODE=debug ./scripts/compile_all.sh
```

## 📚 算法模板库

`templates/` 目录包含面试级别的算法模板，每个模板 500+ 行，包含：

- **核心算法**: 滑动窗口、双指针、DFS/BFS、回溯、二分查找、动态规划等
- **题型识别**: 如何在 30 秒内识别题型
- **面试技巧**: 如何向面试官解释思路
- **真题实战**: 100+ 道 LeetCode 高频题
- **速查手册**: 面试前快速复习

### 使用模板

1. **学习阶段**: 阅读 `templates/interview_ready/` 下的完整模板
2. **面试准备**: 复习 `templates/INTERVIEW_CHEATSHEET.md`
3. **题型识别**: 参考 `templates/PATTERN_RECOGNITION_GUIDE.md`

## 📖 代码特点

每个解题文件都包含：

1. **题目概述** - 用简体中文解释题目要求和关键约束
2. **算法思路** - 详细的思考过程和关键观察
3. **方法一：我的原始解法** - 保留原始代码，添加详细注释
4. **方法二：优化解法** - 如果存在更优解法，作为对比学习
5. **示例推演** - 图示化的执行过程
6. **复杂度对比** - 不同方法的时间空间复杂度分析
7. **特殊情况** - 边界条件和易错点
8. **测试用例** - 可直接运行的测试代码

## 🎯 学习建议

### 学习路径

1. **基础算法** (第 1-2 周)
   - 滑动窗口、双指针、二分查找
   - 参考 `templates/interview_ready/`

2. **搜索算法** (第 3-4 周)
   - DFS、BFS、回溯
   - 重点：树和图的遍历

3. **进阶算法** (第 5-6 周)
   - 动态规划、前缀和、单调栈
   - 重点：状态转移和优化

4. **高级数据结构** (第 7-8 周)
   - 并查集、Trie、LRU Cache
   - 重点：数据结构设计

### 学习方法

1. **先看题目概述**，理解问题要求
2. **阅读算法思路**，理解为什么这样做
3. **对比多种解法**，理解优化过程
4. **手动推演示例**，加深理解
5. **编译运行代码**，验证理解
6. **总结算法模板**，举一反三

## 📝 命名规范

- **源文件**: `leetcode_{题目编号}_{英文简称}.cpp`
  - 例如: `leetcode_437_path_sum_iii.cpp`
- **可执行文件**: 自动生成到 `build/bin/` 或 `build/debug/`
- **多个解法**: 在同一文件中作为不同的类实现

## 🔧 开发环境

- **编译器**: g++ / clang++ (支持 C++17)
- **操作系统**: macOS / Linux / Windows (WSL)
- **IDE**: VSCode / CLion / Vim
- **构建系统**: 自定义 shell 脚本

## 📈 进度追踪

- ✅ **已完成** - 包含完整文档和多种解法
- 📝 **待完善** - 仅有基础实现，需添加文档
- 🚧 **进行中** - 正在编写文档

详细进度请查看 [TRANSFORMATION_STATUS.md](TRANSFORMATION_STATUS.md)

## 📂 目录说明

### solutions/cpp/

历史版本的原始代码，用于版本对比。详见 [solutions/cpp/README.md](solutions/cpp/README.md)

### templates/

算法模板库，包含面试级别的完整模板。详见 [templates/README.md](templates/README.md)

### notes/

个人学习笔记目录（可选）。详见 [notes/README.md](notes/README.md)

## 🤝 贡献

这是个人学习仓库，记录了我的 LeetCode 刷题历程。欢迎参考学习！

## 📄 许可

MIT License

---

**最后更新**: 2026-03-14
**维护状态**: 活跃更新中
