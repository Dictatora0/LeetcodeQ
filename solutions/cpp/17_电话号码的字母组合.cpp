#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> ans;
    string path;

    string map[10] = {
        "",
        "",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",
    };

    void backtrack(string& digits, int index){
        if(index == digits.size()){
            ans.push_back(path);
            return;//要记得返回
        }

        int digit = digits[index] - '0';
        for(char c : map[digit]){
            path += c;
            backtrack(digits, index + 1);
            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits){
        if(digits.empty()) return {};

        backtrack(digits, 0);

        return ans;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
