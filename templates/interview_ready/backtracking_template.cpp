/*
 * ============================================================================
 * 回溯算法 - 面试必备完整模板
 * Backtracking Algorithm - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 回溯是一种通过探索所有可能的候选解来找出所有解的算法。
 * 如果候选解不符合要求，就"回溯"并尝试其他候选解。
 *
 * 【通俗解释】
 * 想象你在走迷宫：
 * - 选择一条路走
 * - 如果走不通，退回来
 * - 选择另一条路继续
 * - 记录所有能走通的路径
 *
 * 【三要素】
 * 1. 选择：每一步有哪些选择
 * 2. 约束：什么情况下不能选择
 * 3. 目标：什么时候找到解
 *
 * 【与其他算法对比】
 * - vs DFS：回溯是 DFS + 撤销选择
 * - vs 动态规划：回溯暴力搜索，DP 记忆化优化
 * - vs 贪心：回溯找所有解，贪心找一个解
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别回溯题目】
 *
 * ✅ 关键词识别：
 * 1. "所有可能的..." - 90% 是回溯
 * 2. "排列/组合" - 回溯
 * 3. "子集" - 回溯
 * 4. "N皇后" - 回溯
 * 5. "括号生成" - 回溯
 *
 * ✅ 题目特征：
 * - 需要找出所有解
 * - 有明确的选择和约束
 * - 可以用树形结构表示搜索过程
 * - 需要撤销选择
 *
 * ❌ 不适合回溯：
 * - 只需要一个解（用贪心或 DP）
 * - 最优解问题（用 DP）
 * - 数据量太大会超时
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：基础回溯框架
// 时间复杂度：O(n!)
// 空间复杂度：O(n)
// ============================================================================

class BacktrackingTemplate {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& path, /* 其他参数 */) {
        // 1. 终止条件
        if (满足条件) {
            result.push_back(path);
            return;
        }

        // 2. 遍历所有选择
        for (int i = 起点; i < 终点; i++) {
            // 3. 做选择
            path.push_back(选择);

            // 4. 递归
            backtrack(path, /* 更新后的参数 */);

            // 5. 撤销选择（回溯）
            path.pop_back();
        }
    }
};

// ============================================================================
// 模板 2：排列问题（元素不重复）
// 时间复杂度：O(n!)
// 空间复杂度：O(n)
// ============================================================================

class PermutationTemplate {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);

        backtrack(nums, path, used, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, vector<int>& path,
                   vector<bool>& used, vector<vector<int>>& result) {
        // 终止条件：路径长度等于数组长度
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 跳过已使用的元素
            if (used[i]) continue;

            // 做选择
            path.push_back(nums[i]);
            used[i] = true;

            // 递归
            backtrack(nums, path, used, result);

            // 撤销选择
            path.pop_back();
            used[i] = false;
        }
    }
};

// ============================================================================
// 模板 3：组合问题
// 时间复杂度：O(2^n)
// 空间复杂度：O(n)
// ============================================================================

class CombinationTemplate {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;

        backtrack(n, k, 1, path, result);
        return result;
    }

private:
    void backtrack(int n, int k, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        // 终止条件：路径长度等于 k
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        // 剪枝：剩余元素不够了
        for (int i = start; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);
            backtrack(n, k, i + 1, path, result);  // 注意是 i+1
            path.pop_back();
        }
    }
};

// ============================================================================
// 模板 4：子集问题
// 时间复杂度：O(2^n)
// 空间复杂度：O(n)
// ============================================================================

class SubsetTemplate {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;

        backtrack(nums, 0, path, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        // 每个节点都是一个子集
        result.push_back(path);

        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, result);
            path.pop_back();
        }
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：全排列
// LeetCode 46: Permutations
// ============================================================================

class Solution_Permute {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);

        backtrack(nums, path, used, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, vector<int>& path,
                   vector<bool>& used, vector<vector<int>>& result) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;

            path.push_back(nums[i]);
            used[i] = true;

            backtrack(nums, path, used, result);

            path.pop_back();
            used[i] = false;
        }
    }
};

// ============================================================================
// 变体 2：组合总和
// LeetCode 39: Combination Sum
// ============================================================================

class Solution_CombinationSum {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> path;

