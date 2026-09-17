#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;

    DSU(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int main() {
    DSU dsu(7);

    // Connect components
    dsu.unite(0, 1);
    dsu.unite(1, 2);

    dsu.unite(3, 4);
    dsu.unite(4, 5);

    // Check whether two nodes are connected
    cout << (dsu.find(0) == dsu.find(2)) << '\n';
    // 1

    cout << (dsu.find(0) == dsu.find(3)) << '\n';
    // 0

    // Connecting two already-connected nodes
    cout << dsu.unite(0, 2) << '\n';
    // 0

    // Connecting two different components
    cout << dsu.unite(2, 3) << '\n';
    // 1
}
