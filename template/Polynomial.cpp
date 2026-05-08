#pragma once
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353; // typical NTT prime
const int G = 3;           // primitive root for NTT

//================ Basic Mod Arithmetic =================
int add(int a,int b){a+=b;return a>=MOD?a-MOD:a;}
int sub(int a,int b){a-=b;return a<0?a+MOD:a;}
int mul(long long a,long long b){return a*b%MOD;}
int modpow(int a,int e){
    int r=1;while(e){if(e&1) r=mul(r,a); a=mul(a,a); e>>=1;}return r;
}
int modinv(int a){return modpow(a,MOD-2);}

//================== NTT =====================
void ntt(vector<int>& a,bool invert){
    int n=a.size();
    vector<int> rev(n,0);
    for(int i=0;i<n;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int len=1;len<n;len<<=1){
        int wlen=modpow(G,(MOD-1)/(len*2));
        if(invert) wlen=modinv(wlen);
        for(int i=0;i<n;i+=2*len){
            int w=1;
            for(int j=0;j<len;j++){
                int u=a[i+j],v=mul(a[i+j+len],w);
                a[i+j]=add(u,v);
                a[i+j+len]=sub(u,v);
                w=mul(w,wlen);
            }
        }
    }
    if(invert){
        int inv=modinv(n);
        for(int &x:a) x=mul(x,inv);
    }
}
vector<int> multiply(vector<int> a, vector<int> b){
    int n=1; while(n<a.size()+b.size()) n<<=1;
    a.resize(n); b.resize(n);
    ntt(a,false); ntt(b,false);
    for(int i=0;i<n;i++) a[i]=mul(a[i],b[i]);
    ntt(a,true);
    return a;
}

//================== Polynomial Inverse =================
vector<int> poly_inverse(const vector<int>& p,int n){
    vector<int> f(1,modinv(p[0]));
    int m=1;
    while(m<=n){
        m<<=1;
        vector<int> pcut(min((int)p.size(),m));
        for(int i=0;i<pcut.size();i++) pcut[i]=p[i];
        vector<int> g=multiply(multiply(f,f),pcut);
        f.resize(m);
        for(int i=0;i<m;i++) f[i]=sub(add(f[i],f[i]),i<g.size()?g[i]:0);
    }
    f.resize(n+1); return f;
}

//================== Polynomial Derivative =================
vector<int> derivative(const vector<int>& a){
    int n=a.size();
    vector<int> res(n-1,0);
    for(int i=1;i<n;i++) res[i-1]=mul(a[i],i);
    return res;
}

//================== Polynomial Integral =================
vector<int> integral(const vector<int>& a){
    int n=a.size();
    vector<int> res(n+1,0);
    for(int i=0;i<n;i++) res[i+1]=mul(a[i],modinv(i+1));
    return res;
}

//================== Polynomial Log =================
vector<int> poly_log(const vector<int>& a,int n){
    vector<int> da=derivative(a);
    vector<int> inva=poly_inverse(a,n);
    vector<int> res=multiply(da,inva);
    res.resize(n);
    return integral(res);
}

//================== Polynomial Exp =================
vector<int> poly_exp(const vector<int>& a,int n){
    vector<int> f(1,1);
    int m=1;
    while(m<=n){
        m<<=1;
        vector<int> fcut=f;
        fcut.resize(m);
        vector<int> ln_f=poly_log(fcut,m);
        for(int i=0;i<m;i++) ln_f[i]=sub(i<a.size()?a[i]:0,ln_f[i]);
        ln_f[0]=add(ln_f[0],1);
        f=multiply(f,ln_f);
        f.resize(m);
    }
    f.resize(n+1); return f;
}

//================== Polynomial Power =================
vector<int> poly_pow(const vector<int>& a,long long k,int n){
    vector<int> ln_a=poly_log(a,n);
    for(int i=0;i<=n;i++) ln_a[i]=mul(ln_a[i],k);
    return poly_exp(ln_a,n);
}

//================== Polynomial Sqrt (Newton) =================
vector<int> poly_sqrt(const vector<int>& a,int n){
    vector<int> f(1,1);
    int m=1;
    while(m<=n){
        m<<=1;
        vector<int> fcut=f;
        fcut.resize(m);
        vector<int> invf=poly_inverse(fcut,m);
        vector<int> res=multiply(fcut,a);
        for(int i=0;i<m;i++) res[i]=mul(add(res[i],fcut[i]),modinv(2));
        f=res;
    }
    f.resize(n+1); return f;
}

//================== Kitamasa (linear recurrence) =================
int kitamasa(const vector<int>& init,const vector<int>& C,long long n){
    int k=C.size();
    vector<int> res(k,0); res[0]=1;
    vector<int> base(k,0); if(k>1) base[1]=1;
    auto mulMod=[&](vector<int> a, vector<int> b) {
        vector<long long> tmp(2*k);
        for(int i = 0; i < k; i++)
            for(int j = 0; j < k; j++)
                tmp[i+j] += 1LL * a[i] * b[j];
                
        for(int i = 2*k-1; i >= k; i--)
            for(int j = 1; j <= k; j++)
                tmp[i-j] += tmp[i] * C[j-1];
    
        vector<int> res(k); 
        for(int i = 0; i < k; i++)res[i] = tmp[i] % MOD;
        return res;
    };
    while(n>0){
        if(n&1) res=mulMod(res,base);
        base=mulMod(base,base);
        n>>=1;
    }
    int ans=0;
    for(int i=0;i<k;i++) ans=(ans+1LL*res[i]*init[i])%MOD;
    return ans;
}

//================== Bostan–Mori (rational GF) =================
int bostan_mori(vector<int> P,vector<int> Q,long long n){
    while(n>0){
        vector<int> Qneg=Q;
        for(int i=1;i<Qneg.size();i+=2) Qneg[i]=(MOD-Qneg[i])%MOD;
        auto R=multiply(P,Qneg);
        auto S=multiply(Q,Qneg);
        vector<int> P_new,S_new;
        for(int i=n%2;i<R.size();i+=2) P_new.push_back(R[i]);
        for(int i=0;i<S.size();i+=2) S_new.push_back(S[i]);
        P=P_new; Q=S_new;
        n/=2;
    }
    return P[0];
}

//================== Berlekamp Massey =================
vector<ll> berlekamp_massey(const vector<ll>& s) {
    vector<ll> C = {1}, B = {1};
    int L = 0, m = 1;
    ll b = 1;

    for (int n = 0; n < (int)s.size(); n++) {
        ll d = 0;
        for (int i = 0; i <= L; i++)
            d = (d + C[i] * s[n - i]) % MOD;

        if (d == 0) {
            m++;
        } else {
            vector<ll> T = C;
            ll coef = d * modpow(b, MOD - 2) % MOD;

            if ((int)C.size() < (int)B.size() + m)
                C.resize(B.size() + m, 0);

            for (int i = 0; i < (int)B.size(); i++)
                C[i + m] = (C[i + m] - coef * B[i]) % MOD;

            if (2 * L > n) {
                m++;
            } else {
                B = T;
                b = d;
                L = n + 1 - L;
                m = 1;
            }
        }
    }

    C.erase(C.begin());
    for (ll& x : C) x = (MOD - x) % MOD;
    return C;
}