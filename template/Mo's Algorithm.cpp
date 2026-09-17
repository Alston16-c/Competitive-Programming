#include <bits/stdc++.h>
using namespace std;

struct Mo {
    struct Query {
        int l, r, id;
    };

    int n, B;
    vector<Query> qs;

    Mo(int n) : n(n), B(sqrt(n) + 1) {}

    void add_query(int l, int r, int id) {
        qs.push_back({l, r, id});
    }

    vector<int> process(const vector<int>& a) {
        sort(qs.begin(), qs.end(), [&](Query x, Query y) {
            int bx = x.l / B;
            int by = y.l / B;

            if (bx != by)
                return bx < by;
            
            return (bx & 1) ? x.r > y.r : x.r < y.r;
        });

        vector<int> ans(qs.size());

        int L = 0, R = -1;

        int cur = 0;

        auto add = [&](int idx) {
            cur += a[idx];
        };

        auto remove = [&](int idx) {
            cur -= a[idx];
        };

        for (auto [l, r, id] : qs) {
            while (L > l) add(--L);
            while (R < r) add(++R);
            while (L < l) remove(L++);
            while (R > r) remove(R--);

            ans[id] = cur;
        }

        return ans;
    }
};

int main() {
    vector<int> a = {2, 7, 1, 9, 4, 6, 3};

    Mo mo(a.size());

    mo.add_query(1, 4, 0);
    mo.add_query(0, 2, 1);
    mo.add_query(3, 6, 2);

    vector<int> ans = mo.process(a);

    for (int x : ans)
        cout << x << '\n';
}
