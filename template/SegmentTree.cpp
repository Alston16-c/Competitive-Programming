#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> seg;

    SegTree(const vector<int>& a) : n(a.size()), seg(4 * n + 5) {
        build(0, 0, n - 1, a);
    }

    int combine(int a, int b) {
        return max(a, b);
    }

    int query(int ql, int qr) {
        return query(0, 0, n - 1, ql, qr);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    int walk(int ql, int x) {
        return walk(0, 0, n - 1, ql, x);
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

        seg[curr] = combine(seg[2 * curr + 1], seg[2 * curr + 2]);
    }

    int query(int curr, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) return seg[curr];

        int mid = (l + r) / 2;

        return combine(
            query(2 * curr + 1, l, mid, ql, qr),
            query(2 * curr + 2, mid + 1, r, ql, qr)
        );
    }

    void update(int curr, int l, int r, int idx, int val) {
        if (l == r) {
            seg[curr] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * curr + 1, l, mid, idx, val);
        else
            update(2 * curr + 2, mid + 1, r, idx, val);

        seg[curr] = combine(seg[2 * curr + 1], seg[2 * curr + 2]);
    }

    int walk(int curr, int l, int r, int ql, int x) {
        if (r < ql || seg[curr] < x) return -1;
        if (l == r) return l;

        int mid = (l + r) / 2;

        int res = walk(2 * curr + 1, l, mid, ql, x);

        if (res != -1) return res;

        return walk(2 * curr + 2, mid + 1, r, ql, x);
    }
};

int main() {
    vector<int> a = {2, 7, 1, 9, 4, 6, 3};

    SegTree st(a);

    // Range maximum
    cout << st.query(1, 4) << '\n';
    // max(7, 1, 9, 4) = 9

    // Point update: a[2] = 10
    st.update(2, 10);

    cout << st.query(1, 4) << '\n';
    // max(7, 10, 9, 4) = 10

    // Find first index >= 3 whose value >= 8
    cout << st.walk(3, 8) << '\n';
    // index 3, because a[3] = 9

    // Find first index >= 4 whose value >= 8
    cout << st.walk(4, 8) << '\n';
    // -1
}
