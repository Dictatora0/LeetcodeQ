#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MinStack {
public:
    stack<int> st;
    stack<int> minSt;

    MinStack() {
    }

    void push(int val) {
        st.push(val);

        if (minSt.empty()) {
            minSt.push(val);
        } else {
            minSt.push(min(val, minSt.top()));
        }
    }

    void pop() {
        st.pop();
        minSt.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minSt.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
int main() {
    MinStack s;

    cout << INT16_MIN << endl;
    // TODO: 添加测试用例
    
    return 0;
}
