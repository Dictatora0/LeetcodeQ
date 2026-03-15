/*
 * LeetCode 155. 最小栈 (Min Stack)
 * 难度：Medium
 *
 * 题目描述：
 * 设计一个支持 push、pop、top 操作，并能在常数时间内检索到最小元素的栈。
 *
 * 实现 MinStack 类：
 * - MinStack() 初始化堆栈对象
 * - void push(int val) 将元素 val 推入堆栈
 * - void pop() 删除堆栈顶部的元素
 * - int top() 获取堆栈顶部的元素
 * - int getMin() 获取堆栈中的最小元素
 *
 * 关键约束：
 * - pop、top 和 getMin 操作总是在非空栈上调用
 * - 所有操作的时间复杂度必须是 O(1)
 *
 * 示例：
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin();   // 返回 -3
 * minStack.pop();
 * minStack.top();      // 返回 0
 * minStack.getMin();   // 返回 -2
 *
 * ============================================================================
 *
 * 核心问题分析：
 *
 * 1. 为什么需要特殊设计？
 *    - 普通栈只能 O(1) 访问栈顶，获取最小值需要 O(n) 遍历
 *    - 需要额外的数据结构来维护最小值信息
 *
 * 2. 设计思路对比：
 *
 *    方法1：辅助栈（推荐）
 *    ┌─────────┐  ┌─────────┐
 *    │  数据栈  │  │  最小栈  │
 *    ├─────────┤  ├─────────┤
 *    │   -3    │  │   -3    │  ← 栈顶
 *    │    0    │  │   -2    │
 *    │   -2    │  │   -2    │
 *    └─────────┘  └─────────┘
 *
 *    优点：思路清晰，易于理解和实现
 *    缺点：空间复杂度 O(n)，最坏情况下需要两倍空间
 *
 *    方法2：单栈差值法
 *    只用一个栈，存储当前值与最小值的差值
 *    优点：空间优化
 *    缺点：实现复杂，需要处理溢出问题
 *
 * 3. 数据结构选择：
 *    - 主栈：vector 或 stack（存储实际数据）
 *    - 辅助栈：vector 或 stack（存储每个状态的最小值）
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

// ============================================================================
// 方法1：辅助栈（双栈法）
// ============================================================================
//
// 算法思路：
// 1. 使用两个栈：数据栈 + 最小值栈
// 2. 数据栈存储所有元素
// 3. 最小值栈存储每个状态下的最小值
// 4. 两个栈同步操作，保持大小一致
//
// 关键点：
// - push 时：最小栈压入 min(val, 当前最小值)
// - pop 时：两个栈同时弹出
// - getMin 时：直接返回最小栈栈顶
//
// 时间复杂度：所有操作 O(1)
// 空间复杂度：O(n)，需要两个栈
//
class MinStack {
private:
    stack<int> dataStack;    // 数据栈：存储所有元素
    stack<int> minStack;     // 最小栈：存储每个状态的最小值

public:
    MinStack() {
        // 构造函数：初始化两个空栈
    }

    void push(int val) {
        // 数据栈直接压入元素
        dataStack.push(val);

        // 最小栈压入当前最小值
        // 如果最小栈为空，或新值更小，压入新值；否则压入当前最小值
        if (minStack.empty()) {
            minStack.push(val);
        } else {
            minStack.push(min(val, minStack.top()));
        }
    }

    void pop() {
        // 两个栈同步弹出
        dataStack.pop();
        minStack.pop();
    }

    int top() {
        // 返回数据栈栈顶
        return dataStack.top();
    }

    int getMin() {
        // 返回最小栈栈顶，即当前状态的最小值
        return minStack.top();
    }
};

// ============================================================================
// 方法2：辅助栈优化版（空间优化）
// ============================================================================
//
// 优化思路：
// 最小栈只在必要时压入元素，减少空间使用
// - 只有当新元素 <= 当前最小值时，才压入最小栈
// - pop 时，只有当弹出元素等于最小值时，才弹出最小栈
//
// 时间复杂度：所有操作 O(1)
// 空间复杂度：O(n)，但平均情况下比方法1节省空间
//
class MinStack2 {
private:
    stack<int> dataStack;
    stack<int> minStack;

public:
    MinStack2() {}

    void push(int val) {
        dataStack.push(val);

        // 只有当新值 <= 当前最小值时，才压入最小栈
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }

    void pop() {
        // 如果弹出的是最小值，最小栈也要弹出
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }

    int top() {
        return dataStack.top();
    }

    int getMin() {
        return minStack.top();
    }
};

// ============================================================================
// 方法3：单栈差值法（高级）
// ============================================================================
//
// 算法思路：
// 1. 只用一个栈，存储当前值与最小值的差值
// 2. 用一个变量 minVal 记录当前最小值
// 3. 当差值为负时，说明遇到了新的最小值
//
// 关键技巧：
// - push(x): 栈中存储 x - minVal
//   - 如果 x < minVal，更新 minVal = x
// - pop(): 如果栈顶 < 0，说明弹出的是最小值
//   - 需要恢复上一个最小值：minVal = minVal - stack.top()
//
// 注意：需要使用 long long 防止溢出
//
// 时间复杂度：所有操作 O(1)
// 空间复杂度：O(n)，只需一个栈
//
class MinStack3 {
private:
    stack<long long> st;
    long long minVal;

public:
    MinStack3() {
        minVal = LLONG_MAX;
    }

    void push(int val) {
        if (st.empty()) {
            st.push(0LL);
            minVal = val;
        } else {
            // 存储差值
            st.push((long long)val - minVal);
            // 如果新值更小，更新最小值
            if (val < minVal) {
                minVal = val;
            }
        }
    }

    void pop() {
        if (st.empty()) return;

        long long diff = st.top();
        st.pop();

        // 如果差值 < 0，说明弹出的是最小值
        // 需要恢复上一个最小值
        if (diff < 0) {
            minVal = minVal - diff;  // minVal = 旧minVal
        }
    }

    int top() {
        long long diff = st.top();
        // 如果差值 < 0，栈顶就是最小值
        if (diff < 0) {
            return (int)minVal;
        }
        // 否则，栈顶 = minVal + diff
        return (int)(minVal + diff);
    }

    int getMin() {
        return (int)minVal;
    }
};

// ============================================================================
// 操作序列演示
// ============================================================================
/*
以方法1为例，演示操作序列：

初始状态：
dataStack: []
minStack:  []

push(-2):
dataStack: [-2]
minStack:  [-2]  // 第一个元素，直接压入

push(0):
dataStack: [-2, 0]
minStack:  [-2, -2]  // min(0, -2) = -2

push(-3):
dataStack: [-2, 0, -3]
minStack:  [-2, -2, -3]  // min(-3, -2) = -3

getMin():
返回 minStack.top() = -3

pop():
dataStack: [-2, 0]
minStack:  [-2, -2]

top():
返回 dataStack.top() = 0

getMin():
返回 minStack.top() = -2
*/

