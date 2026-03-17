#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    vector<int> queens;

    bool isValid(int row,int col){
        for (int i = 0; i < row;i++){
            if (queens[i] == col){
                return false;
            }

            if(abs(row-i)==abs(col-queens[i])){
                return false;
            }
        }
        return true;
    }

    void backtrack(int n,int row){
        if(row == n){
            vector<string> board(n, string(n, '.'));
            for (int i = 0; i < n;i++){
                board[i][queens[i]] = 'Q';
            }
            ans.push_back(board);
            return ;
        }

        for (int col = 0; col < n;col++){
            if(!isValid(row,col)){
                continue;
            }

            queens[row] = col;

            backtrack(n, row + 1);
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        queens.resize(n);
        backtrack(n, 0);

        return ans;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
