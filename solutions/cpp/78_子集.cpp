#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    vector<vector<int>> ans;
    vector<int> path;

   void backtrack(vector<int>& nums,int startIndex){
       ans.emplace_back(path);

       for (int i = startIndex; i < nums.size();i++){
        path.push_back(i);

        backtrack(nums, i + 1);

        path.pop_back();
       }
   }

    vector<vector<int>> subsets(vector<int>& nums) {

        backtrack(nums, 0);
        return ans;
    }
};


int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
