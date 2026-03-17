#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int left = 0;
        int right  = m * n - 1;

        while(left<=right){
            int mid = left + (right - left) / 2;
            if(matrix[mid / n][mid % n]==target){
                return true;
            }else if(matrix[mid / n][mid % n]>target){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }

        return false;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