        backtrack(candidates, target, 0, path, result);
        return result;
    }

private:
    void backtrack(vector<int>& candidates, int target, int start,
                   vector<int>& path, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(path);
            return;
        }

        if (target < 0) return;

        for (int i = start; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            // 可以重复使用，所以还是 i
            backtrack(candidates, target - candidates[i], i, path, result);
            path.pop_back();
        }
    }
};

// ============================================================================
// 变体 3：括号生成
// LeetCode 22: Generate Parentheses
// ============================================================================

class Solution_GenerateParenthesis {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string path;

        backtrack(n, 0, 0, path, result);
        return result;
    }

private:
    void backtrack(int n, int left, int right,
                   string& path, vector<string>& result) {
        // 终止条件
        if (path.size() == 2 * n) {
            result.push_back(path);
            return;
        }

        // 可以添加左括号
        if (left < n) {
            path.push_back('(');
            backtrack(n, left + 1, right, path, result);
            path.pop_back();
        }

        // 可以添加右括号
        if (right < left) {
            path.push_back(')');
            backtrack(n, left, right + 1, path, result);
            path.pop_back();
        }
    }
};

// ============================================================================
// 变体 4：N 皇后
// LeetCode 51: N-Queens
// ============================================================================

class Solution_NQueens {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));

        backtrack(board, 0, result);
        return result;
    }

private:
    void backtrack(vector<string>& board, int row, vector<vector<string>>& result) {
        if (row == board.size()) {
            result.push_back(board);
            return;
        }

        int n = board.size();
        for (int col = 0; col < n; col++) {
            if (!isValid(board, row, col)) continue;

            board[row][col] = 'Q';
            backtrack(board, row + 1, result);
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();

        // 检查列
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // 检查左上对角线
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // 检查右上对角线
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }
};

// ============================================================================
// 变体 5：单词搜索
// LeetCode 79: Word Search
// ============================================================================

class Solution_WordSearch {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    bool backtrack(vector<vector<char>>& board, string& word,
                   int x, int y, int index) {
        if (index == word.size()) return true;

        int m = board.size(), n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n) return false;
        if (board[x][y] != word[index]) return false;

        // 标记已访问
        char temp = board[x][y];
        board[x][y] = '#';

        // 四个方向
        bool found = backtrack(board, word, x-1, y, index+1) ||
                     backtrack(board, word, x+1, y, index+1) ||
                     backtrack(board, word, x, y-1, index+1) ||
                     backtrack(board, word, x, y+1, index+1);

        // 恢复
        board[x][y] = temp;

        return found;
    }
};

/*
 * ============================================================================
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 画出递归树，帮助理解
 * 2. 说明三要素：选择、约束、目标
 * 3. 强调回溯的关键：撤销选择
 *
 * 【易错点】
 * ❌ 忘记撤销选择（回溯）
 * ❌ 终止条件写错
 * ❌ 排列和组合的区别：排列用 used，组合用 start
 * ❌ 忘记剪枝导致超时
 *
 * 【复杂度】
 * 排列：O(n!)
 * 组合/子集：O(2^n)
 * N皇后：O(n!)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 46, LC 39, LC 22
 * ⭐⭐⭐⭐ LC 51, LC 79, LC 78
 *
 * 【速查表】
 * void backtrack(path, 参数) {
 *     if (终止条件) {
 *         result.push_back(path);
 *         return;
 *     }
 *
 *     for (选择 in 选择列表) {
 *         if (不满足约束) continue;
 *         做选择;
 *         backtrack(path, 更新参数);
 *         撤销选择;  // 关键！
 *     }
 * }
 *
 * 【排列 vs 组合 vs 子集】
 * 排列：需要 used 数组，顺序重要
 * 组合：需要 start 参数，顺序不重要
 * 子集：每个节点都是答案
 */

int main() {
    Solution_Permute sol;
    vector<int> nums = {1, 2, 3};
    auto result = sol.permute(nums);

    cout << "全排列结果：" << endl;
    for (auto& perm : result) {
        cout << "[";
        for (int num : perm) cout << num << " ";
        cout << "]" << endl;
    }

    cout << "回溯算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o backtracking backtracking_template.cpp && ./backtracking
 */
