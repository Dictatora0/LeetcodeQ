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
        // 这是最常见的“前面补一个 0”的写法。
        // prefix[i] 表示前 i 个元素的和，也就是 a[0] 到 a[i - 1] 的和。
        // 这种写法的好处是：
        // 1. 区间和公式统一
        // 2. l = 1 时不用单独特判
        // 3. 笔试里最稳
        //
        // 如果题目区间下标按 1-based 给出：
        // sum[l..r] = prefix[r] - prefix[l - 1]
        prefix[i] = prefix[i - 1] + a[i - 1];
    }

    return prefix;
}

long long rangeSum(const vector<long long>& prefix, int l, int r) {
    return prefix[r] - prefix[l - 1];
}

vector<long long> buildPrefixZeroBased(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    vector<long long> prefix(n, 0);

    if (n == 0) {
        return prefix;
    }

    // 0-based 写法里，prefix[i] 表示 a[0..i] 的区间和。
    // 这套写法和很多题目的数组下标风格一致，但查询时要记得处理 l = 0。
    prefix[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i - 1] + a[i];
    }

    return prefix;
}

long long rangeSumZeroBased(const vector<long long>& prefix, int l, int r) {
    // 0-based 区间和公式：
    // 1. 如果 l == 0，答案就是 prefix[r]
    // 2. 否则答案是 prefix[r] - prefix[l - 1]
    //
    // 例如数组 a = [3, 1, 4, 2]
    // prefix = [3, 4, 8, 10]
    // sum[1..3] = 1 + 4 + 2 = 7
    // 对应 prefix[3] - prefix[0] = 10 - 3 = 7
    if (l == 0) {
        return prefix[r];
    }
    return prefix[r] - prefix[l - 1];
}

void prefixSumNotes() {
    /*
    前缀和的核心思想：
    prefix[i] 记录“前面这一段的累计和”，这样多次区间求和可以 O(1) 查询。

    两套最常见写法：

    1. 1-based 风格（最推荐笔试优先写）
       vector<long long> prefix(n + 1, 0);
       for (int i = 1; i <= n; ++i) {
           prefix[i] = prefix[i - 1] + a[i - 1];
       }
       sum[l..r] = prefix[r] - prefix[l - 1]

    2. 0-based 风格（和原数组下标一致）
       vector<long long> prefix(n);
       prefix[0] = a[0];
       for (int i = 1; i < n; ++i) {
           prefix[i] = prefix[i - 1] + a[i];
       }
       如果 l == 0，sum[l..r] = prefix[r]
       否则 sum[l..r] = prefix[r] - prefix[l - 1]

    高频错误：
    1. 0-based 写法忘了特判 l == 0。
    2. 区间端点是 1-based，但你套了 0-based 公式。
    3. 前缀和数组用 int，结果总和溢出。
    */
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
long long gcdValue(long long a, long long b) {
    // std::gcd(a, b) 返回最大公约数。
    // 例如 gcd(12, 18) = 6，因为 6 是同时整除 12 和 18 的最大正整数。
    return gcd(a, b);
}

long long safeLcm(long long a, long long b) {
    // 最小公倍数 lcm(a, b) 表示同时是 a 和 b 倍数的最小正整数。
    // 基本公式：
    // lcm(a, b) = a / gcd(a, b) * b
    //
    // 为什么不是直接写 a * b / gcd(a, b)？
    // 因为 a * b 可能先溢出，所以要“先除后乘”。
    //
    // 例如 a = 12, b = 18
    // gcd = 6
    // lcm = 12 / 6 * 18 = 36
    if (a == 0 || b == 0) {
        return 0;
    }
    long long g = gcd(a, b);
    return a / g * b;
}

void gcdLcmNotes() {
    /*
    gcd:
      greatest common divisor，最大公约数。
      典型用途：约分、判断能否整除、把比例化成最简。

    lcm:
      least common multiple，最小公倍数。
      典型用途：求周期重合时间、多个循环多久再次同时发生。

    常见写法：
      long long g = std::gcd(a, b);
      long long l = a / g * b;

    为什么先除再乘？
      因为 a * b 可能先超过 long long 范围。

    什么时候用 gcd？
    1. 分数约分
    2. 求多个数的公因子
    3. 判断两数按步长变化后能否相遇

    什么时候用 lcm？
    1. 两个周期题求“多久重合一次”
    2. 多个循环同步问题

    高频错误：
    1. 把 lcm 写成 a * b / gcd(a, b)，先乘导致溢出。
    2. 没考虑 a 或 b 为 0。
    3. 只会背公式，不知道 gcd/lcm 分别解决什么问题。
    */
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

    // DFS 的核心思想：
    // 从当前点出发，沿着一个方向不断走到底，再回溯回来。
    // 适合做：
    // 1. 连通块统计
    // 2. 可达性判断
    // 3. 枚举所有可能路径 / 状态（题目规模较小时）
    //
    // 在网格题里，visited[x][y] = 1 表示这个格子已经归属于某个连通块，
    // 后面就不要重复走了。
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

int countGridComponents(const vector<string>& grid) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    vector<vector<int>> visited(n, vector<int>(m, 0));
    int components = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#' || visited[i][j]) {
                continue;
            }

            // 每找到一个还没访问过的空地，就说明发现了一个新连通块。
            ++components;
            dfsGrid(i, j, grid, visited);
        }
    }

    return components;
}

int bfsGridShortestPath(const vector<string>& grid,
                        pair<int, int> start,
                        pair<int, int> target) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    // BFS 的核心思想：
    // 按“层”扩展，离起点距离为 0 的点先出队，
    // 再处理距离为 1 的点、距离为 2 的点……
    //
    // 因此在“无权图最短路”里，BFS 非常合适。
    // 网格上下左右每走一步代价都相同，所以它本质上也是无权图。
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

void graphSearchNotes() {
    /*
    DFS 和 BFS 怎么选？

    1. DFS：
       - 更适合连通块、可达性、回溯、递归枚举
       - 常见问法：
         “有多少个岛屿”
         “这个点能不能走到那个点”
         “枚举所有可能方案”

    2. BFS：
       - 更适合无权图最短路
       - 常见问法：
         “最少走多少步”
         “最短操作次数”
         “从起点扩散到全图需要多久”

    网格题快速识别：
    - 问连通块数量：优先 DFS 或 BFS 都行
    - 问最短步数：优先 BFS

    高频错误：
    1. 求最短路却用了 DFS，结果复杂度高且容易错。
    2. DFS / BFS 都忘了做 visited 或 dist 标记，导致重复搜索。
    3. BFS 出队时不记录距离，最后不知道最短步数是多少。
    4. 网格越界判断写错，尤其是 nx / ny 的上下界。
    */
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
