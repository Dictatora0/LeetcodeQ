/*
 * LeetCode 225. 用队列实现栈 (Implement Stack using Queues)
 * 难度：Easy
 *
 * 题目描述：
 * 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作。
 *
 * 实现 MyStack 类：
 * - void push(int x) 将元素 x 压入栈顶
 * - int pop() 移除并返回栈顶元素
 * - int top() 返回栈顶元素
 * - boolean empty() 如果栈是空的，返回 true；否则，返回 false
 *
 * 注意：
 * - 你只能使用队列的基本操作（push to back, peek/pop from front, size, is empty）
 * - 你所使用的语言也许不支持队列，可以使用 list 或者 deque 来模拟一个队列
 *
 * 进阶：
 * - 你能否仅用一个队列来实现栈？
 *
 * 示例：
 * MyStack myStack = new MyStack();
 * myStack.push(1);
 * myStack.push(2);
 * myStack.top();     // 返回 2
 * myStack.pop();     // 返回 2
 * myStack.empty();   // 返回 false
 *
 * ============================================================================
 *
 * 核心问题分析：
 *
 * 1. 队列与栈的本质区别：
 *    队列 (Queue): FIFO (First In First Out)  先进先出
 *    栈 (Stack):   LIFO (Last In First Out)   后进先出
 *
 *    如何用 FIFO 实现 LIFO？
 *    关键：调整元素顺序！
 *
 * 2. 单队列法的核心思想（最优解）：
 *
 *    push 操作时调整顺序，使得队首始终是最新元素
 *
 *    示例：push(1), push(2), push(3)
 *
 *    push(1):
 *    队列: [1]
 *
 *    push(2):
 *    - 先将 2 入队: [1, 2]
 *    - 将前面的元素（1）重新入队: [2, 1]
 *    结果: [2, 1]  (2 在队首)
 *
 *    push(3):
 *    - 先将 3 入队: [2, 1, 3]
 *    - 将前面的元素（2, 1）重新入队: [3, 2, 1]
 *    结果: [3, 2, 1]  (3 在队首)
 *
 *    pop/top 操作：直接操作队首即可
 *
 * 3. 双队列法的思想：
 *    - 一个队列存储数据
 *    - pop 时，将 n-1 个元素转移到另一个队列
 *    - 剩下的最后一个元素就是栈顶
 *
 * ============================================================================
 */

#include <iostream>
#include <queue>

using namespace std;

// ============================================================================
// 方法1：单队列法（推荐，最优解）
// ============================================================================
//
// 算法思路：
// 1. 只使用一个队列
// 2. push 操作：将新元素入队后，将前面的所有元素依次出队再入队
//    - 这样新元素就到了队首位置
// 3. pop/top 操作：直接操作队首
//
// 关键点：
// - push 时调整顺序，让最新元素在队首
// - 每次 push 需要移动 n-1 个元素（n 是 push 前的队列大小）
//
// 时间复杂度：
// - push: O(n)
// - pop/top/empty: O(1)
// 空间复杂度：O(n)
//
class MyStack {
private:
    queue<int> q;

public:
    MyStack() {
        // 构造函数：初始化空队列
    }

