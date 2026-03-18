#include <iostream>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

/*
LeetCode 295. 数据流的中位数
题型：堆 / 数据流
核心思路：用大顶堆维护较小一半、用小顶堆维护较大一半，并始终让左堆元素个数不少于右堆。
复杂度：addNum 为 O(log n)，findMedian 为 O(1)，空间 O(n)
*/
class MedianFinder {
public:

    priority_queue<int> leftHeap;
    priority_queue<int, vector<int>, greater<int>> rightHeap;

    MedianFinder() {
    }
    
    void addNum(int num) {
        if (!leftHeap.empty() && num < leftHeap.top()) {
            leftHeap.push(num);
        } else {
            rightHeap.push(num);
        }

        if (leftHeap.size() > rightHeap.size() + 1) {
            rightHeap.push(leftHeap.top());
            leftHeap.pop();
        } else if (leftHeap.size() < rightHeap.size()) {
            leftHeap.push(rightHeap.top());
            rightHeap.pop();
        }
    }
    
    double findMedian() {
        if (leftHeap.empty()) return 0.0;

        if (leftHeap.size() > rightHeap.size()) {
            return leftHeap.top();
        } else {
            return (leftHeap.top() + rightHeap.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */



int main() {
    MedianFinder medianFinder;
    medianFinder.addNum(1);
    medianFinder.addNum(2);
    cout << "after [1, 2]: " << medianFinder.findMedian() << " (expected 1.5)" << endl;

    medianFinder.addNum(3);
    cout << "after [1, 2, 3]: " << medianFinder.findMedian() << " (expected 2)" << endl;

    return 0;
}
