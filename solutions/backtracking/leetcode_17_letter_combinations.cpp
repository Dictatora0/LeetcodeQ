/*
LeetCode 17. 电话号码的字母组合 (Letter Combinations of a Phone Number)

题目概述 (Problem Summary)
-------------------------
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按任意顺序返回。

数字到字母的映射（与电话按键相同）：
2: abc
3: def
4: ghi
5: jkl
6: mno
7: pqrs
8: tuv
9: wxyz

关键约束 (Key Constraints)
-------------------------
- 0 <= digits.length <= 4
- digits[i] 是范围 ['2', '9'] 的一个数字

示例 (Example)
-------------
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

输入：digits = ""
输出：[]

输入：digits = "2"
输出：["a","b","c"]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 从多个集合中各选一个元素进行组合，求所有可能的组合

关键观察：
1. 这是一个典型的回溯问题
2. 每个数字对应一组字母，需要从每组中选择一个
3. 选择的顺序是固定的（按照输入数字的顺序）
4. 需要遍历所有可能的组合

回溯决策树：
以 digits = "23" 为例：

                    ""
          /         |         \
        a           b           c
      / | \       / | \       / | \
    ad ae af    bd be bf    cd ce cf

每一层代表一个数字，每个分支代表该数字对应的一个字母。

根据这些观察，可以得到几种典型解法：
1. 回溯法 - 标准解法
2. 迭代法 - 使用队列逐层构建
3. 递归法 - 不使用全局变量
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/*
方法一：我的原始解法 - 回溯法 (Approach 1: My Original Solution - Backtracking)

核心思想
--------
使用回溯法遍历所有可能的字母组合。
维护一个当前路径 path，每次选择一个字母加入路径，
当路径长度等于输入数字长度时，将路径加入结果集。

算法流程：
1. 建立数字到字母的映射表
2. 从第一个数字开始回溯
3. 对于当前数字，遍历其对应的所有字母：
   a. 将字母加入路径
   b. 递归处理下一个数字
   c. 回溯：移除刚加入的字母
4. 当处理完所有数字时，将当前路径加入结果

为什么使用回溯？
- 需要遍历所有可能的组合
- 每个位置的选择相互独立
- 可以通过递归自然地表达"选择-递归-撤销"的过程

复杂度分析
---------
时间复杂度：O(3^m × 4^n)
- m 是对应 3 个字母的数字个数（2,3,4,5,6,8）
- n 是对应 4 个字母的数字个数（7,9）
- 每个组合需要 O(digits.length) 时间构建

空间复杂度：O(digits.length)
- 递归调用栈的深度
- 不计算结果数组的空间

其中：
digits.length = 输入数字的长度
*/
class Solution {
public:
    vector<string> ans;      // 存储所有结果
    string path;             // 当前路径（正在构建的组合）

    // 数字到字母的映射表
    string map[10] = {
        "",      // 0
        "",      // 1
        "abc",   // 2
        "def",   // 3
        "ghi",   // 4
        "jkl",   // 5
        "mno",   // 6
        "pqrs",  // 7
        "tuv",   // 8
        "wxyz",  // 9
    };

    // 回溯函数
    // digits: 输入的数字字符串
    // index: 当前处理到第几个数字
    void backtrack(string& digits, int index){
        // 递归终止条件：已经处理完所有数字
        if(index == digits.size()){
            ans.push_back(path);  // 将当前路径加入结果
            return;  // 要记得返回
        }

        // 获取当前数字对应的字母集合
        int digit = digits[index] - '0';  // 字符转数字

        // 遍历当前数字对应的所有字母
        for(char c : map[digit]){
            path += c;                      // 选择：将字母加入路径
            backtrack(digits, index + 1);   // 递归：处理下一个数字
            path.pop_back();                // 撤销：回溯，移除刚加入的字母
        }
    }

    vector<string> letterCombinations(string digits){
        // 边界情况：空字符串
        if(digits.empty()) return {};

        // 从第一个数字开始回溯
        backtrack(digits, 0);

        return ans;
    }
};

