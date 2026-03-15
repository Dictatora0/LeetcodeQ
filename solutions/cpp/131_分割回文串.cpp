#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    vector<string> path;
    vector<vector<bool>> dp;

    void isPalindrome(string s){
        for (int i = s.length() - 1; i >= 0;i--){
            for (int j = i; j < s.size(); j++){
                if(s[i]==s[j]){
                    if(j-i<=1){
                        dp[i][j] = true;
                    }else{
                        dp[i][j] = dp[i + 1][j - 1];
                    }
            }
        }
    }
}

    void backtrack(string s,int start){
        if(start == s.size()){
            ans.push_back(path);
            return ;
        }

        for (int i = start; i < s.size();i++){
            if(!dp[start][i]){
                continue;
            }

            path.push_back(s.substr(start,i-start+1));

            backtrack(s, i + 1);

            path.pop_back();
        }
    }


    vector<vector<string>> partition(string s) {
        int n = s.size();
        dp.assign(n, vector<bool>(n, false));

        isPalindrome(s);

        backtrack(s, 0);

        return ans;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
