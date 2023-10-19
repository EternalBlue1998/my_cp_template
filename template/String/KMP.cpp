#include <bits/stdc++.h>
using namespace std;

class KMP {
public:
    vector<int> prefix_function(string_view s) {
        int n = s.size();
        vector<int> pi(n);
        for(int i = 1, j = 0; i < n; ++i) { //j = pi[i - 1]
            while(j != 0 and s[i] != s[j]) j = pi[j - 1];
            pi[i] = s[i] == s[j] ? ++j : 0;
        }
        return pi;
    }
    int find_first_id(const string& text, const string& patten) {
        int n = text.size(), m = patten.size();
        vector<int> pi = prefix_function(patten);
        for(int i = 0, j = 0; i < n; ++i) {
            while(j != 0 and text[i] != patten[j]) j = pi[j - 1];
            if(text[i] == patten[j]) j++;
            if(j == m) return i - m + 1;
        }
        return -1;
    }
    vector<int> find_all_id(const string& text, const string& patten) {
        string s = patten + '#' + text;
        int n = text.size(), m = patten.size();
        vector<int> ans;
        vector<int> pi = prefix_function(s);
        for(int i = m + 1; i <= m + n; ++i) {
            if(pi[i] == m) ans.push_back(i - m * 2);
        }
        return ans;
    }
} kmp;