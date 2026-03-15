/*
LeetCode 131. 分割回文串 (Palindrome Partitioning)

题目概述 (Problem Summary)
-------------------------
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
返回 s 所有可能的分割方案。

回文串是正着读和反着读都一样的字符串。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length <= 16
- s 仅由小写英文字母组成

示例 (Example)
-------------
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

输入：s = "a"
输出：[["a"]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将字符串分割成若干个回文子串，找出所有可能的分割方案

关键观察：
1. 这是一个典型的回溯问题（分割问题）
2. 需要判断子串是否为回文串
3. 可以使用动态规划预处理回文串判断，提高效率
4. 每个位置都可以选择是否进行分割

回溯决策树：
以 s = "aab" 为例：

                        ""
                        |
                       aab
                    /   |   \
                  a|ab  aa|b  aab|
                  /      |      \
                [a]     [aa]    [aab]×
               /  \      |
            a|b  ab|×   b|
            /      \     |
          [a,a]   [a,ab]×[aa,b]
           /
         b|
         |
      [a,a,b]

每个节点代表一个分割点，每条路径代表一种分割方案。
× 表示子串不是回文串，剪枝。

根据这些观察，可以得到几种典型解法：
1. 回溯法 + 动态规划预处理 - 标准解法
2. 回溯法 + 双指针判断 - 简单解法
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 - 回溯法 + 动态规划预处理 (Approach 1: My Original Solution - Backtracking with DP Preprocessing)

核心思想
--------
使用动态规划预处理所有子串的回文性质，
然后使用回溯法遍历所有可能的分割方案。

算法流程：
1. 预处理：使用动态规划计算 dp[i][j]，表示 s[i...j] 是否为回文串
   - 状态转移方程：
     - 如果 s[i] == s[j]：
       - 如果 j - i <= 1：dp[i][j] = true（单字符或两个相同字符）
       - 否则：dp[i][j] = dp[i+1][j-1]（取决于内部子串）
     - 否则：dp[i][j] = false
   - 遍历顺序：从后往前，从左往右

2. 回溯：从起始位置开始分割
   - 尝试所有可能的分割点
   - 如果当前子串是回文串，加入路径并继续递归
   - 当到达字符串末尾时，将当前路径加入结果
   - 回溯：移除刚加入的子串

为什么使用动态规划预处理？
- 避免重复计算子串的回文性质
- 时间复杂度从 O(n) 降低到 O(1)

为什么使用回溯？
- 需要遍历所有可能的分割方案
- 可以通过剪枝提前排除非回文子串

复杂度分析
---------
时间复杂度：O(n × 2^n)
- 预处理：O(n^2)
- 回溯：最多有 2^(n-1) 种分割方案（每个间隙可以选择分割或不分割）
- 每个方案需要 O(n) 时间复制字符串

空间复杂度：O(n^2)
- dp 数组：O(n^2)
- 递归调用栈：O(n)
- 不计算结果数组的空间

其中：
n = s.length
*/
class Solution {
public:
    vector<vector<string>> ans;  // 存储所有分割方案
    vector<string> path;         // 当前路径（正在构建的分割方案）
    vector<vector<bool>> dp;     // dp[i][j] 表示 s[i...j] 是否为回文串

