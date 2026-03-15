/*
LeetCode 79. 单词搜索 (Word Search)

题目概述 (Problem Summary)
-------------------------
给定一个 m x n 二维字符网格 board 和一个字符串单词 word。
如果 word 存在于网格中，返回 true；否则，返回 false。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中"相邻"单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

关键约束 (Key Constraints)
-------------------------
- m == board.length
- n == board[i].length
- 1 <= m, n <= 6
- 1 <= word.length <= 15
- board 和 word 仅由大小写英文字母组成

示例 (Example)
-------------
输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]],
     word = "ABCCED"
输出：true

输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]],
     word = "SEE"
输出：true

输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]],
     word = "ABCB"
输出：false

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在二维网格中搜索一条路径，使得路径上的字符按顺序组成目标单词

关键观察：
1. 这是一个典型的回溯问题（路径搜索）
2. 需要从每个可能的起点开始尝试
3. 每个位置有四个方向可以探索（上下左右）
4. 需要标记已访问的单元格，避免重复使用
5. 回溯时需要恢复单元格状态

回溯决策树：
以 board = [["A","B"],["C","D"]], word = "ABCD" 为例：

从 (0,0) 'A' 开始：
                    A(0,0) ✓
                /    |    \    \
              B(0,1)✓ C(1,0) ...
             /  |  \  \
           A  C(1,1)✓ ...
              /  |  \  \
            D(1,1)✓ ...

找到完整路径：A(0,0) → B(0,1) → C(1,1) → D(1,0)

每个节点的选择：
- 向上、向下、向左、向右移动
- 必须满足：在边界内、字符匹配、未被访问

根据这些观察，可以得到几种典型解法：
1. DFS + 回溯 - 标准解法
2. DFS + 标记数组 - 使用额外空间
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
方法一：我的原始解法 - DFS + 回溯 (Approach 1: My Original Solution - DFS with Backtracking)

核心思想
--------
使用深度优先搜索（DFS）在网格中搜索单词。
从每个可能的起点开始，尝试向四个方向扩展。
使用原地标记避免重复访问（将访问过的字符临时改为 '#'）。

算法流程：
1. 遍历网格的每个位置作为起点
2. 对于每个起点，调用 DFS：
   a. 检查边界条件和字符匹配
   b. 如果匹配到单词的最后一个字符，返回 true
   c. 标记当前位置为已访问（改为 '#'）
   d. 向四个方向递归搜索
   e. 回溯：恢复当前位置的字符
3. 如果任何起点找到完整路径，返回 true
4. 否则返回 false

为什么使用 DFS + 回溯？
- 需要探索所有可能的路径
- 路径有方向性（上下左右）
- 需要标记和恢复状态

关键技巧：
1. 原地标记：将访问过的字符改为 '#'，避免使用额外空间
2. 提前终止：找到完整路径后立即返回
3. 边界检查：在递归前检查所有条件

复杂度分析
---------
时间复杂度：O(m × n × 3^L)
- m × n：遍历所有起点
- 3^L：每个位置最多有 3 个方向可以探索（除了来的方向）
- L：单词长度

空间复杂度：O(L)
- 递归调用栈的深度为单词长度
- 原地标记，不使用额外空间

其中：
m = board.length
n = board[0].length
L = word.length
*/
class Solution {
public:
    int row, col;  // 网格的行数和列数

    // DFS 函数
    // board: 字符网格
    // word: 目标单词
    // i, j: 当前位置
    // k: 当前匹配到单词的第 k 个字符
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int k) {
        // 边界检查：超出网格范围
        if (i < 0 || i >= row || j < 0 || j >= col) {
            return false;
        }

        // 字符不匹配
        if (board[i][j] != word[k]) {
            return false;
        }

        // 递归终止条件：已经匹配到单词的最后一个字符
        if (k == word.size() - 1) {
            return true;
        }

        // 标记当前位置为已访问
        char ch = board[i][j];
        board[i][j] = '#';  // 使用特殊字符标记

        // 向四个方向递归搜索
        // 只要有一个方向找到完整路径，就返回 true
        bool find = dfs(board, word, i + 1, j, k + 1) ||  // 向下
                    dfs(board, word, i, j + 1, k + 1) ||  // 向右
                    dfs(board, word, i - 1, j, k + 1) ||  // 向上
                    dfs(board, word, i, j - 1, k + 1);    // 向左

        // 回溯：恢复当前位置的字符
        board[i][j] = ch;

        return find;
    }

    bool exist(vector<vector<char>>& board, string word) {
        row = board.size();
        col = board[0].size();

        // 遍历网格的每个位置作为起点
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // 从当前位置开始搜索
                if (dfs(board, word, i, j, 0)) {
                    return true;  // 找到完整路径
                }
            }
        }

        return false;  // 所有起点都没有找到完整路径
    }
};

