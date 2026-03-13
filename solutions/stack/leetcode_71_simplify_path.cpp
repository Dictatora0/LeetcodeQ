/*
LeetCode 71. 简化路径 (Simplify Path)

题目概述 (Problem Summary)
-------------------------
给定一个 Unix 风格的绝对路径，简化为规范路径。
规则：
- "." 表示当前目录
- ".." 表示上级目录
- 连续的 "/" 视为单个 "/"

关键约束 (Key Constraints)
-------------------------
- 1 <= path.length <= 3000
- path 由字母、数字、'.'、'/' 组成
- path 是绝对路径（以 "/" 开头）

示例 (Example)
-------------
输入：path = "/a/./b/../../c/"
输出："/c"

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将路径按 "/" 分段并处理 "." 与 ".."

关键观察：
1. ".." 需要回退一个目录，可用栈处理
2. "." 与空段直接忽略
3. 最终结果由栈中目录拼接

根据这些观察，可以得到两种典型解法：
1. 分割字符串 + 栈
2. 手动解析字符串 + 栈
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
用 stringstream 按 '/' 分割路径片段，用栈存储有效目录。

算法流程：
1. 用 '/' 分割 path
2. 遇到 ".." 弹栈（若非空）
3. 遇到 "." 或空段跳过
4. 将普通目录压栈
5. 拼接栈得到简化路径

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string segment;
        stringstream ss(path);

        while (getline(ss, segment, '/')) {
            if (segment.empty() || segment == ".") continue;
            if (segment == "..") {
                if (!st.empty()) st.pop_back();
            } else {
                st.push_back(segment);
            }
        }

        if (st.empty()) return "/";
        string result;
        for (const string& dir : st) {
            result += "/" + dir;
        }
        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Manual Parse)

优化思路
--------
手动遍历字符串构造分段，避免 stringstream 的额外开销。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string segment;
        int n = static_cast<int>(path.size());

        for (int i = 0; i <= n; ++i) {
            if (i == n || path[i] == '/') {
                if (!segment.empty()) {
                    if (segment == "..") {
                        if (!st.empty()) st.pop_back();
                    } else if (segment != ".") {
                        st.push_back(segment);
                    }
                    segment.clear();
                }
            } else {
                segment.push_back(path[i]);
            }
        }

        if (st.empty()) return "/";
        string result;
        for (const string& dir : st) {
            result += "/" + dir;
        }
        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
path = "/a/./b/../../c/"
分段：["a", ".", "b", "..", "..", "c"]
处理后栈：["c"]
输出："/c"
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：stringstream 分割
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码简洁
- 缺点：stringstream 有额外开销

方法二：手动解析
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：更高效
- 缺点：实现稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. path = "/"：返回 "/"
2. 多个连续 "/"：视为一个
3. ".." 超过根目录：仍返回 "/"
*/

int main() {
    Solution solution;

    // 测试用例 1
    string path1 = "/a/./b/../../c/";
    cout << "测试用例 1 - 输出: " << solution.simplifyPath(path1)
         << " (期望: /c)" << endl;

    // 测试用例 2
    string path2 = "/home//foo/";
    cout << "测试用例 2 - 输出: " << solution.simplifyPath(path2)
         << " (期望: /home/foo)" << endl;

    return 0;
}
