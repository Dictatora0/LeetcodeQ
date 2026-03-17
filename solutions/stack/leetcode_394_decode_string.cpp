/*
LeetCode 394. 字符串解码 (Decode String)

题目概述 (Problem Summary)
-------------------------
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为：k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。
注意 k 保证为正整数。

关键约束 (Key Constraints)
-------------------------
- 1 <= s.length <= 30
- s 由小写英文字母、数字和方括号 '[]' 组成
- s 保证是一个有效的输入
- s 中所有整数的取值范围为 [1, 300]

示例 (Example)
-------------
输入：s = "3[a]2[bc]"
输出："aaabcbc"

输入：s = "3[a2[c]]"
输出："accaccacc"

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 括号嵌套的字符串重复问题

关键观察：
1. 遇到 '[' 时，需要保存当前状态（数字和字符串）
2. 遇到 ']' 时，需要恢复之前的状态并进行重复操作
3. 这是典型的栈应用场景（保存和恢复状态）
4. 需要两个栈：一个存数字，一个存字符串

根据这些观察，可以得到几种典型解法：
1. 双栈法（数字栈 + 字符串栈）
2. 递归法
3. 单栈法（存储状态对）
*/

#include <iostream>
#include <stack>
#include <string>
using namespace std;

/*
方法一：我的原始解法 - 双栈法 (Approach 1: Two Stacks)

核心思想
--------
使用两个栈分别存储数字和字符串。
遇到 '[' 时保存状态，遇到 ']' 时恢复状态并重复。

算法流程：
1. 初始化：数字栈 nums、字符串栈 strSt、当前数字 num、当前字符串 cur
2. 遍历字符串：
   a. 遇到数字：累积到 num（可能是多位数）
   b. 遇到 '['：
      - 将 num 压入数字栈
      - 将 cur 压入字符串栈
      - 重置 num 和 cur
   c. 遇到 ']'：
      - 从数字栈取出重复次数 repeat
      - 从字符串栈取出之前的字符串 prev
      - 将 cur 重复 repeat 次，拼接到 prev 后面
      - 更新 cur = prev + repeated
   d. 遇到字母：累积到 cur
3. 返回 cur

为什么需要两个栈？
- 数字栈：存储每层的重复次数
- 字符串栈：存储每层之前的字符串

复杂度分析
---------
时间复杂度：O(n * k)
- n 是字符串长度
- k 是最大重复次数
- 最坏情况下需要重复拼接字符串

空间复杂度：O(n)
- 栈的空间
- 临时字符串的空间

其中：
n = s.length
k = 最大重复次数
*/
class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;        // 数字栈：存储重复次数
        stack<string> strSt;    // 字符串栈：存储之前的字符串

        int num = 0;            // 当前数字（可能是多位数）
        string cur = "";        // 当前字符串

        for (char c : s) {
            // 遇到数字：累积到 num
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            }
            // 遇到 '['：保存当前状态
            else if (c == '[') {
                nums.push(num);      // 保存重复次数
                strSt.push(cur);     // 保存之前的字符串

                num = 0;             // 重置数字
                cur = "";            // 重置当前字符串
            }
            // 遇到 ']'：恢复状态并重复
            else if (c == ']') {
                int repeat = nums.top();    // 取出重复次数
                nums.pop();

                string prev = strSt.top();  // 取出之前的字符串
                strSt.pop();

                // 将 cur 重复 repeat 次
                string temp = "";
                for (int i = 0; i < repeat; i++) {
                    temp += cur;
                }

                // 拼接到之前的字符串后面
                cur = prev + temp;
            }
            // 遇到字母：累积到 cur
            else {
                cur += c;
            }
        }

        return cur;
    }
};

/*
方法二：递归法 (Approach 2: Recursion)

核心思想
--------
遇到 '[' 时递归处理内部字符串，遇到 ']' 时返回。

算法流程：
1. 使用全局索引 i 遍历字符串
2. 遇到数字：累积到 num
3. 遇到 '['：
   - 递归调用，处理内部字符串
   - 将结果重复 num 次
4. 遇到 ']'：返回当前字符串
5. 遇到字母：累积到结果

复杂度分析
---------
时间复杂度：O(n * k)
空间复杂度：O(n)（递归栈）
*/
class Solution_Recursion {
private:
    int i = 0;  // 全局索引

    string decode(const string& s) {
        string result = "";
        int num = 0;

        while (i < s.length()) {
            char c = s[i];

            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                i++;
            }
            else if (c == '[') {
                i++;  // 跳过 '['
                string sub = decode(s);  // 递归处理内部
                // 重复 num 次
                for (int j = 0; j < num; j++) {
                    result += sub;
                }
                num = 0;  // 重置数字
            }
            else if (c == ']') {
                i++;  // 跳过 ']'
                return result;  // 返回当前层的结果
            }
            else {
                result += c;
                i++;
            }
        }

