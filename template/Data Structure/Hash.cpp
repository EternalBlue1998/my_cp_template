#include <bits/stdc++.h>
using namespace std;

//自定义哈希
namespace custom_hash {
    struct custom_hash {
        static uint64_t hash_val(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        std::size_t get(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
            return hash_val(x + FIXED_RANDOM);
        }

        template<typename T>
        std::size_t operator()(T x) const {
            return get(std::hash<T>{}(x));
        }
    };

    template<typename K>
    using hashset = std::unordered_set<K, custom_hash>;

    template<typename K, typename V>
    using hashmap = std::unordered_map<K, V, custom_hash>;
}
using custom_hash::hashset, custom_hash::hashmap;


struct HashVal {
    //多变量哈希
    template<typename T>
    inline void hash_combine(std::size_t& seed, const T& v) const{
        seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<typename T>
    inline void hash_val(std::size_t& seed, const T& v) const{
        hash_combine(seed, v);
    }

    template<typename T, typename... Types>
    inline void hash_val(std::size_t& seed, const T& v, const Types& ...args) const{
        hash_combine(seed, v);
        hash_val(seed, args...);
    }

    template<typename... Types>
    inline std::size_t hash_val(const Types& ...args) const{
        std::size_t seed = 0;
        hash_val(seed, args...);
        return seed;
    }
} HV;

struct pair_hash{
    template<typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const{
        return HV.hash_val(p.first, p.second);
    }
};