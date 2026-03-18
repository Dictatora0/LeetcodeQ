#include <iostream>
#include <vector>

using namespace std;

/*
LeetCode 118. 杨辉三角
题型：递推 / 动态规划
核心思路：每一行的两端都是 1，中间位置由上一行的左上角和右上角相加得到。
复杂度：时间 O(numRows^2)，空间 O(numRows^2)
*/
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows <= 0) return {};

        vector<vector<int>> triangle(numRows);
        for (int i = 0; i < numRows; ++i) {
            triangle[i].resize(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }

        return triangle;
    }
};

static void printTriangle(const vector<vector<int>>& triangle) {
    for (const auto& row : triangle) {
        cout << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << row[i];
        }
        cout << "]" << endl;
    }
}

int main() {
    Solution solution;
    vector<vector<int>> triangle = solution.generate(5);

    cout << "numRows = 5" << endl;
    printTriangle(triangle);

    return 0;
}
