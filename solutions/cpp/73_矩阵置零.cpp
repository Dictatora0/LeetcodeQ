#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// LeetCode 73: 矩阵置零

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();

        if(row == 0){
            return ;
        }

        int col = matrix[0].size();

        bool isFirstRowZero = false;
        bool isFirstColZero = false;

        for(int i = 0; i < col; i++){
            //检查第一行中是否有0
            if(matrix[0][i] == 0){
                isFirstRowZero = true;
            }
        }

        for(int i = 0; i < row; i++){
            //检查第一列中是否有0
            if(matrix[i][0] == 0){
                isFirstColZero = true;
            }
        }

        for(int i = 1; i < row; i++){
            for(int j = 1; j < col; j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;   //所在行的第一个元素标记为0
                    matrix[0][j] = 0;   //所在列的第一个元素标记为0
                }
            }
        }

        for(int i = 1; i < row; i++){
            //从第二行开始检查当前行的第一个元素
            if(matrix[i][0] == 0){
                for (int j = 1; j < col; j++){
                    //将被标记的行置0
                    matrix[i][j] = 0;
                }
        }
    }

        for(int j = 1; j < col; j++){
            ////从第二列开始检查当前列的第一个元素
            if(matrix[0][j] == 0){
                for (int i = 1; i < row; i++){
                    //将被标记的列置0
                    matrix[i][j] = 0;
                }
        }
    }

        if(isFirstRowZero){
            for (int i = 0; i < col;i++){
                matrix[0][i] = 0;
            }
        }
        if(isFirstColZero){
            for (int i = 0; i < row;i++){
                matrix[i][0] = 0;
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
