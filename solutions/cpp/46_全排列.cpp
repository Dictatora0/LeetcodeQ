#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> result;

    vector<bool> used;

    vector<int> path;

    void backtrack(vector<int>& nums){
        if(path.size()==nums.size()){
            result.push_back(path);
        }

        for (int i = 0; i < nums.size();i++){
            if(used[i]){
                continue;
            }

            path.push_back(nums[i]);
            used[i] = true;

            backtrack(nums);

            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums){
        used.resize(nums.size(), false);
        backtrack(nums);

        return result;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
