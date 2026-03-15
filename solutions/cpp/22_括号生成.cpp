#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> ans;
    string path;

    void backtrack(int n,int left,int right){
        if(path.size()==2*n){
            ans.push_back(path);
            return;
        }

        if(left<n){
            path.push_back('(');
            backtrack(n, left + 1, right);
            path.pop_back();
        }

        if(right<left){
            path.push_back(')');
            backtrack(n, left, right+1);
            path.pop_back();
        }
    }

        vector<string> generateParenthesis(int n)
    {
        backtrack(n, 0, 0);
        return ans;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
