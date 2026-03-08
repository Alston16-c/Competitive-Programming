#include <bits/stdc++.h>
using namespace std;

template<
    class S,
    class F,
    S (*op)(S, S),
    S (*e)(),
    S (*mapping)(F, S),
    F (*composition)(F, F),
    F (*id)()
>
struct LazySegTree {

    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    LazySegTree(int n) {
        _n = n;
        log = 0;
        while ((1 << log) < n) log++;
        size = 1 << log;

        d.assign(2 * size, e());
        lz.assign(size, id());
    }

    LazySegTree(vector<S> v) : LazySegTree(v.size()) {
        for (int i = 0; i < v.size(); i++)
            d[size + i] = v[i];
        build();
    }

    void build() {
        for (int i = size - 1; i >= 1; i--)
            update(i);
    }

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }

    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(int k) {
        all_apply(2*k, lz[k]);
        all_apply(2*k+1, lz[k]);
        lz[k] = id();
    }

    void set(int p, S x) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);

        d[p] = x;

        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r-1) >> i);
        }

        S sml = e(), smr = e();

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    void apply(int l, int r, F f) {
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r-1) >> i);
        }

        int l2 = l, r2 = r;

        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }

        for (int i = 1; i <= log; i++) {
            if (((l2 >> i) << i) != l2) update(l2 >> i);
            if (((r2 >> i) << i) != r2) update((r2-1) >> i);
        }
    }

    S all_prod() {
        return d[1];
    }
};


struct S{
    long long sum;
    int size;
};
using F = long long;
S op(S a, S b){
    return {
        a.sum + b.sum,
        a.size + b.size
    };
}
S e(){
    return {0,0};
}
S mapping(F f, S x){
    return {
        x.sum + f * x.size,
        x.size
    };
}
F composition(F f, F g){
    return f + g;
}
F id(){
    return 0;
}

int main(){

    int n = 5;
    vector<S> v(n);

    for(int i=0;i<n;i++)
        v[i] = {i+1,1};

    LazySegTree<S,F,op,e,mapping,composition,id> seg(v);

    cout << seg.prod(0,5).sum << endl;

    seg.apply(1,4,10);

    cout << seg.prod(0,5).sum << endl;

}