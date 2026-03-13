# LeetCode 算法学习仓库

这是一个系统化的 LeetCode 算法学习仓库，包含 C++ 解题代码、详细的中文注释和多种解法对比。

## 📊 学习进度

- **总题目数**: 60 题
- **已实现**: 20 题
- **Hot100 进度**: 35 / 100

## 📁 仓库结构

```
Leetcode/
├── solutions/              # 解题代码（按算法分类）
│   ├── array/             # 数组相关题目
│   ├── binary_tree/       # 二叉树相关题目
│   ├── dynamic_programming/  # 动态规划题目
│   ├── linked_list/       # 链表相关题目
│   ├── sliding_window/    # 滑动窗口题目
│   ├── hash_table/        # 哈希表题目
│   ├── two_pointers/      # 双指针题目
│   ├── greedy/            # 贪心算法题目
│   ├── binary_search/     # 二分查找题目
│   ├── stack/             # 栈相关题目
│   ├── prefix_sum/        # 前缀和题目
│   └── cpp/               # 原始代码文件（保留）
├── build/                 # 编译输出
│   ├── bin/              # 可执行文件
│   └── debug/            # 调试符号文件
├── scripts/               # 工具脚本
├── notes/                 # 解题笔记
└── README.md             # 项目说明
```

## 🚀 使用方法

### 编译单个题目

```bash
# 编译并运行（Release 模式，速度优先）
./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp

# 仅编译不运行
./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp --build-only

# 调试模式（编译更快、便于调试）
MODE=debug ./scripts/run_cpp.sh solutions/binary_tree/leetcode_437_path_sum_iii.cpp
```

### 批量编译

```bash
./scripts/compile_all.sh
```

## 📚 题目分类

### 二叉树 (Binary Tree) - 13 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 94 | 二叉树的中序遍历 | Easy | ✅ | [leetcode_94_inorder_traversal.cpp](solutions/binary_tree/leetcode_94_inorder_traversal.cpp) |
| 101 | 对称二叉树 | Easy | ✅ | [leetcode_101_symmetric_tree.cpp](solutions/binary_tree/leetcode_101_symmetric_tree.cpp) |
| 102 | 二叉树的层序遍历 | Medium | ✅ | [leetcode_102_level_order.cpp](solutions/binary_tree/leetcode_102_level_order.cpp) |
| 104 | 二叉树的最大深度 | Easy | ✅ | [leetcode_104_max_depth.cpp](solutions/binary_tree/leetcode_104_max_depth.cpp) |
| 105 | 从前序与中序遍历序列构造二叉树 | Medium | ✅ | [leetcode_105_construct_tree.cpp](solutions/binary_tree/leetcode_105_construct_tree.cpp) |
| 108 | 将有序数组转换为二叉搜索树 | Easy | ✅ | [leetcode_108_sorted_array_to_bst.cpp](solutions/binary_tree/leetcode_108_sorted_array_to_bst.cpp) |
| 114 | 二叉树展开为链表 | Medium | ✅ | [leetcode_114_flatten.cpp](solutions/binary_tree/leetcode_114_flatten.cpp) |
| 199 | 二叉树的右视图 | Medium | ✅ | [leetcode_199_right_side_view.cpp](solutions/binary_tree/leetcode_199_right_side_view.cpp) |
| 226 | 翻转二叉树 | Easy | ✅ | [leetcode_226_invert_tree.cpp](solutions/binary_tree/leetcode_226_invert_tree.cpp) |
| 230 | 二叉搜索树中第K小的元素 | Medium | ✅ | [leetcode_230_kth_smallest.cpp](solutions/binary_tree/leetcode_230_kth_smallest.cpp) |
| 437 | 路径总和 III | Medium | ✅ | [leetcode_437_path_sum_iii.cpp](solutions/binary_tree/leetcode_437_path_sum_iii.cpp) |
| 543 | 二叉树的直径 | Easy | 📝 | [leetcode_543_diameter.cpp](solutions/binary_tree/leetcode_543_diameter.cpp) |
| 98 | 验证二叉搜索树 | Medium | ✅ | [leetcode_98_validate_bst.cpp](solutions/binary_tree/leetcode_98_validate_bst.cpp) |

