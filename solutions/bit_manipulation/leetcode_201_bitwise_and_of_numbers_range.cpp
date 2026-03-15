/*
 * LeetCode 201: 数字范围按位与 (Bitwise AND of Numbers Range)
 * 难度：Medium
 *
 * 题目描述：
 * 给你两个整数 left 和 right，表示区间 [left, right]，
 * 返回此区间内所有数字按位与的结果（包含 left、right 端点）。
 *
 * 关键约束：
 * - 0 <= left <= right <= 2^31 - 1
 *
 * 示例 1：
 * 输入：left = 5, right = 7
 * 输出：4
 * 解释：
 * 5: 101
 * 6: 110
 * 7: 111
 * 按位与: 100 = 4
 *
 * 示例 2：
 * 输入：left = 0, right = 0
 * 输出：0
 *
 * 示例 3：
 * 输入：left = 1, right = 2147483647
 * 输出：0
 *
 * ============================================================================
 *
 * 核心思路：公共前缀
 *
 * 关键观察：
 * 1. 对于一个范围内的所有数字，按位与的结果是它们的公共前缀
 * 2. 为什么？因为在范围内，后面的位一定会出现0和1的变化
 * 3. 只有公共前缀部分在所有数字中都相同，才能在按位与后保留
 *
 * 原理图解：
 *
 * 例如：left = 5, right = 7
 *
 * 5: 101
 * 6: 110
 * 7: 111
 *
 * 观察：
 * - 最高位（第2位）：都是1
 * - 第1位：5是0，6和7是1，按位与后是0
 * - 第0位：5和7是1，6是0，按位与后是0
 *
 * 结果：100 = 4
 *
 * 更直观的理解：
 * - 找到 left 和 right 的公共前缀
 * - 公共前缀后面的位都是0
 *
 * 例如：left = 5 (101), right = 7 (111)
 * - 右移1位：left = 2 (10), right = 3 (11)
 * - 右移2位：left = 1 (1), right = 1 (1) -> 相等！
 * - 公共前缀是 1，左移2位得到 100 = 4
 *
 * 为什么有效？
 * - 在一个范围内，如果 left != right，那么最低位一定会有0和1
 * - 按位与后，这一位就是0
 * - 不断右移，直到 left == right，此时就是公共前缀
 *
 * ============================================================================
 */

#include <iostream>
using namespace std;

class Solution {
public:
    // ========================================================================
    // 方法1：公共前缀（最优解）
    // 时间复杂度：O(log n) - 最多右移32次
    // 空间复杂度：O(1)
    // ========================================================================
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;

        // 找到公共前缀
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }

        // 将公共前缀左移回原位置
        return left << shift;
    }

    // ========================================================================
    // 方法2：Brian Kernighan 算法
    // 时间复杂度：O(log n)
    // 空间复杂度：O(1)
    //
    // 思路：不断消除 right 最右边的1，直到 right <= left
    // 原理：right & (right-1) 消除最右边的1
    // ========================================================================
    int rangeBitwiseAndBK(int left, int right) {
        // 不断消除 right 最右边的1
        while (left < right) {
            right &= (right - 1);
        }
        return right;
    }

    // ========================================================================
    // 方法3：暴力法（会超时，仅用于理解）
    // 时间复杂度：O(right - left)
    // 空间复杂度：O(1)
    // ========================================================================
    int rangeBitwiseAndBrute(int left, int right) {
        int result = left;
        for (int i = left + 1; i <= right; i++) {
            result &= i;
            // 优化：如果结果已经是0，可以提前退出
            if (result == 0) break;
        }
        return result;
    }
};

/*
 * ============================================================================
 * 位运算技巧总结
 * ============================================================================
 *
 * 1. 公共前缀方法：
 *    - 核心思想：范围内所有数字的按位与 = 公共前缀
 *    - 实现：不断右移直到 left == right
 *    - 应用：快速计算范围按位与
 *
 * 2. Brian Kernighan 算法：
 *    - 核心思想：消除 right 的最右边的1，直到 right <= left
 *    - 实现：right &= (right - 1)
 *    - 应用：另一种找公共前缀的方法
 *
 * 3. 为什么公共前缀有效？
 *    - 在范围 [left, right] 内，如果某一位在 left 和 right 中不同
 *    - 那么这一位在范围内一定会有0和1的变化
 *    - 按位与后，这一位就是0
 *    - 只有公共前缀部分在所有数字中都相同
 *
 * 4. 特殊情况：
 *    - left == right：直接返回 left
 *    - left == 0：结果一定是0（因为0与任何数按位与都是0）
 *    - right - left >= right：结果一定是0（范围太大，必然包含所有位的变化）
 *
 * 5. 位运算优化：
 *    - 右移操作：x >> 1 等价于 x / 2
 *    - 左移操作：x << 1 等价于 x * 2
 *    - 消除最右边的1：x & (x-1)
 *
 * ============================================================================
 * 方法对比
 * ============================================================================
 *
 * | 方法           | 时间复杂度      | 空间复杂度 | 优点               | 缺点           |
 * |----------------|-----------------|------------|--------------------|----------------|
 * | 公共前缀       | O(log n)        | O(1)       | 最优，易理解       | 需要理解原理   |
 * | BK算法         | O(log n)        | O(1)       | 简洁               | 不够直观       |
 * | 暴力法         | O(right-left)   | O(1)       | 直观               | 会超时         |
 *
 * ============================================================================
 */

