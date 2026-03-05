#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

// class LRUCache {
// public:
//     int size = 0;
//     unordered_map<int, int> Cache;
//     list<int> keyList;

//     LRUCache(int capacity) {
//         size = capacity;  // 修复：赋值给成员变量
//     }

//     int get(int key) {
//         auto it = Cache.find(key);
//         if (it != Cache.end()) {
//             keyList.remove(key);     // 更新访问顺序
//             keyList.push_back(key);
//             return it->second;
//         }
//         return -1;
//     }

//     void put(int key, int value) {
//         auto it = Cache.find(key);
//         if (it != Cache.end()) {
//             it->second = value;
//             keyList.remove(key);     // 更新访问顺序
//             keyList.push_back(key);
//         } else {
//             Cache[key] = value;
//             keyList.push_back(key);
//             if (Cache.size() > size) {  // 超出容量，删除最久未用
//                 int delKey = keyList.front();
//                 keyList.pop_front();
//                 Cache.erase(delKey);
//             }
//         }
//     }
// };


#include <unordered_map>
#include <list>

class LRUCache {
private:
    int cap;
    // 列表存储 pair<key, value>，最近使用的放在 front
    std::list<std::pair<int, int>> cache;
    // 哈希表存储 key 到 链表迭代器 的映射
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

    // 辅助函数：将已存在的节点提升到“最近使用”状态
    void makeRecently(int key) {
        auto it = map[key];
        // 从当前位置删除，移动到链表头部
        cache.splice(cache.begin(), cache, it);
    }

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }
        // 访问后将其设为最近使用
        makeRecently(key);
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            // key 已存在：修改值并提升优先级
            map[key]->second = value;
            makeRecently(key);
            return;
        }

        // key 不存在：判断是否已满
        if (cache.size() >= cap) {
            // 淘汰最久未使用的（链表尾部）
            int lastKey = cache.back().first;
            map.erase(lastKey);
            cache.pop_back();
        }

        // 插入新节点到头部
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};



/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


int main() {
    // Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}