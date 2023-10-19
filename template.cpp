#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//可变参数打印
template<class T>
void print(T &t) {cout << t <<'\n';}

template<class T, class... Args>
void print(T &t, Args&... rest) {
    cout << t << ' ';
    print(rest...); // 打印剩余参数，注意省略号必须有
}
//埃氏筛
bitset<100000> vis;
void Prime(int n) {
    vis.set();
    vis[0] = vis[1] = 0;
    for (int i = 2; i * i <= n; i++) {
        if (vis[i]) {
            for (int j = i << 1; j <= n; j += i) vis[j] = 0;
        }
    }
}

//质因数分解
namespace{
//预处理LPF(最小质因数)
constexpr int MAXN = 1e5;
int lpf[MAXN + 1];
void init(){
    if(lpf[2] == 2) return;
    for(int i = 2; i <= MAXN; ++i) {
        if(lpf[i] != 0) continue;
        for(int j = i; j <= MAXN; j += i) {
            if(lpf[j] == 0) lpf[j] = i;
        }
    }
}
void get(int x) {
    while(x > 1) {
        int p = lpf[x], cnt = 0;
        while(lpf[x] == p) x /= p, ++cnt;
        //p^cnt
    }
}

}
//随机数
int getRandom(int start, int end){
    random_device r;
    default_random_engine e(r());
    //mt19937 gen(random_device{}());
    uniform_int_distribution<int> u(start, end);
    //uniform_real_distribution<double> u(start, end);
    return u(e);
}

