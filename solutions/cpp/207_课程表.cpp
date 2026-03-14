#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);

        for(auto p:prerequisites){
            int a = p[0];
            int b = p[1];
            graph[b].push_back(a);
            inDegree[a]++;
        }

        queue<int> q;

        for (int i = 0; i < numCourses;i++)
        {
            if(inDegree[i]==0){
                q.push(i);
            }
        }

        int count = 0;
        while(!q.empty()){
            int cur = q.front();
            q.pop();

            count++;

            for(int next:graph[cur]){
                inDegree[next]--;
                if(inDegree[next]==0){
                    q.push(next);
                }
            }
        }

        return count == numCourses;
    }
};

int main() {
    Solution solution;

    cout << INT16_MIN << endl;

    // TODO: 添加测试用例
    
    return 0;
}
