#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int row, col;

    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int k) {
        if (i < 0 || i >= row || j < 0 || j >= col) {
            return false;
        }

        if (board[i][j] != word[k]) {
            return false;
        }

        if (k == word.size() - 1) {
            return true;
        }

        char ch = board[i][j];
        board[i][j] = '#';

        bool find = dfs(board, word, i + 1, j, k + 1) ||
                    dfs(board, word, i, j + 1, k + 1) ||
                    dfs(board, word, i - 1, j, k + 1) ||
                    dfs(board, word, i, j - 1, k + 1);

        board[i][j] = ch;

        return find;
    }

    bool exist(vector<vector<char>>& board, string word) {
        row = board.size();
        col = board[0].size();

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
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
