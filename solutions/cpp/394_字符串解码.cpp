#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;
        stack<string> strSt;

        int num = 0;
        string cur = "";

        for (char c:s){
            if(c>='0'&&c<='9'){
                num = num * 10 + (c - '0');
            }else if(c=='['){
                nums.push(num);
                strSt.push(cur);

                num = 0;
                cur = "";
            }
            else if (c == ']')
            {
                int repeat = nums.top();
                nums.pop();

                string prev =strSt.top();
                strSt.pop();

                string temp = "";
                for (int i = 0; i < repeat; i++)
                {
                    temp += cur;
                }

                cur = prev + temp;
            }else{
                cur += c;
            }
        }

        return cur;
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    
    return 0;
}
