#include <bits/stdc++.h>
using namespace std;

constexpr static int mod = 1e9 + 7;

//矩阵快速幂
struct Matrix {
    int n, m;//row, col
    std::vector<vector<long long>> A;

    Matrix(int n, int m) : n(n), m(m) {
        A.resize(n, std::vector<long long>(m));
    }
};

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix res(a.n, b.m);
    for(int i = 0; i < a.n; ++i) {
        for(int j = 0; j < b.m; ++j) {
            for(int k = 0; k < a.m; ++k) {
                res.A[i][j] += a.A[i][k] * b.A[k][j];
                res.A[i][j] %= mod;
            }
        }
    }
    return res;
}

Matrix mpow(Matrix &a, long long k) {
    Matrix res(a.n, a.m);
    for(int i = 0; i < a.n; ++i) res.A[i][i] = 1;
    while(k) {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}