#include <bits/stdc++.h>
using namespace std;

class LCA{
    //倍增法
    int N;
    vector<vector<int>> fa;
    vector<int> dep;
public:
    LCA(int n, vector<vector<int>>& g) {

        N = std::__lg(n) + 1;
        fa.resize(N, vector<int>(n));
        dep.resize(n);

        auto dfs = [&](auto dfs, int x, int pa, int h)->void{
            fa[0][x] = pa;
            dep[x] = h;
            for(int i = 1; i < N; ++i) {
                if(fa[i - 1][x] == -1) fa[i][x] = -1;
                else fa[i][x] = fa[i - 1][fa[i - 1][x]];
            }
            for(auto &y : g[x]) {
                if(y == pa) continue;
                dfs(dfs, y, x, h + 1);
            }
        };
        dfs(dfs, 0, -1, 0);
    }
    int get(int x, int y) {
        if(dep[x] > dep[y]) swap(x, y);
        int k = dep[y] - dep[x];
        for(int i = 0; i < N; ++i) {
            if(k >> i & 1) y = fa[i][y];
        }
        if(x == y) return x;
        for(int i = N - 1; i >= 0 and x != y; --i) {
            if(fa[i][x] != fa[i][y]) {
                x = fa[i][x];
                y = fa[i][y];
            }
        }
        return fa[0][x];
    }
};


class LCA{
    //targan离线算法
    vector<vector<int>> children;
    vector<vector<int>> query;
    vector<int> pa, vis;
public:
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py) return;
        pa[py] = px;
    }
    int find(int x) {
        if(x != pa[x]) pa[x] = find(pa[x]);
        return pa[x];
    }
    void targan(int x){
        for(auto &y : children[x]) {
            targan(x);
            merge(x, y);
            vis[y] = 1;
        }
        for(auto &y : query[x]) {
            if(x == y) {}
            else if(vis[y] == 0) continue;
            find(y);
        }
    }
};