        return result;
    }

public:
    string decodeString(string s) {
        i = 0;  // 重置索引
        return decode(s);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：s = "3[a2[c]]"

使用方法一（双栈法）：

初始状态：
- nums = []
- strSt = []
- num = 0
- cur = ""

步骤 1：c = '3'
- 是数字，num = 3
- nums = [], strSt = [], num = 3, cur = ""

步骤 2：c = '['
- 遇到 '['，保存状态
- nums.push(3), strSt.push("")
- nums = [3], strSt = [""], num = 0, cur = ""

步骤 3：c = 'a'
- 是字母，cur += 'a'
- nums = [3], strSt = [""], num = 0, cur = "a"

步骤 4：c = '2'
- 是数字，num = 2
- nums = [3], strSt = [""], num = 2, cur = "a"

步骤 5：c = '['
- 遇到 '['，保存状态
- nums.push(2), strSt.push("a")
- nums = [3, 2], strSt = ["", "a"], num = 0, cur = ""

步骤 6：c = 'c'
- 是字母，cur += 'c'
- nums = [3, 2], strSt = ["", "a"], num = 0, cur = "c"

步骤 7：c = ']'
- 遇到 ']'，恢复状态
- repeat = 2, prev = "a"
- temp = "c" * 2 = "cc"
- cur = "a" + "cc" = "acc"
- nums = [3], strSt = [""], num = 0, cur = "acc"

步骤 8：c = ']'
- 遇到 ']'，恢复状态
- repeat = 3, prev = ""
- temp = "acc" * 3 = "accaccacc"
- cur = "" + "accaccacc" = "accaccacc"
- nums = [], strSt = [], num = 0, cur = "accaccacc"

结果："accaccacc"
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：双栈法
- 时间复杂度：O(n * k)
- 空间复杂度：O(n)
- 优点：逻辑清晰，易于理解
- 缺点：需要两个栈

方法二：递归法
- 时间复杂度：O(n * k)
- 空间复杂度：O(n)
- 优点：代码简洁
- 缺点：递归深度可能较大

两种方法时间复杂度相同，双栈法更直观。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 无括号：s = "abc"
   - 直接返回 "abc"

2. 单层括号：s = "3[a]"
   - 返回 "aaa"

3. 多层嵌套：s = "3[a2[c]]"
   - 返回 "accaccacc"

4. 多个括号：s = "3[a]2[bc]"
   - 返回 "aaabcbc"

5. 括号前有字母：s = "abc3[cd]xyz"
   - 返回 "abccdcdcdxyz"

6. 多位数：s = "100[a]"
   - 返回 100 个 'a'

7. 嵌套多位数：s = "2[abc]3[cd]ef"
   - 返回 "abcabccdcdcdef"
*/

int main() {
    Solution solution;

    // 测试用例 1：简单重复
    string s1 = "3[a]2[bc]";
    cout << "测试用例 1: \"" << s1 << "\" -> \""
         << solution.decodeString(s1) << "\" (期望: \"aaabcbc\")" << endl;

    // 测试用例 2：嵌套括号
    string s2 = "3[a2[c]]";
    cout << "测试用例 2: \"" << s2 << "\" -> \""
         << solution.decodeString(s2) << "\" (期望: \"accaccacc\")" << endl;

    // 测试用例 3：混合字母和括号
    string s3 = "2[abc]3[cd]ef";
    cout << "测试用例 3: \"" << s3 << "\" -> \""
         << solution.decodeString(s3) << "\" (期望: \"abcabccdcdcdef\")" << endl;

    // 测试用例 4：括号前后有字母
    string s4 = "abc3[cd]xyz";
    cout << "测试用例 4: \"" << s4 << "\" -> \""
         << solution.decodeString(s4) << "\" (期望: \"abccdcdcdxyz\")" << endl;

    // 测试用例 5：无括号
    string s5 = "abc";
    cout << "测试用例 5: \"" << s5 << "\" -> \""
         << solution.decodeString(s5) << "\" (期望: \"abc\")" << endl;

    // 测试用例 6：多位数
    string s6 = "10[a]";
    cout << "测试用例 6: \"" << s6 << "\" -> \""
         << solution.decodeString(s6) << "\" (期望: 10个'a')" << endl;

    return 0;
}

/*
关键要点总结
-----------
1. 字符串解码是栈的经典应用
2. 需要两个栈分别存储数字和字符串
3. 遇到 '[' 保存状态，遇到 ']' 恢复状态
4. 注意处理多位数的情况
5. 字符串拼接的顺序很重要

相关题目
-------
- LeetCode 726: 原子的数量
- LeetCode 385: 迷你语法分析器
- LeetCode 736: Lisp 语法解析
- LeetCode 1096: 花括号展开 II
- LeetCode 1190: 反转每对括号间的子串
*/
