#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {
            if (c == '(') st.push(')');
            else if (c == '[') st.push(']');
            else if (c == '{') st.push('}');
            else {
                if (st.empty() || st.top() != c) {
                    return false;
                }
                st.pop();
            }
        }

        return st.empty();
    }
};
int main() {
    Solution solution;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
