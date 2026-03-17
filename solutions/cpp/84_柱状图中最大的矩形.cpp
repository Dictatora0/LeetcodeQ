#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        st.push(-1);

        int ans = 0;
        int n = heights.size();

        for (int i = 0; i < n;i++){
            while (st.top() != -1 && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();

                ans = max(ans, h * (heights[i] - st.top() - 1));
            }
            st.push(i);
        }

        while(st.top()!=-1){
            int h = heights[st.top()];
            st.pop();

            ans = max(ans, h * (n - st.top() - 1));
        }


        return ans;
    }
};

int main() {
    Solution s;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