// ============================================================================
// 复杂度分析对比
// ============================================================================
/*
┌──────────┬────────────┬────────────┬────────────────┐
│  方法    │ 时间复杂度  │ 空间复杂度  │     优缺点      │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法1    │   O(1)     │   O(n)     │ 简单清晰，推荐  │
│ 双栈法   │            │            │ 空间稍多       │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法2    │   O(1)     │   O(n)     │ 空间优化       │
│ 优化双栈 │            │  平均更少   │ 实现稍复杂     │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法3    │   O(1)     │   O(n)     │ 空间最优       │
│ 差值法   │            │            │ 实现复杂，需防溢出│
└──────────┴────────────┴────────────┴────────────────┘
*/

// ============================================================================
// 测试用例
// ============================================================================

void testMinStack() {
    cout << "=== 测试 MinStack (方法1：双栈法) ===" << endl;

    MinStack minStack;

    // 测试用例1：基本操作
    cout << "\n测试用例1：基本操作" << endl;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "push(-2), push(0), push(-3)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -3)" << endl;

    minStack.pop();
    cout << "pop()" << endl;
    cout << "top() = " << minStack.top() << " (期望: 0)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -2)" << endl;

    // 测试用例2：重复最小值
    cout << "\n测试用例2：重复最小值" << endl;
    MinStack minStack2;
    minStack2.push(1);
    minStack2.push(1);
    minStack2.push(1);
    cout << "push(1), push(1), push(1)" << endl;
    cout << "getMin() = " << minStack2.getMin() << " (期望: 1)" << endl;
    minStack2.pop();
    cout << "pop()" << endl;
    cout << "getMin() = " << minStack2.getMin() << " (期望: 1)" << endl;

    // 测试用例3：递增序列
    cout << "\n测试用例3：递增序列" << endl;
    MinStack minStack3;
    minStack3.push(1);
    minStack3.push(2);
    minStack3.push(3);
    cout << "push(1), push(2), push(3)" << endl;
    cout << "getMin() = " << minStack3.getMin() << " (期望: 1)" << endl;
    minStack3.pop();
    minStack3.pop();
    cout << "pop(), pop()" << endl;
    cout << "getMin() = " << minStack3.getMin() << " (期望: 1)" << endl;

    // 测试用例4：递减序列
    cout << "\n测试用例4：递减序列" << endl;
    MinStack minStack4;
    minStack4.push(3);
    minStack4.push(2);
    minStack4.push(1);
    cout << "push(3), push(2), push(1)" << endl;
    cout << "getMin() = " << minStack4.getMin() << " (期望: 1)" << endl;
    minStack4.pop();
    cout << "pop()" << endl;
    cout << "getMin() = " << minStack4.getMin() << " (期望: 2)" << endl;
    minStack4.pop();
    cout << "pop()" << endl;
    cout << "getMin() = " << minStack4.getMin() << " (期望: 3)" << endl;
}

void testMinStack2() {
    cout << "\n=== 测试 MinStack2 (方法2：优化双栈) ===" << endl;

    MinStack2 minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "push(-2), push(0), push(-3)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -3)" << endl;

    minStack.pop();
    cout << "pop()" << endl;
    cout << "top() = " << minStack.top() << " (期望: 0)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -2)" << endl;
}

void testMinStack3() {
    cout << "\n=== 测试 MinStack3 (方法3：差值法) ===" << endl;

    MinStack3 minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "push(-2), push(0), push(-3)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -3)" << endl;

    minStack.pop();
    cout << "pop()" << endl;
    cout << "top() = " << minStack.top() << " (期望: 0)" << endl;
    cout << "getMin() = " << minStack.getMin() << " (期望: -2)" << endl;
}

int main() {
    testMinStack();
    testMinStack2();
    testMinStack3();

    return 0;
}

/*
设计要点总结：

1. 数据结构选择：
   - 双栈法是最直观的解决方案
   - 辅助栈同步维护最小值信息
   - 空间换时间，保证 O(1) 操作

2. 关键技巧：
   - 最小栈存储"当前状态"的最小值
   - 每次 push 时更新最小值
   - 每次 pop 时自动恢复上一个状态

3. 优化方向：
   - 方法2：减少最小栈的元素数量
   - 方法3：使用差值法，只用一个栈

4. 边界情况：
   - 空栈时的操作（题目保证不会发生）
   - 重复最小值的处理
   - 整数溢出（差值法需要注意）

5. 实际应用：
   - 股票价格监控（实时最低价）
   - 滑动窗口最小值
   - 表达式求值中的最小值追踪
*/