    // 预处理：使用动态规划计算所有子串的回文性质
    void isPalindrome(string s){
        int n = s.length();

        // 从后往前遍历起始位置
        for (int i = n - 1; i >= 0; i--){
            // 从左往右遍历结束位置
            for (int j = i; j < n; j++){
                // 如果首尾字符相同
                if(s[i] == s[j]){
                    // 如果长度 <= 2，直接判定为回文串
                    if(j - i <= 1){
                        dp[i][j] = true;
                    }
                    // 否则，取决于内部子串是否为回文串
                    else{
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                // 首尾字符不同，不是回文串
                // else { dp[i][j] = false; } // 默认为 false，可省略
            }
        }
    }

    // 回溯函数
    // s: 输入字符串
    // start: 当前搜索的起始位置
    void backtrack(string s, int start){
        // 递归终止条件：已经处理完整个字符串
        if(start == s.size()){
            ans.push_back(path);  // 将当前分割方案加入结果
            return;
        }

        // 尝试所有可能的分割点
        for (int i = start; i < s.size(); i++){
            // 剪枝：如果 s[start...i] 不是回文串，跳过
            if(!dp[start][i]){
                continue;
            }

            // 做选择：将回文子串加入路径
            path.push_back(s.substr(start, i - start + 1));

            // 递归：处理剩余部分
            backtrack(s, i + 1);

            // 撤销选择：回溯，移除刚加入的子串
            path.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        int n = s.size();

        // 初始化 dp 数组
        dp.assign(n, vector<bool>(n, false));

        // 预处理：计算所有子串的回文性质
        isPalindrome(s);

        // 从位置 0 开始回溯
        backtrack(s, 0);

        return ans;
    }
};

/*
方法二：回溯法 + 双指针判断 (Approach 2: Backtracking with Two Pointers)

核心思想
--------
不使用动态规划预处理，而是在回溯过程中使用双指针判断回文串。

算法流程：
与方法一类似，但在需要判断回文串时，使用双指针从两端向中间检查。

复杂度分析
---------
时间复杂度：O(n × 2^n)
- 回溯：O(2^n)
- 每次判断回文串：O(n)
- 总体：O(n × 2^n)

空间复杂度：O(n)
- 递归调用栈：O(n)
- 不需要 dp 数组

其中：
n = s.length

优缺点对比：
- 优点：空间效率高，不需要预处理
- 缺点：重复计算回文串判断，时间效率低
*/
class Solution_TwoPointers {
public:
    vector<vector<string>> ans;
    vector<string> path;

    // 双指针判断回文串
    bool isPalindrome(string& s, int left, int right){
        while(left < right){
            if(s[left] != s[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    void backtrack(string& s, int start){
        if(start == s.size()){
            ans.push_back(path);
            return;
        }

        for (int i = start; i < s.size(); i++){
            // 判断 s[start...i] 是否为回文串
            if(!isPalindrome(s, start, i)){
                continue;
            }

            path.push_back(s.substr(start, i - start + 1));
            backtrack(s, i + 1);
            path.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        backtrack(s, 0);
        return ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：s = "aab"

预处理（动态规划）：

dp 数组（s[i...j] 是否为回文串）：
     0   1   2
   +---+---+---+
0  | T | T | F |  s[0...0]="a"✓, s[0...1]="aa"✓, s[0...2]="aab"×
   +---+---+---+
1  |   | T | F |  s[1...1]="a"✓, s[1...2]="ab"×
   +---+---+---+
2  |   |   | T |  s[2...2]="b"✓
   +---+---+---+

计算过程：
- i=2, j=2: s[2]='b', j-i=0<=1 → dp[2][2]=true
- i=1, j=1: s[1]='a', j-i=0<=1 → dp[1][1]=true
- i=1, j=2: s[1]='a', s[2]='b', s[1]≠s[2] → dp[1][2]=false
- i=0, j=0: s[0]='a', j-i=0<=1 → dp[0][0]=true
- i=0, j=1: s[0]='a', s[1]='a', s[0]=s[1], j-i=1<=1 → dp[0][1]=true
- i=0, j=2: s[0]='a', s[2]='b', s[0]≠s[2] → dp[0][2]=false

回溯过程：

初始：path = [], start = 0

1. i = 0：s[0...0] = "a"，dp[0][0] = true ✓
   - path = ["a"], start = 1
   1.1 i = 1：s[1...1] = "a"，dp[1][1] = true ✓
       - path = ["a", "a"], start = 2
       1.1.1 i = 2：s[2...2] = "b"，dp[2][2] = true ✓
             - path = ["a", "a", "b"], start = 3
             - start == s.size()，加入结果：[["a","a","b"]]
             - 回溯：path = ["a", "a"]
       1.1.2 回溯：path = ["a"]
   1.2 i = 2：s[1...2] = "ab"，dp[1][2] = false ×
       - 跳过
   1.3 回溯：path = []

2. i = 1：s[0...1] = "aa"，dp[0][1] = true ✓
   - path = ["aa"], start = 2
   2.1 i = 2：s[2...2] = "b"，dp[2][2] = true ✓
       - path = ["aa", "b"], start = 3
       - start == s.size()，加入结果：[["a","a","b"], ["aa","b"]]
       - 回溯：path = ["aa"]
   2.2 回溯：path = []

3. i = 2：s[0...2] = "aab"，dp[0][2] = false ×
   - 跳过

最终结果：[["a","a","b"], ["aa","b"]]
*/

/*
回溯模板 (Backtracking Template)
-------------------------------
分割回文串是回溯算法的经典应用，特点是需要判断子串的有效性。

标准回溯模板：

void backtrack(参数) {
    if (终止条件) {
        收集结果;
        return;
    }

    for (选择 : 选择列表) {
        if (剪枝条件) continue;
        做选择;
        backtrack(参数);
        撤销选择;
    }
}

本题的具体应用：
- 终止条件：start == s.size()
- 选择列表：所有可能的分割点 [start, i]
- 剪枝条件：!dp[start][i]（子串不是回文串）
- 做选择：path.push_back(s.substr(start, i - start + 1))
- 撤销选择：path.pop_back()

关键点：
1. 使用动态规划预处理回文串判断
2. 使用 start 参数表示当前搜索的起始位置
3. 使用 substr 提取子串
4. 剪枝：跳过非回文子串
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：回溯法 + 动态规划预处理
- 时间复杂度：O(n^2 + n × 2^n)
- 空间复杂度：O(n^2)
- 优点：回文串判断 O(1)，效率高
- 缺点：需要额外空间存储 dp 数组

方法二：回溯法 + 双指针判断
- 时间复杂度：O(n × 2^n)
- 空间复杂度：O(n)
- 优点：空间效率高
- 缺点：重复计算回文串判断

推荐使用方法一，因为：
1. 时间效率更高（避免重复计算）
2. 空间复杂度可接受（n <= 16）
3. 代码结构更清晰
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单个字符：s = "a"
   - 返回 [["a"]]

2. 全部相同字符：s = "aaa"
   - 返回 [["a","a","a"], ["a","aa"], ["aa","a"], ["aaa"]]

3. 无回文子串（除单字符）：s = "abc"
   - 返回 [["a","b","c"]]

4. 整个字符串是回文串：s = "aba"
   - 返回 [["a","b","a"], ["aba"]]

5. 最大长度：s.length = 16
   - 最多 2^15 = 32768 种分割方案
*/

/*
动态规划详解 (DP Explanation)
-----------------------------
为什么使用动态规划预处理？

1. 问题：判断 s[i...j] 是否为回文串
2. 状态定义：dp[i][j] = s[i...j] 是否为回文串
3. 状态转移：
   - 如果 s[i] == s[j]：
     - 如果 j - i <= 1：dp[i][j] = true
     - 否则：dp[i][j] = dp[i+1][j-1]
   - 否则：dp[i][j] = false

4. 遍历顺序：
   - i 从后往前（因为 dp[i][j] 依赖 dp[i+1][j-1]）
   - j 从左往右

5. 初始化：dp[i][j] = false

示例：s = "aab"

i=2, j=2: s[2]='b', j-i=0 → dp[2][2]=true
i=1, j=1: s[1]='a', j-i=0 → dp[1][1]=true
i=1, j=2: s[1]='a'≠s[2]='b' → dp[1][2]=false
i=0, j=0: s[0]='a', j-i=0 → dp[0][0]=true
i=0, j=1: s[0]='a'=s[1]='a', j-i=1 → dp[0][1]=true
i=0, j=2: s[0]='a'≠s[2]='b' → dp[0][2]=false

最终 dp 数组：
     0   1   2
   +---+---+---+
0  | T | T | F |
   +---+---+---+
1  |   | T | F |
   +---+---+---+
2  |   |   | T |
   +---+---+---+
*/

/*
优化技巧 (Optimization Techniques)
---------------------------------
1. 动态规划预处理：
   - 避免重复计算回文串判断
   - 效果：时间复杂度从 O(n) 降低到 O(1)

2. 剪枝：
   - 跳过非回文子串
   - 效果：减少无效搜索

3. 使用 substr：
   - 直接提取子串，避免手动拼接
   - 效果：代码更简洁

4. 使用 emplace_back：
   - 避免不必要的拷贝
   - 效果：性能提升

5. 提前终止：
   - 如果 s.length == 1，直接返回 [[s]]
   - 效果：避免无效计算
*/

/*
相关问题 (Related Problems)
--------------------------
1. 分割回文串 II（LeetCode 132）：
   - 求最少分割次数
   - 使用动态规划

2. 最长回文子串（LeetCode 5）：
   - 求最长的回文子串
   - 使用动态规划或中心扩展

3. 回文子串（LeetCode 647）：
   - 统计回文子串的数量
   - 使用动态规划或中心扩展

4. 验证回文串（LeetCode 125）：
   - 判断字符串是否为回文串
   - 使用双指针
*/

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    string s1 = "aab";
    vector<vector<string>> result1 = solution.partition(s1);
    cout << "测试用例 1 (s = \"aab\"):" << endl;
    for(const auto& partition : result1) {
        cout << "[";
        for(int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if(i < partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[\"a\",\"a\",\"b\"],[\"aa\",\"b\"]])" << endl;

    // 测试用例 2：单个字符
    string s2 = "a";
    vector<vector<string>> result2 = solution.partition(s2);
    cout << "\n测试用例 2 (s = \"a\"):" << endl;
    for(const auto& partition : result2) {
        cout << "[";
        for(int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if(i < partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[\"a\"]])" << endl;

    // 测试用例 3：全部相同字符
    string s3 = "aaa";
    vector<vector<string>> result3 = solution.partition(s3);
    cout << "\n测试用例 3 (s = \"aaa\"):" << endl;
    for(const auto& partition : result3) {
        cout << "[";
        for(int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if(i < partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[\"a\",\"a\",\"a\"],[\"a\",\"aa\"],[\"aa\",\"a\"],[\"aaa\"]])" << endl;

    // 测试用例 4：整个字符串是回文串
    string s4 = "aba";
    vector<vector<string>> result4 = solution.partition(s4);
    cout << "\n测试用例 4 (s = \"aba\"):" << endl;
    for(const auto& partition : result4) {
        cout << "[";
        for(int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if(i < partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n(期望: [[\"a\",\"b\",\"a\"],[\"aba\"]])" << endl;

    return 0;
}
