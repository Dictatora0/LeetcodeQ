/*
 * LeetCode 232. 用栈实现队列 (Implement Queue using Stacks)
 * 难度：Easy
 *
 * 题目描述：
 * 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作。
 *
 * 实现 MyQueue 类：
 * - void push(int x) 将元素 x 推到队列的末尾
 * - int pop() 从队列的开头移除并返回元素
 * - int peek() 返回队列开头的元素
 * - boolean empty() 如果队列为空，返回 true；否则，返回 false
 *
 * 说明：
 * - 你只能使用标准的栈操作（push to top, peek/pop from top, size, is empty）
 * - 你所使用的语言也许不支持栈，可以使用 list 或者 deque 来模拟一个栈
 *
 * 进阶：
 * - 你能否实现每个操作均摊时间复杂度为 O(1) 的队列？
 * - 换句话说，执行 n 个操作的总时间复杂度为 O(n)，即使其中一个操作可能花费较长时间
 *
 * 示例：
 * MyQueue myQueue = new MyQueue();
 * myQueue.push(1);
 * myQueue.push(2);
 * myQueue.peek();    // 返回 1
 * myQueue.pop();     // 返回 1
 * myQueue.empty();   // 返回 false
 *
 * ============================================================================
 *
 * 核心问题分析：
 *
 * 1. 栈与队列的本质区别：
 *    栈 (Stack):  LIFO (Last In First Out)  后进先出
 *    队列 (Queue): FIFO (First In First Out) 先进先出
 *
 *    如何用 LIFO 实现 FIFO？
 *    关键：利用两次反转！
 *
 * 2. 双栈法的核心思想：
 *
 *    输入栈 (inStack)：负责接收新元素
 *    输出栈 (outStack)：负责输出元素
 *
 *    可视化：
 *    push(1), push(2), push(3)
 *
 *    inStack:        outStack:
 *    ┌───┐          ┌───┐
 *    │ 3 │ ← top    │   │
 *    ├───┤          └───┘
 *    │ 2 │
 *    ├───┤
 *    │ 1 │
 *    └───┘
 *
 *    当需要 pop/peek 时，如果 outStack 为空：
 *    将 inStack 的所有元素倒入 outStack
 *
 *    inStack:        outStack:
 *    ┌───┐          ┌───┐
 *    │   │          │ 1 │ ← top (最先进入的元素)
 *    └───┘          ├───┤
 *                   │ 2 │
 *                   ├───┤
 *                   │ 3 │
 *                   └───┘
 *
 * 3. 为什么是均摊 O(1)？
 *    - 每个元素最多被移动两次（inStack → outStack）
 *    - n 个操作，总共最多 2n 次移动
 *    - 均摊下来每个操作 O(1)
 *
 * ============================================================================
 */

#include <iostream>
#include <stack>

using namespace std;

// ============================================================================
// 方法1：双栈法（推荐，均摊 O(1)）
// ============================================================================
//
// 算法思路：
// 1. 使用两个栈：输入栈 + 输出栈
// 2. push 操作：直接压入输入栈
// 3. pop/peek 操作：
//    - 如果输出栈不为空，直接操作输出栈
//    - 如果输出栈为空，将输入栈的所有元素倒入输出栈
//
// 关键点：
// - 输入栈：新元素总是压入这里
// - 输出栈：只有当它为空时，才从输入栈倒入元素
// - 这样保证了元素的顺序正确
//
// 时间复杂度：
// - push: O(1)
// - pop/peek: 均摊 O(1)，最坏情况 O(n)
// 空间复杂度：O(n)
//
class MyQueue {
private:
    stack<int> inStack;   // 输入栈：接收新元素
    stack<int> outStack;  // 输出栈：输出元素