// 辅助函数：打印二进制表示
void printBinary(int n, const string& label, int width = 32) {
    cout << label;
    for (int i = width - 1; i >= 0; i--) {
        cout << ((n >> i) & 1);
        if (i % 8 == 0 && i > 0) cout << " ";
    }
    cout << " (" << n << ")" << endl;
}

// 辅助函数：打印范围内所有数字的二进制
void printRange(int left, int right) {
    cout << "范围 [" << left << ", " << right << "] 的二进制表示：" << endl;
    int width = 8; // 只显示低8位
    for (int i = left; i <= right && i < left + 10; i++) {
        cout << i << ": ";
        for (int j = width - 1; j >= 0; j--) {
            cout << ((i >> j) & 1);
        }
        cout << endl;
    }
    if (right >= left + 10) {
        cout << "... (省略部分)" << endl;
    }
}

// 测试用例
int main() {
    Solution solution;

    // 测试用例1：基本情况
    cout << "测试用例1: left = 5, right = 7" << endl;
    printRange(5, 7);
    int result1 = solution.rangeBitwiseAnd(5, 7);
    cout << "结果: " << result1 << endl;
    cout << "期望: 4" << endl;
    printBinary(result1, "二进制: ", 8);
    cout << endl;

    // 测试用例2：相同数字
    cout << "测试用例2: left = 0, right = 0" << endl;
    int result2 = solution.rangeBitwiseAnd(0, 0);
    cout << "结果: " << result2 << endl;
    cout << "期望: 0" << endl;
    cout << endl;

    // 测试用例3：大范围
    cout << "测试用例3: left = 1, right = 2147483647" << endl;
    int result3 = solution.rangeBitwiseAnd(1, 2147483647);
    cout << "结果: " << result3 << endl;
    cout << "期望: 0" << endl;
    cout << endl;

    // 测试用例4：2的幂
    cout << "测试用例4: left = 4, right = 7" << endl;
    printRange(4, 7);
    int result4 = solution.rangeBitwiseAnd(4, 7);
    cout << "结果: " << result4 << endl;
    cout << "期望: 4" << endl;
    printBinary(result4, "二进制: ", 8);
    cout << endl;

    // 测试用例5：连续的2的幂
    cout << "测试用例5: left = 8, right = 15" << endl;
    printRange(8, 15);
    int result5 = solution.rangeBitwiseAnd(8, 15);
    cout << "结果: " << result5 << endl;
    cout << "期望: 8" << endl;
    printBinary(result5, "二进制: ", 8);
    cout << endl;

    // 演示公共前缀过程
    cout << "========================================" << endl;
    cout << "公共前缀演示 (left = 5, right = 7):" << endl;
    cout << "========================================" << endl;
    int left = 5, right = 7;
    int shift = 0;

    cout << "初始状态：" << endl;
    printBinary(left, "left:  ", 8);
    printBinary(right, "right: ", 8);
    cout << endl;

    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
        cout << "右移 " << shift << " 位后：" << endl;
        printBinary(left, "left:  ", 8);
        printBinary(right, "right: ", 8);
        cout << endl;
    }

    int result = left << shift;
    cout << "公共前缀: " << left << endl;
    cout << "左移 " << shift << " 位后：" << endl;
    printBinary(result, "结果:  ", 8);
    cout << endl;

    // 演示 Brian Kernighan 算法
    cout << "========================================" << endl;
    cout << "Brian Kernighan 算法演示 (left = 5, right = 7):" << endl;
    cout << "========================================" << endl;
    left = 5;
    right = 7;
    int step = 0;

    cout << "初始状态：" << endl;
    printBinary(left, "left:  ", 8);
    printBinary(right, "right: ", 8);
    cout << endl;

    while (left < right) {
        int prev = right;
        right &= (right - 1);
        step++;
        cout << "第 " << step << " 步：" << endl;
        printBinary(prev, "right:     ", 8);
        printBinary(prev - 1, "right-1:   ", 8);
        printBinary(right, "right&(r-1): ", 8);
        cout << endl;
    }

    cout << "最终结果: " << right << endl;
    cout << endl;

    // 对比三种方法
    cout << "========================================" << endl;
    cout << "方法对比 (left = 26, right = 30):" << endl;
    cout << "========================================" << endl;
    printRange(26, 30);
    cout << "方法1 (公共前缀): " << solution.rangeBitwiseAnd(26, 30) << endl;
    cout << "方法2 (BK算法):   " << solution.rangeBitwiseAndBK(26, 30) << endl;
    cout << "方法3 (暴力法):   " << solution.rangeBitwiseAndBrute(26, 30) << endl;
    cout << endl;

    // 特殊情况测试
    cout << "========================================" << endl;
    cout << "特殊情况测试：" << endl;
    cout << "========================================" << endl;

    // 跨越2的幂
    cout << "跨越2的幂 (left = 3, right = 4):" << endl;
    printRange(3, 4);
    cout << "结果: " << solution.rangeBitwiseAnd(3, 4) << endl;
    cout << "解释: 跨越2的幂，最高位不同，结果为0" << endl;
    cout << endl;

    // 不跨越2的幂
    cout << "不跨越2的幂 (left = 4, right = 5):" << endl;
    printRange(4, 5);
    cout << "结果: " << solution.rangeBitwiseAnd(4, 5) << endl;
    cout << "解释: 不跨越2的幂，保留公共前缀" << endl;
    cout << endl;

    return 0;
}
