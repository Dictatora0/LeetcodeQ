/*
LeetCode 32. 最长有效括号 (Longest Valid Parentheses)

题目概述 (Problem Summary)
-------------------------
给定一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。

关键约束 (Key Constraints)
-------------------------
- 0 <= s.length <= 3 * 10^4
- s[i] 为 '(' 或 ')'

示例 (Example)
-------------
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"

输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找出字符串中最长的有效括号匹配子串

关键观察：
1. 有效括号必须满足：每个 '(' 都有对应的 ')' 匹配
2. dp[i] 表示以 s[i] 结尾的最长有效括号长度
3. 只有 s[i] = ')' 时才可能形成有效括号
4. 需要考虑两种情况：
   - s[i-1] = '('：形成 "()" 对
   - s[i-1] = ')'：需要检查更前面的字符

根据这些观察，可以得到三种典型解法：
1. 动态规划
2. 栈
3. 双向扫描
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/*
方法一：动态规划 (Approach 1: Dynamic Programming)

核心思想
--------
使用 dp[i] 表示以 s[i] 结尾的最长有效括号长度。

状态定义：
dp[i] = 以 s[i] 结尾的最长有效括号子串的长度

状态转移方程：
如果 s[i] = '('：dp[i] = 0（左括号不能作为有效括号的结尾）

如果 s[i] = ')'：
  情况1：s[i-1] = '('，形成 "()"
    dp[i] = dp[i-2] + 2

  情况2：s[i-1] = ')'，需要检查 s[i - dp[i-1] - 1]
    如果 s[i - dp[i-1] - 1] = '('，可以匹配
    dp[i] = dp[i-1] + 2 + dp[i - dp[i-1] - 2]

初始状态：
dp[0] = 0

算法流程：
1. 创建 dp 数组，初始化为 0
2. 从 i=1 开始遍历
3. 根据状态转移方程更新 dp[i]
4. 返回 dp 数组中的最大值

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_DP {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if (n < 2) return 0;

        vector<int> dp(n, 0);
        int maxLen = 0;

        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    // 情况1：形成 "()"
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    // 情况2：s[i-1] = ')'，检查更前面的字符
                    dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] >= 2 ? dp[i - dp[i - 1] - 2] : 0);
                }
                maxLen = max(maxLen, dp[i]);
            }
        }

        return maxLen;
    }
};

/*
方法二：栈 (Approach 2: Stack)

核心思想
--------
使用栈来记录括号的索引，栈底保持最后一个未匹配的 ')' 的索引。

算法流程：
1. 初始化栈，压入 -1 作为初始边界
2. 遍历字符串：
   - 遇到 '('：压入索引
   - 遇到 ')'：弹出栈顶
     - 如果栈为空：当前 ')' 无法匹配，压入索引作为新边界
     - 如果栈不为空：计算当前有效长度 i - stack.top()

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Stack {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);  // 作为初始边界
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();  // 尝试匹配一个 '('

                if (st.empty()) {
                    st.push(i);  // 当前 ')' 无法匹配，作为新的边界
                } else {
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};

/*
方法三：双向扫描 (Approach 3: Two-Pass Scan)

优化思路
--------
从左到右扫描一次，从右到左扫描一次，不需要额外空间。

算法流程：
1. 左到右扫描：
   - 记录 left 和 right 计数
   - left == right 时更新最大长度
   - right > left 时重置计数

2. 右到左扫描：
   - 记录 left 和 right 计数
   - left == right 时更新最大长度
   - left > right 时重置计数

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_TwoPass {
public:
    int longestValidParentheses(string s) {
        int left = 0, right = 0, maxLen = 0;

        // 从左到右扫描
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }

            if (left == right) {
                maxLen = max(maxLen, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }

        left = right = 0;

        // 从右到左扫描
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }

            if (left == right) {
                maxLen = max(maxLen, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }

        return maxLen;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
s = "(()"

方法一：动态规划
dp = [0, 0, 0]

i=1, s[1]='(':
  dp[1] = 0

i=2, s[2]=')':
  s[1]='('，形成 "()"
  dp[2] = dp[0] + 2 = 0 + 2 = 2

最终 dp = [0, 0, 2]
答案：2

s = ")()())"

方法一：动态规划
dp = [0, 0, 0, 0, 0, 0]

i=1, s[1]='(':
  dp[1] = 0

i=2, s[2]=')':
  s[1]='('，形成 "()"
  dp[2] = dp[0] + 2 = 2

i=3, s[3]='(':
  dp[3] = 0

i=4, s[4]=')':
  s[3]='('，形成 "()"
  dp[4] = dp[2] + 2 = 2 + 2 = 4

i=5, s[5]=')':
  s[4]=')'，检查 s[5 - dp[4] - 1] = s[0] = ')'
  不匹配，dp[5] = 0

最终 dp = [0, 0, 2, 0, 4, 0]
答案：4

方法二：栈
s = ")()())"
stack = [-1]

i=0, s[0]=')':
  pop() -> stack=[]
  stack为空，push(0) -> stack=[0]

i=1, s[1]='(':
  push(1) -> stack=[0,1]

i=2, s[2]=')':
  pop() -> stack=[0]
  ans = max(0, 2-0) = 2

i=3, s[3]='(':
  push(3) -> stack=[0,3]

i=4, s[4]=')':
  pop() -> stack=[0]
  ans = max(2, 4-0) = 4

i=5, s[5]=')':
  pop() -> stack=[]
  stack为空，push(5) -> stack=[5]

答案：4
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：动态规划
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：直观易理解
- 缺点：需要额外空间

方法二：栈
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：实现简洁
- 缺点：需要栈空间

方法三：双向扫描
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：需要扫描两次
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空字符串：返回 0
2. 只有一个字符：返回 0
3. 全是 '('：返回 0
4. 全是 ')'：返回 0
5. 完全匹配：返回字符串长度
*/

int main() {
    Solution_DP solution_dp;
    Solution_Stack solution_stack;
    Solution_TwoPass solution_two;

    // 测试用例 1
    string s1 = "(()";
    cout << "测试用例 1 - DP输出: " << solution_dp.longestValidParentheses(s1)
         << " (期望: 2)" << endl;
    cout << "测试用例 1 - Stack输出: " << solution_stack.longestValidParentheses(s1)
         << " (期望: 2)" << endl;
    cout << "测试用例 1 - TwoPass输出: " << solution_two.longestValidParentheses(s1)
         << " (期望: 2)" << endl;

    // 测试用例 2
    string s2 = ")()())";
    cout << "测试用例 2 - DP输出: " << solution_dp.longestValidParentheses(s2)
         << " (期望: 4)" << endl;
    cout << "测试用例 2 - Stack输出: " << solution_stack.longestValidParentheses(s2)
         << " (期望: 4)" << endl;
    cout << "测试用例 2 - TwoPass输出: " << solution_two.longestValidParentheses(s2)
         << " (期望: 4)" << endl;

    // 测试用例 3
    string s3 = "";
    cout << "测试用例 3 - DP输出: " << solution_dp.longestValidParentheses(s3)
         << " (期望: 0)" << endl;
    cout << "测试用例 3 - Stack输出: " << solution_stack.longestValidParentheses(s3)
         << " (期望: 0)" << endl;
    cout << "测试用例 3 - TwoPass输出: " << solution_two.longestValidParentheses(s3)
         << " (期望: 0)" << endl;

    return 0;
}

