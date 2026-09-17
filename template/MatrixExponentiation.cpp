#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

struct Matrix {
    int n, m;
    vector<vector<int>> a;

    Matrix(int n, int m) : n(n), m(m), a(n, vector<int>(m, 0)) {}
    
    Matrix(const vector<vector<int>>& v) : n(v.size()), m(v[0].size()), a(v) {}

    Matrix(int n, bool identity = false) : n(n), m(n), a(n, vector<int>(n, 0)) {
        if(identity){
            for (int i = 0; i < n; i++) a[i][i] = 1;
        }
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n, other.m);

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (a[i][k] == 0) continue;

                for (int j = 0; j < other.m; j++) {
                    res.a[i][j] = (res.a[i][j] + 1LL * a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return res;
    }

    Matrix operator^(long long k) const {
        Matrix res(n, true);
        Matrix base = *this;

        while (k) {
            if (k & 1)
                res = res * base;

            base = base * base;
            k >>= 1;
        }

        return res;
    }
};

int main() {
    long long n = 10;
    
    //an = an−1 + an−2, a1 = 2, a2 = 3

    Matrix A(2, 2);

    A.a[0][0] = 1;
    A.a[0][1] = 1;
    A.a[1][0] = 1;
    A.a[1][1] = 0;
    
    /*
    Matrix A({
        {1, 1},
        {1, 0}
    });
    */

    Matrix init(2, 1);
    init.a[0][0] = 3; // a2
    init.a[1][0] = 2; // a1

    Matrix ans = (A ^ (n - 2)) * init;

    cout << ans.a[0][0] << '\n';
}