    // 辅助函数：将输入栈的元素倒入输出栈
    void in2out() {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    MyQueue() {
        // 构造函数：初始化两个空栈
    }

    // 将元素 x 推到队列的末尾
    void push(int x) {
        // 直接压入输入栈
        inStack.push(x);
    }

    // 从队列的开头移除并返回元素
    int pop() {
        // 如果输出栈为空，先将输入栈的元素倒入
        if (outStack.empty()) {
            in2out();
        }
        // 弹出输出栈的栈顶元素
        int val = outStack.top();
        outStack.pop();
        return val;
    }

    // 返回队列开头的元素
    int peek() {
        // 如果输出栈为空，先将输入栈的元素倒入
        if (outStack.empty()) {
            in2out();
        }
        // 返回输出栈的栈顶元素
        return outStack.top();
    }

    // 如果队列为空，返回 true；否则，返回 false
    bool empty() {
        // 两个栈都为空时，队列才为空
        return inStack.empty() && outStack.empty();
    }
};

// ============================================================================
// 方法2：单栈递归法（不推荐，仅作学习）
// ============================================================================
//
// 算法思路：
// 只使用一个栈，通过递归来实现队列的 pop 操作
// - push: 直接压入栈
// - pop: 递归地取出栈底元素
//
// 缺点：
// - pop 操作时间复杂度 O(n)，不是均摊 O(1)
// - 递归深度可能很大，栈溢出风险
//
// 时间复杂度：
// - push: O(1)
// - pop/peek: O(n)
// 空间复杂度：O(n)
//
class MyQueue2 {
private:
    stack<int> st;

    // 递归地移除并返回栈底元素
    int popBottom() {
        int top = st.top();
        st.pop();

        if (st.empty()) {
            // 栈底元素
            return top;
        }

        // 递归获取栈底元素
        int bottom = popBottom();
        // 将当前元素重新压入栈
        st.push(top);
        return bottom;
    }

public:
    MyQueue2() {}

    void push(int x) {
        st.push(x);
    }

    int pop() {
        return popBottom();
    }

    int peek() {
        int val = popBottom();
        st.push(val);  // 重新压入
        return val;
    }

