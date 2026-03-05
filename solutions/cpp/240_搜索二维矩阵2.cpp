#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

//利用矩阵的有序特性，从右上角元素开始搜索，每次比较都能排除一行或一列。
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        // 从右上角开始
        int row = 0, col = n - 1;
        
        while (row < m && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                // 当前值太大，向左移动（排除当前列）
                col--;
            } else {
                // 当前值太小，向下移动（排除当前行）
                row++;
            }
        }
        
        return false;
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
