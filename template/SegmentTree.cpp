#include <bits/stdc++.h>
using namespace std;

template<class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int _n, size, log;
    vector<S> d;

    SegTree(int n) {
        _n = n;
        log = 0;
        while ((1 << log) < n) log++;
        size = 1 << log;
        d.assign(2 * size, e());
    }

    SegTree(const vector<S>& v) : SegTree(v.size()) {
        for (int i = 0; i < (int)v.size(); i++)
            d[size + i] = v[i];
        build();
    }

    void build() {
        for (int i = size - 1; i >= 1; i--)
            d[i] = op(d[2 * i], d[2 * i + 1]);
    }

    void set(int p, S x) {
        p += size;
        d[p] = x;
        for (p >>= 1; p >= 1; p >>= 1)
            d[p] = op(d[2 * p], d[2 * p + 1]);
    }

    S get(int p) {
        return d[p + size];
    }

    S prod(int l, int r) {
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() {
        return d[1];
    }
};

int op(int a, int b) {
    return a + b;
}

int e() {
    return 0;
}

int main() {
    vector<int> v = {1,2,3,4,5};

    SegTree<int, op, e> seg(v);

    cout << seg.prod(1,4) << endl; // 2+3+4 = 9

    seg.set(2,10);

    cout << seg.prod(1,4) << endl; // 2+10+4 = 16
}