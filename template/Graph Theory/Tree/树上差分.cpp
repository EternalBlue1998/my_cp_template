#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g; //邻接矩阵
vector<int> p; //父节点
vector<int> d; //差分数组

//init 父节点数组
void dfs_p(int x, int pa) {
    p[x] == pa;
    for(auto y : g[x]) {
        if(y == pa) continue;
        dfs_p(y, x);
    }
}
//点权差分
//点x到点y路径上所有点权值加k，LCA(x, y) = o
void update_v(int x, int y, int o, int k) {
    d[x] += k;
    d[y] += k;
    d[o] -= k;
    if(p[o] != -1) d[p[o]] -= k;
}

//边权差分
//点x到点y路径上所有边权值加k，LCA(x, y) = o
void update_e(int x, int y, int o, int k) {
    d[x] += k;
    d[y] += k;
    d[o] -= 2 * k;
}


//dfs得到结果
int dfs(int x,int pa) {
    int cnt = d[x];
    for(auto y : g[x]) {
        cnt += dfs(y, x);
    }
    return cnt;
}