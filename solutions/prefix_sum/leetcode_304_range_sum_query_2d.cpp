/*
 * LeetCode 304: 二维区域和检索 - 矩阵不可变 (Range Sum Query 2D - Immutable)
 * 难度：Medium
 *
 * ============================================================================
 * 题目概述
 * ============================================================================
 * 给定一个二维矩阵 matrix，以下类型的多个请求：
 * 计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1)，右下角为 (row2, col2)。
 *
 * 实现 NumMatrix 类：
 * - NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
 * - int sumRegion(int row1, int col1, int row2, int col2) 返回左上角 (row1, col1)、
 *   右下角 (row2, col2) 所描述的子矩阵的元素总和
 *
 * 关键约束：
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 200
 * - -10^4 <= matrix[i][j] <= 10^4
 * - 0 <= row1 <= row2 < m
 * - 0 <= col1 <= col2 < n
 * - 最多调用 10^4 次 sumRegion 方法
 *
 * ============================================================================
 * 示例
 * ============================================================================
 * 输入：
 * ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
 * [[[[3, 0, 1, 4, 2],
 *    [5, 6, 3, 2, 1],
 *    [1, 2, 0, 1, 5],
 *    [4, 1, 0, 1, 7],
 *    [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
 *
 * 输出：
 * [null, 8, 11, 12]
 *
 * 解释：
 * NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],
 *                                       [5,6,3,2,1],
 *                                       [1,2,0,1,5],
 *                                       [4,1,0,1,7],
 *                                       [1,0,3,0,5]]);
 * numMatrix.sumRegion(2, 1, 4, 3); // 返回 8 (左上角 (2,1) 到右下角 (4,3) 的子矩阵和)
 * numMatrix.sumRegion(1, 1, 2, 2); // 返回 11
 * numMatrix.sumRegion(1, 2, 2, 4); // 返回 12
 *
 * ============================================================================
 * 核心思想：二维前缀和
 * ============================================================================
 *
 * 1. 二维前缀和定义：
 *    prefixSum[i][j] = 从 (0,0) 到 (i-1,j-1) 的矩形区域的元素和
 *    prefixSum[0][j] = 0（第 0 行全为 0）
 *    prefixSum[i][0] = 0（第 0 列全为 0）
 *
 * 2. 二维前缀和计算公式：
 *    prefixSum[i][j] = prefixSum[i-1][j]      // 上方矩形
 *                    + prefixSum[i][j-1]      // 左方矩形
 *                    - prefixSum[i-1][j-1]    // 减去重复计算的部分
 *                    + matrix[i-1][j-1]       // 加上当前元素
 *
 * 3. 区域和查询公式：
 *    sum(row1, col1, row2, col2) = prefixSum[row2+1][col2+1]
 *                                - prefixSum[row1][col2+1]
 *                                - prefixSum[row2+1][col1]
 *                                + prefixSum[row1][col1]
 *
 * 4. 为什么要加 1：
 *    - prefixSum 数组比 matrix 多一行一列（第 0 行和第 0 列）
 *    - 避免边界判断，简化代码
 *
 * ============================================================================
 * 二维前缀和图解
 * ============================================================================
 *
 * 原矩阵 matrix:
 *     0   1   2   3   4
 *   +---+---+---+---+---+
 * 0 | 3 | 0 | 1 | 4 | 2 |
 *   +---+---+---+---+---+
 * 1 | 5 | 6 | 3 | 2 | 1 |
 *   +---+---+---+---+---+
 * 2 | 1 | 2 | 0 | 1 | 5 |
 *   +---+---+---+---+---+
 * 3 | 4 | 1 | 0 | 1 | 7 |
 *   +---+---+---+---+---+
 * 4 | 1 | 0 | 3 | 0 | 5 |
 *   +---+---+---+---+---+
 *
 * 前缀和 prefixSum (多一行一列):
 *      0    1    2    3    4    5
 *   +----+----+----+----+----+----+
 * 0 |  0 |  0 |  0 |  0 |  0 |  0 |
 *   +----+----+----+----+----+----+
 * 1 |  0 |  3 |  3 |  4 |  8 | 10 |
 *   +----+----+----+----+----+----+
 * 2 |  0 |  8 | 14 | 18 | 24 | 27 |
 *   +----+----+----+----+----+----+
 * 3 |  0 |  9 | 17 | 21 | 28 | 36 |
 *   +----+----+----+----+----+----+
 * 4 |  0 | 13 | 22 | 26 | 34 | 49 |
 *   +----+----+----+----+----+----+
 * 5 |  0 | 14 | 23 | 30 | 38 | 58 |
 *   +----+----+----+----+----+----+
 *
 * 计算示例：prefixSum[2][2] = 14
 * = prefixSum[1][2] + prefixSum[2][1] - prefixSum[1][1] + matrix[1][1]
 * = 3 + 8 - 3 + 6
 * = 14
 *
 * 查询示例：sumRegion(1, 1, 2, 2)
 * = prefixSum[3][3] - prefixSum[1][3] - prefixSum[3][1] + prefixSum[1][1]
 * = 21 - 4 - 9 + 3
 * = 11
 *
 * ============================================================================
 * 区域和查询公式推导
 * ============================================================================
 *
 * 目标：计算从 (row1, col1) 到 (row2, col2) 的矩形区域和
 *
 * 图示：
 *   +-------+-------+
 *   |   A   |   B   |
 *   +-------+-------+
 *   |   C   | 目标  |
 *   +-------+-------+
 *
 * 其中：
 * - A = prefixSum[row1][col1]
 * - A + B = prefixSum[row1][col2+1]
 * - A + C = prefixSum[row2+1][col1]
 * - A + B + C + 目标 = prefixSum[row2+1][col2+1]
 *
 * 推导：
 * 目标 = (A + B + C + 目标) - (A + B) - (A + C) + A
 *      = prefixSum[row2+1][col2+1]
 *      - prefixSum[row1][col2+1]
 *      - prefixSum[row2+1][col1]
 *      + prefixSum[row1][col1]
 *
 * ============================================================================
 * 复杂度分析
 * ============================================================================
 *
 * 方法1：二维前缀和（最优）
 * 预处理时间：O(m * n) - 计算所有前缀和
 * 查询时间：O(1) - 直接计算
 * 空间复杂度：O(m * n) - 存储前缀和数组
 *
 * 方法2：一维前缀和
 * 预处理时间：O(m * n) - 计算每行的前缀和
 * 查询时间：O(m) - 遍历每一行
 * 空间复杂度：O(m * n) - 存储每行的前缀和
 *
 * 方法3：暴力
 * 预处理时间：O(1)
 * 查询时间：O(m * n) - 遍历整个区域
 * 空间复杂度：O(1)
 *
 * ============================================================================
 * 特殊情况处理
 * ============================================================================
 *
 * 1. 单个元素：row1 == row2 && col1 == col2
 * 2. 单行：row1 == row2
 * 3. 单列：col1 == col2
 * 4. 整个矩阵：row1 = 0, col1 = 0, row2 = m-1, col2 = n-1
 * 5. 负数：前缀和可能为负，不影响算法正确性
 *
 */

