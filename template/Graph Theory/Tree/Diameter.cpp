#include <bits/stdc++.h>
using namespace std;

class TreeDiameter{
    int c;
public:
    void dfs(int x, int pa, vector<int>& dis, vector<vector<int>>& g) {
        for(auto &y : g[x]) {
            if(y == pa) continue;
            dis[y] = dis[x] + 1;
            if(dis[y] > dis[c]) {
                c = y;
            }
            dfs(y, x, dis, g);
        }
    }
    void GetDiameter(int n){
        vector<vector<int>> g(n);
        vector<int> dis(n);
        //
        int a = 0;
        c = a;
        dis[a] = 0;
        dfs(0, -1, dis, g);
        //记录第一个端点u = c
        dis[c] = 0;
        dfs(c, -1, dis, g);
        //记录第二个端点v = c，直径为dis[c]
    }
};