    bool empty() {
        return st.empty();
    }
};

// ============================================================================
// 操作序列演示（方法1：双栈法）
// ============================================================================
/*
初始状态：
inStack:  []
outStack: []

操作1: push(1)
inStack:  [1]
outStack: []

操作2: push(2)
inStack:  [1, 2]  (2 在栈顶)
outStack: []

操作3: push(3)
inStack:  [1, 2, 3]  (3 在栈顶)
outStack: []

操作4: peek()
- outStack 为空，触发 in2out()
- 将 inStack 的元素依次弹出并压入 outStack
  - 弹出 3，压入 outStack
  - 弹出 2，压入 outStack
  - 弹出 1，压入 outStack

inStack:  []
outStack: [3, 2, 1]  (1 在栈顶)
返回 outStack.top() = 1

操作5: pop()
- outStack 不为空，直接弹出栈顶
inStack:  []
outStack: [3, 2]  (2 在栈顶)
返回 1

操作6: push(4)
inStack:  [4]
outStack: [3, 2]  (2 在栈顶)

操作7: pop()
- outStack 不为空，直接弹出栈顶
inStack:  [4]
outStack: [3]  (3 在栈顶)
返回 2

操作8: pop()
- outStack 不为空，直接弹出栈顶
inStack:  [4]
outStack: []
返回 3

操作9: pop()
- outStack 为空，触发 in2out()
inStack:  []
outStack: [4]
返回 4
*/

// ============================================================================
// 均摊分析
// ============================================================================
/*
为什么是均摊 O(1)？

考虑 n 个操作的序列：
1. 每个元素最多被移动 2 次：
   - 第 1 次：push 到 inStack
   - 第 2 次：从 inStack 移到 outStack

2. 总操作次数分析：
   - n 次 push：每次 O(1)，总共 O(n)
   - n 次 pop：虽然单次可能 O(n)，但总共最多移动 n 个元素，总共 O(n)
   - 总时间：O(n) + O(n) = O(2n) = O(n)
   - 均摊到每个操作：O(n) / n = O(1)

3. 最坏情况分析：
   - 连续 push n 个元素：O(n)
   - 第一次 pop：需要移动 n 个元素，O(n)
   - 后续 n-1 次 pop：每次 O(1)
   - 总时间：O(n) + O(n) + O(n-1) = O(3n) = O(n)
   - 均摊：O(1)

示例：
操作序列：push(1), push(2), push(3), pop(), pop(), pop()

push(1): 1 次操作
push(2): 1 次操作
push(3): 1 次操作
pop():   3 次操作 (移动 3 个元素) + 1 次弹出 = 4 次操作
pop():   1 次操作
pop():   1 次操作

总共：1 + 1 + 1 + 4 + 1 + 1 = 9 次操作
6 个操作，均摊：9 / 6 = 1.5 次操作/每个操作 = O(1)
*/

// ============================================================================
// 复杂度分析对比
// ============================================================================
/*
┌──────────┬────────────┬────────────┬────────────────┐
│  方法    │ push       │ pop/peek   │     优缺点      │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法1    │   O(1)     │ 均摊 O(1)  │ 推荐，最优解    │
│ 双栈法   │            │ 最坏 O(n)  │ 空间 O(n)      │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法2    │   O(1)     │   O(n)     │ 不推荐         │
│ 单栈递归 │            │            │ 递归深度大     │
└──────────┴────────────┴────────────┴────────────────┘

空间复杂度：两种方法都是 O(n)
*/

// ============================================================================
// 测试用例
// ============================================================================

void testMyQueue() {
    cout << "=== 测试 MyQueue (方法1：双栈法) ===" << endl;

    MyQueue myQueue;

    // 测试用例1：基本操作
    cout << "\n测试用例1：基本操作" << endl;
    myQueue.push(1);
    myQueue.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "peek() = " << myQueue.peek() << " (期望: 1)" << endl;
    cout << "pop() = " << myQueue.pop() << " (期望: 1)" << endl;
    cout << "empty() = " << (myQueue.empty() ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例2：交替 push 和 pop
    cout << "\n测试用例2：交替 push 和 pop" << endl;
    MyQueue myQueue2;
    myQueue2.push(1);
    myQueue2.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "pop() = " << myQueue2.pop() << " (期望: 1)" << endl;
    myQueue2.push(3);
    cout << "push(3)" << endl;
    cout << "pop() = " << myQueue2.pop() << " (期望: 2)" << endl;
    cout << "pop() = " << myQueue2.pop() << " (期望: 3)" << endl;
    cout << "empty() = " << (myQueue2.empty() ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例3：大量操作
    cout << "\n测试用例3：大量操作" << endl;
    MyQueue myQueue3;
    for (int i = 1; i <= 5; i++) {
        myQueue3.push(i);
    }
    cout << "push(1) ~ push(5)" << endl;
    cout << "依次 pop: ";
    while (!myQueue3.empty()) {
        cout << myQueue3.pop() << " ";
    }
    cout << "(期望: 1 2 3 4 5)" << endl;

    // 测试用例4：peek 不改变队列
    cout << "\n测试用例4：peek 不改变队列" << endl;
    MyQueue myQueue4;
    myQueue4.push(1);
    myQueue4.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "peek() = " << myQueue4.peek() << " (期望: 1)" << endl;
    cout << "peek() = " << myQueue4.peek() << " (期望: 1)" << endl;
    cout << "pop() = " << myQueue4.pop() << " (期望: 1)" << endl;
}

void testMyQueue2() {
    cout << "\n=== 测试 MyQueue2 (方法2：单栈递归) ===" << endl;

    MyQueue2 myQueue;
    myQueue.push(1);
    myQueue.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "peek() = " << myQueue.peek() << " (期望: 1)" << endl;
    cout << "pop() = " << myQueue.pop() << " (期望: 1)" << endl;
    cout << "empty() = " << (myQueue.empty() ? "true" : "false") << " (期望: false)" << endl;
}

int main() {
    testMyQueue();
    testMyQueue2();

    return 0;
}

/*
设计要点总结：

1. 核心思想：
   - 用两个栈模拟队列的 FIFO 特性
   - 输入栈负责接收，输出栈负责输出
   - 利用两次反转实现顺序转换

2. 关键技巧：
   - 延迟转移：只有当输出栈为空时才转移元素
   - 批量转移：一次性转移所有元素，减少操作次数
   - 均摊分析：每个元素最多移动两次

3. 优化要点：
   - 不要每次 pop/peek 都转移元素
   - 充分利用输出栈中已有的元素
   - 保持两个栈的职责分离

4. 边界情况：
   - 空队列的 pop/peek（题目保证不会发生）
   - 单个元素的队列
   - 交替 push 和 pop

5. 实际应用：
   - 理解栈和队列的本质区别
   - 学习均摊分析的方法
   - 数据结构转换的经典案例

6. 扩展思考：
   - 如果要求 push 也是均摊 O(1)，如何设计？
   - 如果用队列实现栈，如何设计？（LeetCode 225）
   - 如果要求线程安全，如何加锁？
*/
