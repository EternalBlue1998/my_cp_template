#include <bits/stdc++.h>
using namespace std;

class DSU{
public:
    DSU() =default;
    explicit DSU(int n){
        init(n);
    }
    int find(int x){
        if(x != pa[x]) pa[x] = find(pa[x]);
        return pa[x];
    }
    void merge(int x, int y){
        int px = find(x), py = find(y);
        if(px == py) return ;
        if(sz[px] < sz[py]){
            sz[py] += sz[px];
            pa[px] = py;
        }
        else{
            sz[px] += sz[py];
            pa[py] = px;
        }
        --this->cnt;
    }
    bool connect(int x, int y){
        return find(x) == find(y);
    }
    int size(int x) {
        return sz[find(x)];
    }
    int count(){
        return this->cnt;
    }

    void init(int n) {
        pa = vector<int>(n, 0);
        iota(pa.begin(), pa.end(), 0);
        sz = vector<int>(n, 1);
        this->cnt = n;
    }
private:
    vector<int> pa;
    vector<int> sz;
    int cnt;
};