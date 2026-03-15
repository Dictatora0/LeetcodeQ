/*
 * LeetCode 338: 比特位计数 (Counting Bits)
 * 难度：Easy
 *
 * 题目描述：
 * 给你一个整数 n，对于 0 <= i <= n 中的每个 i，计算其二进制表示中 1 的个数，
 * 返回一个长度为 n + 1 的数组 ans 作为答案。
 *
 * 关键约束：
 * - 0 <= n <= 10^5
 * - 要求：O(n) 时间复杂度
 * - 进阶：
 *   - 很容易就能实现时间复杂度为 O(n log n) 的解决方案，你可以在线性时间复杂度 O(n) 内用一趟扫描解决吗？
 *   - 你能不使用任何内置函数解决吗？（如 C++ 中的 __builtin_popcount）
 *
 * 示例 1：
 * 输入：n = 2
 * 输出：[0,1,1]
 * 解释：
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 *
 * 示例 2：
 * 输入：n = 5
 * 输出：[0,1,1,2,1,2]
 * 解释：
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 * 3 --> 11
 * 4 --> 100
 * 5 --> 101
 *
 * ============================================================================
 *
 * 核心思路：动态规划 + 位运算
 *
 * 关键观察：
 * 1. 可以利用之前计算的结果来计算当前数字的1的个数
 * 2. 有多种递推关系可以利用
 *
 * 方法1：DP + i & (i-1)
 * - i & (i-1) 消除了 i 最右边的一个1
 * - 所以 dp[i] = dp[i & (i-1)] + 1
 *
 * 方法2：DP + 最低位
 * - i >> 1 是 i 除以2（右移一位）
 * - i & 1 是 i 的最低位
 * - 所以 dp[i] = dp[i >> 1] + (i & 1)
 *
 * 方法3：DP + 最高位
 * - 找到不大于 i 的最大2的幂 b
 * - dp[i] = dp[i - b] + 1
 *
 * 原理图解（方法1）：
 *
 * i = 0: 0000, dp[0] = 0
 * i = 1: 0001, dp[1] = dp[0 & 0] + 1 = dp[0] + 1 = 1
 * i = 2: 0010, dp[2] = dp[2 & 1] + 1 = dp[0] + 1 = 1
 * i = 3: 0011, dp[3] = dp[3 & 2] + 1 = dp[2] + 1 = 2
 * i = 4: 0100, dp[4] = dp[4 & 3] + 1 = dp[0] + 1 = 1
 * i = 5: 0101, dp[5] = dp[5 & 4] + 1 = dp[4] + 1 = 2
 * i = 6: 0110, dp[6] = dp[6 & 5] + 1 = dp[4] + 1 = 2
 * i = 7: 0111, dp[7] = dp[7 & 6] + 1 = dp[6] + 1 = 3
 *
 * 原理图解（方法2）：
 *
 * i = 0: 0000, dp[0] = 0
 * i = 1: 0001, dp[1] = dp[0] + 1 = 1
 * i = 2: 0010, dp[2] = dp[1] + 0 = 1
 * i = 3: 0011, dp[3] = dp[1] + 1 = 2
 * i = 4: 0100, dp[4] = dp[2] + 0 = 1
 * i = 5: 0101, dp[5] = dp[2] + 1 = 2
 * i = 6: 0110, dp[6] = dp[3] + 0 = 2
 * i = 7: 0111, dp[7] = dp[3] + 1 = 3
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // ========================================================================
    // 方法1：DP + i & (i-1)（推荐）
    // 时间复杂度：O(n)
    // 空间复杂度：O(1) - 不计输出数组
    // ========================================================================
    vector<int> countBits(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            // i & (i-1) 消除最右边的1
            // 所以 dp[i] = dp[i & (i-1)] + 1
            dp[i] = dp[i & (i - 1)] + 1;
        }

        return dp;
    }

    // ========================================================================
    // 方法2：DP + 最低位（最直观）
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    // ========================================================================
    vector<int> countBitsLowestBit(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            // i >> 1 是 i 除以2
            // i & 1 是 i 的最低位
            dp[i] = dp[i >> 1] + (i & 1);
        }

        return dp;
    }

    // ========================================================================
    // 方法3：DP + 最高位
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    // ========================================================================
    vector<int> countBitsHighestBit(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;

        int highBit = 0; // 当前最高位

        for (int i = 1; i <= n; i++) {
            // 当 i 是2的幂时，更新最高位
            if ((i & (i - 1)) == 0) {
                highBit = i;
            }
            // dp[i] = dp[i - highBit] + 1
            dp[i] = dp[i - highBit] + 1;
        }

        return dp;
    }

    // ========================================================================
    // 方法4：暴力法（用于对比）
    // 时间复杂度：O(n * log n) - 每个数字需要 O(log n) 时间计算
    // 空间复杂度：O(1)
    // ========================================================================
    vector<int> countBitsBrute(int n) {
        vector<int> result(n + 1);

        for (int i = 0; i <= n; i++) {
            result[i] = countOnes(i);
        }

        return result;
    }

private:
    // 计算一个数字中1的个数
    int countOnes(int n) {
        int count = 0;
        while (n) {
            n &= (n - 1);
            count++;
        }
        return count;
    }
};

/*
 * ============================================================================
 * 位运算技巧总结
 * ============================================================================
 *
 * 1. 动态规划 + 位运算的结合：
 *    - 利用位运算找到递推关系
 *    - 避免重复计算，提高效率
 *
 * 2. 三种递推关系：
 *    a) dp[i] = dp[i & (i-1)] + 1
 *       - 利用消除最右边1的性质
 *       - 最简洁
 *
 *    b) dp[i] = dp[i >> 1] + (i & 1)
 *       - 利用右移和最低位
 *       - 最直观
 *
 *    c) dp[i] = dp[i - highBit] + 1
 *       - 利用最高位
 *       - 需要额外变量跟踪
 *
 * 3. 位运算优化技巧：
 *    - i >> 1 等价于 i / 2，但更快
 *    - i & 1 等价于 i % 2，但更快
 *    - (i & (i-1)) == 0 判断是否是2的幂
 *
 * 4. 时间复杂度分析：
 *    - 暴力法：O(n * log n)
 *    - DP方法：O(n)
 *    - DP方法通过利用之前的结果，将每个数字的计算降到O(1)
 *
 * ============================================================================
 * 方法对比
 * ============================================================================
 *
 * | 方法           | 时间复杂度 | 空间复杂度 | 优点               | 缺点           |
 * |----------------|------------|------------|--------------------|----------------|
 * | DP+i&(i-1)     | O(n)       | O(1)       | 简洁，高效         | 需要理解原理   |
 * | DP+最低位      | O(n)       | O(1)       | 最直观             | 无             |
 * | DP+最高位      | O(n)       | O(1)       | 另一种思路         | 需要额外变量   |
 * | 暴力法         | O(n*logn)  | O(1)       | 简单               | 效率低         |
 *
 * ============================================================================
 */

