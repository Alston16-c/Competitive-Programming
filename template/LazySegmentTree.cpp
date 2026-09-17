#include <bits/stdc++.h>
using namespace std;

struct LazySegTree {
    int n;
    vector<int> seg, lazy;

    LazySegTree(const vector<int>& a) : n(a.size()), seg(4 * n + 5), lazy(4 * n + 5, 0) {
        build(0, 0, n - 1, a);
    }

    int combine(int a, int b) {
        return max(a, b);
    }

    void update(int ql, int qr, int val) {
        update(0, 0, n - 1, ql, qr, val);
    }

    int query(int ql, int qr) {
        return query(0, 0, n - 1, ql, qr);
    }
private:
    void build(int curr, int l, int r, const vector<int>& a) {
        if (l == r) {
            seg[curr] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(2 * curr + 1, l, mid, a);
        build(2 * curr + 2, mid + 1, r, a);

        seg[curr] = combine(
            seg[2 * curr + 1],
            seg[2 * curr + 2]
        );
    }

    void apply(int curr, int val) {
        seg[curr] += val;
        lazy[curr] += val;
    }

    void push(int curr) {
        if (lazy[curr] == 0) return;

        apply(2 * curr + 1, lazy[curr]);
        apply(2 * curr + 2, lazy[curr]);

        lazy[curr] = 0;
    }

    void update(int curr, int l, int r, int ql, int qr, int val) {
        if (r < ql || l > qr)
            return;

        if (ql <= l && r <= qr) {
            apply(curr, val);
            return;
        }

        push(curr);

        int mid = (l + r) / 2;

        update(2 * curr + 1, l, mid, ql, qr, val);
        update(2 * curr + 2, mid + 1, r, ql, qr, val);

        seg[curr] = combine(
            seg[2 * curr + 1],
            seg[2 * curr + 2]
        );
    }

    int query(int curr, int l, int r, int ql, int qr) {
        if (r < ql || l > qr)
            return 0;

        if (ql <= l && r <= qr)
            return seg[curr];

        push(curr);

        int mid = (l + r) / 2;

        return combine(
            query(2 * curr + 1, l, mid, ql, qr),
            query(2 * curr + 2, mid + 1, r, ql, qr)
        );
    }
};

int main() {
    vector<int> a = {2, 7, 1, 9, 4, 6, 3};

    LazySegTree st(a);

    // Query maximum on [1, 4]
    cout << st.query(1, 4) << '\n';
    // 9

    // Add 5 to every element in [2, 5]
    // a = {2, 7, 6, 14, 9, 11, 3}
    st.update(2, 5, 5);

    // Maximum on [1, 4]
    cout << st.query(1, 4) << '\n';
    // 14

    // Add 10 to every element in [0, 2]
    // a = {12, 17, 16, 14, 9, 11, 3}
    st.update(0, 2, 10);

    // Maximum of entire array
    cout << st.query(0, 6) << '\n';
    // 17

    // Maximum on [0, 2]
    cout << st.query(0, 2) << '\n';
    // 17
}
