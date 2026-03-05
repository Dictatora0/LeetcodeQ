#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        if(matrix.empty()||matrix[0].empty()){
            return;
        }

        int n = matrix.size();

        vector<int> mem; //保存旋转后数组的正确形式
        mem.reserve(n * n);

        //从每一列的最下方元素（即旋转后形成的行的第一个元素）开始
        for (int i = 0; i < n; i++){
            for (int j = n-1; j >= 0; j--){//上移指针，得到旋转后数组的一行并记录
                mem.push_back(matrix[j][i]);
            }
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrix[i][j] = mem[i * n + j];//根据坐标规律修改原数组
            }
        }
        }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