    // 将元素 x 压入栈顶
    void push(int x) {
        int n = q.size();  // 记录当前队列大小
        q.push(x);         // 新元素入队

        // 将前面的 n 个元素依次出队再入队
        // 这样新元素就到了队首
        for (int i = 0; i < n; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    // 移除并返回栈顶元素
    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    // 返回栈顶元素
    int top() {
        return q.front();
    }

    // 如果栈是空的，返回 true；否则，返回 false
    bool empty() {
        return q.empty();
    }
};

// ============================================================================
// 方法2：双队列法
// ============================================================================
//
// 算法思路：
// 1. 使用两个队列：q1 和 q2
// 2. push 操作：直接入队到 q1
// 3. pop 操作：
//    - 将 q1 的前 n-1 个元素转移到 q2
//    - q1 剩下的最后一个元素就是栈顶，弹出它
//    - 交换 q1 和 q2
//
// 时间复杂度：
// - push: O(1)
// - pop: O(n)
// - top: O(n)
// 空间复杂度：O(n)
//
class MyStack2 {
private:
    queue<int> q1;
    queue<int> q2;

public:
    MyStack2() {}

    void push(int x) {
        q1.push(x);
    }

    int pop() {
        // 将 q1 的前 n-1 个元素转移到 q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        // q1 剩下的最后一个元素就是栈顶
        int val = q1.front();
        q1.pop();

        // 交换 q1 和 q2
        swap(q1, q2);

        return val;
    }

    int top() {
        // 将 q1 的前 n-1 个元素转移到 q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        // q1 剩下的最后一个元素就是栈顶
        int val = q1.front();

        // 将栈顶元素也转移到 q2
        q2.push(val);
        q1.pop();

        // 交换 q1 和 q2
        swap(q1, q2);

        return val;
    }

    bool empty() {
        return q1.empty();
    }
};

// ============================================================================
// 方法3：双队列优化版（push 时调整）
// ============================================================================
//
// 算法思路：
// 1. 使用两个队列：q1 和 q2
// 2. push 操作：
//    - 新元素入队到 q2
//    - 将 q1 的所有元素转移到 q2
//    - 交换 q1 和 q2
// 3. pop/top 操作：直接操作 q1 的队首
//
// 时间复杂度：
// - push: O(n)
// - pop/top: O(1)
// 空间复杂度：O(n)
//
class MyStack3 {
private:
    queue<int> q1;
    queue<int> q2;

public:
    MyStack3() {}

    void push(int x) {
        // 新元素入队到 q2
        q2.push(x);

        // 将 q1 的所有元素转移到 q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // 交换 q1 和 q2
        swap(q1, q2);
    }

    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }

    int top() {
        return q1.front();
    }

    bool empty() {
        return q1.empty();
    }
};

// ============================================================================
// 操作序列演示（方法1：单队列法）
// ============================================================================
/*
初始状态：
q: []

操作1: push(1)
- 入队 1: [1]
- 前面有 0 个元素，不需要调整
q: [1]  (队首 → 队尾)

操作2: push(2)
- 入队 2: [1, 2]
- 前面有 1 个元素，需要调整
  - 将 1 出队再入队: [2, 1]
q: [2, 1]  (2 在队首)

操作3: push(3)
- 入队 3: [2, 1, 3]
- 前面有 2 个元素，需要调整
  - 将 2 出队再入队: [1, 3, 2]
  - 将 1 出队再入队: [3, 2, 1]
q: [3, 2, 1]  (3 在队首)

操作4: top()
- 返回队首元素
返回 3

操作5: pop()
- 弹出队首元素
q: [2, 1]
返回 3

操作6: push(4)
- 入队 4: [2, 1, 4]
- 前面有 2 个元素，需要调整
  - 将 2 出队再入队: [1, 4, 2]
  - 将 1 出队再入队: [4, 2, 1]
q: [4, 2, 1]  (4 在队首)

操作7: pop()
q: [2, 1]
返回 4
*/

// ============================================================================
// 复杂度分析对比
// ============================================================================
/*
┌──────────┬────────────┬────────────┬────────────────┐
│  方法    │ push       │ pop/top    │     优缺点      │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法1    │   O(n)     │   O(1)     │ 推荐，代码简洁  │
│ 单队列   │            │            │ 只需一个队列    │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法2    │   O(1)     │   O(n)     │ pop 操作慢     │
│ 双队列   │            │            │ 需要两个队列    │
├──────────┼────────────┼────────────┼────────────────┤
│ 方法3    │   O(n)     │   O(1)     │ 与方法1等价    │
│ 双队列优化│           │            │ 代码稍复杂     │
└──────────┴────────────┴────────────┴────────────────┘

空间复杂度：所有方法都是 O(n)

选择建议：
- 如果 push 操作频繁，选择方法2
- 如果 pop/top 操作频繁，选择方法1
- 一般情况下，推荐方法1（代码最简洁）
*/

// ============================================================================
// 与 LeetCode 232 的对比
// ============================================================================
/*
LeetCode 232: 用栈实现队列
- 双栈法可以实现均摊 O(1) 的所有操作
- 关键：延迟转移，批量处理

LeetCode 225: 用队列实现栈
- 无法实现所有操作都是 O(1)
- 必须在 push 或 pop 时付出 O(n) 的代价
- 原因：队列的 FIFO 特性与栈的 LIFO 特性差异更大

为什么 232 可以均摊 O(1)，而 225 不行？
- 232: 元素可以在输出栈中"停留"，不需要每次都转移
- 225: 每次操作都需要调整顺序，无法"复用"之前的调整

数据结构的本质：
- 栈：只能访问一端（栈顶）
- 队列：可以访问两端（队首和队尾）
- 队列的灵活性更高，所以用栈实现队列更容易
*/

// ============================================================================
// 测试用例
// ============================================================================

void testMyStack() {
    cout << "=== 测试 MyStack (方法1：单队列法) ===" << endl;

    MyStack myStack;

    // 测试用例1：基本操作
    cout << "\n测试用例1：基本操作" << endl;
    myStack.push(1);
    myStack.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "top() = " << myStack.top() << " (期望: 2)" << endl;
    cout << "pop() = " << myStack.pop() << " (期望: 2)" << endl;
    cout << "empty() = " << (myStack.empty() ? "true" : "false") << " (期望: false)" << endl;

    // 测试用例2：交替 push 和 pop
    cout << "\n测试用例2：交替 push 和 pop" << endl;
    MyStack myStack2;
    myStack2.push(1);
    myStack2.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "pop() = " << myStack2.pop() << " (期望: 2)" << endl;
    myStack2.push(3);
    cout << "push(3)" << endl;
    cout << "pop() = " << myStack2.pop() << " (期望: 3)" << endl;
    cout << "pop() = " << myStack2.pop() << " (期望: 1)" << endl;
    cout << "empty() = " << (myStack2.empty() ? "true" : "false") << " (期望: true)" << endl;

    // 测试用例3：大量操作
    cout << "\n测试用例3：大量操作" << endl;
    MyStack myStack3;
    for (int i = 1; i <= 5; i++) {
        myStack3.push(i);
    }
    cout << "push(1) ~ push(5)" << endl;
    cout << "依次 pop: ";
    while (!myStack3.empty()) {
        cout << myStack3.pop() << " ";
    }
    cout << "(期望: 5 4 3 2 1)" << endl;

    // 测试用例4：top 不改变栈
    cout << "\n测试用例4：top 不改变栈" << endl;
    MyStack myStack4;
    myStack4.push(1);
    myStack4.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "top() = " << myStack4.top() << " (期望: 2)" << endl;
    cout << "top() = " << myStack4.top() << " (期望: 2)" << endl;
    cout << "pop() = " << myStack4.pop() << " (期望: 2)" << endl;
}

void testMyStack2() {
    cout << "\n=== 测试 MyStack2 (方法2：双队列法) ===" << endl;

    MyStack2 myStack;
    myStack.push(1);
    myStack.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "top() = " << myStack.top() << " (期望: 2)" << endl;
    cout << "pop() = " << myStack.pop() << " (期望: 2)" << endl;
    cout << "empty() = " << (myStack.empty() ? "true" : "false") << " (期望: false)" << endl;
}

void testMyStack3() {
    cout << "\n=== 测试 MyStack3 (方法3：双队列优化版) ===" << endl;

    MyStack3 myStack;
    myStack.push(1);
    myStack.push(2);
    cout << "push(1), push(2)" << endl;
    cout << "top() = " << myStack.top() << " (期望: 2)" << endl;
    cout << "pop() = " << myStack.pop() << " (期望: 2)" << endl;
    cout << "empty() = " << (myStack.empty() ? "true" : "false") << " (期望: false)" << endl;
}

int main() {
    testMyStack();
    testMyStack2();
    testMyStack3();

    return 0;
}

/*
设计要点总结：

1. 核心思想：
   - 用队列的 FIFO 特性模拟栈的 LIFO 特性
   - 关键是调整元素顺序
   - 单队列法：push 时调整
   - 双队列法：pop 时调整

2. 关键技巧：
   - 单队列法：每次 push 后，将前面的元素重新入队
   - 双队列法：pop 时，将 n-1 个元素转移到另一个队列
   - 选择在哪个操作上付出 O(n) 的代价

3. 优化要点：
   - 单队列法代码最简洁，推荐使用
   - 根据实际使用场景选择优化方向
   - push 频繁 → 优化 push（方法2）
   - pop 频繁 → 优化 pop（方法1）

4. 边界情况：
   - 空栈的 pop/top（题目保证不会发生）
   - 单个元素的栈
   - 交替 push 和 pop

5. 实际应用：
   - 理解数据结构的本质特性
   - 学习如何在不同操作间权衡时间复杂度
   - 数据结构转换的经典案例

6. 与 LeetCode 232 的对比：
   - 232 可以实现均摊 O(1)，225 不行
   - 原因：队列比栈更灵活（可以访问两端）
   - 用栈实现队列比用队列实现栈更容易
*/
