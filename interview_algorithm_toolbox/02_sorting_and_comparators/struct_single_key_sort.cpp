/*
题目 / 示例名称：结构体按单关键字排序
核心知识点：结构体、普通比较函数、单关键字排序
适用场景：需要按成绩、长度、时间等一个主键排序
关键思路：定义结构体保存信息，再写 `compareStudent` 表示“谁应该排前面”
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 比较器参数不写 `const &`，产生不必要拷贝。
2. 比较器返回 `a.score >= b.score`，破坏严格弱序。
3. 忘记考虑主键相等时是否需要稳定输出。
示例输入：
3
alice 82
bob 95
cindy 90
示例输出：
bob 95
cindy 90
alice 82
手动推演：
按 score 降序，所以 95 在最前，82 在最后。
对比说明：
- 普通函数比较器最适合教学和笔试复盘。
- Lambda 也能写，但这里优先展示更容易讲清楚的版本。
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    int score;
};

bool compareStudent(const Student& a, const Student& b) {
    // compare(a, b) 为 true，表示 a 应排在 b 前面。
    return a.score > b.score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        cin >> students[i].name >> students[i].score;
    }

    sort(students.begin(), students.end(), compareStudent);

    for (const Student& student : students) {
        cout << student.name << ' ' << student.score << '\n';
    }

    return 0;
}
