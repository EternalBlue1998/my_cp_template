#include <bits/stdc++.h>
using namespace std;

struct node{
    int dis, u;
    bool operator>(const node& a) const {
        return dis > a.dis;
    }
};
vector<vector<pair<int, int>>> g;//建图
void dijkstra(int s, int n, vector<vector<pair<int, int>>>& g) {
    //优先队列优化，时间复杂度O(mlogm)
    int dis[n], vis[n];
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, s});
    dis[s] = 0;
    while(!pq.empty()) {
        auto x = pq.top().u;
        pq.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(auto &p : g[x]){
            auto y = p.first, w = p.second;
            if(dis[y] > dis[x] + w){
                dis[y] = dis[x] + w;
                pq.push({dis[y], y});
            }
        }
    }
}
void dijkstra(int s, int n, vector<vector<pair<int, int>>>& g) {
    //朴素算法，时间复杂度O(n^2)
    int dis[n], vis[n];
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    for(int i = 0; i < n; ++i) {
        int x = 0, mind = 0x3f3f3f3f;
        for(int j = 0; j < n; ++j) {
            if(vis[j] == 0 && dis[j] < mind) x = j, mind = dis[j];
        }
        vis[x] = 1;
        for(auto &p : g[x]) {
            int y = p.first, w = p.second;
            if(dis[y] > dis[x] + w) dis[y] = dis[x] + w;
        }
    }
}