#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// 方法1：二维前缀和（最优解法）
// ============================================================================
class NumMatrix {
private:
    // 前缀和数组：prefixSum[i][j] 表示从 (0,0) 到 (i-1,j-1) 的矩形区域和
    // 多一行一列，避免边界判断
    vector<vector<int>> prefixSum;

public:
    // 构造函数：预处理前缀和
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }

        int m = matrix.size();
        int n = matrix[0].size();

        // 初始化前缀和数组（多一行一列）
        prefixSum.resize(m + 1, vector<int>(n + 1, 0));

        // 计算前缀和
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 二维前缀和公式：
                // prefixSum[i][j] = 上方 + 左方 - 左上（重复） + 当前元素
                prefixSum[i][j] = prefixSum[i - 1][j]      // 上方矩形
                                + prefixSum[i][j - 1]      // 左方矩形
                                - prefixSum[i - 1][j - 1]  // 减去重复计算的左上角
                                + matrix[i - 1][j - 1];    // 加上当前元素
            }
        }
    }

    // 查询区域和
    int sumRegion(int row1, int col1, int row2, int col2) {
        // 区域和公式：
        // sum = 整个大矩形 - 上方矩形 - 左方矩形 + 左上角（重复减去）
        return prefixSum[row2 + 1][col2 + 1]      // 整个大矩形
             - prefixSum[row1][col2 + 1]          // 减去上方矩形
             - prefixSum[row2 + 1][col1]          // 减去左方矩形
             + prefixSum[row1][col1];             // 加上左上角（被重复减去）
    }
};

