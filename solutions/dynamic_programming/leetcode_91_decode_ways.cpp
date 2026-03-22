/*
LeetCode 91. Decode Ways (解码方法)

题目概述 (Problem Summary)
-------------------------
给定一个只含数字的字符串 s，映射规则是：
- '1' -> 'A', ..., '26' -> 'Z'
求 s 有多少种不同解码方式。

示例
----
- "12" -> "AB" / "L"，共 2 种
- "226" -> "BZ" / "VF" / "BBF"，共 3 种
- "06" -> 0 种（前导 0 非法）

关键词
------
- 线性 DP
- 单字符 / 双字符转移
- 0 的特殊处理

算法思路 (Algorithm Thinking)
----------------------------
定义 dp[i]：前 i 个字符（s[0..i-1]）的解码方案数。

转移来源有两个：
1. 把 s[i-1] 单独解码（必须是 '1'..'9'）
   dp[i] += dp[i-1]
2. 把 s[i-2..i-1] 作为一个两位数解码（必须在 [10,26]）
   dp[i] += dp[i-2]

边界：
- dp[0] = 1（空串有 1 种“什么都不做”的方式）
- s[0] == '0' 直接返回 0

因为 dp[i] 只依赖前两项，可压缩为 O(1) 空间。

常见变体
--------
1. LeetCode 639 Decode Ways II：含 '*'，状态更多
2. 只判断能否解码：可用布尔 DP
3. 输出一种具体解码路径：需要记录决策并回溯

面试追问
--------
Q1: 为什么 '0' 不能单独解码？
A1: 映射只有 1..26，没有 0。

Q2: "100" 为什么是 0？
A2: "10" 合法，但剩余最后一个 '0' 无法单独解码。

Q3: 为什么 dp[0] 要设为 1？
A3: 统一转移边界，表示“前缀为空时有一种构成方式”。

Q4: 时间复杂度和空间复杂度？
A4: 时间 O(n)，空间 O(1)。
*/

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        const int n = static_cast<int>(s.size());
        if (n == 0 || s[0] == '0') return 0;

        // prev2 = dp[i-2], prev1 = dp[i-1]
        int prev2 = 1;
        int prev1 = 1;

        for (int i = 2; i <= n; ++i) {
            int cur = 0;

            if (s[i - 1] != '0') {
                cur += prev1;
            }

            int two = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (two >= 10 && two <= 26) {
                cur += prev2;
            }

            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

/*
示例推演
--------
以 s = "226" 为例：
- i=1: "2" -> 1 种
- i=2: "22"
  - 单独看 '2'：+dp[1]
  - 合并看 "22"：+dp[0]
  => dp[2]=2
- i=3: "226"
  - 单独看 '6'：+dp[2]=2
  - 合并看 "26"：+dp[1]=1
  => dp[3]=3

易错点
------
1. 忽略 "0" 的非法单独解码
2. 两位数判断写成 [1,26]（错误，应是 [10,26]）
3. 把 dp 下标和字符串下标混淆
*/

int main() {
    Solution sol;

    assert(sol.numDecodings("12") == 2);
    assert(sol.numDecodings("226") == 3);
    assert(sol.numDecodings("06") == 0);
    assert(sol.numDecodings("2101") == 1);
    assert(sol.numDecodings("11106") == 2);
    assert(sol.numDecodings("100") == 0);

    cout << "LeetCode 91 tests passed.\n";
    return 0;
}
