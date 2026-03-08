#include <bits/stdc++.h>
using namespace std;

template <class T>
struct fenwick_tree {
private:
    int _n;
    vector<T> data;

public:
    fenwick_tree(int n) : _n(n), data(n, 0) {}

    void add(int p, T x) {
        for (p++; p <= _n; p += p & -p)
            data[p - 1] += x;
    }

    // prefix sum [0, r)
    T sum(int r) const {
        T s = 0;
        for (; r > 0; r -= r & -r)
            s += data[r - 1];
        return s;
    }

    // range sum [l, r)
    T sum(int l, int r) const {
        return sum(r) - sum(l);
    }
};

int main() {
    fenwick_tree<long long> fw(10);

    fw.add(3, 5);   // a[3] += 5
    fw.add(5, 2);   // a[5] += 2

    cout << fw.sum(0,6) << endl; // sum of [0..5]
}