#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;

        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addtoHead(Node* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void movetoHead(Node* node) {
        remove(node);
        addtoHead(node);
    }

    Node* removeTail() {
        Node* node = tail->prev;
        remove(node);
        return node;
    }

public:
    unordered_map<int, Node*> cache;
    int capacity = 0;
    int size = 0;

    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;

        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }

        Node* node = cache[key];
        movetoHead(node);

        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            movetoHead(node);
        } else {
            Node* node = new Node(key, value);
            addtoHead(node);
            cache[key] = node;
            size++;

            if (size > capacity) {
                Node* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                size--;
            }
        }
    }
};
