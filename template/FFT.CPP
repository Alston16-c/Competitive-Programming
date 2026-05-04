#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    static vector<int> rev;
    static vector<cd> roots{ {0,0}, {1,0} };

    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (k-1));
    }

    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            double ang = 2 * PI / (1 << (k+1));
            for (int i = 1 << (k-1); i < (1 << k); i++) {
                roots[2*i] = roots[i];
                double a = ang * (2*i + 1 - (1 << k));
                roots[2*i + 1] = cd(cos(a), sin(a));
            }
            k++;
        }
    }

    for (int i = 0; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += 2*len)
            for (int j = 0; j < len; j++) {
                cd u = a[i+j];
                cd v = a[i+j+len] * roots[len+j];
                a[i+j] = u + v;
                a[i+j+len] = u - v;
            }

    if (inv) {
        reverse(a.begin() + 1, a.end());
        for (cd &x : a) x /= n;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> res(n);
    for (int i = 0; i < n; i++)
        res[i] = (int)round(fa[i].real());

    res.resize(a.size() + b.size() - 1);
    return res;
}

void solve(){
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5};
    
    auto c1 = multiply(a,b);

    for(int x:c1) cout << x << ' ';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	//cin >> t;
	while(t--) solve();
}