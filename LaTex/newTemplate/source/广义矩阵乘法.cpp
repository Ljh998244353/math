#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// N: 矩阵最大维度 (编译期确定，分配在栈/BSS段，速度快)
template<int N>
struct Matrix {
    int n; // 实际使用的维度
    ll mat[N][N];

    // ================= 配置区域 (根据题目修改这里) =================
    // 场景：求最短路 (Min-Plus)
    const static ll INF = 4e18;      // 广义零元 (无效值)
    const static ll IDENTITY_VAL = 0;// 广义单位元 (对角线初始值)
    
    // 广义加法：取 min (用于外层合并)
    inline void _add(ll &a, ll b) const {
        a = min(a, b); 
    }
    
    // 广义乘法：普通加法 (用于内层路径拼接)
    inline ll _mul(ll a, ll b) const {
        if (a == INF || b == INF) return INF; // 防止溢出
        return a + b;
    }
    // ==============================================================

    Matrix(int _n = N) : n(_n) {
        // 默认初始化为 INF (广义零矩阵)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                mat[i][j] = INF;
    }

    // 构造单位矩阵 I (A * I = A)
    static Matrix identity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) res.mat[i][i] = IDENTITY_VAL;
        return res;
    }

    // 矩阵乘法
    Matrix operator*(const Matrix &other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (mat[i][k] == INF) continue; // 剪枝
                for (int j = 0; j < n; j++) {
                    // res[i][j] += this[i][k] * other[k][j]
                    _add(res.mat[i][j], _mul(mat[i][k], other.mat[k][j]));
                }
            }
        }
        return res;
    }

    // 快速幂
    Matrix pow(ll k) {
        Matrix res = identity(n);
        Matrix a = *this;
        while (k) {
            if (k & 1) res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }
    
    // 调试打印
    void print() {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) 
                cout << (mat[i][j] == INF ? -1 : mat[i][j]) << " ";
            cout << "\n";
        }
    }
};