// ============================================================================
// 方法2：一维前缀和（用于对比）
// ============================================================================
class NumMatrixOneDim {
private:
    // 每行的前缀和
    vector<vector<int>> rowPrefixSum;

public:
    NumMatrixOneDim(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }

        int m = matrix.size();
        int n = matrix[0].size();

        // 初始化每行的前缀和（多一列）
        rowPrefixSum.resize(m, vector<int>(n + 1, 0));

        // 计算每行的前缀和
        for (int i = 0; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                rowPrefixSum[i][j] = rowPrefixSum[i][j - 1] + matrix[i][j - 1];
            }
        }
    }

    // 查询区域和：遍历每一行
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            sum += rowPrefixSum[i][col2 + 1] - rowPrefixSum[i][col1];
        }
        return sum;
    }
};

// ============================================================================
// 方法3：暴力（用于对比）
// ============================================================================
class NumMatrixBruteForce {
private:
    vector<vector<int>> matrix;

public:
    NumMatrixBruteForce(vector<vector<int>>& mat) {
        matrix = mat;
    }

    // 查询区域和：直接遍历
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            for (int j = col1; j <= col2; j++) {
                sum += matrix[i][j];
            }
        }
        return sum;
    }
};

// ============================================================================
// 示例推演：展示二维前缀和的计算过程
// ============================================================================
void demonstrateAlgorithm() {
    cout << "============================================" << endl;
    cout << "二维前缀和计算过程演示" << endl;
    cout << "============================================" << endl;

    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    int m = matrix.size();
    int n = matrix[0].size();

    cout << "原矩阵：" << endl;
    for (int i = 0; i < m; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 计算前缀和
    vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));

    cout << "前缀和计算过程：" << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefixSum[i][j] = prefixSum[i - 1][j]
                            + prefixSum[i][j - 1]
                            - prefixSum[i - 1][j - 1]
                            + matrix[i - 1][j - 1];

            cout << "prefixSum[" << i << "][" << j << "] = "
                 << prefixSum[i - 1][j] << " + "
                 << prefixSum[i][j - 1] << " - "
                 << prefixSum[i - 1][j - 1] << " + "
                 << matrix[i - 1][j - 1] << " = "
                 << prefixSum[i][j] << endl;
        }
    }
    cout << endl;

    cout << "前缀和数组：" << endl;
    for (int i = 0; i <= m; i++) {
        cout << "  ";
        for (int j = 0; j <= n; j++) {
            cout << prefixSum[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "============================================" << endl << endl;
}

// ============================================================================
// 区域和查询演示
// ============================================================================
void demonstrateQuery() {
    cout << "============================================" << endl;
    cout << "区域和查询演示" << endl;
    cout << "============================================" << endl;

    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    NumMatrix numMatrix(matrix);

    // 查询 1：(2, 1) 到 (4, 3)
    int row1 = 2, col1 = 1, row2 = 4, col2 = 3;
    int result = numMatrix.sumRegion(row1, col1, row2, col2);

    cout << "查询 1: sumRegion(" << row1 << ", " << col1 << ", "
         << row2 << ", " << col2 << ")" << endl;
    cout << "  区域：" << endl;
    for (int i = row1; i <= row2; i++) {
        cout << "    ";
        for (int j = col1; j <= col2; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "  结果: " << result << endl << endl;

    // 查询 2：(1, 1) 到 (2, 2)
    row1 = 1; col1 = 1; row2 = 2; col2 = 2;
    result = numMatrix.sumRegion(row1, col1, row2, col2);

    cout << "查询 2: sumRegion(" << row1 << ", " << col1 << ", "
         << row2 << ", " << col2 << ")" << endl;
    cout << "  区域：" << endl;
    for (int i = row1; i <= row2; i++) {
        cout << "    ";
        for (int j = col1; j <= col2; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "  结果: " << result << endl << endl;

    cout << "============================================" << endl << endl;
}

// ============================================================================
// 测试用例
// ============================================================================
int main() {
    // 演示算法过程
    demonstrateAlgorithm();

    // 演示查询过程
    demonstrateQuery();

    // 测试矩阵
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    // 创建三种实现
    NumMatrix numMatrix(matrix);
    NumMatrixOneDim numMatrixOneDim(matrix);
    NumMatrixBruteForce numMatrixBruteForce(matrix);

    // 测试用例
    vector<vector<int>> queries = {
        {2, 1, 4, 3},  // 期望: 8
        {1, 1, 2, 2},  // 期望: 11
        {1, 2, 2, 4},  // 期望: 12
        {0, 0, 4, 4},  // 期望: 58 (整个矩阵)
        {0, 0, 0, 0},  // 期望: 3 (单个元素)
        {2, 2, 2, 2}   // 期望: 0 (单个元素)
    };

    cout << "测试用例：" << endl;
    for (int i = 0; i < queries.size(); i++) {
        int row1 = queries[i][0];
        int col1 = queries[i][1];
        int row2 = queries[i][2];
        int col2 = queries[i][3];

        int result1 = numMatrix.sumRegion(row1, col1, row2, col2);
        int result2 = numMatrixOneDim.sumRegion(row1, col1, row2, col2);
        int result3 = numMatrixBruteForce.sumRegion(row1, col1, row2, col2);

        cout << "查询 " << (i + 1) << ": sumRegion(" << row1 << ", " << col1
             << ", " << row2 << ", " << col2 << ")" << endl;
        cout << "  二维前缀和: " << result1 << endl;
        cout << "  一维前缀和: " << result2 << endl;
        cout << "  暴力: " << result3 << endl;
        cout << "  一致性: " << (result1 == result2 && result2 == result3 ? "✓" : "✗")
             << endl << endl;
    }

    return 0;
}

/*
 * ============================================================================
 * 关键要点总结
 * ============================================================================
 *
 * 1. 二维前缀和的定义：
 *    prefixSum[i][j] = 从 (0,0) 到 (i-1,j-1) 的矩形区域和
 *
 * 2. 二维前缀和的计算：
 *    prefixSum[i][j] = prefixSum[i-1][j] + prefixSum[i][j-1]
 *                    - prefixSum[i-1][j-1] + matrix[i-1][j-1]
 *    - 上方 + 左方 - 左上（重复） + 当前
 *
 * 3. 区域和的查询：
 *    sum = prefixSum[row2+1][col2+1] - prefixSum[row1][col2+1]
 *        - prefixSum[row2+1][col1] + prefixSum[row1][col1]
 *    - 大矩形 - 上方 - 左方 + 左上（重复减）
 *
 * 4. 为什么多一行一列：
 *    - 避免边界判断（i-1, j-1 可能越界）
 *    - 简化代码逻辑
 *    - prefixSum[0][j] = 0, prefixSum[i][0] = 0
 *
 * 5. 容斥原理的应用：
 *    - 计算时：加上重复的部分
 *    - 查询时：减去重复的部分
 *
 * 6. 时间复杂度权衡：
 *    - 预处理 O(m*n)，查询 O(1)
 *    - 适合多次查询的场景
 *    - 如果只查询一次，暴力更快
 *
 * 7. 空间优化：
 *    - 如果只需要一维前缀和，可以节省空间
 *    - 但查询时间会增加到 O(m) 或 O(n)
 *
 * ============================================================================
 * 相关题目
 * ============================================================================
 *
 * - LeetCode 303: 区域和检索 - 数组不可变（一维版本）
 * - LeetCode 308: 二维区域和检索 - 可变（支持更新）
 * - LeetCode 1314: 矩阵区域和
 * - LeetCode 1277: 统计全为 1 的正方形子矩阵
 * - LeetCode 221: 最大正方形
 *
 */
