#include <bits/stdc++.h>
using namespace std;

//区间查询、单点修改
template<typename T>
class SegTree{
    vector<T> a;
    vector<T> tree;
    int tag;//0-sum, 1-min, 2-max
public:
    explicit SegTree(int _tag, vector<T>& arr) : tag(_tag) {
        int n = arr.size();
        a = arr;
        tree.resize(n << 2);
        build(0, n - 1, 0);
    }
    explicit SegTree(int _tag, int n, T val) : tag(_tag) {
        a.resize(n, val);
        tree.resize(n << 2);
        build(0, n - 1, 0);
    }
    T Query(int l, int r) {
        //区间查询
        return query(l, r, 0, a.size() - 1, 0);
    }
    void Change(int x, T v) {
        //单点修改
        change(x, v, 0, a.size() - 1, 0);
    }
private:
    void build(int L, int R, int p) {
        if(L == R) {
            tree[p] = a[L];
            return;
        }
        int m = ((R - L) >> 1) + L;
        build(L, m, (p << 1) + 1);
        build(m + 1, R, (p + 1) << 1);
        switch (tag) {
            case 0:
                tree[p] = tree[(p << 1) + 1] + tree[(p + 1) << 1];
                break;
            case 1:
                tree[p] = min(tree[(p << 1) + 1], tree[(p + 1) << 1]);
                break;
            case 2:
                tree[p] = max(tree[(p << 1) + 1], tree[(p + 1) << 1]);
                break;
        }
        
    }
    T query(int l, int r, int L ,int R, int p) {
        if(l <= L && r >= R) {
            return tree[p];
        }
        int m = ((R - L) >> 1) + L;
        T res;
        // 取最值时注意res初值是否恰当
        switch (tag) {
            case 0:
                res = 0;
                if(l <= m) res += query(l, r, L, m, (p << 1) + 1);
                if(r > m) res += query(l, r, m + 1, R, (p + 1) << 1);
                break;
            case 1:
                res = INT_MAX;
                if(l <= m) res = min(res, query(l, r, L, m, (p << 1) + 1));
                if(r > m) res = min(res, query(l, r, m + 1, R, (p + 1) << 1));
                break;
            case 2:
                res = INT_MIN;
                if(l <= m) res = max(res, query(l, r, L, m, (p << 1) + 1));
                if(r > m) res = max(res, query(l, r, m + 1, R, (p + 1) << 1));
                break;
        }
        return res;
    }
    void change(int x, T v, int L, int R, int p) {
        if(L == R && L == x) {
            tree[p] = v;
            return;
        }
        int m = ((R - L) >> 1) + L;
        if(x <= m) change(x, v, L, m, (p << 1) + 1);
        else change(x, v, m + 1, R, (p + 1) << 1);
        switch (tag) {
            case 0:
                tree[p] = tree[(p << 1) + 1] + tree[(p + 1) << 1];
                break;
            case 1:
                tree[p] = min(tree[(p << 1) + 1], tree[(p + 1) << 1]);
                break;
            case 2:
                tree[p] = max(tree[(p << 1) + 1], tree[(p + 1) << 1]);
                break;
        }
    }
};


//区间查询、区间修改
template<typename T>
class SegTree{
    vector<T> a;
    vector<T> tree;
    vector<int> tag;//对“子区间”的标记，不影响本身的值
public:
    explicit SegTree(vector<T>& arr) {
        int n = arr.size();
        a = arr;
        tree.resize(n << 2);
        tag.resize(n << 2);
        build(0, n - 1, 0);
    }
    explicit SegTree(int n, T val) {
        a.resize(n, val);
        tree.resize(n << 2);
        tag.resize(n << 2);
        build(0, n - 1, 0);
    }
    T Query(int l, int r) {
        //区间查询
        return query(l, r, 0, a.size() - 1, 0);
    }
    void Update(int l, int r, T k) {
        //区间修改
        update(l, r, 0, a.size() - 1, 0, k);
    }
private:
    inline int lc(int p) {
        return (p << 1) + 1;
    }
    inline int rc(int p) {
        return (p + 1) << 1;
    }
    inline void push_up(int p) {
        tree[p] = tree[lc(p)] + tree[rc(p)];
        // tree[p] = max(tree[(p << 1) + 1], tree[(p + 1) << 1]);
        // tree[p] = min(tree[(p << 1) + 1], tree[(p + 1) << 1]);
    }
    inline void push_down(int p, int L, int R) {
        int m = (R - L >> 1) + L;
        if(L != R && tag[p]) { //区间加
            tag[lc(p)] += tag[p];
            tag[rc(p)] += tag[p];
            tree[lc(p)] += tag[p] * (m - L + 1);
            tree[rc(p)] += tag[p] * (R - m);
            tag[p] = 0;
        }

        // if(L != R && tag[p]) { //区间修改
        //     tag[lc(p)] = tag[p];
        //     tag[rc(p)] = tag[p];
        //     tree[lc(p)] = tag[p] * (m - L + 1);
        //     tree[rc(p)] = tag[p] * (R - m);
        //     tag[p] = 0;
        // }
    }
    void build(int L, int R, int p) {
        if(L == R) {
            tree[p] = a[L];
            return;
        }
        int m = ((R - L) >> 1) + L;
        build(L, m, (p << 1) + 1);
        build(m + 1, R, (p + 1) << 1);
        push_up(p);     
    }
    void update(int l, int r, int L, int R, int p, T k) {
        
        if(l <= L && r >= R) { //区间加
            tree[p] += k * (R - L + 1);
            tag[p] += k;
            return;
        }
        
        // if(l <= L && r >= R) { //区间修改
        //     tree[p] = k * (R - L + 1);
        //     tag[p] = k;
        //     return;
        // }

        int m = ((R - L) >> 1) + L;
        push_down(p, L, R);
        if(l <= m) update(l, r, L, m, lc(p), k);
        if(r > m) update(l, r, m + 1, R, rc(p), k);
        push_up(p);
    }
    T query(int l, int r, int L ,int R, int p) {
        if(l <= L && r >= R) {
            return tree[p];
        }
        int m = ((R - L) >> 1) + L;
        T res = T();
        push_down(p, L, R);
        if(l <= m) res += query(l, r, L, m, (p << 1) + 1);
        if(r > m) res += query(l, r, m + 1, R, (p + 1) << 1);
        // 取最值时注意res初值是否恰当
        // if(l <= m) res = max(res, query(l, r, L, m, (p << 1) + 1));
        // if(r > m) res = max(res, query(l, r, m + 1, R, (p + 1) << 1));
        return res;
    }
};