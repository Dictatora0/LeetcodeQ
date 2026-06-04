/*
题目 / 示例名称：C++ 笔试复习工具箱
核心知识点：ACM 模板、排序、字符串、前缀和、哈希、栈队列、位运算、二分、gcd/lcm、DFS/BFS
适用场景：笔试前 10 分钟快速翻看常用片段；答题时复制最稳妥的模板
关键思路：把高频片段拆成若干个小函数，保证文件本身可编译，同时便于直接摘取
时间复杂度：本文件是片段合集，不对应单一复杂度
空间复杂度：本文件是片段合集，不对应单一复杂度
常见错误：
1. 只记模板，不理解什么时候能用。
2. 混淆 0-based 和 1-based 前缀和写法。
3. 比较器写成 `<=` 或 `>=`。
4. 位运算忘记给字面量加 `1LL`。
示例输入：
无
示例输出：
toolbox ready
手动推演：
本文件不是刷题题解，而是“能复制的骨架 + 为什么这样写”。
对比说明：
- 真题文件用于完整训练。
- 本文件用于快速查阅，不追求单一题目的完整输入输出。
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace toolbox {

// ------------------------------------------------------------------
// 1. 基础输入输出
// ------------------------------------------------------------------
void ioTemplateNotes() {
    /*
    单组数据模板：
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    多组数据模板：
    int t;
    cin >> t;
    while (t--) {
        // 把每组变量定义在这里，避免忘记重置
    }
    */
}

// ------------------------------------------------------------------
// 2. 常用类型
// ------------------------------------------------------------------
void typeNotes() {
    /*
    int:
      适合题目明确保证范围在 2e9 内的单个数、下标、长度。
    long long:
      适合总和、乘积、前缀和、答案可能到 1e12 以上的情况。
    unsigned long long:
      更偏底层位运算题，普通笔试里不必强行使用。
    string:
      字符串遍历、双指针、哈希统计。
    vector<int> / vector<long long>:
      动态数组，比赛里最常用。
    pair<int, int>:
      常用于坐标、区间端点、队列中的状态。
    */
}

// ------------------------------------------------------------------
// 3. 排序
// ------------------------------------------------------------------
struct Student {
    string name;
    int score;
    int id;
};

bool compareStudent(const Student& a, const Student& b) {
    // compare(a, b) 返回 true，表示 a 应排在 b 前面。
    // 本题先按分数降序，再按 id 升序。
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.id < b.id;
}

void sortNotes() {
    vector<int> a = {4, 1, 3, 2};
    sort(a.begin(), a.end());
    sort(a.begin(), a.end(), greater<int>());

    vector<Student> students = {
        {"alice", 90, 2},
        {"bob", 90, 1},
        {"cindy", 85, 3}
    };
    sort(students.begin(), students.end(), compareStudent);

    (void)a;
    (void)students;
}

// ------------------------------------------------------------------
// 4. 字符串遍历
// ------------------------------------------------------------------
void stringNotes() {
    string s = "aabB19";
    vector<int> freq(26, 0);
    int digits = 0;

    for (char ch : s) {
        if ('a' <= ch && ch <= 'z') {
            ++freq[ch - 'a'];
        } else if ('0' <= ch && ch <= '9') {
            ++digits;
        }
    }

    (void)freq;
    (void)digits;
}

// ------------------------------------------------------------------
// 5. 前缀和
// ------------------------------------------------------------------
vector<long long> buildPrefix(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    vector<long long> prefix(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        // 1-based 写法最适合区间和：sum[l..r] = prefix[r] - prefix[l - 1]
        prefix[i] = prefix[i - 1] + a[i - 1];
    }

    return prefix;
}

long long rangeSum(const vector<long long>& prefix, int l, int r) {
    return prefix[r] - prefix[l - 1];
}

