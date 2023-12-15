#include <bits/stdc++.h>
using namespace std;

class DFSOrder{
public:
    DFSOrder(vector<vector<int>> &g) {
        n = g.size();
        in.resize(n);
        out.resize(n);
        dfs(g, 0, -1);
    }
private:
    void dfs(vector<vector<int>> &g, int x, int pa) {
        in[x] = a.size();
        a.push_back(x);
        for(auto y : g[x]) {
            if(y == pa) continue;
            dfs(g, y, x);
        }
        out[x] = a.size();
    }
public:
    int n;
    vector<int> a; //dfs序数组，存放的是节点编号
    //  [ in[x], out[x] ) 表示以节点x为根的子树范围，左闭右开
    vector<int> in;
    vector<int> out;
};