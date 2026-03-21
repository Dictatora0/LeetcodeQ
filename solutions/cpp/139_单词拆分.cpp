#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> dict(wordDict.begin(),wordDict.end());

        vector<bool> dp(n + 1, false);// dp[i] 表示前 i 个字符组成的子串 s[0...i-1] 是否可以被字典中的单词拼出来

        dp[0] = true;

        for (int i = 1; i <= n;i++){
            for (int j = 1; j < i;j++){
                if(dp[j]&&dict.count(s.substr(j,i-j))){
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