// ------------------------------------------------------------------
// 6. 哈希表与集合
// ------------------------------------------------------------------
void hashNotes() {
    unordered_map<int, int> frequency;
    unordered_set<int> seen;

    vector<int> a = {2, 2, 5, 7, 7, 7};
    for (int x : a) {
        ++frequency[x];
        seen.insert(x);
    }

    (void)frequency;
    (void)seen;
}

// ------------------------------------------------------------------
// 7. 栈与队列
// ------------------------------------------------------------------
bool singleBracketValid(const string& s) {
    int balance = 0;
    for (char ch : s) {
        if (ch == '(') {
            ++balance;
        } else {
            --balance;
        }
        if (balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

bool multiBracketValid(const string& s) {
    stack<char> st;
    unordered_map<char, char> match = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else {
            if (st.empty() || st.top() != match[ch]) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

void queueNotes() {
    queue<int> q;
    q.push(3);
    q.push(5);
    if (!q.empty()) {
        q.pop();
    }
}

// ------------------------------------------------------------------
// 8. 位运算
// ------------------------------------------------------------------
long long setBit(long long x, int k) {
    return x | (1LL << k);
}

long long clearBit(long long x, int k) {
    return x & ~(1LL << k);
}

long long toggleBit(long long x, int k) {
    return x ^ (1LL << k);
}

int getBit(long long x, int k) {
    return static_cast<int>((x >> k) & 1LL);
}

int popcountByRemovingLowestOne(long long x) {
    int count = 0;
    while (x > 0) {
        // x & (x - 1) 会把最低位的一个 1 删除。
        // 例如 101100 -> 101000。
        x = x & (x - 1);
        ++count;
    }
    return count;
}

long long lowbit(long long x) {
    // x & (-x) 只保留最低位的 1。
    // 例如 12 的二进制是 1100，lowbit(12) = 0100 = 4。
    return x & (-x);
}

// ------------------------------------------------------------------
// 9. 二分查找
// ------------------------------------------------------------------
int binarySearchExact(const vector<int>& a, int target) {
    int left = 0;
    int right = static_cast<int>(a.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) {
            return mid;
        }
        if (a[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int firstPositionGE(const vector<int>& a, int target) {
    int left = 0;
    int right = static_cast<int>(a.size());

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

// ------------------------------------------------------------------
// 10. gcd 与 lcm
// ------------------------------------------------------------------
long long safeLcm(long long a, long long b) {
    long long g = gcd(a, b);
    // 先除再乘，避免 a * b 直接溢出。
    return a / g * b;
}

// ------------------------------------------------------------------
// 11. DFS 与 BFS 基础框架
// ------------------------------------------------------------------
const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

void dfsGrid(int x, int y,
             const vector<string>& grid,
             vector<vector<int>>& visited) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    visited[x][y] = 1;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + DX[dir];
        int ny = y + DY[dir];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            continue;
        }
        if (visited[nx][ny] || grid[nx][ny] == '#') {
            continue;
        }
        dfsGrid(nx, ny, grid, visited);
    }
}

int bfsGridShortestPath(const vector<string>& grid,
                        pair<int, int> start,
                        pair<int, int> target) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        if (current == target) {
            return dist[current.first][current.second];
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = current.first + DX[dir];
            int ny = current.second + DY[dir];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (grid[nx][ny] == '#' || dist[nx][ny] != -1) {
                continue;
            }

            dist[nx][ny] = dist[current.first][current.second] + 1;
            q.push({nx, ny});
        }
    }

    return -1;
}

// ------------------------------------------------------------------
// 12. 常见防错提醒
// ------------------------------------------------------------------
void checklistNotes() {
    /*
    - 多组数据变量要重置
    - 数组下标别越界
    - int 求和和乘法容易溢出
    - 整数除法会直接截断
    - 比较器不能写 <= 或 >=
    - 读题时先看数据范围
    - 输出格式要和题面完全一致
    - 循环边界 < 与 <= 不要混
    */
}

}  // namespace toolbox

int main() {
    cout << "toolbox ready\n";
    return 0;
}