//快速幂
const int mod = 1e9 + 7;
int fpow(int a,int b){
    int ans = 1;
    while(b){
        if(b & 1) ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ans;
}
//Miller-Rabin 素性测试
class MR{
public:
    long long quick_pow(long long x, long long p, long long mod) {  // 快速幂
        long long ans = 1;
        while (p) {
            if (p & 1) ans = (__int128)ans * x % mod;
            x = (__int128)x * x % mod;
            p >>= 1;
        }
        return ans;
    }
    bool Miller_Rabin(long long p) {  // 判断素数
        if (p < 2) return 0;
        if (p == 2) return 1;
        if (p == 3) return 1;
        long long d = p - 1, r = 0;
        while (!(d & 1)) ++r, d >>= 1;  // 将d处理为奇数
        for(long long k = 0; k < 10; ++k) {
            long long a = rand() % (p - 2) + 2;
            long long x = quick_pow(a, d, p);
            if (x == 1 || x == p - 1) continue;
                for (int i = 0; i < r - 1; ++i) {
                    x = (__int128)x * x % p;
                    if (x == p - 1) break;
                }
            if (x != p - 1) return 0;
        }
        return 1;
    }
};

//带余运算重载的INT， LONG类

// template<i64 P>
// struct MLong {
//     i64 x;
//     constexpr MLong() : x{} {}
//     constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
//     static i64 Mod;
//     constexpr static i64 getMod() {
//         if (P > 0) {
//             return P;
//         } else {
//             return Mod;
//         }
//     }
//     constexpr static void setMod(i64 Mod_) {
//         Mod = Mod_;
//     }
//     constexpr i64 norm(i64 x) const {
//         if (x < 0) {
//             x += getMod();
//         }
//         if (x >= getMod()) {
//             x -= getMod();
//         }
//         return x;
//     }
//     constexpr i64 val() const {
//         return x;
//     }
//     explicit constexpr operator i64() const {
//         return x;
//     }
//     constexpr MLong operator-() const {
//         MLong res;
//         res.x = norm(getMod() - x);
//         return res;
//     }
//     constexpr MLong inv() const {
//         assert(x != 0);
//         return power(*this, getMod() - 2);
//     }
//     constexpr MLong &operator*=(MLong rhs) & {
//         x = mul(x, rhs.x, getMod());
//         return *this;
//     }
//     constexpr MLong &operator+=(MLong rhs) & {
//         x = norm(x + rhs.x);
//         return *this;
//     }
//     constexpr MLong &operator-=(MLong rhs) & {
//         x = norm(x - rhs.x);
//         return *this;
//     }
//     constexpr MLong &operator/=(MLong rhs) & {
//         return *this *= rhs.inv();
//     }
//     friend constexpr MLong operator*(MLong lhs, MLong rhs) {
//         MLong res = lhs;
//         res *= rhs;
//         return res;
//     }
//     friend constexpr MLong operator+(MLong lhs, MLong rhs) {
//         MLong res = lhs;
//         res += rhs;
//         return res;
//     }
//     friend constexpr MLong operator-(MLong lhs, MLong rhs) {
//         MLong res = lhs;
//         res -= rhs;
//         return res;
//     }
//     friend constexpr MLong operator/(MLong lhs, MLong rhs) {
//         MLong res = lhs;
//         res /= rhs;
//         return res;
//     }
//     friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
//         i64 v;
//         is >> v;
//         a = MLong(v);
//         return is;
//     }
//     friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
//         return os << a.val();
//     }
//     friend constexpr bool operator==(MLong lhs, MLong rhs) {
//         return lhs.val() == rhs.val();
//     }
//     friend constexpr bool operator!=(MLong lhs, MLong rhs) {
//         return lhs.val() != rhs.val();
//     }
// };

// template<>
// i64 MLong<0LL>::Mod = 1;





//（带名次的）平衡树
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_multiset = __gnu_pbds::tree<T, null_type, std::less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 对于ordere_multiset，lower_bound(x)与upper_bound(x)功能相反
template<typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key(x)：返回 x 以 Cmp_Fn 比较的排名
// find_by_order(x)：返回 Cmp_Fn 比较的排名所对应元素的迭代器
// lower_bound(x)：以 Cmp_Fn 比较做 lower_bound，返回迭代器
// upper_bound(x)：以 Cmp_Fn 比较做 upper_bound，返回迭代器



//
template<typename T>
class Venice{
    map<T, T> mp;
    T  water_level = 0;
public:
    void Add(T key, T val) {
        mp[key + water_level] = val;
    }
    void Remove(T key) {
        mp.erase(key + water_level);
    }
    void Modify(T key, T val) {
        mp[key + water_level] = val;
    }
    void UpdateAll(T val) {
        //所有数减去val
        water_level += val;
    }
    pair<T, T> Getmin(){
        return *mp.begin();
    }
};


//SG函数打表
class SG{
    int mex(vector<int>& sorted_nums) {
        int n = sorted_nums.size();
        if(n == 0) return 0;
        for(int i = 0; i < n; ++i) {
            if(sorted_nums[i] != i) return i;
        }
        return n;
    }
    int mex(set<int>& st) {
        int res = 0;
        for(auto it = st.begin(); it != st.end(); ++it) {
            if(*it == res) ++res;
            else return res;
        }
        return res;
    }
    void get_sg(int n) {
        vector<int> nums;
        //set<int> nums;
        //处理后继状态
        for(int i = 0; i < n; ++i) nums.push_back(sg_arr[i]);
        for(int i = 1; i <= n - i; ++i) nums.push_back(sg_arr[i] ^ sg_arr[n - i]);
        //
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        sg_arr[n] = mex(nums);
    }
public:
    SG() =default;
    void PrintSG(int n){
        sg_arr.resize(n + 1);
        sg_arr[0] = 0;
        for(int i = 1; i <= n; ++i) {
            get_sg(i);
        }
        for(int i = 0; i <= n; ++i) {
            cout << "N:"<< i << "SG(N):" << sg_arr[i] << endl;
        }
    }
private:
    vector<int> sg_arr;
};

//数位DP模板
class digitDP{
public:
    void f(string s, int m) {
        //s = '0'为特殊情况
        int n = s.size();
        int memo[n][m];
        memset(memo, -1, sizeof(memo));
        function<int(int, int, bool, bool)> foo = [&](int i, int sum, bool islimit, bool isnum)->int{
            if(i == n) return isnum;
            //if(!islimit && isnum && memo[i][sum] != -1) return memo[i][sum];
            int res = 0;
            if(!isnum) res += foo(i + 1, sum, false, false);
            int start = isnum ? 0 : 1, end = islimit ? (s[i] - '0') : 9;
            for(int d = start; d <= end; ++d) {
                res += foo(i + 1, sum + d, islimit && (d == end), true);
            }
            //if(!islimit && isnum) memo[i][sum] = res;
            return res;
        };
    }
};

//Gosper's Hack 枚举大小为k的子集
void GospersHack(int k, int n) {
    int x = (1 << k) - 1;
    while(x < (1 << n)) {
        // l = x + lb; r = ((l ^ x) / lb) >> 2 or ((r ^ cur) >> __builtin_ctz(lb) + 2)
        int lb = x & -x;
        x = (x + lb) | ((x ^ (x + lb)) >> __builtin_ctz(lb) + 2);
    }
}