### 链表 (Linked List) - 8 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 19 | 删除链表的倒数第N个结点 | Medium | ✅ | [leetcode_19_remove_nth_from_end.cpp](solutions/linked_list/leetcode_19_remove_nth_from_end.cpp) |
| 24 | 两两交换链表中的节点 | Medium | ✅ | [leetcode_24_swap_pairs.cpp](solutions/linked_list/leetcode_24_swap_pairs.cpp) |
| 25 | K个一组翻转链表 | Hard | ✅ | [leetcode_25_reverse_k_group.cpp](solutions/linked_list/leetcode_25_reverse_k_group.cpp) |
| 71 | 简化路径 | Medium | 📝 | [leetcode_71_simplify_path.cpp](solutions/linked_list/leetcode_71_simplify_path.cpp) |
| 138 | 随机链表的复制 | Medium | ✅ | [leetcode_138_copy_random_list.cpp](solutions/linked_list/leetcode_138_copy_random_list.cpp) |
| 146 | LRU 缓存 | Medium | ✅ | [leetcode_146_lru_cache.cpp](solutions/linked_list/leetcode_146_lru_cache.cpp) |
| 148 | 排序链表 | Medium | ✅ | [leetcode_148_sort_list.cpp](solutions/linked_list/leetcode_148_sort_list.cpp) |
| 380 | O(1)时间插入、删除和获取随机元素 | Medium | 📝 | [leetcode_380_random_set.cpp](solutions/linked_list/leetcode_380_random_set.cpp) |

### 动态规划 (Dynamic Programming) - 11 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 53 | 最大子数组和 | Medium | 📝 | [leetcode_53_max_subarray.cpp](solutions/dynamic_programming/leetcode_53_max_subarray.cpp) |
| 62 | 不同路径 | Medium | 📝 | [leetcode_62_unique_paths.cpp](solutions/dynamic_programming/leetcode_62_unique_paths.cpp) |
| 63 | 不同路径 II | Medium | 📝 | [leetcode_63_unique_paths_ii.cpp](solutions/dynamic_programming/leetcode_63_unique_paths_ii.cpp) |
| 64 | 最小路径和 | Medium | 📝 | [leetcode_64_min_path_sum.cpp](solutions/dynamic_programming/leetcode_64_min_path_sum.cpp) |
| 120 | 三角形最小路径和 | Medium | 📝 | [leetcode_120_triangle.cpp](solutions/dynamic_programming/leetcode_120_triangle.cpp) |
| 198 | 打家劫舍 | Medium | 📝 | [leetcode_198_house_robber.cpp](solutions/dynamic_programming/leetcode_198_house_robber.cpp) |
| 221 | 最大正方形 | Medium | 📝 | [leetcode_221_maximal_square.cpp](solutions/dynamic_programming/leetcode_221_maximal_square.cpp) |
| 509 | 斐波那契数 | Easy | 📝 | [leetcode_509_fibonacci.cpp](solutions/dynamic_programming/leetcode_509_fibonacci.cpp) |
| 746 | 使用最小花费爬楼梯 | Easy | 📝 | [leetcode_746_min_cost_stairs.cpp](solutions/dynamic_programming/leetcode_746_min_cost_stairs.cpp) |
| 931 | 下降路径最小和 | Medium | 📝 | [leetcode_931_min_falling_path.cpp](solutions/dynamic_programming/leetcode_931_min_falling_path.cpp) |
| 1423 | 可获得的最大点数 | Medium | 📝 | [leetcode_1423_max_score.cpp](solutions/dynamic_programming/leetcode_1423_max_score.cpp) |

### 滑动窗口 (Sliding Window) - 6 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 3 | 无重复字符的最长子串 | Medium | 📝 | [leetcode_3_longest_substring.cpp](solutions/sliding_window/leetcode_3_longest_substring.cpp) |
| 76 | 最小覆盖子串 | Hard | 📝 | [leetcode_76_min_window.cpp](solutions/sliding_window/leetcode_76_min_window.cpp) |
| 209 | 长度最小的子数组 | Medium | 📝 | [leetcode_209_min_subarray_len.cpp](solutions/sliding_window/leetcode_209_min_subarray_len.cpp) |
| 239 | 滑动窗口最大值 | Hard | 📝 | [leetcode_239_max_sliding_window.cpp](solutions/sliding_window/leetcode_239_max_sliding_window.cpp) |
| 438 | 找到字符串中所有字母异位词 | Medium | 📝 | [leetcode_438_find_anagrams.cpp](solutions/sliding_window/leetcode_438_find_anagrams.cpp) |
| 1052 | 爱生气的书店老板 | Medium | 📝 | [leetcode_1052_grumpy_bookstore.cpp](solutions/sliding_window/leetcode_1052_grumpy_bookstore.cpp) |