/*
方法二：DFS + 标记数组 (Approach 2: DFS with Visited Array)

核心思想
--------
使用额外的 visited 数组标记已访问的单元格，
而不是修改原始网格。

算法流程：
与方法一类似，但使用 visited[i][j] 标记访问状态。

复杂度分析
---------
时间复杂度：O(m × n × 3^L)
- 与方法一相同

空间复杂度：O(m × n + L)
- visited 数组：O(m × n)
- 递归调用栈：O(L)

其中：
m = board.length
n = board[0].length
L = word.length

优缺点对比：
- 优点：不修改原始数据
- 缺点：需要额外空间
*/
class Solution_Visited {
public:
    int row, col;
    vector<vector<bool>> visited;

    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int k) {
        // 边界检查
        if (i < 0 || i >= row || j < 0 || j >= col) {
            return false;
        }

        // 已访问或字符不匹配
        if (visited[i][j] || board[i][j] != word[k]) {
            return false;
        }

        // 找到完整路径
        if (k == word.size() - 1) {
            return true;
        }

        // 标记为已访问
        visited[i][j] = true;

        // 向四个方向递归搜索
        bool find = dfs(board, word, i + 1, j, k + 1) ||
                    dfs(board, word, i, j + 1, k + 1) ||
                    dfs(board, word, i - 1, j, k + 1) ||
                    dfs(board, word, i, j - 1, k + 1);

        // 回溯：取消标记
        visited[i][j] = false;

        return find;
    }

    bool exist(vector<vector<char>>& board, string word) {
        row = board.size();
        col = board[0].size();
        visited.assign(row, vector<bool>(col, false));

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]],
     word = "ABCCED"

网格索引：
     0   1   2   3
0   A   B   C   E
1   S   F   C   S
2   A   D   E   E

搜索过程：

1. 从 (0,0) 'A' 开始：
   - 匹配 word[0] = 'A' ✓
   - 标记 (0,0) 为 '#'
   - 向四个方向搜索 word[1] = 'B'

2. 向右 (0,1) 'B'：
   - 匹配 word[1] = 'B' ✓
   - 标记 (0,1) 为 '#'
   - 向四个方向搜索 word[2] = 'C'

3. 向右 (0,2) 'C'：
   - 匹配 word[2] = 'C' ✓
   - 标记 (0,2) 为 '#'
   - 向四个方向搜索 word[3] = 'C'

4. 向下 (1,2) 'C'：
   - 匹配 word[3] = 'C' ✓
   - 标记 (1,2) 为 '#'
   - 向四个方向搜索 word[4] = 'E'

5. 向下 (2,2) 'E'：
   - 匹配 word[4] = 'E' ✓
   - 标记 (2,2) 为 '#'
   - 向四个方向搜索 word[5] = 'D'

6. 向左 (2,1) 'D'：
   - 匹配 word[5] = 'D' ✓
   - k = 5 = word.size() - 1，找到完整路径！
   - 返回 true

路径：A(0,0) → B(0,1) → C(0,2) → C(1,2) → E(2,2) → D(2,1)

网格状态变化：

初始：
A B C E
S F C S
A D E E

标记 A(0,0)：
# B C E
S F C S
A D E E

标记 B(0,1)：
# # C E
S F C S
A D E E

标记 C(0,2)：
# # # E
S F C S
A D E E

标记 C(1,2)：
# # # E
S F # S
A D E E

标记 E(2,2)：
# # # E
S F # S
A D # E

标记 D(2,1)：
# # # E
S F # S
A # # E

找到完整路径，返回 true！
*/

