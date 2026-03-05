#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {

        if (matrix.empty() || matrix[0].empty()) return {};

        int row = matrix.size();
        int col = matrix[0].size();

        vector<int> ans;
        ans.reserve(row * col);// 提前分配空间，提高效率

        int left = 0,right = col-1;
        int top = 0,bottom = row-1;

        while (top <= bottom && left <= right) {
                // 从左到右遍历上边界
                for (int j = left; j <= right; ++j) {
                    ans.push_back(matrix[top][j]);
                }
                ++top; // 上边界下移

                // 从上到下遍历右边界
                for (int i = top; i <= bottom; ++i) {
                    ans.push_back(matrix[i][right]);
                }
                --right; // 右边界左移

                // 从右到左遍历下边界（需检查是否还有行）
                if (top <= bottom) {
                    for (int j = right; j >= left; --j) {
                        ans.push_back(matrix[bottom][j]);
                    }
                    --bottom; // 下边界上移
                }

                // 从下到上遍历左边界（需检查是否还有列）
                if (left <= right) {
                    for (int i = bottom; i >= top; --i) {
                        ans.push_back(matrix[i][left]);
                    }
                    ++left; // 左边界右移
                }
            }
            return ans;
        }
    };

int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
