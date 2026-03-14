#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Trie {
public:

    Trie* children[26];
    bool isEnd;

    Trie() {

        isEnd = false;

        for(int i=0;i<26;i++)
            children[i] = nullptr;
    }

    void insert(string word) {

        Trie* node = this;

        for(char c : word){

            int idx = c - 'a';

            if(node->children[idx] == nullptr)
                node->children[idx] = new Trie();

            node = node->children[idx];
        }

        node->isEnd = true;
    }

    bool search(string word) {

        Trie* node = this;

        for(char c : word){

            int idx = c - 'a';

            if(node->children[idx] == nullptr)
                return false;

            node = node->children[idx];
        }

        return node->isEnd;
    }

    bool startsWith(string prefix) {

        Trie* node = this;

        for(char c : prefix){

            int idx = c - 'a';

            if(node->children[idx] == nullptr)
                return false;

            node = node->children[idx];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