/*
回溯模板 (Backtracking Template)
-------------------------------
单词搜索是回溯算法在二维网格中的经典应用。

标准回溯模板：

bool dfs(参数) {
    if (边界条件) {
        return false;
    }

    if (终止条件) {
        return true;
    }

    标记当前状态;

    for (方向 : 四个方向) {
        if (dfs(新位置)) {
            return true;
        }
    }

    恢复当前状态;
    return false;
}

本题的具体应用：
- 边界条件：超出网格范围、字符不匹配
- 终止条件：k == word.size() - 1
- 标记状态：board[i][j] = '#'
- 恢复状态：board[i][j] = ch
- 四个方向：上下左右

关键点：
1. 原地标记避免额外空间
2. 回溯时恢复状态
3. 找到解立即返回
4. 从每个可能的起点开始尝试
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：DFS + 原地标记
- 时间复杂度：O(m × n × 3^L)
- 空间复杂度：O(L) - 递归栈
- 优点：空间效率高，不需要额外数组
- 缺点：修改原始数据（虽然会恢复）

方法二：DFS + 标记数组
- 时间复杂度：O(m × n × 3^L)
- 空间复杂度：O(m × n + L)
- 优点：不修改原始数据
- 缺点：需要额外空间

推荐使用方法一，因为：
1. 空间效率更高
2. 回溯会恢复原始数据
3. 代码更简洁
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单个字符：word = "A", board = [["A"]]
   - 返回 true

2. 单词不存在：word = "ABCB"
   - 同一个单元格不能重复使用
   - 返回 false

3. 单词长度大于网格大小：word = "ABCDEFGHIJK", board = [["A","B"]]
   - 不可能找到
   - 返回 false

4. 需要回溯的情况：
   - 某条路径走不通，需要回溯尝试其他路径

5. 最大规模：m = n = 6, word.length = 15
   - 需要高效的剪枝
*/

/*
优化技巧 (Optimization Techniques)
---------------------------------
1. 提前终止：
   - 如果 word.length > m × n，直接返回 false
   - 效果：避免无效搜索

2. 字符频率检查：
   - 统计 board 和 word 的字符频率
   - 如果 word 中某个字符的频率大于 board，返回 false
   - 效果：提前剪枝

3. 双向搜索：
   - 从 word 的两端同时搜索
   - 效果：减少搜索深度

4. 优先搜索频率低的字符：
   - 从 word 中频率最低的字符开始搜索
   - 效果：减少起点数量

5. 原地标记：
   - 使用 '#' 标记已访问
   - 效果：避免额外空间
*/

/*
相关问题 (Related Problems)
--------------------------
1. 单词搜索 II（LeetCode 212）：
   - 在网格中搜索多个单词
   - 使用 Trie 树优化

2. 岛屿数量（LeetCode 200）：
   - 二维网格 DFS 的基础问题

3. 太平洋大西洋水流问题（LeetCode 417）：
   - 二维网格 DFS 的变体

4. 被围绕的区域（LeetCode 130）：
   - 二维网格 DFS 的应用
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word1 = "ABCCED";
    bool result1 = solution.exist(board1, word1);
    cout << "测试用例 1 (word = \"ABCCED\"): " << (result1 ? "true" : "false");
    cout << "\n(期望: true)" << endl;

    // 测试用例 2：标准情况
    vector<vector<char>> board2 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word2 = "SEE";
    bool result2 = solution.exist(board2, word2);
    cout << "\n测试用例 2 (word = \"SEE\"): " << (result2 ? "true" : "false");
    cout << "\n(期望: true)" << endl;

    // 测试用例 3：重复使用单元格
    vector<vector<char>> board3 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word3 = "ABCB";
    bool result3 = solution.exist(board3, word3);
    cout << "\n测试用例 3 (word = \"ABCB\"): " << (result3 ? "true" : "false");
    cout << "\n(期望: false - 不能重复使用单元格)" << endl;

    // 测试用例 4：单个字符
    vector<vector<char>> board4 = {{'A'}};
    string word4 = "A";
    bool result4 = solution.exist(board4, word4);
    cout << "\n测试用例 4 (word = \"A\", board = [[\"A\"]]): " << (result4 ? "true" : "false");
    cout << "\n(期望: true)" << endl;

    // 测试用例 5：需要回溯
    vector<vector<char>> board5 = {
        {'A', 'B'},
        {'C', 'D'}
    };
    string word5 = "ABDC";
    bool result5 = solution.exist(board5, word5);
    cout << "\n测试用例 5 (word = \"ABDC\"): " << (result5 ? "true" : "false");
    cout << "\n(期望: false)" << endl;

    return 0;
}