/*
方法二：迭代法 - 使用队列 (Approach 2: Iterative - Using Queue)

核心思想
--------
使用队列逐层构建组合。
初始时队列中只有空字符串，每次处理一个数字时，
将队列中的每个字符串与该数字对应的每个字母组合，生成新的字符串。

算法流程：
1. 初始化队列，加入空字符串
2. 对于每个数字：
   a. 获取当前队列的大小（当前层的节点数）
   b. 处理当前层的所有节点：
      - 取出队首字符串
      - 将其与当前数字对应的每个字母组合
      - 将新字符串加入队列
3. 最终队列中的所有字符串即为结果

复杂度分析
---------
时间复杂度：O(3^m × 4^n)
- 与回溯法相同

空间复杂度：O(3^m × 4^n)
- 队列中最多存储所有可能的组合

其中：
m = 对应 3 个字母的数字个数
n = 对应 4 个字母的数字个数
*/
class Solution_Iterative {
public:
    string map[10] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};

        queue<string> q;
        q.push("");  // 初始化：空字符串

        // 逐个处理每个数字
        for(char d : digits){
            int digit = d - '0';
            int size = q.size();  // 当前层的节点数

            // 处理当前层的所有节点
            for(int i = 0; i < size; i++){
                string curr = q.front();
                q.pop();

                // 将当前字符串与该数字对应的每个字母组合
                for(char c : map[digit]){
                    q.push(curr + c);
                }
            }
        }

        // 将队列转换为 vector
        vector<string> result;
        while(!q.empty()){
            result.push_back(q.front());
            q.pop();
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：digits = "23"

回溯决策树：

                    ""
          /         |         \
        a           b           c
      / | \       / | \       / | \
    ad ae af    bd be bf    cd ce cf

执行过程：

1. index = 0, digit = 2, map[2] = "abc"
   - 选择 'a': path = "a"
     - index = 1, digit = 3, map[3] = "def"
       - 选择 'd': path = "ad" → 加入结果
       - 选择 'e': path = "ae" → 加入结果
       - 选择 'f': path = "af" → 加入结果
   - 选择 'b': path = "b"
     - index = 1, digit = 3, map[3] = "def"
       - 选择 'd': path = "bd" → 加入结果
       - 选择 'e': path = "be" → 加入结果
       - 选择 'f': path = "bf" → 加入结果
   - 选择 'c': path = "c"
     - index = 1, digit = 3, map[3] = "def"
       - 选择 'd': path = "cd" → 加入结果
       - 选择 'e': path = "ce" → 加入结果
       - 选择 'f': path = "cf" → 加入结果

最终结果：["ad","ae","af","bd","be","bf","cd","ce","cf"]
*/

/*
回溯模板 (Backtracking Template)
-------------------------------
电话号码字母组合是回溯算法的经典应用。

标准回溯模板：

void backtrack(参数) {
    if (终止条件) {
        收集结果;
        return;
    }

    for (选择 : 选择列表) {
        做选择;
        backtrack(参数);
        撤销选择;
    }
}

本题的具体应用：
- 终止条件：index == digits.size()
- 选择列表：当前数字对应的字母集合
- 做选择：path += c
- 撤销选择：path.pop_back()

关键点：
1. 不需要 used 数组（因为不是排列问题，每个位置的选择独立）
2. 不需要剪枝（所有组合都是有效的）
3. 路径长度固定（等于输入数字的长度）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：回溯法
- 时间复杂度：O(3^m × 4^n)
- 空间复杂度：O(digits.length) - 递归栈
- 优点：代码简洁，易于理解
- 缺点：递归调用有额外开销

方法二：迭代法
- 时间复杂度：O(3^m × 4^n)
- 空间复杂度：O(3^m × 4^n) - 队列空间
- 优点：避免递归，更直观
- 缺点：空间占用较大

两种方法时间复杂度相同，回溯法空间效率更高。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：digits = ""
   - 返回空数组 []

2. 单个数字：digits = "2"
   - 返回 ["a", "b", "c"]

3. 包含 7 或 9：digits = "79"
   - 7 对应 4 个字母，9 对应 4 个字母
   - 总共 4 × 4 = 16 种组合

4. 最长输入：digits = "2345"
   - 3 × 3 × 3 × 3 = 81 种组合
*/

int main() {
    Solution solution;

    // 测试用例 1：两个数字
    string digits1 = "23";
    vector<string> result1 = solution.letterCombinations(digits1);
    cout << "测试用例 1 (digits = \"23\"): ";
    for(const string& s : result1) {
        cout << s << " ";
    }
    cout << "\n(期望: ad ae af bd be bf cd ce cf)" << endl;

    // 测试用例 2：空字符串
    string digits2 = "";
    vector<string> result2 = solution.letterCombinations(digits2);
    cout << "\n测试用例 2 (digits = \"\"): ";
    if(result2.empty()) {
        cout << "[]";
    }
    cout << "\n(期望: [])" << endl;

    // 测试用例 3：单个数字
    string digits3 = "2";
    vector<string> result3 = solution.letterCombinations(digits3);
    cout << "\n测试用例 3 (digits = \"2\"): ";
    for(const string& s : result3) {
        cout << s << " ";
    }
    cout << "\n(期望: a b c)" << endl;

    // 测试用例 4：包含 7 和 9
    string digits4 = "79";
    vector<string> result4 = solution.letterCombinations(digits4);
    cout << "\n测试用例 4 (digits = \"79\"): ";
    cout << "共 " << result4.size() << " 种组合";
    cout << "\n(期望: 16 种组合)" << endl;

    return 0;
}
