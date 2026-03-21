#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);  // 作为初始边界
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();  // 尝试匹配一个 '('

                if (st.empty()) {
                    st.push(i);  // 当前 ')' 无法匹配，作为新的边界
                } else {
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};



int main() {
    Solution solution;
    
    // TODO: 添加测试用例

    cout << INT_MIN << endl;
    
    return 0;
}