// 辅助函数：打印二进制表示
void printBinary(int n, int width = 8) {
    for (int i = width - 1; i >= 0; i--) {
        cout << ((n >> i) & 1);
    }
}

// 测试用例
int main() {
    Solution solution;

    // 测试用例1：n = 2
    cout << "测试用例1: n = 2" << endl;
    vector<int> result1 = solution.countBits(2);
    cout << "结果: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望: [0,1,1]" << endl;
    cout << endl;

    // 测试用例2：n = 5
    cout << "测试用例2: n = 5" << endl;
    vector<int> result2 = solution.countBits(5);
    cout << "结果: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望: [0,1,1,2,1,2]" << endl;
    cout << endl;

    // 测试用例3：n = 0
    cout << "测试用例3: n = 0" << endl;
    vector<int> result3 = solution.countBits(0);
    cout << "结果: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望: [0]" << endl;
    cout << endl;

    // 详细演示：n = 8
    cout << "========================================" << endl;
    cout << "详细演示: n = 8" << endl;
    cout << "========================================" << endl;
    int n = 8;
    vector<int> demo = solution.countBits(n);

    cout << "i\t二进制\t\t1的个数" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i <= n; i++) {
        cout << i << "\t";
        printBinary(i);
        cout << "\t" << demo[i] << endl;
    }
    cout << endl;

    // 演示递推过程（方法1）
    cout << "========================================" << endl;
    cout << "递推过程演示（方法1: i & (i-1)）" << endl;
    cout << "========================================" << endl;
    vector<int> dp(9);
    dp[0] = 0;
    cout << "dp[0] = 0" << endl;

    for (int i = 1; i <= 8; i++) {
        int prev = i & (i - 1);
        dp[i] = dp[prev] + 1;
        cout << "dp[" << i << "] = dp[" << i << " & " << (i-1) << "] + 1 = dp[" << prev << "] + 1 = " << dp[i];
        cout << "  (";
        printBinary(i, 4);
        cout << " & ";
        printBinary(i-1, 4);
        cout << " = ";
        printBinary(prev, 4);
        cout << ")" << endl;
    }
    cout << endl;

    // 演示递推过程（方法2）
    cout << "========================================" << endl;
    cout << "递推过程演示（方法2: i >> 1）" << endl;
    cout << "========================================" << endl;
    vector<int> dp2(9);
    dp2[0] = 0;
    cout << "dp[0] = 0" << endl;

    for (int i = 1; i <= 8; i++) {
        int half = i >> 1;
        int lowest = i & 1;
        dp2[i] = dp2[half] + lowest;
        cout << "dp[" << i << "] = dp[" << i << " >> 1] + (" << i << " & 1) = dp[" << half << "] + " << lowest << " = " << dp2[i];
        cout << "  (";
        printBinary(i, 4);
        cout << " >> 1 = ";
        printBinary(half, 4);
        cout << ")" << endl;
    }
    cout << endl;

    // 对比四种方法
    cout << "========================================" << endl;
    cout << "方法对比 (n = 15):" << endl;
    cout << "========================================" << endl;
    vector<int> r1 = solution.countBits(15);
    vector<int> r2 = solution.countBitsLowestBit(15);
    vector<int> r3 = solution.countBitsHighestBit(15);
    vector<int> r4 = solution.countBitsBrute(15);

    cout << "方法1 (i&(i-1)): [";
    for (int i = 0; i < r1.size(); i++) {
        cout << r1[i];
        if (i < r1.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    cout << "方法2 (最低位):  [";
    for (int i = 0; i < r2.size(); i++) {
        cout << r2[i];
        if (i < r2.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    cout << "方法3 (最高位):  [";
    for (int i = 0; i < r3.size(); i++) {
        cout << r3[i];
        if (i < r3.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    cout << "方法4 (暴力法):  [";
    for (int i = 0; i < r4.size(); i++) {
        cout << r4[i];
        if (i < r4.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}