### 数组 (Array) - 9 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 15 | 三数之和 | Medium | 📝 | [leetcode_15_three_sum.cpp](solutions/array/leetcode_15_three_sum.cpp) |
| 27 | 移除元素 | Easy | 📝 | [leetcode_27_remove_element.cpp](solutions/array/leetcode_27_remove_element.cpp) |
| 41 | 缺失的第一个正数 | Hard | 📝 | [leetcode_41_first_missing_positive.cpp](solutions/array/leetcode_41_first_missing_positive.cpp) |
| 48 | 旋转图像 | Medium | ✅ | [leetcode_48_rotate.cpp](solutions/array/leetcode_48_rotate.cpp) |
| 54 | 螺旋矩阵 | Medium | ✅ | [leetcode_54_spiral_matrix.cpp](solutions/array/leetcode_54_spiral_matrix.cpp) |
| 59 | 螺旋矩阵 II | Medium | 📝 | [leetcode_59_spiral_matrix_ii.cpp](solutions/array/leetcode_59_spiral_matrix_ii.cpp) |
| 73 | 矩阵置零 | Medium | ✅ | [leetcode_73_set_zeroes.cpp](solutions/array/leetcode_73_set_zeroes.cpp) |
| 189 | 轮转数组 | Medium | 📝 | [leetcode_189_rotate_array.cpp](solutions/array/leetcode_189_rotate_array.cpp) |
| 283 | 移动零 | Easy | 📝 | [leetcode_283_move_zeroes.cpp](solutions/array/leetcode_283_move_zeroes.cpp) |

### 哈希表 (Hash Table) - 4 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 49 | 字母异位词分组 | Medium | 📝 | [leetcode_49_group_anagrams.cpp](solutions/hash_table/leetcode_49_group_anagrams.cpp) |
| 128 | 最长连续序列 | Medium | 📝 | [leetcode_128_longest_consecutive.cpp](solutions/hash_table/leetcode_128_longest_consecutive.cpp) |
| 238 | 除自身以外数组的乘积 | Medium | 📝 | [leetcode_238_product_except_self.cpp](solutions/hash_table/leetcode_238_product_except_self.cpp) |
| 560 | 和为 K 的子数组 | Medium | 📝 | [leetcode_560_subarray_sum.cpp](solutions/hash_table/leetcode_560_subarray_sum.cpp) |

### 双指针 (Two Pointers) - 2 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 240 | 搜索二维矩阵 II | Medium | ✅ | [leetcode_240_search_matrix.cpp](solutions/two_pointers/leetcode_240_search_matrix.cpp) |
| 977 | 有序数组的平方 | Easy | 📝 | [leetcode_977_sorted_squares.cpp](solutions/two_pointers/leetcode_977_sorted_squares.cpp) |

### 贪心 (Greedy) - 2 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 134 | 加油站 | Medium | 📝 | [leetcode_134_gas_station.cpp](solutions/greedy/leetcode_134_gas_station.cpp) |
| 135 | 分发糖果 | Hard | 📝 | [leetcode_135_candy.cpp](solutions/greedy/leetcode_135_candy.cpp) |

### 栈 (Stack) - 1 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 42 | 接雨水 | Hard | 📝 | [leetcode_42_trap.cpp](solutions/stack/leetcode_42_trap.cpp) |

### 二分查找 (Binary Search) - 1 题

| ID | 题目 | 难度 | 状态 | 文件 |
|----|------|------|------|------|
| 704 | 二分查找 | Easy | 📝 | [leetcode_704_binary_search.cpp](solutions/binary_search/leetcode_704_binary_search.cpp) |

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

1. **按分类学习** - 先掌握一个算法类别，再进入下一个
2. **对比多种解法** - 理解从暴力到优化的思维过程
3. **手动推演** - 在纸上画图模拟算法执行
4. **编译运行** - 使用提供的脚本编译运行，验证理解
5. **总结模板** - 每个类别都有通用的解题模板

## 📝 命名规范

- **源文件**: `leetcode_{题目编号}_{英文简称}.cpp`
  - 例如: `leetcode_437_path_sum_iii.cpp`
- **可执行文件**: `{题目编号}`
  - 例如: `437`
- **多个解法**: `leetcode_{题目编号}_{英文简称}_v{版本}.cpp`
  - 例如: `leetcode_128_longest_consecutive_v2.cpp`

## 🔧 开发环境

- **编译器**: g++ / clang++ (支持 C++11 及以上)
- **操作系统**: macOS / Linux / Windows (WSL)
- **IDE**: VSCode / CLion / Vim

## 📈 进度追踪

- ✅ 已完成并添加详细注释
- 📝 待完善（仅有模板或需要添加注释）
- 🚧 进行中

## 🤝 贡献

这是个人学习仓库，记录了我的 LeetCode 刷题历程。欢迎参考学习！

## 📄 许可

MIT License

---

**最后更新**: 2026-03-13
