#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(),0);
        stack<int> st;

        for (int i = 0; i < temperatures.size();i++){
            while(!st.empty()&&temperatures[i]>temperatures[st.top()]){
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
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
