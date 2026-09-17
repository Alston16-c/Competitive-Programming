#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

struct MinMaxMatrix {
    int n, m;
    vector<vector<int>> a;

    MinMaxMatrix(int n, int m)
        : n(n), m(m), a(n, vector<int>(m, INF)) {}

    MinMaxMatrix(const vector<vector<int>>& v)
        : n(v.size()), m(v[0].size()), a(v) {}

    MinMaxMatrix(int n, bool identity = false)
        : n(n), m(n), a(n, vector<int>(n, INF)) {
        if (identity) {
            for (int i = 0; i < n; i++)
                a[i][i] = 0;
        }
    }

    MinMaxMatrix operator*(const MinMaxMatrix& other) const {
        MinMaxMatrix res(n, other.m);

        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                if (a[i][k] != INF)
                    for (int j = 0; j < other.m; j++)
                        if (other.a[k][j] != INF)
                            res.a[i][j] = min(
                                res.a[i][j],
                                a[i][k] + other.a[k][j]
                            );

        return res;
    }

    MinMaxMatrix operator^(long long k) const {
        MinMaxMatrix res(n, true);
        MinMaxMatrix base = *this;

        while (k) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }

        return res;
    }
};

int main() {
    MinMaxMatrix A({
        {0,   5,   2},
        {INF, 0,   3},
        {INF, INF, 0}
    });

    int k = 2;

    MinMaxMatrix B = A ^ k;

    cout << B.a[0][2] << '\n';
}
